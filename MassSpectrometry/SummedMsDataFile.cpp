#include "SummedMsDataFile.h"

#include "DataScan/IMsDataScan.h"
#include "MzSpectra/IMzPeak.h"
#include "MzSpectra/IMzSpectrum.h"
#include "IMsDataFile.h"
#include "../MzLibUtil/MzLibException.h"
#include "Enums/Polarity.h"
#include "Enums/MzAnalyzerType.h"
#include "../MzLibUtil/MzRange.h"
#include "DataScan/MsDataScan.h"
#include "GeneratedPeak.h"
#include "GeneratedMzSpectrum.h"

//using namespace MzLibUtil;

namespace MassSpectrometry {

    SummedMsDataFile::SummedMsDataFile(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *raw, int numScansToAverage, double ppmToleranceForPeakCombination) :
        MsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*>(1, MassSpectrometry::SourceFile("(scan number only nativeID format)",
                                           raw->getSourceFile()->getMassSpectrometerFileFormat(),
                                           raw->getSourceFile()->getCheckSum(),
                                           raw->getSourceFile()->getFileChecksumType(),
                                           raw->getSourceFile()->getUri(),
                                           raw->getSourceFile()->getId(),
                                           raw->getSourceFile()->getFileName())),
        raw(raw), numScansToAverage(numScansToAverage),
        ppmToleranceForPeakCombination(ppmToleranceForPeakCombination) {
    }

    IMsDataScan<IMzSpectrum<IMzPeak*>*> *SummedMsDataFile::GetOneBasedScan(int oneBasedScanNumber) {
        if (Scans[oneBasedScanNumber - 1] == nullptr) {
            auto representativeScanNumber = oneBasedScanNumber + (numScansToAverage - 1) / 2;
            auto representative = raw->GetOneBasedScan(representativeScanNumber);
            if (representative->getMsnOrder() != 1) {
                throw MzLibException("Scan " + std::to_string(representativeScanNumber) + " is not MS1 scan");
            }
            int msnOrder = 1;
            Polarity polarity = representative->getPolarity();
            if (!representative->getIsCentroid()) {
                throw MzLibException("Scan " + std::to_string(representativeScanNumber) + " is not centroid scan");
            }
            bool isCentroid = true;
            double retentionTime = representative->getRetentionTime();
            MZAnalyzerType mzAnalyzer = representative->getMzAnalyzer();

#ifdef ORIG
            IMzSpectrum<IMzPeak*> *peaks = CombinePeaks(raw->Where([&] (std::any b) {
                return b::OneBasedScanNumber >= oneBasedScanNumber &&
                b::OneBasedScanNumber <= oneBasedScanNumber + numScansToAverage - 1;
            })->Select([&] (std::any b) {
                b::MassSpectrum;
            }).ToList(), ppmToleranceForPeakCombination);
#endif
            std::vector<IMzSpectrum<IMzPeak*>*> v;
            for ( auto b : *raw) {
                if (b->getOneBasedScanNumber() >= oneBasedScanNumber &&
                    b->getOneBasedScanNumber() <= oneBasedScanNumber + numScansToAverage - 1) {
                    v.push_back(b->getMassSpectrum());
                }
            }
            IMzSpectrum<IMzPeak*> *peaks = CombinePeaks( v, ppmToleranceForPeakCombination);

            MzRange *scanWindowRange = representative->getScanWindowRange();

            double totalIonCurrent = peaks->sumOfAllY.value();
            Nullable<double> injectionTime = NAN;
            Nullable<double>& ijTime= injectionTime;
            std::vector<std::vector<double>> noiseData;

            Scans[oneBasedScanNumber - 1] = new MsDataScan<IMzSpectrum<IMzPeak*>*>(peaks, oneBasedScanNumber, msnOrder, isCentroid, polarity, retentionTime, scanWindowRange, "", mzAnalyzer, totalIonCurrent, ijTime, noiseData, "scan=" + std::to_string(oneBasedScanNumber));
        }
        return Scans[oneBasedScanNumber - 1];
    }

    IMzSpectrum<IMzPeak*> *SummedMsDataFile::CombinePeaks(std::vector<IMzSpectrum<IMzPeak*>*> &spectraToCombine, double ppmTolerance) {
        std::vector<IMzPeak*> finalizedPeaks;

#ifdef ORIG
        std::vector<int> peaksLeft = spectraToCombine.Select([&] (std::any b) {
            b::Size;
        })->ToArray();
#endif
        std::vector<int> peaksLeft;
        for ( auto b : spectraToCombine ) {
            peaksLeft.push_back (b->getSize());
        }

#ifdef ORIG
        std::vector<int> totalPeaks = spectraToCombine.Select([&] (std::any b) {
            b::Size;
        })->ToArray();
#endif
        std::vector<int> totalPeaks;
        for ( auto b : spectraToCombine ) {
            totalPeaks.push_back(b->getSize());
        }

#ifdef ORIG
        std::vector<double> nextPeakMzs = spectraToCombine.Select([&] (std::any b) {
            b::XArray[0];
        })->ToArray();
#endif
        std::vector<double> nextPeakMzs;
        for ( auto b : spectraToCombine ) {
            nextPeakMzs.push_back(b->XArray[0]);
        }
    
#ifdef ORIG
        std::vector<double> nextPeaksIntensites = spectraToCombine.Select([&] (std::any b) {
            b::YArray[0];
        })->ToArray();
#endif
        std::vector<double> nextPeaksIntensites;
        for ( auto b : spectraToCombine ) {
            nextPeaksIntensites.push_back(b->YArray[0]);
        }

#ifdef ORIG
        double nextMz = nextPeakMzs.Min();
        int indexOfNextScanToConsider = Array::IndexOf(nextPeakMzs, nextMz);
#endif
        auto it = std::min_element(nextPeakMzs.begin(), nextPeakMzs.end() );
        double nextMz = *it;
        int index=std::distance(nextPeakMzs.begin(), it);
        GeneratedPeak *lastPeak = new GeneratedPeak(nextMz, nextPeaksIntensites[index]);
    
        bool cont=true;
        do {
#ifdef ORIG
            nextMz = nextPeakMzs.Min();
            indexOfNextScanToConsider = Array::IndexOf(nextPeakMzs, nextMz);
#endif
            it = std::min_element(nextPeakMzs.begin(), nextPeakMzs.end() );
            nextMz = *it;
            index = std::distance(nextPeakMzs.begin(), it);
            
            if ((nextMz - lastPeak->getMz()) / lastPeak->getMz() * 1e6 <= ppmTolerance) {
                // Combine next peak with lastPeak
                lastPeak->AddMzPeak(nextMz, nextPeaksIntensites[index]);
            }
            else {
                // Replace lastPeak
                finalizedPeaks.push_back(lastPeak);
                lastPeak = new GeneratedPeak(nextMz, nextPeaksIntensites[index]);
            }
   
            peaksLeft[index]--;
            if (peaksLeft[index] == 0) {
                nextPeakMzs[index] = std::numeric_limits<double>::max();
            }
            else {
                nextPeakMzs[index] = spectraToCombine[index]->XArray[totalPeaks[index] - peaksLeft[index]];
                nextPeaksIntensites[index] = spectraToCombine[index]->YArray[totalPeaks[index] - peaksLeft[index]];
            }
            
#ifdef ORIG
//        } while (peaksLeft.Any([&] (std::any b) {
//                    //C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement
//                    // was not added since lastPeak was passed to a method or constructor.
//                    // Handle memory management manually.
//                    return b > 0;
//                }));
#endif
            cont = false;
            for ( auto b : peaksLeft ) {
                if ( b > 0 ) {
                    cont = true;
                    break;
                }
            }
        } while (cont);
        
        finalizedPeaks.push_back(lastPeak);
    
    //C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement was not added
    // since lastPeak was passed to a method or constructor. Handle memory management manually.
#ifdef ORIG
        return new GeneratedMzSpectrum(finalizedPeaks.Select([&] (std::any b) {
                    b::Mz;
                })->ToArray(), finalizedPeaks.Select([&] (std::any b) {
                        b::Intensity;
                    })->ToArray(), false);
#endif
        std::vector<double> Mzv, Inv;
        for ( auto f :finalizedPeaks ) {
            Mzv.push_back(f->getMz());
            Inv.push_back(f->getIntensity());
        }
        return new GeneratedMzSpectrum (Mzv, Inv, false);
        //C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement was not added
        // since lastPeak was passed to a method or constructor. Handle memory management manually.
    }
}
