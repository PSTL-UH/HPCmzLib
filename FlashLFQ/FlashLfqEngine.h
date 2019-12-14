#pragma once

#include "../MzLibUtil/PpmTolerance.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class SpectraFileInfo; }
namespace FlashLFQ { class Identification; }
namespace FlashLFQ { class FlashLfqResults; }
namespace FlashLFQ { class Ms1ScanInfo; }
namespace FlashLFQ { class PeakIndexingEngine; }
namespace MzLibUtil { class Tolerance; }
namespace FlashLFQ { class ChromatographicPeak; }

using namespace Chemistry;
using namespace MathNet::Numerics::Statistics;
using namespace MzLibUtil;
using namespace UsefulProteomicsDatabases;

namespace FlashLFQ
{
    class FlashLfqEngine
    {
        // settings
    public:
        const bool Silent;
        const int MaxThreads;
        const double PeakfindingPpmTolerance;
        const double PpmTolerance;
        const double RtTol;
        const double IsotopePpmTolerance;
        const bool Integrate;
        const int MissedScansAllowed;
        const int NumIsotopesRequired;
        const double MbrRtWindow;
        const double MbrPpmTolerance;
        const bool ErrorCheckAmbiguousMatches;
        const bool MatchBetweenRuns;
        const bool IdSpecificChargeState;
        const bool RequireMonoisotopicMass;
        const bool Normalize;
        const double MinDiscFactorToCutAt;
        const bool AdvancedProteinQuant;

        // structures used in the FlashLFQ engine
    private:
        std::vector<SpectraFileInfo*> _spectraFileInfo;
        Stopwatch *_globalStopwatch;
        std::vector<Identification*> _allIdentifications;
        std::unordered_map<std::string, std::vector<KeyValuePair<double, double>*>> _baseSequenceToIsotopicDistribution;
        std::vector<int> _chargeStates;
        FlashLfqResults *_results;
        std::unordered_map<SpectraFileInfo*, std::vector<Ms1ScanInfo*>> _ms1Scans;
        PeakIndexingEngine *_peakIndexingEngine;

    public:
        virtual ~FlashLfqEngine()
        {
            delete _globalStopwatch;
            delete _results;
            delete _peakIndexingEngine;
        }

        FlashLfqEngine(std::vector<Identification*> &allIdentifications, bool normalize = false, bool advancedProteinQuant = false, bool matchBetweenRuns = false, double ppmTolerance = 10.0, double isotopeTolerancePpm = 5.0, double matchBetweenRunsPpmTolerance = 5.0, bool integrate = false, int numIsotopesRequired = 2, bool idSpecificChargeState = false, bool requireMonoisotopicMass = true, bool silent = false, const std::string &optionalPeriodicTablePath = "", double maxMbrWindow = 2.5, int maxThreads = -1);

        FlashLfqResults *Run();

    private:
        void CalculateTheoreticalIsotopeDistributions();

        void QuantifyMs2IdentifiedPeptides(SpectraFileInfo *fileInfo);

        void QuantifyMatchBetweenRunsPeaks(SpectraFileInfo *idAcceptorFile);

            Tolerance *mbrTol = new PpmTolerance(MbrPpmTolerance);

            std::unordered_map<std::string, ChromatographicPeak*> bestMbrHits = std::unordered_map<std::string, ChromatographicPeak*>();

            private *foreach(SpectraFileInfo idDonorFile in *_spectraFileInfo);

            // save MBR results
            private *foreach(var peak in *bestMbrHits);

            RunErrorChecking(idAcceptorFile);
    };

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private RetentionTimeCalibDataPoint[] GetRtCalSpline(SpectraFileInfo donor, SpectraFileInfo acceptor)

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private void RunErrorChecking(SpectraFileInfo spectraFile)

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private List<IsotopicEnvelope> GetIsotopicEnvelopes(List<IndexedMassSpectralPeak> peaks, Identification identification, int chargeState, bool matchBetweenRuns)

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private List<IndexedMassSpectralPeak> Peakfind(double idRetentionTime, double mass, int charge, SpectraFileInfo spectraFileInfo, Tolerance tolerance)

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private void CutPeak(ChromatographicPeak peak, double identificationTime)
}
}
