#include "TestMzML.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "FakeMsDataFile.h"
#include "../MassSpectrometry/FilteringParams.h"

#ifdef ORIG
#include "../MzIdentML/mzIdentML111.Generated.MzIdentMLType111.h"
#include "../MzIdentML/mzIdentML111.Generated.DataCollectionType.h"
#include "../MzIdentML/mzIdentML111.Generated.AnalysisDataType.h"
#include "../MzIdentML/mzIdentML111.Generated.SpectrumIdentificationListType.h"
#include "../MzIdentML/mzIdentML111.Generated.SpectrumIdentificationResultType.h"
#include "../MzIdentML/mzIdentML111.Generated.SpectrumIdentificationItemType.h"
#include "../MzIdentML/mzIdentML111.Generated.CVParamType.h"
#include "../MzIdentML/mzIdentML111.Generated.IonTypeType.h"
#include "../MzIdentML/mzIdentML111.Generated.FragmentArrayType.h"
#include "../MzIdentML/mzIdentML111.Generated.PeptideEvidenceRefType.h"
#include "../MzIdentML/mzIdentML111.Generated.InputsType.h"
#include "../MzIdentML/mzIdentML111.Generated.SpectraDataType.h"
#include "../MzIdentML/mzIdentML111.Generated.FileFormatType.h"
#include "../MzIdentML/mzIdentML111.Generated.SequenceCollectionType.h"
#include "../MzIdentML/mzIdentML111.Generated.PeptideEvidenceType.h"
#include "../MzIdentML/mzIdentML111.Generated.PeptideType.h"
#include "../MzIdentML/mzIdentML111.Generated.ModificationType.h"
#include "../MzIdentML/mzIdentML111.Generated.DBSequenceType.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../MzIdentML/mzIdentML111.Generated.AnalysisProtocolCollectionType.h"
#include "../MzIdentML/mzIdentML111.Generated.SpectrumIdentificationProtocolType.h"
#include "../MzIdentML/MzidIdentifications.h"
#include "../MzIdentML/mzIdentML120.Generated.MzIdentMLType120.h"
#include "../MzIdentML/mzIdentML120.Generated.DataCollectionType.h"
#include "../MzIdentML/mzIdentML120.Generated.AnalysisDataType.h"
#include "../MzIdentML/mzIdentML120.Generated.SpectrumIdentificationListType.h"
#include "../MzIdentML/mzIdentML120.Generated.SpectrumIdentificationResultType.h"
#include "../MzIdentML/mzIdentML120.Generated.SpectrumIdentificationItemType.h"
#include "../MzIdentML/mzIdentML120.Generated.CVParamType.h"
#include "../MzIdentML/mzIdentML120.Generated.IonTypeType.h"
#include "../MzIdentML/mzIdentML120.Generated.FragmentArrayType.h"
#include "../MzIdentML/mzIdentML120.Generated.PeptideEvidenceRefType.h"
#include "../MzIdentML/mzIdentML120.Generated.InputsType.h"
#include "../MzIdentML/mzIdentML120.Generated.SpectraDataType.h"
#include "../MzIdentML/mzIdentML120.Generated.FileFormatType.h"
#include "../MzIdentML/mzIdentML120.Generated.SequenceCollectionType.h"
#include "../MzIdentML/mzIdentML120.Generated.PeptideEvidenceType.h"
#include "../MzIdentML/mzIdentML120.Generated.PeptideType.h"
#include "../MzIdentML/mzIdentML120.Generated.ModificationType.h"
#include "../MzIdentML/mzIdentML120.Generated.DBSequenceType.h"
#include "../MzIdentML/mzIdentML120.Generated.AnalysisProtocolCollectionType.h"
#include "../MzIdentML/mzIdentML120.Generated.SpectrumIdentificationProtocolType.h"
#endif

#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Chemistry/ChemicalFormula.h"

#ifdef ORIG
#include "../MzIdentML/mzIdentML110.Generated.MzIdentMLType110.h"
#include "../MzIdentML/mzIdentML110.Generated.DataCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.AnalysisDataType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationListType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationResultType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationItemType.h"
#include "../MzIdentML/mzIdentML110.Generated.CVParamType.h"
#include "../MzIdentML/mzIdentML110.Generated.IonTypeType.h"
#include "../MzIdentML/mzIdentML110.Generated.FragmentArrayType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideEvidenceRefType.h"
#include "../MzIdentML/mzIdentML110.Generated.InputsType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectraDataType.h"
#include "../MzIdentML/mzIdentML110.Generated.FileFormatType.h"
#include "../MzIdentML/mzIdentML110.Generated.SequenceCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideEvidenceType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideType.h"
#include "../MzIdentML/mzIdentML110.Generated.ModificationType.h"
#include "../MzIdentML/mzIdentML110.Generated.DBSequenceType.h"
#include "../MzIdentML/mzIdentML110.Generated.AnalysisProtocolCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationProtocolType.h"
#endif

#include "../Chemistry/IsotopicDistribution.h"

#include <experimental/filesystem>
#include "Assert.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <../include/Sort.h>
#include <math.h>

//need to include .h files
using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
// using namespace MzIdentML;
using namespace MzLibUtil;
// using namespace NUnit::Framework;
using namespace Proteomics::AminoAcidPolymer;
// namespace Stopwatch = System::Diagnostics::Stopwatch;

int main ( int argc, char **argv )
{
    srand (time(NULL));
    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

    std::cout << ++i << ". AnotherMzMLtest" << std::endl;
    Test::TestMzML::AnotherMzMLtest();

#ifdef THROWS_EXCEPTION
    std::cout << ++i << ". LoadBadMzml" << std::endl;
    Test::TestMzML::LoadBadMzml();
#endif

    std::cout << ++i << ". TestPeakTrimmingWithOneWindow" << std::endl;
    Test::TestMzML::TestPeakTrimmingWithOneWindow();

    std::cout << ++i << ". TestPeakTrimmingWithTooManyWindows" << std::endl;
    Test::TestMzML::TestPeakTrimmingWithTooManyWindows();

    std::cout << ++i << ". WriteEmptyScan" << std::endl;
    Test::TestMzML::WriteEmptyScan();

    std::cout << ++i << ". DifferentAnalyzersTest" << std::endl;
    Test::TestMzML::DifferentAnalyzersTest();

#ifdef LATER
    std::cout << ++i << ". Mzid111Test" << std::endl;
    Test::TestMzML::Mzid111Test();

    std::cout << ++i << ". Mzid120Test" << std::endl;
    TestTestMzML::Mzid120Test();
#endif

#ifdef TESTING
    std::cout << ++i << ". LoadMzmlTest" << std::endl;
    Test::TestMzML::LoadMzmlTest();
#endif

#ifdef FIX_LATER
    std::cout << ++i << ". LoadMzmlFromConvertedMGFTest" << std::endl;
    Test::TestMzML::LoadMzmlFromConvertedMGFTest();
#endif

    std::cout << ++i << ". WriteMzmlTest" << std::endl;
    Test::TestMzML::WriteMzmlTest();

#ifdef LATER
    std::cout << ++i << ". MzidTest" << std::endl;
    Test::TestMzML::MzidTest();

    std::cout << ++i << ". Mzid110Test" << std::endl;
    Test::TestMzML::Mzid110Test();

    std::cout << ++i << ". Mzid111Test_" << std::endl;
    Test::TestMzML::Mzid111Test_();

    std::cout << ++i << ". Mzid120Test_" << std::endl;
    Test::TestMzML::Mzid120Test_();
#endif

    std::cout << ++i << ". MzmlFindPrecursorReferenceScan" << std::endl;
    Test::TestMzML::MzmlFindPrecursorReferenceScan();

    return 0;
}

namespace Test
{

    void TestMzML::AnotherMzMLtest()
    {
        std::vector<MsDataScan*> scans(4);

        std::vector<double> intensities1 = {1};
        std::vector<double> mz1 = {50};
        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        MzRange tempVar(1, 100);
        scans[0] = new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, &tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");

        //ms2
        std::vector<double> intensities2 = {1};
        std::vector<double> mz2 = {30};
        MzSpectrum *massSpec2 = new MzSpectrum(mz2, intensities2, false);
        MzRange tempVar2(1, 100);
        scans[1] = new MsDataScan(massSpec2, 2, 2, true, Polarity::Positive, 2, &tempVar2, "f", MZAnalyzerType::Orbitrap, massSpec2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(1), std::nullopt);

        std::vector<double> intensities3 = {1};
        std::vector<double> mz3 = {50};
        MzSpectrum *massSpec3 = new MzSpectrum(mz3, intensities3, false);
        MzRange tempVar3(1, 100);
        scans[2] = new MsDataScan(massSpec3, 3, 1, true, Polarity::Positive, 1, &tempVar3, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "3");

        //ms2
        std::vector<double> intensities4 = {1};
        std::vector<double> mz4 = {30};
        MzSpectrum *massSpec4 = new MzSpectrum(mz4, intensities4, false);
        MzRange tempVar4(1, 100);
        scans[3] = new MsDataScan(massSpec4, 4, 2, true, Polarity::Positive, 2, &tempVar4, "f", MZAnalyzerType::Orbitrap, massSpec2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "4", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(3), std::nullopt);

        FakeMsDataFile *f = new FakeMsDataFile(scans);

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, std::experimental::filesystem::current_path().string() + "/what.mzML", false);
    	Mzml *ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/what.mzML");

#ifdef ORIG
        auto scanWithPrecursor = ok->GetAllScansList().Last([&] (std::any b)){

// //C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
// //C# TO C++ CONVERTER TODO TASK: A 'delete massSpec4' statement was not added since massSpec4 was passed to a method or constructor. Handle memory management manually.
// //C# TO C++ CONVERTER TODO TASK: A 'delete massSpec3' statement was not added since massSpec3 was passed to a method or constructor. Handle memory management manually.
// //C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
// //C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
            return b::MsnOrder != 1;
        };
#endif

        std::vector<MsDataScan*> scansList = ok->GetAllScansList();
        MsDataScan *scanWithPrecursor;

        std::vector<MsDataScan*> filteredScansList;
        for (unsigned long int i=0; i<scansList.size(); i++){
            if (scansList[i]->getMsnOrder() != 1){
                filteredScansList.push_back(scansList[i]);
            }
        }
        scanWithPrecursor = filteredScansList.back();
        Assert::AreEqual(3, scanWithPrecursor->getOneBasedPrecursorScanNumber().value());

        std::string filePath = std::experimental::filesystem::current_path().string() + "/what.mzML";
        remove(filePath.c_str());

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec4' statement was not added since massSpec4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec3' statement was not added since massSpec3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
    }

#ifdef THROWS_EXCEPTION
    void TestMzML::LoadBadMzml()
    {
        // File::Delete(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "asdfasdfasdfasdfasdf.mzML")); // just to be sure
        std::string bad_mzml = std::experimental::filesystem::current_path().string() + "/asdfasdfasdfasdfasdf.mzML";
        remove(bad_mzml.c_str());

        Assert::Throws<FileNotFoundException*>([&] ()
        {
            // Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "asdfasdfasdfasdfasdf.mzML"));
           Mzml::LoadAllStaticData(bad_mzml); 
        });
    }
#endif

    void TestMzML::TestPeakTrimmingWithOneWindow()
    {
        // Nick: not sure why 100 arugment is used here
        // Random *rand = new Random(100);
        // srand (time(NULL));

        int numPeaks = 200;
        double minRatio = 0.01;
        int numWindows = 1;

        auto testFilteringParams = new FilteringParams(std::make_optional(numPeaks), std::make_optional(minRatio), std::make_optional(numWindows), true, true);
        
        // std::vector<(double mz, double intensity)*> myPeaks;
        std::vector<std::pair<double,double>> myPeaks;

        for (int mz = 400; mz < 1600; mz++)
        {
            // myPeaks.push_back((mz, rand->Next(1000, 1000000)));
            std::pair<double, double> v;
            v.first = mz;
            v.second = rand() % 1000000 + 1000;
            myPeaks.push_back(v);
        }

        //-------------------------------------------
        //find max intensity
    #ifdef ORIG
        double myMaxIntensity = myPeaks.Max([&] (std::any p)
        {
            p::intensity;
        });
    #endif

        using pair_type = decltype(myPeaks)::value_type;
        auto max = std::max_element(myPeaks.begin(), myPeaks.end(), [](const pair_type& p1, const pair_type& p2) {
            return p1.second < p2.second; 
        });
        double myMaxIntensity = max->second;
        //---------------------------------------------

        //----------------------------------------------
        //sort peaks by intensity in descending order
    #ifdef ORIG
        auto myPeaksOrderedByIntensity = myPeaks.OrderByDescending([&] (std::any p)
        {
            p::intensity;
        }).ToList();
        myPeaksOrderedByIntensity = myPeaksOrderedByIntensity.Take(numPeaks).ToList();
        myPeaksOrderedByIntensity = myPeaksOrderedByIntensity.Where([&] (std::any p)
        {
        delete testFilteringParams;
        delete rand;
            return (p::intensity / myMaxIntensity) > minRatio;
        }).ToList();
    #endif

        std::vector<std::pair<double,double>> myPeaksOrderedByIntensity;
        myPeaksOrderedByIntensity = myPeaks;

        //sort in descending order
        std::sort(myPeaksOrderedByIntensity.begin(), myPeaksOrderedByIntensity.end(), [](auto &left, auto &right) {
            return left.second > right.second;
        });

        //take first 'numPeaks' number of elements from beginning of sorted vector
        std::vector<std::pair<double, double>> top_intensity_peaks(&myPeaksOrderedByIntensity[0], &myPeaksOrderedByIntensity[numPeaks]);
        // myPeaksOrderedByIntensity = top_intensity_peaks;

        //filter peaks
        std::vector<std::pair<double,double>> filteredPeaks;
        for (long unsigned int i=0;i<top_intensity_peaks.size();i++){
            if ((top_intensity_peaks[i].second / myMaxIntensity) > minRatio){
                filteredPeaks.push_back(top_intensity_peaks[i]);
            }
        }
        // myPeaksOrderedByIntensity = filteredPeaks;
        //----------------------------------------------

        //-----------------------------------------------
        //sum of peak intensities
    #ifdef ORIG
        double sumOfAllIntensities = myPeaksOrderedByIntensity.Sum([&] (std::any p)
        {
            p::intensity;
        });
    #endif

        double sumOfAllIntensities = 0;
        for (long unsigned int i=0;i<filteredPeaks.size();i++){
            sumOfAllIntensities += filteredPeaks[i].second;
        }
        //----------------------------------------------

        //----------------------------------------------
        //create vector of intensities and a vector of mz values from myPeaks vector
    #ifdef ORIG
        std::vector<double> intensities1 = myPeaks.Select([&] (std::any p)
        {
            p::intensity;
        })->ToArray();
        std::vector<double> mz1 = myPeaks.Select([&] (std::any p)
        {
            p::mz;
        })->ToArray();
    #endif

        std::vector<double> intensities1;
        std::vector<double> mz1;
        for (long unsigned int i=0;i<myPeaks.size();i++){
            intensities1.push_back(myPeaks[i].second);
            mz1.push_back(myPeaks[i].first);
        }
        //-----------------------------------------------

        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        MzRange *tempVar = new MzRange(400, 1600);
        MsDataScan* scan = new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");
        // std::vector<MsDataScan*> scans = {new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1")};
        std::vector<MsDataScan*> scans;
        scans.push_back(scan);
        FakeMsDataFile *f = new FakeMsDataFile(scans);

        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzml.mzML"), false);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, std::experimental::filesystem::current_path().string() + "/mzml.mzML", false);

        // Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzml.mzML"), testFilteringParams);
        Mzml *ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/mzml.mzML", testFilteringParams);

        //Nick TODO is this unused.  Looks like its unused in C# version too
        // int expNumPeaks = ok->GetAllScansList().front().MassSpectrum.XArray->Length;
        int expNumPeaks = ok->GetAllScansList().front()->getMassSpectrum()->getXArray().size();

    #ifdef ORIG
        double expMinRatio = ok->GetAllScansList().front().MassSpectrum.YArray.Min([&] (std::any p)
        {
//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete testFilteringParams' statement was not added since testFilteringParams was passed to a method or constructor. Handle memory management manually.
        delete rand;
            return p / ok->GetAllScansList().front().MassSpectrum.YofPeakWithHighestY;
        })->Value;
    #endif

        std::vector<double> YArray = ok->GetAllScansList().front()->getMassSpectrum()->getYArray();
        auto peakWithHighestY = ok->GetAllScansList().front()->getMassSpectrum()->getYofPeakWithHighestY().value();
        for (long unsigned int i=0;i<YArray.size();i++){
            YArray[i] = YArray[i] / peakWithHighestY;
        }

        auto expMinRatioPtr = std::min_element(YArray.begin(), YArray.end());
        double expMinRatio = *expMinRatioPtr;

        // std::vector<(double mz, double intensity)*> myExpPeaks;
        std::vector<std::pair<double, double>> myExpPeaks;

        for (long unsigned int i = 0; i < ok->GetAllScansList().front()->getMassSpectrum()->getYArray().size(); i++)
        {
            // myExpPeaks.push_back((ok->GetAllScansList().front().MassSpectrum.XArray[i], ok->GetAllScansList().front().MassSpectrum.YArray[i]));
            std::pair<double,double> p;
            p.first = ok->GetAllScansList().front()->getMassSpectrum()->getXArray()[i];
            p.second = ok->GetAllScansList().front()->getMassSpectrum()->getYArray()[i];
            myExpPeaks.push_back(p);
        }

        //C# Asserts
        // Assert.That(Math.Round(myMaxIntensity, 0) == Math.Round(ok.GetAllScansList().First().MassSpectrum.YofPeakWithHighestY.Value, 0));
        // Assert.That(Math.Round(sumOfAllIntensities, 0) == Math.Round(ok.GetAllScansList().First().MassSpectrum.SumOfAllY, 0));
        // Assert.That(myPeaksOrderedByIntensity.Count == ok.GetAllScansList().First().MassSpectrum.XArray.Length);
        // Assert.That(expMinRatio >= minRatio);
        // Assert.That(!myExpPeaks.Except(myPeaksOrderedByIntensity).Any());
        // Assert.That(!myPeaksOrderedByIntensity.Except(myExpPeaks).Any());

        // Assert::That(std::round(myMaxIntensity * std::pow(10, 0)) / std::pow(10, 0) == std::round(ok->GetAllScansList().front().MassSpectrum.YofPeakWithHighestY->Value * std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(myMaxIntensity * std::pow(10, 0)) / std::pow(10, 0), std::round(ok->GetAllScansList().front()->getMassSpectrum()->getYofPeakWithHighestY().value() * std::pow(10, 0)) / std::pow(10, 0));
        // Assert::That(std::round(sumOfAllIntensities * std::pow(10, 0)) / std::pow(10, 0) == std::round(ok->GetAllScansList().front().MassSpectrum.SumOfAllY * std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(sumOfAllIntensities * std::pow(10, 0)) / std::pow(10, 0), std::round(ok->GetAllScansList().front()->getMassSpectrum()->getSumOfAllY() * std::pow(10, 0)) / std::pow(10, 0));
        // Assert::That(myPeaksOrderedByIntensity.size() == ok->GetAllScansList().front().MassSpectrum.XArray->Length);
        Assert::AreEqual(filteredPeaks.size(), ok->GetAllScansList().front()->getMassSpectrum()->getXArray().size());
        // Assert::That(expMinRatio >= minRatio);
        Assert::IsTrue(expMinRatio >= minRatio);
        //tests that myExpPeaks with myPeaksOrderedByIntensity elements removed contains no values
        //Any() returns True or False if array contains values
        //Expects !False = True
        std::vector<std::pair<double, double>> myExpPeaksCopy;
        std::vector<std::pair<double, double>> myPeaksOrderedByIntensityCopy;
        myExpPeaksCopy = myExpPeaks;
        myPeaksOrderedByIntensityCopy = filteredPeaks;
        for (long unsigned int i=0;i<filteredPeaks.size();i++){
            myExpPeaksCopy.erase(std::remove(myExpPeaksCopy.begin(), myExpPeaksCopy.end(), filteredPeaks[i]), myExpPeaksCopy.end());
        }
        for (long unsigned int i=0;i<myExpPeaks.size();i++){
            myPeaksOrderedByIntensityCopy.erase(std::remove(myPeaksOrderedByIntensityCopy.begin(), myPeaksOrderedByIntensityCopy.end(), myExpPeaks[i]), myPeaksOrderedByIntensityCopy.end());
        }
        Assert::IsTrue(myExpPeaksCopy.size() == 0);
        //tests that myPeaksOrderedByIntensity with myExpPeaks elements removed still contains values
        Assert::IsTrue(myPeaksOrderedByIntensityCopy.size() == 0);

        std::string filePath = std::experimental::filesystem::current_path().string() + "/mzml.mzML";
        remove(filePath.c_str());

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete testFilteringParams' statement was not added since testFilteringParams was passed to a method or constructor. Handle memory management manually.
        //Nick: TODO delete statements?
        // delete rand;
    }

    void TestMzML::TestPeakTrimmingWithTooManyWindows()
    {
        // Random *rand = new Random();
        int numPeaks = 200;
        double minRatio = 0.01;
        int numWindows = 10;

        auto testFilteringParams = new FilteringParams(std::make_optional(numPeaks), std::make_optional(minRatio),
                                                       std::make_optional(numWindows), true, true);
        // only 1 peak but 10 windows
    #ifdef ORIG
        std::vector<(double mz, double intensity)*> myPeaks =
        {
            {(400, rand->Next(1000, 1000000))}
        };

        std::vector<double> intensities1 = myPeaks.Select([&] (std::any p)
        {
            p::intensity;
        })->ToArray();
        std::vector<double> mz1 = myPeaks.Select([&] (std::any p)
        {
            p::mz;
        })->ToArray();
    #endif
        //pair = (mz, intensity)
        std::vector<std::pair<double, double>> myPeaks;
        std::pair<double, double> p;
        p.first = 400;
        p.second = rand() % 1000000 + 1000;
        // p.second = 250000;
        myPeaks.push_back(p); 

        std::vector<double> intensities1;
        std::vector<double> mz1;
        for (unsigned long int i=0; i<myPeaks.size();i++){
            intensities1.push_back(myPeaks[i].second);
            mz1.push_back(myPeaks[i].first);
        }

        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        // MzRange tempVar(400, 1600);
        MzRange *tempVar = new MzRange(400, 1600);

        MsDataScan* scan = new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");

        // std::vector<MsDataScan*> scans = {new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, tempVar,
                                                         // "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(),
                                                         // std::nullopt, std::vector<std::vector<double>>(), "1")};
        std::vector<MsDataScan*> scans;
        scans.push_back(scan);
        FakeMsDataFile *f = new FakeMsDataFile(scans);

        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory,
        //                                                                               "mzml.mzML"), false);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, std::experimental::filesystem::current_path().string() +
                                                               "/mzml2.mzML", false);

        // Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory,
        //                                                        "mzml.mzML"), testFilteringParams);
        Mzml *ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/mzml2.mzML",
                                           testFilteringParams);

        // Assert::That(std::round(myPeaks[0]->intensity * std::pow(10, 0)) / std::pow(10, 0) ==
        // std::round(ok->GetAllScansList().front().MassSpectrum.YofPeakWithHighestY->Value *
        //            std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(myPeaks[0].second * std::pow(10, 0)) / std::pow(10, 0),
                         std::round(ok->GetAllScansList().front()->getMassSpectrum()->getYofPeakWithHighestY().value() *
                                    std::pow(10, 0)) / std::pow(10, 0));

        // Assert::That(std::round(myPeaks[0]->intensity * std::pow(10, 0)) / std::pow(10, 0) ==
        //  std::round(ok->GetAllScansList().front().MassSpectrum.SumOfAllY * std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(myPeaks[0].second * std::pow(10, 0)) / std::pow(10, 0),
                         std::round(ok->GetAllScansList().front()->getMassSpectrum()->getSumOfAllY() *
                                    std::pow(10, 0)) / std::pow(10, 0));
        
        // Assert::That(1 == ok->GetAllScansList().front().MassSpectrum.XArray->Length);
        Assert::AreEqual(1, static_cast<int>(ok->GetAllScansList().front()->getMassSpectrum()->getXArray().size()));

        // Assert::That(std::round(myPeaks[0]->mz * std::pow(10, 0)) / std::pow(10, 0) ==
        //    std::round(ok->GetAllScansList().front().MassSpectrum.XArray[0] * std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(myPeaks[0].first * std::pow(10, 0)) / std::pow(10, 0),
                         std::round(ok->GetAllScansList().front()->getMassSpectrum()->getXArray()[0] * std::pow(10, 0)) / std::pow(10, 0));

        // Assert::That(std::round(myPeaks[0]->intensity * std::pow(10, 0)) / std::pow(10, 0) ==
        //    std::round(ok->GetAllScansList().front().MassSpectrum.YArray[0] * std::pow(10, 0)) / std::pow(10, 0));
        Assert::AreEqual(std::round(myPeaks[0].second * std::pow(10, 0)) / std::pow(10, 0),
                         std::round(ok->GetAllScansList().front()->getMassSpectrum()->getYArray()[0] * std::pow(10, 0)) / std::pow(10, 0));

        std::string filePath = std::experimental::filesystem::current_path().string() + "/mzml2.mzML";
        remove(filePath.c_str());
//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete testFilteringParams' statement was not added since testFilteringParams was passed to a method or constructor. Handle memory management manually.
        // delete rand;
    }

    void TestMzML::WriteEmptyScan()
    {
        std::vector<double> intensities1;
        std::vector<double> mz1;
        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        MzRange tempVar(1, 100);
        std::vector<MsDataScan*> scans = {new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, &tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1")};
        FakeMsDataFile *f = new FakeMsDataFile(scans);

        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzmlWithEmptyScan.mzML"), false);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan.mzML", false);

        // Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzmlWithEmptyScan.mzML"));
        Mzml *ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan.mzML");

        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzmlWithEmptyScan2.mzML"), false);
#ifdef FIX_LATER
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(ok, std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan2.mzML", false);

        auto testFilteringParams = new FilteringParams(std::make_optional(200), std::make_optional(0.01), std::make_optional(5), true, true);

        // ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "mzmlWithEmptyScan2.mzML"), testFilteringParams);
        ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan2.mzML", testFilteringParams);
#endif
//C# TO C++ CONVERTER TODO TASK: A 'delete testFilteringParams' statement was not added since testFilteringParams was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.

        std::string filePath = std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan.mzML";
        remove(filePath.c_str());
        std::string filePath1 = std::experimental::filesystem::current_path().string() + "/mzmlWithEmptyScan2.mzML";
        remove(filePath1.c_str());
    }

    void TestMzML::DifferentAnalyzersTest()
    {
        std::vector<MsDataScan*> scans(2);

        std::vector<double> intensities1 = {1};
        std::vector<double> mz1 = {50};
        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        MzRange tempVar(1, 100);
        scans[0] = new MsDataScan(massSpec1, 1, 1, true, Polarity::Positive, 1, &tempVar, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");

        std::vector<double> intensities2 = {1};
        std::vector<double> mz2 = {30};
        MzSpectrum *massSpec2 = new MzSpectrum(mz2, intensities2, false);
        MzRange tempVar2(1, 100);
        scans[1] = new MsDataScan(massSpec2, 2, 2, true, Polarity::Positive, 2, &tempVar2, "f", MZAnalyzerType::IonTrap3D, massSpec2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(1), std::nullopt);

        FakeMsDataFile *f = new FakeMsDataFile(scans);

        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "asdfefsf.mzML"), false);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, std::experimental::filesystem::current_path().string() + "/asdfefsf.mzML", false);

        // Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "asdfefsf.mzML"));
        Mzml *ok = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/asdfefsf.mzML");

        Assert::IsTrue(MZAnalyzerType::Orbitrap == ok->GetAllScansList().front()->getMzAnalyzer());
        Assert::IsTrue(MZAnalyzerType::IonTrap3D == ok->GetAllScansList().back()->getMzAnalyzer());

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.

        std::string filePath = std::experimental::filesystem::current_path().string() + "/asdfefsf.mzML";
        remove(filePath.c_str());        
    }


#ifdef LATER
    void TestMzML::Mzid111Test()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML111::Generated::MzIdentMLType111));
        auto _mzid = new mzIdentML111::Generated::MzIdentMLType111();
        mzIdentML111::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML111::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML111::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML111::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML111::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML111::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML111::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML111::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML111::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML111::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML111::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML111::Generated::CVParamType *tempVar6 = new mzIdentML111::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam(std::vector<mzIdentML111::Generated::CVParamType*> {tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML111::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML111::Generated::IonTypeType*>(1);
        mzIdentML111::Generated::IonTypeType *tempVar7 = new mzIdentML111::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML111::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML111::Generated::FragmentArrayType *tempVar8 = new mzIdentML111::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML111::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML111::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML111::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML111::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML111::Generated::SpectraDataType*>(1));
        mzIdentML111::Generated::SpectraDataType *tempVar11 = new mzIdentML111::Generated::SpectraDataType();
        mzIdentML111::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML111::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML111::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML111::Generated::PeptideEvidenceType*>(1));
        mzIdentML111::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML111::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML111::Generated::PeptideType*>(1));
        mzIdentML111::Generated::PeptideType *tempVar15 = new mzIdentML111::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML111::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML111::Generated::DBSequenceType*>(1));
        mzIdentML111::Generated::DBSequenceType *tempVar16 = new mzIdentML111::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML111::Generated::ModificationType *tempVar17 = new mzIdentML111::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML111::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML111::Generated::CVParamType *tempVar18 = new mzIdentML111::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML111::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML111::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML111::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML111::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML111::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML111::Generated::CVParamType *tempVar21 = new mzIdentML111::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML111::Generated::CVParamType*>(1);
        mzIdentML111::Generated::CVParamType *tempVar22 = new mzIdentML111::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    void TestMzML::Mzid120Test()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML120::Generated::MzIdentMLType120));
        auto _mzid = new mzIdentML120::Generated::MzIdentMLType120();
        mzIdentML120::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML120::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML120::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML120::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML120::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML120::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML120::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML120::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML120::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML120::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML120::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML120::Generated::CVParamType *tempVar6 = new mzIdentML120::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML120::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML120::Generated::IonTypeType*>(1);
        mzIdentML120::Generated::IonTypeType *tempVar7 = new mzIdentML120::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML120::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML120::Generated::FragmentArrayType *tempVar8 = new mzIdentML120::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML120::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML120::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML120::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML120::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML120::Generated::SpectraDataType*>(1));
        mzIdentML120::Generated::SpectraDataType *tempVar11 = new mzIdentML120::Generated::SpectraDataType();
        mzIdentML120::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML120::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML120::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML120::Generated::PeptideEvidenceType*>(1));
        mzIdentML120::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML120::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML120::Generated::PeptideType*>(1));
        mzIdentML120::Generated::PeptideType *tempVar15 = new mzIdentML120::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML120::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML120::Generated::DBSequenceType*>(1));
        mzIdentML120::Generated::DBSequenceType *tempVar16 = new mzIdentML120::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML120::Generated::ModificationType *tempVar17 = new mzIdentML120::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML120::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML120::Generated::CVParamType *tempVar18 = new mzIdentML120::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML120::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML120::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML120::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML120::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML120::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML120::Generated::CVParamType *tempVar21 = new mzIdentML120::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML120::Generated::CVParamType*>(1);
        mzIdentML120::Generated::CVParamType *tempVar22 = new mzIdentML120::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }
#endif

#ifdef ORIG
    void TestMzML::Setup()
    {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(R"(elements.dat)");
    }
#endif

    void TestMzML::LoadMzmlTest()
    {
        // Assert::Throws<AggregateException*>([&] ()
        // {
        //     Mzml::LoadAllStaticData(R"(tiny.pwiz.1.1.mzML)");
        // }, "Reading profile mode mzmls not supported");
    }

#ifdef FIX_LATER
    void TestMzML::LoadMzmlFromConvertedMGFTest()
    {
        Mzml *a = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/tester.mzML");

        auto ya = a->GetOneBasedScan(1)->getMassSpectrum();
        Assert::AreEqual(192, ya->getSize());
        auto ya2 = a->GetOneBasedScan(3)->getMassSpectrum();
        Assert::AreEqual(165, ya2->getSize());
        auto ya3 = a->GetOneBasedScan(5)->getMassSpectrum();
        Assert::AreEqual(551, ya3->getSize());

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, std::experimental::filesystem::current_path().string() + "/CreateFileFromConvertedMGF.mzML", false);

        Mzml *b = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/CreateFileFromConvertedMGF.mzML");

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(b, std::experimental::filesystem::current_path().string() + "/CreateFileFromConvertedMGF2.mzML", false);
    }
#endif
    void TestMzML::WriteMzmlTest()
    {
        auto peptide = new Peptide("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        OldSchoolChemicalFormulaModification *carbamidomethylationOfCMod = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("H3C2NO"), "carbamidomethylation of C", ModificationSites::C);
        peptide->AddModification(carbamidomethylationOfCMod);

        MzSpectrum *MS1 = CreateSpectrum(peptide->GetChemicalFormula(), 300, 2000, 1);

        // MzSpectrum *TestMzML::CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2)
        auto p = peptide->Fragment(FragmentTypes::b | FragmentTypes::y, true);
        MzSpectrum *MS2 = CreateMS2spectrum(p, 100, 1500);

        std::vector<MsDataScan*> Scans(2);

        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, true, Polarity::Positive, 1.0, &tempVar, " first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::make_optional(1), std::vector<std::vector<double>>(), "scan=1");
        //            scans[1] = new MsDataScanZR(massSpec2, 2, 2, true, Polarity.Positive, 2, new MzRange(1, 100), "f", MZAnalyzerType.IonTrap3D, massSpec2.SumOfAllY, null, null, "2", 50, null, null, 50, 1, DissociationType.CID, 1, null);

        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, true, Polarity::Positive, 2.0, &tempVar2, " second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::make_optional(1), std::vector<std::vector<double>>(), "scan=2", std::make_optional(1134.26091302033), std::make_optional(3), std::make_optional(0.141146966879759), std::make_optional(1134.3), std::make_optional(1), std::make_optional(DissociationType::Unknown), std::make_optional(1), std::make_optional(1134.26091302033));

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto oldFirstValue = myMsDataFile->GetOneBasedScan(1)->getMassSpectrum()->getFirstX();

        auto secondScan = myMsDataFile->GetOneBasedScan(2);
        Assert::AreEqual((double)1, secondScan->getIsolationRange()->getMaximum() - secondScan->getIsolationRange()->getMinimum());

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(myMsDataFile, std::experimental::filesystem::current_path().string() + "/argh.mzML", false);

        Mzml *okay = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/argh.mzML");
        okay->GetOneBasedScan(2);

        Assert::AreEqual(1, okay->GetClosestOneBasedSpectrumNumber(1));
        Assert::AreEqual(2, okay->GetClosestOneBasedSpectrumNumber(2));

        auto newFirstValue = okay->GetOneBasedScan(1)->getMassSpectrum()->getFirstX();
        Assert::AreEqual(oldFirstValue.value(), newFirstValue.value(), 1e-9);

        auto secondScan2 = okay->GetOneBasedScan(2);

        Assert::AreEqual((double)1, secondScan2->getIsolationRange()->getMaximum() - secondScan2->getIsolationRange()->getMinimum());

    #ifdef ORIG
        secondScan2->getMassSpectrum().ReplaceXbyApplyingFunction([&] (a)
        {
            44;
        });
    #endif

        std::function<double(MzPeak*)> f1 = [&](MzPeak* a){return 44;};
        secondScan2->getMassSpectrum()->ReplaceXbyApplyingFunction(f1);
        Assert::AreEqual(44, secondScan2->getMassSpectrum()->getLastX());

//C# TO C++ CONVERTER TODO TASK: A 'delete myMsDataFile' statement was not added since myMsDataFile was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete carbamidomethylationOfCMod' statement was not added since carbamidomethylationOfCMod was passed to a method or constructor. Handle memory management manually.
        
        std::string filePath = std::experimental::filesystem::current_path().string() + "/argh.mzML";
        remove(filePath.c_str());

        delete peptide;
    }

#ifdef LATER
    void TestMzML::MzidTest()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML110::Generated::MzIdentMLType110));
        auto _mzid = new mzIdentML110::Generated::MzIdentMLType110();
        mzIdentML110::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML110::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML110::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML110::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML110::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML110::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML110::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML110::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML110::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML110::Generated::CVParamType *tempVar6 = new mzIdentML110::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML110::Generated::IonTypeType*>(1);
        mzIdentML110::Generated::IonTypeType *tempVar7 = new mzIdentML110::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML110::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML110::Generated::FragmentArrayType *tempVar8 = new mzIdentML110::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML110::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML110::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML110::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->passThreshold = true;

        mzIdentML110::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML110::Generated::SpectraDataType*>(1));
        mzIdentML110::Generated::SpectraDataType *tempVar11 = new mzIdentML110::Generated::SpectraDataType();
        mzIdentML110::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML110::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML110::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML110::Generated::PeptideEvidenceType*>(1));
        mzIdentML110::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML110::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setisDecoy(false);
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML110::Generated::PeptideType*>(1));
        mzIdentML110::Generated::PeptideType *tempVar15 = new mzIdentML110::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML110::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML110::Generated::DBSequenceType*>(1));
        mzIdentML110::Generated::DBSequenceType *tempVar16 = new mzIdentML110::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML110::Generated::ModificationType *tempVar17 = new mzIdentML110::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML110::Generated::CVParamType *tempVar18 = new mzIdentML110::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML110::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML110::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML110::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML110::Generated::CVParamType *tempVar21 = new mzIdentML110::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML110::Generated::CVParamType*>(1);
        mzIdentML110::Generated::CVParamType *tempVar22 = new mzIdentML110::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    void TestMzML::Mzid110Test()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML110::Generated::MzIdentMLType110));
        auto _mzid = new mzIdentML110::Generated::MzIdentMLType110();
        mzIdentML110::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML110::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML110::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML110::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML110::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML110::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML110::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML110::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML110::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML110::Generated::CVParamType *tempVar6 = new mzIdentML110::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML110::Generated::IonTypeType*>(1);
        mzIdentML110::Generated::IonTypeType *tempVar7 = new mzIdentML110::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML110::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML110::Generated::FragmentArrayType *tempVar8 = new mzIdentML110::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML110::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML110::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML110::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML110::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML110::Generated::SpectraDataType*>(1));
        mzIdentML110::Generated::SpectraDataType *tempVar11 = new mzIdentML110::Generated::SpectraDataType();
        mzIdentML110::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML110::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML110::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML110::Generated::PeptideEvidenceType*>(1));
        mzIdentML110::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML110::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML110::Generated::PeptideType*>(1));
        mzIdentML110::Generated::PeptideType *tempVar15 = new mzIdentML110::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML110::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML110::Generated::DBSequenceType*>(1));
        mzIdentML110::Generated::DBSequenceType *tempVar16 = new mzIdentML110::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML110::Generated::ModificationType *tempVar17 = new mzIdentML110::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML110::Generated::CVParamType *tempVar18 = new mzIdentML110::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML110::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML110::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML110::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML110::Generated::CVParamType *tempVar21 = new mzIdentML110::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML110::Generated::CVParamType*>(1);
        mzIdentML110::Generated::CVParamType *tempVar22 = new mzIdentML110::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    void TestMzML::Mzid111Test_()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML111::Generated::MzIdentMLType111));
        auto _mzid = new mzIdentML111::Generated::MzIdentMLType111();
        mzIdentML111::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML111::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML111::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML111::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML111::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML111::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML111::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML111::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML111::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML111::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML111::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML111::Generated::CVParamType *tempVar6 = new mzIdentML111::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam(std::vector<mzIdentML111::Generated::CVParamType*> {tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML111::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML111::Generated::IonTypeType*>(1);
        mzIdentML111::Generated::IonTypeType *tempVar7 = new mzIdentML111::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML111::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML111::Generated::FragmentArrayType *tempVar8 = new mzIdentML111::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML111::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML111::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML111::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML111::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML111::Generated::SpectraDataType*>(1));
        mzIdentML111::Generated::SpectraDataType *tempVar11 = new mzIdentML111::Generated::SpectraDataType();
        mzIdentML111::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML111::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML111::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML111::Generated::PeptideEvidenceType*>(1));
        mzIdentML111::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML111::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML111::Generated::PeptideType*>(1));
        mzIdentML111::Generated::PeptideType *tempVar15 = new mzIdentML111::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML111::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML111::Generated::DBSequenceType*>(1));
        mzIdentML111::Generated::DBSequenceType *tempVar16 = new mzIdentML111::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML111::Generated::ModificationType *tempVar17 = new mzIdentML111::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML111::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML111::Generated::CVParamType *tempVar18 = new mzIdentML111::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML111::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML111::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML111::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML111::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML111::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML111::Generated::CVParamType *tempVar21 = new mzIdentML111::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML111::Generated::CVParamType*>(1);
        mzIdentML111::Generated::CVParamType *tempVar22 = new mzIdentML111::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    void TestMzML::Mzid120Test_()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML120::Generated::MzIdentMLType120));
        auto _mzid = new mzIdentML120::Generated::MzIdentMLType120();
        mzIdentML120::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML120::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML120::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML120::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML120::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML120::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML120::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML120::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID("spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML120::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML120::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML120::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML120::Generated::CVParamType *tempVar6 = new mzIdentML120::Generated::CVParamType();
        tempVar6->setaccession("MS:1002354");
        tempVar6->setvalue("0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML120::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML120::Generated::IonTypeType*>(1);
        mzIdentML120::Generated::IonTypeType *tempVar7 = new mzIdentML120::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML120::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML120::Generated::FragmentArrayType *tempVar8 = new mzIdentML120::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML120::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML120::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML120::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref("PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML120::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML120::Generated::SpectraDataType*>(1));
        mzIdentML120::Generated::SpectraDataType *tempVar11 = new mzIdentML120::Generated::SpectraDataType();
        mzIdentML120::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML120::Generated::CVParamType();
        .FileFormat::cvParam->name = "mzML format";
        mzIdentML120::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML120::Generated::PeptideEvidenceType*>(1));
        mzIdentML120::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML120::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref("DB_1");
        tempVar14->setpeptide_ref("P_1");
        tempVar14->setid("PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML120::Generated::PeptideType*>(1));
        mzIdentML120::Generated::PeptideType *tempVar15 = new mzIdentML120::Generated::PeptideType();
        tempVar15->setid("P_1");
        tempVar15->setPeptideSequence("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML120::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML120::Generated::DBSequenceType*>(1));
        mzIdentML120::Generated::DBSequenceType *tempVar16 = new mzIdentML120::Generated::DBSequenceType();
        tempVar16->setid("DB_1");
        tempVar16->setname("Protein name");
        tempVar16->setaccession("ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML120::Generated::ModificationType *tempVar17 = new mzIdentML120::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML120::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML120::Generated::CVParamType *tempVar18 = new mzIdentML120::Generated::CVParamType();
        tempVar18->setaccession("MS:1001460");
        tempVar18->setname("unknown modification");
        tempVar18->setvalue("Carbamidomethyl");
        tempVar18->setcvRef("PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML120::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML120::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML120::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML120::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML120::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML120::Generated::CVParamType *tempVar21 = new mzIdentML120::Generated::CVParamType();
        tempVar21->setunitName("dalton");
        tempVar21->setvalue("0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML120::Generated::CVParamType*>(1);
        mzIdentML120::Generated::CVParamType *tempVar22 = new mzIdentML120::Generated::CVParamType();
        tempVar22->setunitName("dalton");
        tempVar22->setvalue("0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter("myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications("myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual("MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual("PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual("Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual("spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual("GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual("Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual("ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual("2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual("34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
        delete tempVar22;
        delete tempVar21;
        delete tempVar20;
        delete tempVar18;
        delete tempVar17;
        delete tempVar16;
        delete tempVar15;
        delete tempVar14;
        delete tempVar11;
        delete tempVar9;
        delete tempVar8;
        delete tempVar7;
        delete tempVar6;
        delete tempVar5;
        delete tempVar4;
        delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

#endif

    void TestMzML::MzmlFindPrecursorReferenceScan()
    {
        //some ms2 scans dont have properly assigned precursor scans
        //this unit test is intended to test the fallback option in MzML\Mzml.cs @ lines 459-47
        //constructs three ms1 scans and three ms2 scans
        //if ms2 scan precusor reference is null, assumes most recent ms1 scan is correct reference

        std::vector<MsDataScan*> scans(6);
        std::vector<MsDataScan*> scans1(4);

        std::vector<double> intensities0 = {1};
        std::vector<double> mz0 = {50};
        MzSpectrum *massSpec0 = new MzSpectrum(mz0, intensities0, false);
        MzRange tempVar(1, 100);
        scans[0] = new MsDataScan(massSpec0, 1, 1, true, Polarity::Positive, 1, &tempVar, "f", MZAnalyzerType::Orbitrap, massSpec0->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");
        scans1[0] = scans[0];

        std::vector<double> intensities1 = {1};
        std::vector<double> mz1 = {50};
        MzSpectrum *massSpec1 = new MzSpectrum(mz1, intensities1, false);
        MzRange tempVar2(1, 100);
        scans[1] = new MsDataScan(massSpec0, 2, 1, true, Polarity::Positive, 1, &tempVar2, "f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");

        std::vector<double> intensities2 = {1};
        std::vector<double> mz2 = {50};
        MzSpectrum *massSpec2 = new MzSpectrum(mz2, intensities2, false);
        MzRange tempVar3(1, 100);
        scans[2] = new MsDataScan(massSpec2, 3, 1, true, Polarity::Positive, 1, &tempVar3, "f", MZAnalyzerType::Orbitrap, massSpec2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "1");

        //ms2
        std::vector<double> intensities3 = {1};
        std::vector<double> mz3 = {30};
        MzSpectrum *massSpec3 = new MzSpectrum(mz3, intensities3, false);
        MzRange tempVar4(1, 100);
        scans[3] = new MsDataScan(massSpec3, 4, 2, true, Polarity::Positive, 2, &tempVar4, "f", MZAnalyzerType::Orbitrap, massSpec3->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(3), std::nullopt);
        MzRange tempVar5(1, 100);
        scans1[1] = new MsDataScan(massSpec3, 2, 2, true, Polarity::Positive, 2, &tempVar5, "f", MZAnalyzerType::Orbitrap, massSpec3->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(1), std::nullopt);

        //ms2
        std::vector<double> intensities4 = {1};
        std::vector<double> mz4 = {30};
        MzSpectrum *massSpec4 = new MzSpectrum(mz4, intensities4, false);
        MzRange tempVar6(1, 100);
        scans[4] = new MsDataScan(massSpec4, 5, 2, true, Polarity::Positive, 2, &tempVar6, "f", MZAnalyzerType::Orbitrap, massSpec4->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(3), std::nullopt);
        MzRange tempVar7(1, 100);
        scans1[2] = new MsDataScan(massSpec4, 3, 2, true, Polarity::Positive, 2, &tempVar7, "f", MZAnalyzerType::Orbitrap, massSpec4->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "2", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::make_optional(1), std::nullopt);

        //ms2
        std::vector<double> intensities5 = {1};
        std::vector<double> mz5 = {30};
        MzSpectrum *massSpec5 = new MzSpectrum(mz5, intensities5, false);
        MzRange tempVar8(1, 100);
        scans[5] = new MsDataScan(massSpec5, 6, 2, true, Polarity::Positive, 2, &tempVar8, "f", MZAnalyzerType::Orbitrap, massSpec5->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "4", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::nullopt, std::nullopt);
        MzRange tempVar9(1, 100);
        scans1[3] = new MsDataScan(massSpec5, 4, 2, true, Polarity::Positive, 2, &tempVar9, "f", MZAnalyzerType::Orbitrap, massSpec5->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "4", std::make_optional(50), std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), std::make_optional(DissociationType::CID), std::nullopt, std::nullopt);

        FakeMsDataFile *fakeFile = new FakeMsDataFile(scans);
        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(fakeFile, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "what.mzML"), false);
        // Mzml *fakeMzml = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "what.mzML"));
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(fakeFile, std::experimental::filesystem::current_path().string() + "/what.mzML", false);
        Mzml *fakeMzml = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/what.mzML");
        

        FakeMsDataFile *fakeFile1 = new FakeMsDataFile(scans1);
        // MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(fakeFile1, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "what1.mzML"), false);
        // Mzml *fakeMzml1 = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "what1.mzML"));
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(fakeFile1, std::experimental::filesystem::current_path().string() + "/what1.mzML", false);
        Mzml *fakeMzml1 = Mzml::LoadAllStaticData(std::experimental::filesystem::current_path().string() + "/what1.mzML");

        Assert::AreEqual(3, fakeMzml->GetAllScansList().at(5)->getOneBasedPrecursorScanNumber().value());
        Assert::AreEqual(1, fakeMzml1->GetAllScansList().at(3)->getOneBasedPrecursorScanNumber().value());

//C# TO C++ CONVERTER TODO TASK: A 'delete fakeFile1' statement was not added since fakeFile1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete fakeFile' statement was not added since fakeFile was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec5' statement was not added since massSpec5 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec4' statement was not added since massSpec4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec3' statement was not added since massSpec3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
        std::string filePath = std::experimental::filesystem::current_path().string() + "/what.mzML";
        remove(filePath.c_str());        
        std::string filePath1 = std::experimental::filesystem::current_path().string() + "/what1.mzML";
        remove(filePath1.c_str());

        delete massSpec1;
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec0' statement was not added since massSpec0 was passed to a method or constructor. Handle memory management manually.
    }

    MzSpectrum *TestMzML::CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2)
    {
        std::vector<double> allMasses;
        std::vector<double> allIntensities;
        for (auto f : fragments)
        {
            if (dynamic_cast<ChemicalFormulaFragment*>(f) != nullptr){
                auto spec = CreateSpectrum(((ChemicalFormulaFragment*)f)->getThisChemicalFormula(), v1, v2, 2);
                for (int i = 0; i < spec->getSize(); i++)
                {
                    allMasses.push_back(spec->getXArray()[i]);
                    allIntensities.push_back(spec->getYArray()[i]);
                }
            }
        }
        // auto allMassesArray = allMasses.ToArray();
        // auto allIntensitiessArray = allIntensities.ToArray();
        auto allMassesArray = allMasses;
        auto allIntensitiessArray = allIntensities;

        // Array::Sort(allMassesArray, allIntensitiessArray);
        Sort::SortPairs(allMassesArray, allIntensitiessArray, allMassesArray.size());
        return new MzSpectrum(allMassesArray, allIntensitiessArray, false);
    }

    MzSpectrum *TestMzML::CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge)
    {
        IsotopicDistribution *isodist = IsotopicDistribution::GetDistribution(f, 0.1);

        // return new MzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);
        std::vector<double> mz = isodist->getMasses();
        std::vector<double> intensities = isodist->getIntensities();
        return new MzSpectrum(mz, intensities, false);
        //massSpectrum1 = massSpectrum1.FilterByNumberOfMostIntense(5);

        //var chargeToLookAt = minCharge;
        //var correctedSpectrum = massSpectrum1.NewSpectrumApplyFunctionToX(s => s.ToMz(chargeToLookAt));

        //List<double> allMasses = new List<double>();
        //List<double> allIntensitiess = new List<double>();

        //while (correctedSpectrum.FirstX > lowerBound)
        //{
        //    foreach (var thisPeak in correctedSpectrum)
        //    {
        //        if (thisPeak.Mz > lowerBound && thisPeak.Mz < upperBound)
        //        {
        //            allMasses.Add(thisPeak.Mz);
        //            allIntensitiess.Add(thisPeak.Intensity);
        //        }
        //    }
        //    chargeToLookAt += 1;
        //    correctedSpectrum = massSpectrum1.NewSpectrumApplyFunctionToX(s => s.ToMz(chargeToLookAt));
        //}

        //var allMassesArray = allMasses.ToArray();
        //var allIntensitiessArray = allIntensitiess.ToArray();

        //Array.Sort(allMassesArray, allIntensitiessArray);

        //return new MzmlMzSpectrum(allMassesArray, allIntensitiessArray, false);
    }
}
