#include "CZE.h"

namespace Proteomics
{
    namespace RetentionTimePrediction
    {

        CZE::CZE(double columnLength, double voltsPerMeter) : ColumnLength(columnLength), VoltsPerMeter(voltsPerMeter)
        {
        }

        double CZE::ExperimentalElectrophoreticMobility(double timeMin)
        {
            if (ColumnLength >= 0 && timeMin >= 0)
            {
                return ColumnLength / (60 * timeMin * VoltsPerMeter) * 1e9;
            }
            else
            {
                return -1;
            }
        }

        double CZE::TheoreticalElutionTime(double electrophoreticMobility)
        {
            if (ColumnLength >= 0)
            {
                return (ColumnLength * 1e9) / (60 * VoltsPerMeter * electrophoreticMobility);
            }
            else
            {
                return -1;
            }
        }

        double CZE::PredictedElectrophoreticMobility(const std::string &peptideSequence, double observedMass)
        {
            double predictedMu = 0;

            //calculation described in Anal Chem. 2017 Feb 7;89(3):2000-2008
            //3.069 and 386 are coefficients applied to align output with experimentally measured values(slope 1 and intercept 0 in). I think we may need to reset these.
            //other values from best fit model of Cifuentes and Poppe (J. Chromatogr. A 1994, 680, 321−340) used as described in the AC paper.
            predictedMu = 3.069 + 386 * std::log(1 + 0.35 * PredictedChargeCorrected(peptideSequence)) / (std::pow(observedMass, 0.411) + Offset(PredictedChargeCorrected(peptideSequence), peptideSequence.length()));

            return predictedMu;
        }

        double CZE::PredictedCharge(const std::string &peptideSequence)
        {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            std::string substitutedString = StringHelper::replace(StringHelper::replace(peptideSequence, "R", ""), "K", "")->Replace("H", "")->ToString();
            return (1 + (peptideSequence.length() - substitutedString.length()));
        }

        double CZE::PredictedChargeCorrected(const std::string &peptideSequence)
        {
            double runningSum = 0;
            std::string internalString = peptideSequence.substr(3, peptideSequence.length() - 5);

            char firstAA = peptideSequence[0];
            if (firstAA == 'D')
            {
                runningSum -= 0.26741;
            }
            else if (firstAA == 'E')
            {
                runningSum -= 0.06852;
            }
            else if (firstAA == 'N')
            {
                runningSum += 0.011699;
            }
            else
            {
                //change nothing
            }

            char secondAA = peptideSequence[1];
            if (secondAA == 'D')
            {
                runningSum -= 0.10947;
            }
            else if (secondAA == 'E')
            {
                runningSum -= 0.04011;
            }
            else if (secondAA == 'N')
            {
                runningSum += 0.012535;
            }
            else if (secondAA == 'Q')
            {
                runningSum += 0.011699;
            }
            else
            {
                //change nothing
            }

            char thirdAA = peptideSequence[2];
            if (thirdAA == 'D')
            {
                runningSum -= 0.08022;
            }
            else if (thirdAA == 'E')
            {
                runningSum -= 0.03426;
            }
            else if (thirdAA == 'N')
            {
                runningSum += 0.016713;
            }
            else if (thirdAA == 'Q')
            {
                runningSum += 0.00585;
            }
            else
            {
                //change nothing
            }

            char secondToLastAA = peptideSequence[peptideSequence.length() - 2];
            if (secondToLastAA == 'D')
            {
                runningSum -= 0.03844;
            }
            else if (secondToLastAA == 'E')
            {
                runningSum -= 0.01337;
            }
            else if (secondToLastAA == 'N')
            {
                runningSum += 0.026741;
            }
            else if (secondToLastAA == 'Q')
            {
                runningSum -= 0.00084;
            }
            else
            {
                //change nothing
            }

            char lastAA = peptideSequence[peptideSequence.length() - 1];
            if (lastAA == 'D')
            {
                runningSum -= 0.02256;
            }
            else if (lastAA == 'E')
            {
                runningSum -= 0.00418;
            }
            else if (lastAA == 'N')
            {
                runningSum += 0.010864;
            }
            else if (lastAA == 'Q')
            {
                runningSum -= 0.0117;
            }
            else
            {
                //change nothing
            }

            //consider internal residues
            if (internalString.find("D") != std::string::npos)
            {
                runningSum -= 0.05014;
            }
            if (internalString.find("E") != std::string::npos)
            {
                runningSum -= 0.01922;
            }
            if (internalString.find("N") != std::string::npos)
            {
                runningSum += 0.012535;
            }
            if (internalString.find("Q") != std::string::npos)
            {
                runningSum -= 0.000251;
            }

            runningSum += PredictedCharge(peptideSequence);

            return runningSum;
        }

        double CZE::Offset(double correctedCharge, int length)
        {
            return 0;
            //should fit 5th order polynomical to plot of (ExperimentalElectrophoreticMobility - PredictedElectrophoreticMobility) vs. (Zc/N) where N is peptidelength.
        }
    }
}
