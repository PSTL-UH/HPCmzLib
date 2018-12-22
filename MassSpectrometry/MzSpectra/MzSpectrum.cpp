#include "MzSpectrum.h"
#include "../../Chemistry/ChemicalFormula.h"
#include "../../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry {

    MzSpectrum<TPeak>::StaticConstructor::StaticConstructor() {
        // AVERAGINE
        constexpr double averageC = 4.9384;
        constexpr double averageH = 7.7583;
        constexpr double averageO = 1.4773;
        constexpr double averageN = 1.3577;
        constexpr double averageS = 0.0417;
        
        constexpr double fineRes = 0.125;
        constexpr double minRes = 1e-8;
        
        for (int i = 0; i < numAveraginesToGenerate; i++) {
            double averagineMultiplier = (i + 1) / 2.0;
            //Console.Write("numAveragines = " + numAveragines);
            ChemicalFormula *chemicalFormula = new ChemicalFormula();
            chemicalFormula->Add(L"C", FloatingPointToInteger::ToInt32(averageC * averagineMultiplier));
            chemicalFormula->Add(L"H", FloatingPointToInteger::ToInt32(averageH * averagineMultiplier));
            chemicalFormula->Add(L"O", FloatingPointToInteger::ToInt32(averageO * averagineMultiplier));
            chemicalFormula->Add(L"N", FloatingPointToInteger::ToInt32(averageN * averagineMultiplier));
            chemicalFormula->Add(L"S", FloatingPointToInteger::ToInt32(averageS * averagineMultiplier));
        
            {
                auto chemicalFormulaReg = chemicalFormula;
                IsotopicDistribution *ye = IsotopicDistribution::GetDistribution(chemicalFormulaReg, fineRes, minRes);
                auto masses = ye->getMasses().ToArray();
                auto intensities = ye->getIntensities().ToArray();
                Array::Sort(intensities, masses);
                Array::Reverse(intensities);
                Array::Reverse(masses);
        
                mostIntenseMasses[i] = masses[0];
                diffToMonoisotopic[i] = masses[0] - chemicalFormulaReg->getMonoisotopicMass();
                allMasses[i] = masses;
                allIntensities[i] = intensities;
            }

            delete chemicalFormula;
        }
        
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(155, std::vector<double> {0.915094568, 0.07782302, 0.006528797, 0.000289506}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(226, std::vector<double> {0.88015657, 0.107467263, 0.011417303, 0.000730494}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(310, std::vector<double> {0.837398069, 0.142430845, 0.01821746, 0.001683771}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(437, std::vector<double> {0.777595132, 0.186958768, 0.031114269, 0.003704342, 0.000220493}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(620, std::vector<double> {0.701235526, 0.238542629, 0.050903269, 0.008082801, 0.000985192}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(888, std::vector<double> {0.602453248, 0.291899044, 0.084076553, 0.01790019, 0.002916629, 0.000410371}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(1243, std::vector<double> {0.492328432, 0.333344333, 0.128351944, 0.035959923, 0.008063481, 0.001433271, 0.000195251}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(1797, std::vector<double> {0.348495022, 0.336686099, 0.193731423, 0.082270917, 0.028068866, 0.008052644, 0.001907311, 0.000372359, 4.52281E-05}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(2515, std::vector<double> {0.229964408, 0.313975523, 0.238643189, 0.130654102, 0.056881604, 0.020732138, 0.006490044, 0.001706308, 0.000373761, 4.55951E-05}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(3532, std::vector<double> {0.12863395, 0.247015676, 0.254100853, 0.184302695, 0.104989402, 0.049731171, 0.020279668, 0.007267861, 0.002300006, 0.000619357, 9.64322E-05}));
        intensityFractions.push_back(std::tuple<double, std::vector<double>>(5019, std::vector<double> {0.053526677, 0.145402081, 0.208920636, 0.209809764, 0.164605485, 0.107024765, 0.059770563, 0.029447041, 0.012957473, 0.005127018, 0.001845335, 0.000572486, 0.000115904}));
    }
}
