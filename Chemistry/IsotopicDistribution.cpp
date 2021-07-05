/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */

#include "IsotopicDistribution.h"
#include "ChemicalFormula.h"
#include "Isotope.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <iomanip>

namespace Chemistry {

    std::vector<double> IsotopicDistribution::factorLnArray;
    int IsotopicDistribution::_factorLnTop;
    
    IsotopicDistribution::IsotopicDistribution(int count) : masses(std::vector<double>(count, 0.0)),
        intensities(std::vector<double>(count, 0.0)) {
    }

    std::vector<double> IsotopicDistribution::getMasses() const {
        return masses;
    }

    std::vector<double> IsotopicDistribution::getIntensities() const {
        return intensities;
    }

    IsotopicDistribution *IsotopicDistribution::GetDistribution(ChemicalFormula *formula) {
        return GetDistribution(formula, defaultFineResolution, defaultMinProbability, defaultMolecularWeightResolution);
    }

    IsotopicDistribution *IsotopicDistribution::GetDistribution(ChemicalFormula *formula, double fineResolution) {
        return GetDistribution(formula, fineResolution, defaultMinProbability, defaultMolecularWeightResolution);
    }

    IsotopicDistribution *IsotopicDistribution::GetDistribution(ChemicalFormula *formula, double fineResolution,
                                                                double minProbability) {
        return GetDistribution(formula, fineResolution, minProbability, defaultMolecularWeightResolution);
    }

    IsotopicDistribution *IsotopicDistribution::GetDistribution(ChemicalFormula *formula, double fineResolution,
                                                                double minProbability, double molecularWeightResolution) {
        auto a = GetNewFineAndMergeResolutions(fineResolution);
        fineResolution = std::get<0>(a);
        double _mergeFineResolution = std::get<1>(a);
        std::vector<std::vector<Composition*>> elementalComposition;

        // Get all the unique elements that might have isotopes
        std::list<std::tuple<Element*, int>> allElements;
        // reversing the order of how eleemnts are processed, since there seems to be a difference
        // on how C++ and C# report the elements from a HashSet and an unordered_map, and the order seems to matter!
        for (auto e : formula->getElements()) {
            allElements.push_front(std::make_tuple(e.first, e.second));
        }

        for (auto  elementAndCount : allElements )  {
            //int count = elementAndCount.second;
            int count = std::get<1>(elementAndCount);
            auto  isotopeComposition = new std::vector<Composition*>();

            // for (Isotope *isotope : std::sort(elementAndCount.first->getIsotopes().begin(),
            // elementAndCount.first->getIsotopes().end(),[ ] (const Isotope* &l, const Isotope* &r) {
            //         return l->getAtomicMass() > r->getAtomicMass(); }  ))  {
            // EG WARNING: Isotopes are sorted in the C++ version based on their order in the input
            // file, which is most of the time also based on the Atomic Mass, but there is no
            // guarantee for that.
            for (Isotope *isotope : std::get<0>(elementAndCount)->getIsotopes() )  {
                Composition *c = new Composition();
                c->Atoms = count;
                c->MolecularWeight = isotope->getAtomicMass();
                c->Power = isotope->getAtomicMass();
                c->Probability = isotope->getRelativeAbundance();

                isotopeComposition->push_back(c);
            }
            elementalComposition.push_back(*isotopeComposition);
        }

        for (auto compositions : elementalComposition) {
            double sumProb = 0.0;
            for ( auto c : compositions ) {
                sumProb += c->Probability;
            }
            for (auto composition : compositions) {
                composition->Probability /= sumProb;
                composition->LogProbability = std::log(composition->Probability);
                composition->Power = std::floor(composition->MolecularWeight / molecularWeightResolution + 0.5);
            }
        }

        IsotopicDistribution *dist = CalculateFineGrain(elementalComposition, molecularWeightResolution,
                                                        _mergeFineResolution, fineResolution,
                                                        minProbability);

        double additionalMass = 0;
        for (auto isotopeAndCount : formula->getIsotopes()) {
            additionalMass += isotopeAndCount.first->getAtomicMass() * isotopeAndCount.second;
        }

        for (long unsigned int i = 0; i < dist->masses.size(); i++) {
            dist->masses[i] += additionalMass;
        }

        return dist;
    }

    std::tuple<double, double> IsotopicDistribution::GetNewFineAndMergeResolutions(double fineResolution) {
        return std::tuple<double, double>(fineResolution / 2.0, fineResolution);
    }

    void IsotopicDistribution::MergeFinePolynomial(std::vector<IsotopicDistribution::Polynomial> &tPolynomial,
                                                   double _mwResolution,
                                                   double _mergeFineResolution) {
        // Sort by mass (i.e. power)
        // ORIGINAL LINE: tPolynomial.Sort((a, b) => a.Power.CompareTo(b.Power));
        std::sort(tPolynomial.begin(), tPolynomial.end(), [ ] (auto &a, auto &b) {
                return a.Power < b.Power;
        });

        int count = tPolynomial.size();
        
        for (int k = 1; k <= 9; k++) {
            for (int i = 0; i < count; i++) {
                double power = tPolynomial[i].Power;

                if (std::isnan(power)) {
                    continue;
                }

                double probability = tPolynomial[i].Probablity;
                Polynomial tempPolynomial;
                tempPolynomial.Power = power * probability;
                tempPolynomial.Probablity = probability;

                for (int j = i + 1; j < count; j++) {
                    double value = std::abs(tPolynomial[i].Power * _mwResolution - tPolynomial[j].Power * _mwResolution);

                    double threshold = (k <= 8) ? k * _mergeFineResolution / 8 : _mergeFineResolution + _mergeFineResolution / 100;

                    // Combine terms if their mass difference (i.e. power difference) is less than some threshold
                    if (value <= threshold) {
                        tempPolynomial.Power = tempPolynomial.Power + tPolynomial[j].Power * tPolynomial[j].Probablity;
                        tempPolynomial.Probablity = tempPolynomial.Probablity + tPolynomial[j].Probablity;
                        Polynomial tempVar;
                        tempVar.Power = tempPolynomial.Power / tempPolynomial.Probablity;
                        tempVar.Probablity = tempPolynomial.Probablity;
                        tPolynomial[i] = tempVar;
                        Polynomial tempVar2;
                        tempVar2.Probablity = NAN;
                        tempVar2.Power = NAN;
                        tPolynomial[j] = tempVar2;
                    }
                    else {
                        break;
                    }
                }

                Polynomial tempVar3;
                tempVar3.Power = tempPolynomial.Power / tempPolynomial.Probablity;
                tempVar3.Probablity = tempPolynomial.Probablity;
                tPolynomial.at(i) = tempVar3;
            }
        }

        // return only non-zero terms
        //for ( int t= (int)tPolynomial.size()-1; t>=0; t-- ) {
        //    if ( std::isnan ( tPolynomial[t].Power )) {
        //        tPolynomial.erase (tPolynomial.begin() + t) ;
        //    }
        //}
        // This version is faster in C++ than the version above.
        std::vector<IsotopicDistribution::Polynomial> temp = tPolynomial;
        tPolynomial.clear();
        for ( auto t : temp ) {
            if ( !std::isnan(t.Power) ) {
                tPolynomial.push_back(t);
            }
        }
        
        return;
    }

    std::vector<IsotopicDistribution::Polynomial> IsotopicDistribution::MultiplyFinePolynomial(std::vector<std::vector<IsotopicDistribution::Composition*>> &elementalComposition,
                                                                                               double _fineResolution, double _mwResolution,
                                                                                               double _fineMinProb) {
        constexpr int nc = 10;
        constexpr int ncAddValue = 1;
        constexpr int nAtoms = 200;
        std::vector<IsotopicDistribution::Polynomial> tPolynomial;

        int n = 0;
        int k;

        for (auto composition : elementalComposition) {
            if (composition.size() > 0) {
                n++;
            }
        }

        std::vector<std::vector<IsotopicDistribution::Polynomial>> fPolynomial;
        for (int i = 0; i < n; i++) {
            fPolynomial.push_back(std::vector<IsotopicDistribution::Polynomial>());
        }

        for (k = 0; k < n; k++) {
            tPolynomial.clear();

            std::vector<Composition*> composition = elementalComposition[k];
            int size = composition.size();
            int atoms = composition[0]->Atoms;

            int ncAdd = atoms < nAtoms ? 10 : ncAddValue;

            if (size == 1) {
                double probability = composition[0]->Probability;

                int n1 = static_cast<int>(atoms * probability);

                double prob = FactorLn(atoms) - FactorLn(n1) + n1 * composition[0]->LogProbability;
                prob = std::exp(prob);

                Polynomial tempVar;
                tempVar.Power = n1 * composition[0]->Power;
                tempVar.Probablity = prob;
                fPolynomial[k].push_back(tempVar);
            }
            else {
                std::vector<int> means(size);
                std::vector<int> stds(size);
                for (int i = 0; i < size; i++) {
                    int n1 = static_cast<int>(elementalComposition[k][0]->Atoms * elementalComposition[k][i]->Probability);
                    int s1 = static_cast<int>(std::ceil(ncAdd + nc * std::sqrt(elementalComposition[k][i]->Atoms * elementalComposition[k][i]->Probability * (1.0 - elementalComposition[k][i]->Probability))));

                    means[i] = n1;
                    stds[i] = s1;
                }
                std::vector<int> mins(means.size() - 1);
                std::vector<int> maxs(means.size() - 1);
                std::vector<int> indices = std::vector<int>(means.size() - 1);
                for (long unsigned int i = 0; i < means.size() - 1; i++) {
                    auto max = std::max(0, means[i] - stds[i]);
                    indices[i] = max;
                    mins[i] = max;
                    maxs[i] = means[i] + stds[i];
                }

                MultipleFinePolynomialRecursiveHelper(mins, maxs, indices, 0, fPolynomial[k], composition, atoms,
                                                      _fineMinProb, means[means.size() - 1] + stds[stds.size() - 1]);
            }
        }

        tPolynomial = fPolynomial[0];

        if (k <= 1) {
            return tPolynomial;
        }

        std::vector<Polynomial> fgidPolynomial;
        for (k = 1; k < n; k++) {
            MultiplyFineFinalPolynomial(tPolynomial, fPolynomial[k], fgidPolynomial, _fineResolution,
                                        _mwResolution, _fineMinProb);
        }

        return tPolynomial;
    }

    void IsotopicDistribution::MultiplyFineFinalPolynomial(std::vector<IsotopicDistribution::Polynomial> &tPolynomial,
                                                           std::vector<IsotopicDistribution::Polynomial> &fPolynomial,
                                                           std::vector<IsotopicDistribution::Polynomial> &fgidPolynomial,
                                                           double _fineResolution, double _mwResolution, double _fineMinProb) {
        long unsigned int i = tPolynomial.size();
        long unsigned int j = fPolynomial.size();

        if (i == 0 || j == 0) {
            return;
        }

        double deltaMass = (_fineResolution / _mwResolution);
        double minProbability = _fineMinProb;

        double minMass = tPolynomial[0].Power + fPolynomial[0].Power;
        double maxMass = tPolynomial[i - 1].Power + fPolynomial[j - 1].Power;

        long unsigned int maxIndex = static_cast<int>(std::abs(maxMass - minMass) / deltaMass + 0.5);
        if (maxIndex >= fgidPolynomial.size()) {
            j = maxIndex - fgidPolynomial.size();
            for (i = 0; i <= j; i++) {
                Polynomial tempVar;
                tempVar.Probablity = NAN;
                tempVar.Power = NAN;
                fgidPolynomial.push_back(tempVar);
            }
        }

        for (long unsigned int t = 0; t < tPolynomial.size(); t++) {
            for (long unsigned int f = 0; f < fPolynomial.size(); f++) {
                double prob = tPolynomial[t].Probablity * fPolynomial[f].Probablity;
                if (prob <= minProbability) {
                    continue;
                }

                double power = tPolynomial[t].Power + fPolynomial[f].Power;
                auto indext = static_cast<int>(std::abs(power - minMass) / deltaMass + 0.5);

                Polynomial tempPolynomial = fgidPolynomial.at(indext);

                auto poww = tempPolynomial.Power;
                auto probb = tempPolynomial.Probablity;
                if (std::isnan(poww) || std::isnan(prob)) {
                    Polynomial tempVar2;
                    tempVar2.Power = power * prob;
                    tempVar2.Probablity = prob;
                    fgidPolynomial.at(indext) = tempVar2;
                }
                else {
                    Polynomial tempVar3;
                    tempVar3.Power = poww + power * prob;
                    tempVar3.Probablity = probb + prob;
                    fgidPolynomial.at(indext) = tempVar3;
                }
            }
        }

        auto index = tPolynomial.size();
        j = 0;
        for (i = 0; i < fgidPolynomial.size(); i++) {
            if (!std::isnan(fgidPolynomial[i].Probablity)) {
                if (j < index) {
                    Polynomial tempVar4;
                    tempVar4.Power = fgidPolynomial[i].Power / fgidPolynomial[i].Probablity;
                    tempVar4.Probablity = fgidPolynomial[i].Probablity;
                    tPolynomial.at(j) = tempVar4;
                    j++;
                }
                else {
                    Polynomial tempVar5;
                    tempVar5.Power = fgidPolynomial[i].Power / fgidPolynomial[i].Probablity;
                    tempVar5.Probablity = fgidPolynomial[i].Probablity;
                    tPolynomial.push_back(tempVar5);
                }
            }

            Polynomial tempVar6;
            tempVar6.Probablity = NAN;
            tempVar6.Power = NAN;
            fgidPolynomial.at(i) = tempVar6;
        }

        if (j < index) {
            // tPolynomial.RemoveRange(j, tPolynomial.size() - j);
            tPolynomial.erase(tPolynomial.begin()+j, tPolynomial.end());
        }
    }

    void IsotopicDistribution::MultipleFinePolynomialRecursiveHelper(std::vector<int> &mins,
                                                                     std::vector<int> &maxs,
                                                                     std::vector<int> &indices,
                                                                     int index,
                                                                     std::vector<Polynomial> &fPolynomial,
                                                                     std::vector<Composition*> &elementalComposition,
                                                                     int atoms, double minProb, int maxValue) {
        for (indices[index] = mins[index]; indices[index] <= maxs[index]; indices[index]++) {
            if ((long unsigned int) index < mins.size() - 1) {
                MultipleFinePolynomialRecursiveHelper(mins, maxs, indices, index + 1,
                                                      fPolynomial, elementalComposition, atoms,
                                                      minProb, maxValue);
            }
            else {
                // int l = atoms - indices.Sum();
                int sum=0;
                for ( auto ii: indices ) {
                    sum += ii;
                }
                int l = atoms - sum;
                if (l < 0 || l > maxValue) {
                    continue;
                }

                double prob = FactorLn(atoms) - FactorLn(l) + l * elementalComposition[elementalComposition.size() - 1]->LogProbability;
                double power = l * elementalComposition[elementalComposition.size() - 1]->Power;
                for (long unsigned int i = 0; i <= elementalComposition.size() - 2; i++) {
                    int indexValue = indices[i];
                    Composition *tComposition = elementalComposition[i];
                    prob -= FactorLn(indexValue);
                    prob += indexValue * tComposition->LogProbability;
                    power += indexValue * tComposition->Power;
                }

                prob = std::exp(prob);
                if (prob >= minProb) {
                    Polynomial tPolynomial;
                    tPolynomial.Probablity = prob;
                    tPolynomial.Power = power;
                    fPolynomial.push_back(tPolynomial);
                }
            }
        }
    }

    double IsotopicDistribution::FactorLn(int n) {
        if (n <= 1) {
            return 0;
        }
        if (factorLnArray.empty()) {
            factorLnArray.resize(50003, 0.0);
            _factorLnTop = 1;
        }
        while (_factorLnTop <= n) {
            int j = _factorLnTop++;
            factorLnArray[j + 1] = factorLnArray[j] + std::log(_factorLnTop);
        }
        return factorLnArray[n];
    }

    IsotopicDistribution *IsotopicDistribution::CalculateFineGrain(std::vector<std::vector<Composition*>> &elementalComposition,
                                                                   double _mwResolution, double _mergeFineResolution,
                                                                   double _fineResolution, double _fineMinProb)
    {
        std::vector<Polynomial> fPolynomial = MultiplyFinePolynomial(elementalComposition, _fineResolution,
                                                                     _mwResolution, _fineMinProb);
        //fPolynomial = MergeFinePolynomial(fPolynomial, _mwResolution, _mergeFineResolution);
        MergeFinePolynomial(fPolynomial, _mwResolution, _mergeFineResolution);

        // Convert polynomial to spectrum
        int count = fPolynomial.size();
        IsotopicDistribution *dist = new IsotopicDistribution(count);
        double totalProbability = 0;
        double basePeak = 0;
        int i = 0;
        for (auto polynomial : fPolynomial) {
            totalProbability += polynomial.Probablity;
            if (polynomial.Probablity > basePeak) {
                basePeak = polynomial.Probablity;
            }
            dist->masses[i] = polynomial.Power * _mwResolution;
            dist->intensities[i] = polynomial.Probablity;
            i++;
        }

        return dist;
    }
}
