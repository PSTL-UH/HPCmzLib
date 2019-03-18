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

using namespace MzLibUtil;

namespace MassSpectrometry {

    SummedMsDataFile::SummedMsDataFile(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *raw, int numScansToAverage, double ppmToleranceForPeakCombination) : MsDataFile<IMsDataScan<IMzSpectrum<IMzPeak>>>(R"(scan number only nativeID format)", raw->getSourceFile()->getMassSpectrometerFileFormat(), raw->getSourceFile()->getCheckSum(), raw->getSourceFile()->getFileChecksumType(), raw->getSourceFile()->getUri(), raw->getSourceFile()->getId(), raw->getSourceFile()->getFileName()), raw(raw), numScansToAverage(numScansToAverage), ppmToleranceForPeakCombination(ppmToleranceForPeakCombination) {
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

            IMzSpectrum<IMzPeak*> *peaks = CombinePeaks(raw->Where([&] (std::any b) {
                return b::OneBasedScanNumber >= oneBasedScanNumber && b::OneBasedScanNumber <= oneBasedScanNumber + numScansToAverage - 1;
            })->Select([&] (std::any b) {
                b::MassSpectrum;
            }).ToList(), ppmToleranceForPeakCombination);

            MzRange *scanWindowRange = representative->getScanWindowRange();

            double totalIonCurrent = peaks->SumOfAllY;
            double injectionTime = NAN;
            std::vector<std::vector<double>> noiseData;

            Scans[oneBasedScanNumber - 1] = new MsDataScan<IMzSpectrum<IMzPeak*>*>(peaks, oneBasedScanNumber, msnOrder, isCentroid, polarity, retentionTime, scanWindowRange, "", mzAnalyzer, totalIonCurrent, std::make_optional(injectionTime), noiseData, "scan=" + std::to_string(oneBasedScanNumber));
        }
        return Scans[oneBasedScanNumber - 1];
    }

    IMzSpectrum<IMzPeak*> *SummedMsDataFile::CombinePeaks(std::vector<IMzSpectrum<IMzPeak*>*> &spectraToCombine, double ppmTolerance) {
        std::vector<IMzPeak*> finalizedPeaks;

        std::vector<int> peaksLeft = spectraToCombine.Select([&] (std::any b) {
            b::Size;
        })->ToArray();
        std::vector<int> totalPeaks = spectraToCombine.Select([&] (std::any b) {
            b::Size;
        })->ToArray();
        std::vector<double> nextPeakMzs = spectraToCombine.Select([&] (std::any b) {
            b::XArray[0];
        })->ToArray();
        std::vector<double> nextPeaksIntensites = spectraToCombine.Select([&] (std::any b) {
            b::YArray[0];
        })->ToArray();

        double nextMz = nextPeakMzs.Min();
        int indexOfNextScanToConsider = Array::IndexOf(nextPeakMzs, nextMz);
        GeneratedPeak *lastPeak = new GeneratedPeak(nextMz, nextPeaksIntensites[indexOfNextScanToConsider]);

        do {
            nextMz = nextPeakMzs.Min();
            indexOfNextScanToConsider = Array::IndexOf(nextPeakMzs, nextMz);

            if ((nextMz - lastPeak->getMz()) / lastPeak->getMz() * 1e6 <= ppmTolerance) {
                // Combine next peak with lastPeak
                lastPeak->AddMzPeak(nextMz, nextPeaksIntensites[indexOfNextScanToConsider]);
            }
            else {
                // Replace lastPeak
                finalizedPeaks.push_back(lastPeak);
                lastPeak = new GeneratedPeak(nextMz, nextPeaksIntensites[indexOfNextScanToConsider]);
            }

            peaksLeft[indexOfNextScanToConsider]--;
            if (peaksLeft[indexOfNextScanToConsider] == 0) {
                nextPeakMzs[indexOfNextScanToConsider] = std::numeric_limits<double>::max();
            }
            else {
                nextPeakMzs[indexOfNextScanToConsider] = spectraToCombine[indexOfNextScanToConsider]->XArray[totalPeaks[indexOfNextScanToConsider] - peaksLeft[indexOfNextScanToConsider]];
                nextPeaksIntensites[indexOfNextScanToConsider] = spectraToCombine[indexOfNextScanToConsider]->YArray[totalPeaks[indexOfNextScanToConsider] - peaksLeft[indexOfNextScanToConsider]];
            }
        } while (peaksLeft.Any([&] (std::any b) {
//C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement was not added since lastPeak was passed to a method or constructor. Handle memory management manually.
            return b > 0;
        }));

        finalizedPeaks.push_back(lastPeak);

//C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement was not added since lastPeak was passed to a method or constructor. Handle memory management manually.
        return new GeneratedMzSpectrum(finalizedPeaks.Select([&] (std::any b) {
            b::Mz;
        })->ToArray(), finalizedPeaks.Select([&] (std::any b) {
            b::Intensity;
        })->ToArray(), false);

//C# TO C++ CONVERTER TODO TASK: A 'delete lastPeak' statement was not added since lastPeak was passed to a method or constructor. Handle memory management manually.
    }
}
