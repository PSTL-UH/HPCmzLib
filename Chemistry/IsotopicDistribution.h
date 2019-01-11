#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "ChemicalFormula.h"
//namespace Chemistry { class ChemicalFormula; }
//namespace Chemistry { class Polynomial; }
//namespace Chemistry { class Composition; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (IsotopicDistribution.cs) is part of Chemistry Library.
//
// Chemistry Library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chemistry Library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>.


namespace Chemistry {
    /// <summary>
    /// Calculates the isotopic distributions of molecules
    /// </summary>
    /// <remarks>
    /// C# version by Derek Bailey 2014
    /// Modified by Stefan Solntsev 2016
    ///
    /// This is a port of software written in C++ and detailed in the following publication:
    ///
    /// Molecular Isotopic Distribution Analysis (MIDAs) with Adjustable Mass Accuracy.
    /// Gelio Alves, Aleksy Y. Ogurtsov, and Yi-Kuo Yu
    /// J. Am. Soc. Mass Spectrom. (2014) 25:57-70
    /// DOI: 10.1007/s13361-013-0733-7
    ///
    /// Please cite that publication if using these algorithms in your own publications.
    ///
    /// Only calculates the fine grained distribution.
    /// </remarks>
    class IsotopicDistribution {

    private:
        class Polynomial {

        public:
            double Power = 0;
            double Probablity = 0;

        };

    private:
        class Composition {

        public:
            double Power = 0;
            double Probability = 0;
            double LogProbability = 0;
            double MolecularWeight = 0;
            int Atoms = 0;
        };
 
    private:
        static constexpr double defaultFineResolution = 0.01;
        static constexpr double defaultMinProbability = 1e-200;
        static constexpr double defaultMolecularWeightResolution = 1e-12;
        static std::vector<double> const factorLnArray;
        static int _factorLnTop;
        std::vector<double> const masses;
        std::vector<double> const intensities;

        IsotopicDistribution(int count);

    public:
        std::vector<double> getMasses() const;
        std::vector<double> getIntensities() const;

        static IsotopicDistribution *GetDistribution(ChemicalFormula *formula);

        static IsotopicDistribution *GetDistribution(ChemicalFormula *formula, double fineResolution);

        static IsotopicDistribution *GetDistribution(ChemicalFormula *formula, double fineResolution, double minProbability);

        static IsotopicDistribution *GetDistribution(ChemicalFormula *formula, double fineResolution, double minProbability,
                                                     double molecularWeightResolution);

        /// <summary>
        /// Calculates the fineResolution and mergeFineResolution parameters
        /// </summary>
        /// <returns>Tuple of fineResolution and mergeFineResolution</returns>
    private:
        static std::tuple<double, double> GetNewFineAndMergeResolutions(double fineResolution);

        static std::vector<Polynomial> MergeFinePolynomial(std::vector<Polynomial> &tPolynomial, double _mwResolution,
                                                           double _mergeFineResolution);

        static std::vector<Polynomial> MultiplyFinePolynomial(std::vector<std::vector<Composition*>> &elementalComposition,
                                                              double _fineResolution, double _mwResolution, double _fineMinProb);

        static void MultiplyFineFinalPolynomial(std::vector<Polynomial> &tPolynomial, std::vector<Polynomial> &fPolynomial,
                                                std::vector<Polynomial> &fgidPolynomial, double _fineResolution, double _mwResolution,
                                                double _fineMinProb);

        static void MultipleFinePolynomialRecursiveHelper(std::vector<int> &mins, std::vector<int> &maxs, std::vector<int> &indices,
                                                          int index, std::vector<Polynomial> &fPolynomial,
                                                          std::vector<Composition*> &elementalComposition, int atoms, double minProb,
                                                          int maxValue);

        static double FactorLn(int n);

        static IsotopicDistribution *CalculateFineGrain(std::vector<std::vector<Composition*>> &elementalComposition,
                                                        double _mwResolution, double _mergeFineResolution, double _fineResolution,
                                                        double _fineMinProb);

    };
}
