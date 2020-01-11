#pragma once

#include <unordered_set>
#include <vector>
#include <deque>
#include <iostream>
#include <cmath>
#include <any>
#include <functional>
#include <mutex>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class FlashLfqResults; }
namespace FlashLFQ { class Peptide; }
namespace FlashLFQ { class SpectraFileInfo; }

using namespace FlashLFQ::BoundedNelderMeadOptimizer;
//using namespace MathNet::Numerics::Statistics;
using namespace SharpLearning::Optimization;

namespace FlashLFQ
{
    class IntensityNormalizationEngine
    {
    private:
        static constexpr int numPeptidesDesiredFromEachFraction = 500;
        static constexpr int numPeptidesDesiredInMatrix = 5000;
        FlashLfqResults *const results;
        const bool integrate;
        const bool silent;
        const int maxThreads;

    public:
        virtual ~IntensityNormalizationEngine()
        {
            //delete results;
        }

        IntensityNormalizationEngine(FlashLfqResults *results, bool integrate, bool silent, int maxThreads);

        /// <summary>
        /// Runs the normalization functions.
        /// </summary>
        void NormalizeResults();

        /// <summary>
        /// This method normalizes peptide intensities so that the median fold-change between technical replicates
        /// is zero. The median is used instead of the average because it is more robust to outliers (i.e., if there are
        /// many changing peptides, the median will perform better than using the average).
        /// </summary>
    private:
        void NormalizeTechreps();

        /// <summary>
        /// This method uses a bounded Nelder-Mead optimization algorithm to find linear normalization factors
        /// so that coefficient of variation of peptide intensity between two biological replicates will be minimized.
        /// Calls "GetNormalizationFactors" to calculate the normalization factors.
        /// </summary>
        void NormalizeFractions();

        /// <summary>
        /// This method normalizes peptide intensities so that the median fold-change between any two biological replicates
        /// (regardless of condition) is ~zero. The median is used instead of the average because it is more robust to outliers.
        /// The assumption in this method is that the median fold-change between bioreps of different conditions
        /// is zero (i.e., that most peptides do not change in abundance between conditions).
        /// </summary>
        void NormalizeBioreps();

        /// <summary>
        /// This method takes a list of peptides and creates a subset list of peptides to normalize with, to avoid
        /// excessive computation time in normalization functions.
        /// </summary>
        std::vector<Peptide*> SubsetData(std::vector<Peptide*> &initialList, std::vector<SpectraFileInfo*> &spectraFiles);

        /// <summary>
        /// Calculates normalization factors for fractionated data using a bounded Nelder-Mead optimization algorithm.
        /// Called by NormalizeFractions().
        /// </summary>
        static std::vector<double> GetNormalizationFactors(std::vector<std::vector<std::vector<double>>> &peptideIntensities, int numP, int numB, int numF, int maxThreads);
    };
}
