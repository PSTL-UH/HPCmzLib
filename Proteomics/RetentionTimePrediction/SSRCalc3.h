#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { namespace RetentionTimePrediction { class CLUSTCOMB_List; } }
namespace Proteomics { namespace RetentionTimePrediction { class AAParams; } }

using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{
    namespace RetentionTimePrediction
    {
        /**
        /*
        /* reference, O. V. Krokhin, R. Craig, V. Spicer, W. Ens, K. G. Standing, R. C. Beavis, J. A. Wilkins
        /* An improved model for prediction of retention times of tryptic peptides in ion-pair reverse-phase HPLC:
        /* its application to protein peptide mapping by off-line HPLC-MALDI MS
        /* Molecular and Cellular Proteomics 2004 Sep;3(9):908-19.
        /* URL, http://hs2.proteome.ca/SSRCalc/SSRCalc.html
        /*
        /*
        /* These subroutines are based on web version SSRCalculator of the Copyright holder listed as in the following:
        /*
        /* Version 3.0   2005.02.28
        /* Copyright (c) 2005 John Wilkins
        /* Sequence Specific Retention Calculator
        /* Authors: Oleg Krokhin, Vic Spicer, John Cortens
         */

        /* Translated from perl to C, Ted Holzman FHCRC, 6/2006  */
        /* Retranslated from C to Java, Ted Holzman FHCRC 7/2006 */
        /* Translated from Java to C#, Brendan MacLean UW 10/2008 */
        /* NB: This is a version 0.1 direct translation.
        /*     An attempt has been made to keep function names, variable names, and algorithms
        /*     as close as possible to the original perl.
         */


        // ReSharper disable InconsistentNaming
        // ReSharper disable CharImplicitlyConvertedToNumeric
        class SSRCalc3
        {
        private:
            std::string privateName;
            int privateNOELECTRIC = 0;
            int privateNOCLUSTER = 0;
            int privateNODIGEST = 0;
            int privateNOSMALL = 0;
            int privateNOHELIX1 = 0;
            int privateNOHELIX2 = 0;
            int privateNOEHEL = 0;

            /* Lookup table data.  These are translations of the .h table in C which is a    */
            /* translation of the ReadParmFile perl routine.  This does not read a parameter */
            /* file; it makes static initializers for the parameter data.                    */

        public:
            static const std::string VERSION; // Not L10N

            std::vector<PeptideWithSetModifications*> ChooseRegressionPeptides(std::vector<PeptideWithSetModifications*> &peptides, int &minCount);

            std::vector<PeptideWithSetModifications*> GetStandardPeptides(std::vector<PeptideWithSetModifications*> &peptides);

            //public RetentionScoreCalculatorSpec Initialize(IProgressMonitor loadMonitor)
            //{
            //    return null;
            //}

        private:
            static CLUSTCOMB_List *const CLUSTCOMB;
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, double> HlxScore4 = new Dictionary<string, double>();
            static std::unordered_map<std::string, double> HlxScore4;
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, double> HlxScore5 = new Dictionary<string, double>();
            static std::unordered_map<std::string, double> HlxScore5;
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, double> HlxScore6 = new Dictionary<string, double>();
            static std::unordered_map<std::string, double> HlxScore6;
            static const std::vector<int> EMap;

        private:
            class CLUSTCOMB_List final : public std::vector<KeyValuePair<Regex*, double>*>
            {
            public:
                void Add(const std::string &pattern, double value);
            };

            private:
                class StaticConstructor
                {
                public:
                    StaticConstructor();
                };

            private:
                static SSRCalc3::StaticConstructor staticConstructor;


        public:
            enum class Column
            {
                A300,
                A100
            };

        public:
            std::vector<AAParams*> AAPARAMS = std::vector<AAParams*>(128);

            SSRCalc3(const std::string &name, Column column);

                std::string getName() const;
                void setName(const std::string &value);

        private:
            void A300Column();

            // Note: The 100 A version is not yet verified.
            void A100Column();

            // control variables, 0 means leaving them ON, 1 means turning them OFF
            // Translator1 note:  Some day these may be turned into options.  For the
            //    time being they are unchanging, and the tests for them in each function
            //    are superfluous and absurd.
            // Translator2 note:  To avoid warnings on unreachable code, these were changed
            //    to auto-implemented properties, which means they can now be set.

            public:
                int getNOELECTRIC() const;
                void setNOELECTRIC(int value);
                int getNOCLUSTER() const;
                void setNOCLUSTER(int value);
                int getNODIGEST() const;
                void setNODIGEST(int value);
                int getNOSMALL() const;
                void setNOSMALL(int value);
                int getNOHELIX1() const;
                void setNOHELIX1(int value);
                int getNOHELIX2() const;
                void setNOHELIX2(int value);
                int getNOEHEL() const;
                void setNOEHEL(int value);

            //Translator1 note:  This constant controls whether "bugs" in the original
            //perl code are maintained.  A conversation with the developers has revealed
            //that the constant data in the static initialization blocks has been "tuned"
            //to the algorithm in its undebugged state.  In other words, using a correct
            //algorithm would invalidate the results.
        private:
            static constexpr bool DUPLICATE_ORIGINAL_CODE = true;
            //Translator1 note:  Some code is supposed to be executed only when
            // $SSRCVERSION==3.  SSRCVERSION was commented out in my version of the perl
            // code.  This may need some reworking.  Speaking with the developers, it
            // was determined that it ought not to have been commented out.  So --
            // ALGORITHM_VERSION may be used to choose the older or newer code
            static constexpr int ALGORITHM_VERSION = 3;

            // Length Scaling length limits and scaling factors
            static constexpr int LPLim = 20;
            static constexpr int SPLim = 8;
            static constexpr double LPSFac = 0.0270;
            static constexpr double SPSFac = -0.055;

            // UnDigested (missed cuts) scaling Factors
            static constexpr double UDF21 = 0.0, UDF22 = 0.0; // rightmost
            static constexpr double UDF31 = 1.0, UDF32 = 0.0; // inside string

            // total correction values, 20..30 / 30..40 / 40..50 /50..500
            static constexpr double SUMSCALE1 = 0.27, SUMSCALE2 = 0.33, SUMSCALE3 = 0.38, SUMSCALE4 = 0.447;

            // clusterness scaling: i.e. weight to give cluster correction.
            static constexpr double KSCALE = 0.4;

            // isoelectric scaling factors
            static constexpr double Z01 = -0.03, Z02 = 0.60, NDELTAWT = 0.8; // negative delta values
            static constexpr double Z03 = 0.00, Z04 = 0.00, PDELTAWT = 1.0; // positive delta values

            // proline chain scores
            static constexpr double PPSCORE = 1.2, PPPSCORE = 3.5, PPPPSCORE = 5.0;

            // helix scaling factors
            static constexpr double HELIX1SCALE = 1.6, HELIX2SCALE = 0.255;

            /// <summary>
            /// No such thing as an unkown score for this calculator.  ScoreSequence
            /// always returns a value.
            /// </summary>
        public:
            double getUnknownScore() const;

            double ScoreSequence(PeptideWithSetModifications *item);

        private:
            double Smallness(int sqlen, double tsum);

            double Undigested(const std::string &sq);

            // ============================================================
            // compute clusterness of a string - v 2,3 algorithm
            // code W,L,F,I as 5
            // code M,Y,V as 1
            // code all others as 0

            double Clusterness(const std::string &sq);

            // ============================================================
            //  process based on proline - v 2,3 algorithm
            static double Proline(const std::string &sq);

            // ============================================================
            //  scaling based on length - v 1,2,3 algorithms
            static double Length_scale(int sqlen);

            // ============================================================
            // compute partial charge - v 2,3 algorithms
            static double Partial_charge(double pK, double pH);

            // ============================================================
            //    - v 2,3 algorithms
            double Electric(const std::string &sq);

            // ============================================================
            // compute R - v 2,3 algorithms
            double CalcR(double pH, double PK0, double PK1, std::vector<int> &CNTref);

            double NewIso(const std::string &sq, double tsum);

            // ============================================================
            // called by helicity1  - v 3 algorithm
            static double Heli1TermAdj(const std::string &ss1, int ix2, int sqlen);

            // ============================================================
            // helicity1 adjust for short helices or sections - v 3 algorithm
            //
            double Helicity1(const std::string &sq);

            // ============================================================
            // called by heli2calc  - v 3 algorithm
            double EvalH2pattern(const std::string &pattern, const std::string &testsq, int posn, char etype);

            // ============================================================
            // called by evalH2pattern  - v 3 algorithm
            double Connector(char acid, char lp, char rp, const std::string &ct, char far1, char far2);

            static constexpr int HISC = 0;
            static constexpr int GSC = 1;

            // ============================================================
            // called by helicity2  - v 3 algorithm
            std::vector<double> Heli2Calc(const std::string &sq);

            // ============================================================
            // helicity2 adjust for long helices - v 3 algorithm
            double Helicity2(const std::string &sq);

            double Helectric(const std::string &sq);

        public:
            class AAParams
            {
            private:
                double privateRC = 0;
                double privateRC1 = 0;
                double privateRC2 = 0;
                double privateRCN = 0;
                double privateRCN2 = 0;
                double privateRCS = 0;
                double privateRC1S = 0;
                double privateRC2S = 0;
                double privateRCNS = 0;
                double privateRCN2S = 0;
                double privateUndKRH = 0;
                double privateAMASS = 0;
                double privateCT = 0;
                double privateNT = 0;
                double privatePK = 0;
                double privateH2BASCORE = 0;
                double privateH2CMULT = 0;

                //Retention Factors
                public:
                    double getRC() const;
                    void setRC(double value);
                    double getRC1() const;
                    void setRC1(double value);
                    double getRC2() const;
                    void setRC2(double value);
                    double getRCN() const;
                    void setRCN(double value);
                    double getRCN2() const;
                    void setRCN2(double value);
                //Short peptide retention factors
                    double getRCS() const;
                    void setRCS(double value);
                    double getRC1S() const;
                    void setRC1S(double value);
                    double getRC2S() const;
                    void setRC2S(double value);
                    double getRCNS() const;
                    void setRCNS(double value);
                    double getRCN2S() const;
                    void setRCN2S(double value);

                    double getUndKRH() const;
                    void setUndKRH(double value);
                    double getAMASS() const;
                    void setAMASS(double value);
                                                           //isoelectric factors
                    double getCT() const;
                    void setCT(double value);
                    double getNT() const;
                    void setNT(double value);
                    double getPK() const;
                    void setPK(double value);
                //helicity2 bascore & connector multiplier
                    double getH2BASCORE() const;
                    void setH2BASCORE(double value);
                    double getH2CMULT() const;
                    void setH2CMULT(double value);

                AAParams(double rc, double rc1, double rc2, double rcn, double rcn2, double rcs, double rc1s, double rc2s, double rcns, double rcn2s, double undkrh, double amass, double ct, double nt, double pk, double h2bascore, double h2cmult);
            };
            /*
             * Translator2 note: The code for the Isoparams array was found in
             *      the Java version, but never used.  Refering to the Perl
             *      version showed that the only place these values were used
             *      was in the electric_scale() function, which in turn was never
             *      used.  Both the array and function are included here for
             *      completeness, but commented out, since they are never used.
             *
            private class Isoparams
            {
                public double emin { get; private set; }
                public double emax { get; private set; }
                public double eK { get; private set; }
    
                public Isoparams(double EMIN, double EMAX, double EK)
                {
                    emin = EMIN; emax = EMAX; eK = EK;
                }
            }
    
            private static readonly Isoparams[] ISOPARAMS = new[]
            {
                new Isoparams(3.8, 4.0, 0.880),
                new Isoparams(4.0, 4.2, 0.900),
                new Isoparams(4.2, 4.4, 0.920),
                new Isoparams(4.4, 4.6, 0.940),
                new Isoparams(4.6, 4.8, 0.960),
                new Isoparams(4.8, 5.0, 0.980),
                new Isoparams(5.0, 6.0, 0.990),
                new Isoparams(6.0, 7.0, 0.995),
                new Isoparams(7.0, 8.0, 1.005),
                new Isoparams(8.0, 9.0, 1.010),
                new Isoparams(9.0, 9.2, 1.020),
                new Isoparams(9.2, 9.4, 1.030),
                new Isoparams(9.4, 9.6, 1.040),
                new Isoparams(9.6, 9.8, 1.060),
                new Isoparams(9.8, 10.0, 1.080)
            };
    
            // convert electric to scaler - v 2,3 algorithms
            private static double electric_scale(double v)
            {
                double best=1.0;
    
                // Translator2 Note: this is commented out in the perl source
                // if (NOELECTRIC==1) { return 1.0; }
    
                foreach (Isoparams p in ISOPARAMS)
                {
                    if (v > p.emin && v < p.emax)
                        best= p.eK;
                }
    
                return best;            
            }
            */
        };

        class HelpersLocal final
        {
            /// <summary>
            /// Replace amino acids in a sequence string with some other value.
            /// </summary>
            /// <param name="s">The sequence string with AAs in uppercase</param>
            /// <param name="aas">The amino acid characters, or A-Z for all, to replace</param>
            /// <param name="newValue">The value to use as a replacement</param>
            /// <returns>Modified string with specified AAs replaced</returns>
        public:
            static std::string ReplaceAAs(std::vector<char> &s, const std::string &aas, const std::string &newValue);

            /// <summary>
            /// Inspects a sequence of amino acids, and returns true if it contains
            /// any of the designated amino acid characters.
            /// </summary>
            /// <param name="s">Amino acid sequence</param>
            /// <param name="aas">List of characters to search for</param>
            /// <returns>True if any of the amino acid characters are found</returns>
            static bool ContainsAA(std::vector<char> &s, const std::string &aas);

            static std::string Backwards(std::vector<char> &s);
        };
        // ReSharper restore CharImplicitlyConvertedToNumeric
        // ReSharper restore InconsistentNaming
    }
}


