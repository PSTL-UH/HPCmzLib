#include "bits/stdc++.h"

#include "MsDataFile.h"
#include "SourceFile.h"
#include "MsDataScan.h"
#include "IFilteringParams.h"
#include "MzSpectra/MzPeak.h"
#include "../Chemistry/ClassExtensions.h"
#include "FilteringParams.h"
#include "DeconvolutionFeatureWithMassesAndScans.h"
#include "MzSpectra/IsotopicEnvelope.h"

#include "Sort.h"

using namespace MzLibUtil;

namespace MassSpectrometry
{
    
    MsDataFile::MsDataFile(int numSpectra, MassSpectrometry::SourceFile *sourceFile)
    {
        Scans = std::vector<MsDataScan*>(numSpectra);
        privateSourceFile = sourceFile;
    }
    
    MsDataFile::MsDataFile(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile)
    {
        Scans = scans;
        privateSourceFile = sourceFile;
    }
    
    MassSpectrometry::SourceFile *MsDataFile::getSourceFile() const
    {
        return privateSourceFile;
    }
    
    int MsDataFile::getNumSpectra() const
    {
        return Scans.size();
    }
    
    std::vector<MsDataScan*> MsDataFile::GetAllScansList()
    {
        return Scans;
    }
    
    int MsDataFile::TopNpeakHelper(std::vector<double> &intensities, std::vector<double> &mArray, IFilteringParams *filteringParams)
    {
        // IComparer<double> *c = new ReverseComparer();
        // Array::Sort(intensities, mArray, c);
        // Explanation for the previous sort from C# doc:
        //    Sort(Array, Array, IComparer) 	
        //    Sorts a pair of one-dimensional Array objects (one contains the keys and
        //    the other contains the corresponding items) based on the keys in the first
        //    Array using the specified IComparer.
        // For the C++ version, I replace it by a bubble-sort for the moment.
        int numPeaks = intensities.size();
        Sort::SortPairs ( intensities, mArray, numPeaks );
        
        if (filteringParams->getMinimumAllowedIntensityRatioToBasePeakM().has_value())
        {
            double minIntensity = filteringParams->getMinimumAllowedIntensityRatioToBasePeakM().value() * intensities[0];
#ifdef ORIG
            numPeaks = std::min(intensities.Count([&] (std::any b)
            {
                //C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c
                //was passed to a method or constructor. Handle memory management manually.
                return b >= minIntensity;
            }), numPeaks);
#endif
            int num=0;
            std::for_each ( intensities.begin(), intensities.end(), [&] ( double &b ) {
                    if (b >= minIntensity ){
                        num++;
                    }
                });
            numPeaks = std::min ( num, numPeaks);
        }
        
        if (filteringParams->getNumberOfPeaksToKeepPerWindow().has_value())
        {
            numPeaks = std::min(filteringParams->getNumberOfPeaksToKeepPerWindow().value(),
                                numPeaks);
        }
        
        // C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c
        // was passed to a method or constructor. Handle memory management manually.
        return numPeaks;
    }
    
    void MsDataFile::WindowModeHelper(std::vector<double> &intensities, std::vector<double> &mArray, IFilteringParams *filteringParams, double scanRangeMinMz, double scanRangeMaxMz, std::optional<double> WindowMaxNormalizationToValue)
    {
        //Array::Sort(mArray, intensities);
        Sort::SortPairs ( mArray, intensities, mArray.size() );
        constexpr double shiftToMakeRangeInclusive = 0.000000001;
        std::vector<MzPeak*> mzIntensites;
        std::vector<MzPeak*> mzIntensites_reduced;
        int numberOfWindows = 1;
        if (filteringParams->getNumberOfWindows().has_value())
        {
            numberOfWindows = filteringParams->getNumberOfWindows().value();
        }
        
        // make MzPeaks of each mz/intensity pair and create a list of pairs for everything with
        // intensity above the minimum cutoff
        // double maximumIntensityInArray = intensities.Max();
        double maximumIntensityInArray = 0;
        std::for_each ( intensities.begin(), intensities.end(), [&] (double &i){
                if ( i> maximumIntensityInArray )
                    maximumIntensityInArray = i;
            });
        
        for (unsigned long int i = 0; i < mArray.size(); i++)
        {
            if ((!filteringParams->getMinimumAllowedIntensityRatioToBasePeakM().has_value()) ||
                (intensities[i] > (maximumIntensityInArray * filteringParams->getMinimumAllowedIntensityRatioToBasePeakM().value())))
            {
                MzPeak *tempVar = new MzPeak(mArray[i], intensities[i]);
                mzIntensites.push_back(tempVar);
            }
        }
        
        double mzRangeInOneWindow = scanRangeMaxMz - scanRangeMinMz;
        Chemistry::ClassExtensions::TupleList<double, double> *ranges = new Chemistry::ClassExtensions::TupleList<double, double>();
        
        double scanMin = scanRangeMinMz;
        if (filteringParams->getNumberOfWindows().has_value() &&
            filteringParams->getNumberOfWindows().value() > 0)
        {
            mzRangeInOneWindow = mzRangeInOneWindow / filteringParams->getNumberOfWindows().value();
            
            for (int i = 1; i <= numberOfWindows; i++)
            {
                if (i == 1) // first
                {
                    ranges->push_back(std::make_tuple(scanMin-shiftToMakeRangeInclusive, (scanMin + mzRangeInOneWindow)));
                }
                else if (i == (numberOfWindows)) //last
                {
                    ranges->push_back(std::make_tuple(scanMin, (scanMin + mzRangeInOneWindow) + shiftToMakeRangeInclusive));
                }
                else //middle
                {
                    ranges->push_back(std::make_tuple(scanMin, (scanMin + mzRangeInOneWindow)));
                }
                scanMin += mzRangeInOneWindow;
            }
        }
        else
        {
            ranges->push_back(std::make_tuple(scanRangeMinMz - shiftToMakeRangeInclusive, scanRangeMaxMz + shiftToMakeRangeInclusive));
        }
        
        for (auto range : *ranges)
        {
            std::vector<MzPeak*> handyLittleListofMzPeaksThatIsOnlyNeededTemporarily;
            for (auto mzIntensityPair : mzIntensites)
            {
                if (mzIntensityPair->getMz() > std::get<0>(range) &&
                    mzIntensityPair->getMz() <= std::get<1>(range))
                {
                    handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.push_back(mzIntensityPair);
                }
            }
            if (handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.size() > 0)
            {
                // C# TO C++ CONVERTER TODO TASK: The 'Compare' parameter of std::sort produces a boolean
                // value, while the .NET Comparison parameter produces a tri-state result:
                // ORIGINAL LINE:
                // handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.Sort((x, y)
                // => y.Intensity.CompareTo(x.Intensity));
                std::sort(handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.begin(),
                          handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.end(), [&] (MzPeak *xp, MzPeak* yp)
                          {
                              double x = xp->getIntensity();
                              double y = yp->getIntensity();
                              return (x > y);
                          }); //sort tuple in place decending by item 2, reverse by changing x and y
                
#ifdef ORIG
                double maxIntensity = handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.Max([&] (std::any x)
                                                                                              {
                                                                                                  x::Intensity;
                                                                                              });
#endif
                double maxIntensity=0;
                std::for_each ( handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.begin(),
                                handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.end(), [&] (MzPeak *i){
                                    if ( i->getIntensity() > maxIntensity )
                                        maxIntensity = i->getIntensity();
                });
                
                int countOfPeaksToKeep = handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.size();
                if (filteringParams->getNumberOfPeaksToKeepPerWindow().has_value())
                {
                    int size = handyLittleListofMzPeaksThatIsOnlyNeededTemporarily.size();
                    int filterparam = filteringParams->getNumberOfPeaksToKeepPerWindow().value();
                    countOfPeaksToKeep = std::min(size , filterparam);
                }
                for (int i = 0; i < countOfPeaksToKeep; i++)
                {
                    if (WindowMaxNormalizationToValue.has_value())
                    {
                        double normalizedIntensity = handyLittleListofMzPeaksThatIsOnlyNeededTemporarily[i]->getIntensity() / maxIntensity * WindowMaxNormalizationToValue.value();
                        MzPeak tempVar2(handyLittleListofMzPeaksThatIsOnlyNeededTemporarily[i]->getMz(),
                                        normalizedIntensity);
                        mzIntensites_reduced.push_back(&tempVar2);
                    }
                    else
                    {
                        mzIntensites_reduced.push_back(handyLittleListofMzPeaksThatIsOnlyNeededTemporarily[i]);
                    }
                }
            }
        }
        
        // convert merged results to array and sort by m/z
        //C# TO C++ CONVERTER TODO TASK: The 'Compare' parameter of std::sort produces a boolean value,
        // while the .NET Comparison parameter produces a tri-state result:
        //ORIGINAL LINE: mzIntensites_reduced.Sort((x, y) => x.Mz.CompareTo(y.Mz));
        std::sort(mzIntensites_reduced.begin(), mzIntensites_reduced.end(), [&] (MzPeak *xp, MzPeak *yp) {
                double x = xp->getMz();
                double y = yp->getMz();
                return (x > y);
        });
#ifdef ORIG
        mArray = mzIntensites_reduced.Select([&] (std::any i)
                                             {
                                                 i::Mz;
                                             })->ToArray();
#endif
        mArray.clear();
        std::for_each ( mzIntensites_reduced.begin(), mzIntensites_reduced.end(), [&] (MzPeak *m) {
                mArray.push_back(m->getMz());
            });
#ifdef ORIG
        intensities = mzIntensites_reduced.Select([&] (std::any i)
                                                  {
                                                      i::Intensity;
                                                  })->ToArray();
#endif
        intensities.clear();
        std::for_each ( mzIntensites_reduced.begin(), mzIntensites_reduced.end(), [&] (MzPeak *m) {
                intensities.push_back(m->getIntensity());
            });
        
        delete ranges;
    }
    
    void MsDataFile::XCorrPrePreprocessing(std::vector<double> &intensities, std::vector<double> &mArray,
                                           double scanRangeMinMz, double scanRangeMaxMz, double precursorMz,
                                           double precursorDiscardRange, double discreteMassBin,
                                           double percentMaxThreshold)
    {
        //The discrete bin value 1.0005079 was from J. Proteome Res., 2018, 17 (11), pp 3644–3656
        //Array::Sort(mArray, intensities);
        Sort::SortPairs (mArray, intensities, mArray.size());
        int numberOfWindows = static_cast<int>(std::round((scanRangeMaxMz - scanRangeMinMz + discreteMassBin) / discreteMassBin * std::pow(10, 0))) / std::pow(10, 0);
        
        FilteringParams *firstFilter = new FilteringParams(std::make_optional<int>(1),
                                                           std::make_optional<double>(percentMaxThreshold / 100),
                                                           std::optional<double>(numberOfWindows), false, false);
        
        for (long unsigned int i = 0; i < mArray.size(); i++)
        {
            if (std::abs(intensities[i]) > 0.000001) //some small number
            {
                intensities[i] = std::sqrt(intensities[i]);
            }
        }
        
        //set intensity of precursor ions to zero
        for (long unsigned int i = 0; i < mArray.size(); i++)
        {
            if (mArray[i] > (precursorMz - precursorDiscardRange) && mArray[i] < (precursorMz + precursorDiscardRange))
            {
                intensities[i] = 0;
            }
        }
        
        // We filter twice below: the second filter, which is 10 windows with 10 peaks, you
        // could end up with 10 peaks that are not all separated minimally by 1.0005079 daltons.T
        // The first pass gets one peak(maximally) at every dalton and the second pass keeps up to
        // 10 of those in each of the 10 windows.
        
        //filter peaks into discrete mass bins. makes one bin for every single integer m/z.
        double minMz = scanRangeMinMz - discreteMassBin / 2;
        double maxMz = scanRangeMaxMz + discreteMassBin / 2;
        
        MsDataFile::WindowModeHelper(intensities, mArray, firstFilter, minMz, maxMz);
        
        //normalize intensity in segments to max 50 intensity keeping only 10 peaks per window.
        FilteringParams *secondFilter = new FilteringParams(std::make_optional(static_cast<int>(std::ceil(numberOfWindows / 10))), std::nullopt, std::make_optional(10), false, false);
        
        MsDataFile::WindowModeHelper(intensities, mArray, secondFilter, minMz, maxMz, std::make_optional(50));
        
        for (long unsigned int i = 0; i < mArray.size(); i++)
        {
            mArray[i] = std::round(mArray[i] / discreteMassBin * std::pow(10, 0)) / std::pow(10, 0) * discreteMassBin;
        }
        
        //fill in missing mz values in array with zero intensity
        std::vector<double> allPossibleMzValues;
        double start = std::round(scanRangeMinMz / discreteMassBin * std::pow(10, 0)) / std::pow(10, 0) * discreteMassBin;
        //don't use minMz here, that would be WRONG

        while (start < (maxMz))
        {
            allPossibleMzValues.push_back(start);
            start += discreteMassBin;
        }
        
        //remove any that are already in the mArray
        for (auto remainingMzValue : mArray)
        {
            int i=0;
            std::for_each (allPossibleMzValues.begin(), allPossibleMzValues.begin(),[&] (double x) {
                    // C# TO C++ CONVERTER TODO TASK: A 'delete secondFilter' statement was not
                    // added since secondFilter was passed to a method or constructor. Handle memory
                    // management manually.
                    //C# TO C++ CONVERTER TODO TASK: A 'delete firstFilter' statement was not added
                    // since firstFilter was passed to a method or constructor. Handle memory management manually.
                    if ( x > (remainingMzValue - discreteMassBin / 2) &&
                         x < (remainingMzValue + discreteMassBin / 2)) {
                        allPossibleMzValues.erase(allPossibleMzValues.begin() + i);
                    }
                    i++;
           });
        }

        std::vector<double> zeroArray(allPossibleMzValues.size());
        for (long unsigned int i = 0; i < zeroArray.size(); i++)
        {
            zeroArray[i] = 0;
        }
        
        int original_mArray_count = mArray.size();
#ifdef ORIG
        // C# interface:
        // public static void Copy (Array sourceArray, int sourceIndex,
        //          Array destinationArray, int destinationIndex, int length);
        // C++ interface:
        // std::copy(InputIt first, InputIt last, OutputIt d_first );
        
        Array::Resize<double>(mArray, mArray.size() + allPossibleMzValues.size());
        Array::Copy(allPossibleMzValues.ToArray(), 0, mArray, original_mArray_count, allPossibleMzValues.size());
        
        Array::Resize<double>(intensities, intensities.size() + zeroArray.size());
        Array::Copy(zeroArray.ToArray(), 0, intensities, original_mArray_count, zeroArray.size());
#endif
        mArray.resize(mArray.size() + allPossibleMzValues.size());
        std::copy(allPossibleMzValues.begin(), allPossibleMzValues.end(), mArray.begin()+original_mArray_count );
        
        intensities.resize(intensities.size() + zeroArray.size());
        std::copy (zeroArray.begin(), zeroArray.end(), intensities.begin() + original_mArray_count);
        
        //Array::Sort(mArray, intensities);
        Sort::SortPairs ( mArray, intensities, mArray.size() );
        
        //Scale the intensities
        
        constexpr int rangeEnd = 75; //from J. Proteome Res., 2018, 17 (11), pp 3644–3656
        
        std::vector<double> scaledIntensities(intensities.size());
        for ( int i = 0; i < (int)intensities.size(); i++)
        {
            double scaleValue = 0;
            
            int low = std::max(0, i - rangeEnd);
            int high = std::min((int)intensities.size() - 1, (int)(i + rangeEnd));
            int denominator = high - low + 1;
            
            for (int j = low; j <= high; j++)
            {
                scaleValue += intensities[j];
            }
            scaledIntensities[i] = std::max((double)0.0, intensities[i] - 1 / (denominator) * scaleValue);
        }
        intensities = scaledIntensities;
        
        // C# TO C++ CONVERTER TODO TASK: A 'delete secondFilter' statement was not added since
        // secondFilter was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete firstFilter' statement was not added since
        // firstFilter was passed to a method or constructor. Handle memory management manually.
    }
    
    std::vector<MsDataScan*> MsDataFile::GetMS1Scans()
    {
        std::vector<MsDataScan*> v;
        for (int i = 1; i <= getNumSpectra(); i++)
        {
            auto scan = GetOneBasedScan(i);
            if (scan->getMsnOrder() == 1)
            {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent
                // to the C# 'yield' keyword:
                //yield return scan;
                v.push_back (scan);
            }
        }
        return v;
    }
    
    MsDataScan *MsDataFile::GetOneBasedScan(int scanNumber)
    {
        return Scans[scanNumber - 1];
    }
    
    std::vector<MsDataScan*> MsDataFile::GetMsScansInIndexRange(int FirstSpectrumNumber, int LastSpectrumNumber)
    {
        std::vector<MsDataScan*> v;
        for (int oneBasedSpectrumNumber = FirstSpectrumNumber; oneBasedSpectrumNumber <= LastSpectrumNumber;
             oneBasedSpectrumNumber++)
        {
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            //yield return GetOneBasedScan(oneBasedSpectrumNumber);
            v.push_back(GetOneBasedScan(oneBasedSpectrumNumber));
        }
        return v;
    }
    
    std::vector<MsDataScan*> MsDataFile::GetMsScansInTimeRange(double firstRT, double lastRT)
    {
        std::vector<MsDataScan*> v;
        int oneBasedSpectrumNumber = GetClosestOneBasedSpectrumNumber(firstRT);
        while (oneBasedSpectrumNumber <= getNumSpectra())
        {
            MsDataScan *scan = GetOneBasedScan(oneBasedSpectrumNumber);
            double rt = scan->getRetentionTime();
            if (rt < firstRT)
            {
                oneBasedSpectrumNumber++;
                continue;
            }
            if (rt > lastRT)
            {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield break;
                return v;
            }
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            //yield return scan;
            v.push_back(scan);
            oneBasedSpectrumNumber++;
        }
        return v;
    }
    
    int MsDataFile::GetClosestOneBasedSpectrumNumber(double retentionTime)
    {
        // TODO need to convert this to a binary search of some sort. Or if the data is
        // indexedMZML see if the indices work better.
        double bestDiff = std::numeric_limits<double>::max();
        for (int i = 0; i < getNumSpectra(); i++)
        {
            double diff = std::abs(GetOneBasedScan(i + 1)->getRetentionTime() - retentionTime);
            if (diff > bestDiff)
            {
                return i;
            }
            bestDiff = diff;
        }
        return getNumSpectra();
    }
    
#ifdef ORIG
    // EG: removed this function from the C++ version.
    IEnumerator<MsDataScan*> *MsDataFile::GetEnumerator()
    {
        return GetMsScansInIndexRange(1, getNumSpectra()).begin();
    }
#endif
    
    std::vector<DeconvolutionFeatureWithMassesAndScans*> MsDataFile::Deconvolute(std::optional<int> &minScan,
                                                                                 std::optional<int> &maxScan,
                                                                                 int minAssumedChargeState,
                                                                                 int maxAssumedChargeState,
                                                                                 double deconvolutionTolerancePpm,
                                                                                 double intensityRatioLimit,
                                                                                 double aggregationTolerancePpm,
                                                                                 std::function<bool(MsDataScan*)> scanFilterFunc,
                                                                                 int maxThreads)
    {
        std::vector<DeconvolutionFeatureWithMassesAndScans*> v;
        
        minScan = std::make_optional(minScan.has_value() ? minScan.value() : 1);
        maxScan = std::make_optional(maxScan.has_value() ? maxScan.value() : getNumSpectra());
        
        auto allAggregateGroups = std::vector<std::vector<IsotopicEnvelope*>>(maxScan.value() - minScan.value() + 1);
#ifdef ORIG        
        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = maxThreads;
        
        Parallel::ForEach(Partitioner::Create(minScan.value(), maxScan.value() + 1), tempVar, [&] (std::any fff){
                for (int scanIndex = fff::Item1; scanIndex < fff::Item2; scanIndex++) {
                }});
#endif 
        for ( int scanIndex = minScan.value(); scanIndex < maxScan.value()+1; scanIndex++)  {
            auto theScan = GetOneBasedScan(scanIndex);
            if (scanFilterFunc(theScan))   {
                MzRange tempVar2(0, std::numeric_limits<double>::infinity());
                allAggregateGroups[scanIndex - minScan.value()] = theScan->getMassSpectrum()->Deconvolute(&tempVar2,
                                                                                                          minAssumedChargeState,
                                                                                                          maxAssumedChargeState,
                                                                                                          deconvolutionTolerancePpm,
                                                                                                          intensityRatioLimit);//.ToList();
            }
        }
        
        std::vector<DeconvolutionFeatureWithMassesAndScans*> currentListOfGroups;
        for (int scanIndex = minScan.value(); scanIndex <= maxScan.value(); scanIndex++)  {
            if (allAggregateGroups[scanIndex - minScan.value()].empty()) {
                continue;
            }
            for (auto isotopicEnvelope : allAggregateGroups[scanIndex - minScan.value()])  {
                DeconvolutionFeatureWithMassesAndScans *matchingGroup = nullptr;
                auto mass = isotopicEnvelope->monoisotopicMass;
                for (auto possibleGroup : currentListOfGroups) {
                    auto possibleGroupMass = possibleGroup->getMass();
                    if (std::abs(mass - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm               ||
                        std::abs(mass + 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm ||
                        std::abs(mass + 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm ||
                        std::abs(mass + 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm ||
                        std::abs(mass - 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm ||
                        std::abs(mass - 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm ||
                        std::abs(mass - 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm)  {
                        matchingGroup = possibleGroup;
                        matchingGroup->AddEnvelope(isotopicEnvelope, scanIndex, GetOneBasedScan(scanIndex)->getRetentionTime());
                        break;
                    }
                }
                
                if (matchingGroup == nullptr)  {
                    auto newGroupScans = new DeconvolutionFeatureWithMassesAndScans();
                    newGroupScans->AddEnvelope(isotopicEnvelope, scanIndex, GetOneBasedScan(scanIndex)->getRetentionTime());
                    currentListOfGroups.push_back(newGroupScans);
                    
                    //C# TO C++ CONVERTER TODO TASK: A 'delete newGroupScans' statement was not added 
                    // since newGroupScans was passed to a method or constructor. Handle memory
                    // management manually.
                }
            }
#ifdef ORIG
            for (auto ok : currentListOfGroups.Where([&] (std::any b) {
                        // C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since
                        // tempVar was passed to a method or constructor. Handle memory management manually.
                        return b::MaxScanIndex < scanIndex;
                    }))
                currentListOfGroups.RemoveAll([&] (std::any b) {
                        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since
                        // tempVar was passed to a method or constructor. Handle memory management manually.
                        return b::MaxScanIndex < scanIndex;
                    });
        
#endif
            std::vector<MassSpectrometry::DeconvolutionFeatureWithMassesAndScans*>::const_iterator ok;
            for ( ok = currentListOfGroups.begin(); ok != currentListOfGroups.end(); ++ok )  {     
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return ok;
                auto okk = *ok;
                if (okk->getMaxScanIndex() < scanIndex ) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    //yield return ok;
                    v.push_back (okk);
                    currentListOfGroups.erase (ok);
                }   
            }
            for (auto ok : currentListOfGroups) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return ok;
                v.push_back(ok);
            }
        }
        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since
        //tempVar was passed to a method or constructor. Handle memory management manually.
        return v;
    }

#ifdef NOT_USED
    int MsDataFile::ReverseComparer::Compare (double x, double y){
        int val=0;
        if ( y > x ) {
            val = -1;
        }
        else if ( y < x ) {
            val = 1;
        }
        return val;   
    }
#endif
}
