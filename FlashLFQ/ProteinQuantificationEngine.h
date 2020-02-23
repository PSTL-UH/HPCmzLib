#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <tuple>
#include <mutex>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "FlashLfqResults.h"
//namespace FlashLFQ { class FlashLfqResults; }
#include "Peptide.h"
//namespace FlashLFQ { class Peptide; }

//using namespace Accord::Math;
//using namespace Accord::Math::Decompositions;
//using namespace MathNet::Numerics::Statistics;

namespace FlashLFQ
{
    /// <summary>
    /// This is the "advanced" protein quantification engine used by FlashLFQ. It weights peptides by how well they co-vary with other peptides assigned to the same protein.
    /// The protein intensity is simply a weighted sum of the peptide intensities. For a peptide to be used in protein quant, it must have a weight of at least 0.5.
    /// This uses a C# translation of a portion of Diffacto, which in turn is a python translation of an R program called FARMS.
    /// 
    /// Diffacto: 
    ///    Zhang B, Pirmoradian M, Zubarev R, and Käll L (2017). Covariation
    ///    of Peptide Abundances Accurately Reflects Protein Concentration
    ///    Differences. Molecular and Cellular Proteomics, mcp-O117,
    ///    http://www.mcponline.org/content/16/5/936.full.
    /// FARMS: 
    ///    Hochreiter S, Clevert D, and Obermayer K (2006). A new summarization
    ///    method for affymetrix probe level data. Bioinformatics, 22(8),
    ///    http://bioinformatics.oxfordjournals.org/cgi/content/abstract/22/8/943.
    /// </summary>
    class ProteinQuantificationEngine
    {
    private:
        static constexpr double MIN_WEIGHT = 0.5;
        static constexpr double MU = 0.1;
        static constexpr double MIN_NOISE = 1e-4;
        static constexpr double ALPHA = 0.1;
        static constexpr int MAX_ITER = 1000;
        FlashLfqResults *const results;
        const int maxThreads;

        /// <summary>
        /// Constructs the protein quantification engine
        /// </summary>
    public:

        ProteinQuantificationEngine(FlashLfqResults *results, int maxThreads);

        /// <summary>
        /// Runs the protein quantification engine
        /// </summary>
        void Run();

        /// <summary>
        /// Bayesian Factor Analysis for Proteomics Summarization
        ///    A C# translation of function "generateExprVal.method.farms" from
        ///    Bioconductor FARMS.
        ///    [http://www.bioconductor.org/packages/release/bioc/html/farms.html]
        ///    [http://www.bioinf.jku.at/publications/papers/farms/supplementary.ps]
        ///
        /// Reference:
        ///    Hochreiter S, Clevert D, and Obermayer K (2006). A new summarization
        ///    method for affymetrix probe level data. Bioinformatics, 22(8),
        ///    http://bioinformatics.oxfordjournals.org/cgi/content/abstract/22/8/943.
        ///
        /// Inputs:
        ///    probes: peptide abundance array(N peptides, M samples) in log scale.
        ///    weight: Hyperparameter(backscale factor) value in the range of[0, 1]
        ///             which determines the influence of the prior.
        ///    mu:     Hyperparameter value which allows to quantify different aspects
        ///             of potential prior knowledge.A value near zero assumes that
        ///             most genes do not contain a signal, and introduces a bias for
        ///            loading matrix elements near zero.
        /// </summary>
        static std::tuple<std::vector<double>, double> FastFarms(std::vector<std::vector<double>> &readouts, double mu = 0, double weight = 0.5, int max_iter = 1000, bool force_iter = false, double min_noise = 1e-4, double fill_nan = 0.0);

        /// <summary>
        /// Builds a 2d matrix of covariance data 
        /// (how each peptide co-varies with the other peptides)
        /// </summary>
    private:
        static std::vector<std::vector<double>> GetCovarianceMatrix(std::vector<std::vector<double>> &data);

        /// <summary>
        /// Converts the list of peptides w/ intensities to a (peptide x intensity)
        /// 2d array structure for use in FARMS
        /// </summary>
        std::vector<std::vector<double>> GetIntensityArray(std::vector<Peptide*> &peptides);
    };
}
