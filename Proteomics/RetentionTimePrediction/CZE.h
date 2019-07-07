#pragma once

#include <string>
#include <cmath>
#include "stringhelper.h"


namespace Proteomics
{
    namespace RetentionTimePrediction
    {
        /// <summary>
        /// This class will return theoretical retention times, hydrobphobicites, electrophoretic mobilities and etc. for peptides.
        /// These values would be useful for comparision with experimentally observed retention times. This information might be
        /// informative for evaluation of false positives and also for discerning the prescence of certain PTMs that would
        /// alter the experimental chromatographic behavior.
        ///
        /// This class returns calculated electrophoretic mobility for an observed peptide. The calculation requires use of an
        /// observed retention time(min), the total capillary length(m) and the applied voltage (V/m)
        ///
        /// The public methods of this class are limited to electrophoretic mobilities of peptides detected in a CZE-MS/MS experiment.
        /// </summary>
        class CZE
        {
        private:
            const double ColumnLength; //in meters
            const double VoltsPerMeter; //in volts/meter
        public:
            CZE(double columnLength, double voltsPerMeter);

            /// <summary>
            /// This method returns calculated electrophoretic mobility for an observed peptide. The calculation requires use of an
            /// observed retention time(min), the total capillary length(m) and the applied voltage (V/m)
            /// </summary>
            /// <param name="timeMin"></param>
            /// <returns></returns>
            double ExperimentalElectrophoreticMobility(double timeMin);

            /// <summary>
            /// This method returns an expected retention time for a given electrophoretic mobility and experiment. The calculation requires use of an
            /// electrophoretic mobility, the total capillary length(m) and the applied voltage (V/m)
            /// </summary>
            /// <param name="electrophoreticMobility"></param>
            /// <returns></returns>
            double TheoreticalElutionTime(double electrophoreticMobility);

            /// <summary>
            /// This calculated the predicted electrophoretic mobility of a peptide.
            ///
            /// See for reference
            /// Anal Chem. 2017 Feb 7;89(3):2000-2008. doi: 10.1021/acs.analchem.6b04544. Epub 2017 Jan 19.
            /// Predicting Electrophoretic Mobility of Tryptic Peptides for High-Throughput CZE-MS Analysis.
            /// Krokhin OV, Anderson G, Spicer V, Sun L1, Dovichi NJ2.
            /// https://www.ncbi.nlm.nih.gov/pubmed/28208305
            ///
            /// </summary>
            /// <param name="peptideSequence"></param>
            /// <param name="observedMass"></param>
            /// <returns></returns>
            static double PredictedElectrophoreticMobility(const std::string &peptideSequence, double observedMass);

            /// <summary>
            /// The predicted charge is plus 1 for the N-terminal and plus for the count of lysine(K), arginine(R) and histidine(H).
            /// </summary>
            /// <param name="peptideSequence"></param>
            /// <returns></returns>
        private:
            static double PredictedCharge(const std::string &peptideSequence);

            /// <summary>
            /// minimal charge correction is position dependenat and predominantly at the peptide termini. Adjustments are made for presence of D, E, N and Q
            /// at the ends and in the middle.
            ///
            /// In the future, I would like to use linear algebra to estimate these more accurately for each dataset separately. Currently
            /// these numbers are from a table in Anal Chem. 2017 Feb 7;89(3):2000-2008. doi: 10.1021/acs.analchem.6b04544. Epub 2017 Jan 19.
            ///
            /// </summary>
            /// <param name="peptideSequence"></param>
            /// <returns></returns>
            static double PredictedChargeCorrected(const std::string &peptideSequence);

            /// <summary>
            ///
            /// The offset in the AC paper is a 5th order polynomial best fit to a plot of Zc/N versus the difference between experimental and predicted electrophoretic mobility.
            /// This smells of dead fish. I'm leaving it out for not but it might need to be used as some point.
            ///
            /// </summary>
            /// <param name="correctedCharge"></param>
            /// <param name="length"></param>
            /// <returns></returns>
            static double Offset(double correctedCharge, int length);
        };
    }
}
