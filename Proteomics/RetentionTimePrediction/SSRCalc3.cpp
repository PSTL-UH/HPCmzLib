#include "SSRCalc3.h"

using namespace Proteomics::ProteolyticDigestion;
namespace Proteomics
{
    namespace RetentionTimePrediction
    {

const std::string SSRCalc3::VERSION = "Krokhin,3.0";

        std::vector<PeptideWithSetModifications*> SSRCalc3::ChooseRegressionPeptides(std::vector<PeptideWithSetModifications*> &peptides, int &minCount)
        {
            minCount = 0;
            return peptides;
        }

        std::vector<PeptideWithSetModifications*> SSRCalc3::GetStandardPeptides(std::vector<PeptideWithSetModifications*> &peptides)
        {
            return std::vector<PeptideWithSetModifications*> ();
        }

CLUSTCOMB_List *const SSRCalc3::CLUSTCOMB = new CLUSTCOMB_List();
std::unordered_map<std::string, double> SSRCalc3::HlxScore4;
std::unordered_map<std::string, double> SSRCalc3::HlxScore5;
std::unordered_map<std::string, double> SSRCalc3::HlxScore6;
const std::vector<int> SSRCalc3::EMap = std::vector<int>(128);

        void SSRCalc3::CLUSTCOMB_List::Add(const std::string &pattern, double value)
        {
            Regex tempVar(pattern);
            this->push_back(KeyValuePair<Regex*, double>(&tempVar, value));
        }

        SSRCalc3::StaticConstructor::StaticConstructor()
        {
                
        /*
          Translator1 note:  For the Java version we are prepending and appending 0s to the "pick" (key) column.  This
          is done dynamically and repeatedly in the perl code.  As far as I can tell, pick is never used
          without the surrounding 0s.
        */
                
        // ReSharper disable NonLocalizedString
        CLUSTCOMB->push_back("0110", 0.3);
        CLUSTCOMB->push_back("0150", 0.4);
        CLUSTCOMB->push_back("0510", 0.4);
        CLUSTCOMB->push_back("0550", 1.3);
        CLUSTCOMB->push_back("01110", 0.5);
        CLUSTCOMB->push_back("01150", 0.7);
        CLUSTCOMB->push_back("01510", 0.7);
        CLUSTCOMB->push_back("01550", 2.1);
        CLUSTCOMB->push_back("05110", 0.7);
        CLUSTCOMB->push_back("05150", 2.1);
        CLUSTCOMB->push_back("05510", 2.1);
        CLUSTCOMB->push_back("05550", 2.8);
        CLUSTCOMB->push_back("011110", 0.7);
        CLUSTCOMB->push_back("011150", 0.9);
        CLUSTCOMB->push_back("011510", 0.9);
        CLUSTCOMB->push_back("011550", 2.2);
        CLUSTCOMB->push_back("015110", 0.9);
        CLUSTCOMB->push_back("015150", 2.2);
        CLUSTCOMB->push_back("015510", 0.9);
        CLUSTCOMB->push_back("015550", 3.0);
        CLUSTCOMB->push_back("051110", 0.9);
        CLUSTCOMB->push_back("051150", 2.2);
        CLUSTCOMB->push_back("051510", 2.2);
        CLUSTCOMB->push_back("051550", 3.0);
        CLUSTCOMB->push_back("055110", 2.2);
        CLUSTCOMB->push_back("055150", 3.0);
        CLUSTCOMB->push_back("055510", 3.0);
        CLUSTCOMB->push_back("055550", 3.5);
        CLUSTCOMB->push_back("0111110", 0.9);
        CLUSTCOMB->push_back("0111150", 1.0);
        CLUSTCOMB->push_back("0111510", 1.0);
        CLUSTCOMB->push_back("0111550", 2.3);
        CLUSTCOMB->push_back("0115110", 1.0);
        CLUSTCOMB->push_back("0115150", 2.3);
        CLUSTCOMB->push_back("0115510", 2.3);
        CLUSTCOMB->push_back("0115550", 3.1);
        CLUSTCOMB->push_back("0151110", 1.0);
        CLUSTCOMB->push_back("0151150", 2.3);
        CLUSTCOMB->push_back("0151510", 2.3);
        CLUSTCOMB->push_back("0151550", 3.1);
        CLUSTCOMB->push_back("0155110", 2.3);
        CLUSTCOMB->push_back("0155150", 3.1);
        CLUSTCOMB->push_back("0155510", 3.1);
        CLUSTCOMB->push_back("0155550", 3.6);
        CLUSTCOMB->push_back("0511110", 1.0);
        CLUSTCOMB->push_back("0511150", 2.3);
        CLUSTCOMB->push_back("0511510", 2.3);
        CLUSTCOMB->push_back("0511550", 3.1);
        CLUSTCOMB->push_back("0515110", 3.6);
        CLUSTCOMB->push_back("0515150", 2.3);
        CLUSTCOMB->push_back("0515510", 3.1);
        CLUSTCOMB->push_back("0515550", 3.6);
        CLUSTCOMB->push_back("0551110", 2.3);
        CLUSTCOMB->push_back("0551150", 3.1);
        CLUSTCOMB->push_back("0551510", 3.1);
        CLUSTCOMB->push_back("0551550", 3.6);
        CLUSTCOMB->push_back("0555110", 3.1);
        CLUSTCOMB->push_back("0555150", 3.6);
        CLUSTCOMB->push_back("0555510", 3.6);
        CLUSTCOMB->push_back("0555550", 4.0);
        CLUSTCOMB->push_back("01111110", 1.1);
        CLUSTCOMB->push_back("01111150", 1.7);
        CLUSTCOMB->push_back("01111510", 1.7);
        CLUSTCOMB->push_back("01111550", 2.5);
        CLUSTCOMB->push_back("01115110", 1.7);
        CLUSTCOMB->push_back("01115150", 2.5);
        CLUSTCOMB->push_back("01115510", 2.5);
        CLUSTCOMB->push_back("01115550", 3.3);
        CLUSTCOMB->push_back("01151110", 1.7);
        CLUSTCOMB->push_back("01151150", 2.5);
        CLUSTCOMB->push_back("01151510", 2.5);
        CLUSTCOMB->push_back("01151550", 3.3);
        CLUSTCOMB->push_back("01155110", 2.5);
        CLUSTCOMB->push_back("01155150", 3.3);
        CLUSTCOMB->push_back("01155510", 3.3);
        CLUSTCOMB->push_back("01155550", 3.7);
        CLUSTCOMB->push_back("01511110", 1.7);
        CLUSTCOMB->push_back("01511150", 2.5);
        CLUSTCOMB->push_back("01511510", 2.5);
        CLUSTCOMB->push_back("01511550", 3.3);
        CLUSTCOMB->push_back("01515110", 2.5);
        CLUSTCOMB->push_back("01515150", 3.3);
        CLUSTCOMB->push_back("01515510", 3.3);
        CLUSTCOMB->push_back("01515550", 3.7);
        CLUSTCOMB->push_back("01551110", 2.5);
        CLUSTCOMB->push_back("01551150", 3.3);
        CLUSTCOMB->push_back("01551510", 3.3);
        CLUSTCOMB->push_back("01551550", 3.7);
        CLUSTCOMB->push_back("01555110", 3.3);
        CLUSTCOMB->push_back("01555150", 3.7);
        CLUSTCOMB->push_back("01555510", 3.7);
        CLUSTCOMB->push_back("01555550", 4.1);
        CLUSTCOMB->push_back("05111110", 1.7);
        CLUSTCOMB->push_back("05111150", 2.5);
        CLUSTCOMB->push_back("05111510", 2.5);
        CLUSTCOMB->push_back("05111550", 3.3);
        CLUSTCOMB->push_back("05115110", 2.5);
        CLUSTCOMB->push_back("05115150", 3.3);
        CLUSTCOMB->push_back("05115510", 3.3);
        CLUSTCOMB->push_back("05115550", 3.7);
        CLUSTCOMB->push_back("05151110", 2.5);
        CLUSTCOMB->push_back("05151150", 3.3);
        CLUSTCOMB->push_back("05151510", 3.3);
        CLUSTCOMB->push_back("05151550", 3.7);
        CLUSTCOMB->push_back("05155110", 3.3);
        CLUSTCOMB->push_back("05155150", 3.7);
        CLUSTCOMB->push_back("05155510", 3.7);
        CLUSTCOMB->push_back("05155550", 4.1);
        CLUSTCOMB->push_back("05511110", 2.5);
        CLUSTCOMB->push_back("05511150", 3.3);
        CLUSTCOMB->push_back("05511510", 3.3);
        CLUSTCOMB->push_back("05511550", 3.7);
        CLUSTCOMB->push_back("05515110", 3.3);
        CLUSTCOMB->push_back("05515150", 3.7);
        CLUSTCOMB->push_back("05515510", 3.7);
        CLUSTCOMB->push_back("05515550", 4.1);
        CLUSTCOMB->push_back("05551110", 3.3);
        CLUSTCOMB->push_back("05551150", 3.7);
        CLUSTCOMB->push_back("05551510", 3.7);
        CLUSTCOMB->push_back("05551550", 4.1);
        CLUSTCOMB->push_back("05555110", 3.7);
        CLUSTCOMB->push_back("05555150", 4.1);
        CLUSTCOMB->push_back("05555510", 4.1);
        CLUSTCOMB->push_back("05555550", 4.5);
                
        HlxScore4.emplace("XXUX", 0.8);
        HlxScore4.emplace("XZOX", 0.8);
        HlxScore4.emplace("XUXX", 0.8);
        HlxScore4.emplace("XXOX", 0.7);
        HlxScore4.emplace("XOXX", 0.7);
        HlxScore4.emplace("XZUX", 0.7);
        HlxScore4.emplace("XXOZ", 0.7);
        HlxScore4.emplace("ZXOX", 0.7);
        HlxScore4.emplace("XOZZ", 0.7);
        HlxScore4.emplace("ZOXX", 0.7);
        HlxScore4.emplace("ZOZX", 0.7);
        HlxScore4.emplace("ZUXX", 0.7);
        HlxScore4.emplace("ZXUX", 0.5);
        HlxScore4.emplace("XOZX", 0.5);
        HlxScore4.emplace("XZOZ", 0.5);
        HlxScore4.emplace("XUZX", 0.5);
        HlxScore4.emplace("ZZOX", 0.2);
        HlxScore4.emplace("ZXOZ", 0.2);
        HlxScore4.emplace("ZOXZ", 0.2);
        HlxScore4.emplace("XOXZ", 0.2);
        HlxScore4.emplace("ZZUZ", 0.2);
        HlxScore4.emplace("XUXZ", 0.2);
        HlxScore4.emplace("ZUXZ", 0.2);
        HlxScore4.emplace("XZUZ", 0.2);
        HlxScore4.emplace("XUZZ", 0.2);
        HlxScore4.emplace("ZXUZ", 0.2);
        HlxScore4.emplace("ZOZZ", 0.2);
        HlxScore4.emplace("ZZOZ", 0.2);
        HlxScore4.emplace("ZZUX", 0.2);
        HlxScore4.emplace("ZUZX", 0.2);
        HlxScore4.emplace("XXUZ", 0.2);
        HlxScore4.emplace("ZUZZ", 0.2);
                
        HlxScore5.emplace("XXOXX", 3.75);
        HlxScore5.emplace("XXOXZ", 3.75);
        HlxScore5.emplace("XXOZX", 3.75);
        HlxScore5.emplace("XZOXX", 3.75);
        HlxScore5.emplace("ZXOXX", 3.75);
        HlxScore5.emplace("XXOZZ", 2.7);
        HlxScore5.emplace("XZOXZ", 2.7);
        HlxScore5.emplace("XZOZX", 2.7);
        HlxScore5.emplace("ZXOXZ", 2.7);
        HlxScore5.emplace("ZXOZX", 2.7);
        HlxScore5.emplace("ZZOXX", 2.7);
        HlxScore5.emplace("ZXOZZ", 1.3);
        HlxScore5.emplace("XZOZZ", 1.3);
        HlxScore5.emplace("ZZOXZ", 1.3);
        HlxScore5.emplace("ZZOZX", 1.3);
        HlxScore5.emplace("ZZOZZ", 1.3);
        HlxScore5.emplace("XXUXX", 3.75);
        HlxScore5.emplace("XXUXZ", 3.75);
        HlxScore5.emplace("XXUZX", 3.75);
        HlxScore5.emplace("XZUXX", 3.75);
        HlxScore5.emplace("ZXUXX", 3.75);
        HlxScore5.emplace("XXUZZ", 1.1);
        HlxScore5.emplace("XZUXZ", 1.1);
        HlxScore5.emplace("XZUZX", 1.1);
        HlxScore5.emplace("ZXUZX", 1.1);
        HlxScore5.emplace("ZXUXZ", 1.1);
        HlxScore5.emplace("ZZUXX", 1.1);
        HlxScore5.emplace("XZUZZ", 1.3);
        HlxScore5.emplace("ZXUZZ", 1.3);
        HlxScore5.emplace("ZZUXZ", 1.3);
        HlxScore5.emplace("ZZUZX", 1.3);
        HlxScore5.emplace("ZZUZZ", 1.3);
        HlxScore5.emplace("XXOOX", 1.25);
        HlxScore5.emplace("ZXOOX", 1.25);
        HlxScore5.emplace("XZOOX", 1.25);
        HlxScore5.emplace("XOOXX", 1.25);
        HlxScore5.emplace("XOOXZ", 1.25);
        HlxScore5.emplace("XOOZX", 1.25);
        HlxScore5.emplace("XXOOZ", 1.25);
        HlxScore5.emplace("ZXOOZ", 1.25);
        HlxScore5.emplace("XZOOZ", 1.25);
        HlxScore5.emplace("ZZOOX", 1.25);
        HlxScore5.emplace("ZZOOZ", 1.25);
        HlxScore5.emplace("ZOOXX", 1.25);
        HlxScore5.emplace("ZOOXZ", 1.25);
        HlxScore5.emplace("ZOOZX", 1.25);
        HlxScore5.emplace("XOOZZ", 1.25);
        HlxScore5.emplace("ZOOZZ", 1.25);
        HlxScore5.emplace("XXOUX", 1.25);
        HlxScore5.emplace("ZXOUX", 1.25);
        HlxScore5.emplace("XXUOX", 1.25);
        HlxScore5.emplace("ZXUOX", 1.25);
        HlxScore5.emplace("XOUXX", 1.25);
        HlxScore5.emplace("XOUXZ", 1.25);
        HlxScore5.emplace("XUOXX", 1.25);
        HlxScore5.emplace("XUOXZ", 1.25);
        HlxScore5.emplace("XXOUZ", 0.75);
        HlxScore5.emplace("ZXOUZ", 0.75);
        HlxScore5.emplace("XZOUX", 0.75);
        HlxScore5.emplace("XZOUZ", 0.75);
        HlxScore5.emplace("ZZOUX", 0.75);
        HlxScore5.emplace("ZZOUZ", 0.75);
        HlxScore5.emplace("XXUOZ", 0.75);
        HlxScore5.emplace("ZXUOZ", 0.75);
        HlxScore5.emplace("XZUOX", 0.75);
        HlxScore5.emplace("XZUOZ", 0.75);
        HlxScore5.emplace("ZZUOX", 0.75);
        HlxScore5.emplace("ZZUOZ", 0.75);
        HlxScore5.emplace("ZOUXX", 0.75);
        HlxScore5.emplace("ZOUXZ", 0.75);
        HlxScore5.emplace("XOUZX", 0.75);
        HlxScore5.emplace("ZOUZX", 0.75);
        HlxScore5.emplace("XOUZZ", 0.75);
        HlxScore5.emplace("ZOUZZ", 0.75);
        HlxScore5.emplace("ZUOXX", 0.75);
        HlxScore5.emplace("ZUOXZ", 0.75);
        HlxScore5.emplace("XUOZX", 0.75);
        HlxScore5.emplace("ZUOZX", 0.75);
        HlxScore5.emplace("XUOZZ", 0.75);
        HlxScore5.emplace("ZUOZZ", 0.75);
        HlxScore5.emplace("XUUXX", 1.25);
        HlxScore5.emplace("XXUUX", 1.25);
        HlxScore5.emplace("XXUUZ", 0.6);
        HlxScore5.emplace("ZXUUX", 0.6);
        HlxScore5.emplace("ZXUUZ", 0.6);
        HlxScore5.emplace("XZUUX", 0.6);
        HlxScore5.emplace("XZUUZ", 0.6);
        HlxScore5.emplace("ZZUUX", 0.6);
        HlxScore5.emplace("ZZUUZ", 0.6);
        HlxScore5.emplace("ZUUXX", 0.6);
        HlxScore5.emplace("XUUXZ", 0.6);
        HlxScore5.emplace("ZUUXZ", 0.6);
        HlxScore5.emplace("XUUZX", 0.6);
        HlxScore5.emplace("ZUUZX", 0.6);
        HlxScore5.emplace("XUUZZ", 0.6);
        HlxScore5.emplace("ZUUZZ", 0.6);
                
        HlxScore6.emplace("XXOOXX", 3.0);
        HlxScore6.emplace("XXOOXZ", 3.0);
        HlxScore6.emplace("ZXOOXX", 3.0);
        HlxScore6.emplace("ZXOOXZ", 3.0);
        HlxScore6.emplace("XXOUXX", 3.0);
        HlxScore6.emplace("XXOUXZ", 3.0);
        HlxScore6.emplace("XXUOXX", 3.0);
        HlxScore6.emplace("XXUOXZ", 3.0);
        HlxScore6.emplace("ZXUOXX", 3.0);
        HlxScore6.emplace("ZXOUXX", 3.0);
        HlxScore6.emplace("XXOOZX", 1.6);
        HlxScore6.emplace("XXOOZZ", 1.6);
        HlxScore6.emplace("XZOOXX", 1.6);
        HlxScore6.emplace("XZOOXZ", 1.6);
        HlxScore6.emplace("XZOOZX", 1.6);
        HlxScore6.emplace("XZOOZZ", 1.6);
        HlxScore6.emplace("ZXOOZX", 1.6);
        HlxScore6.emplace("ZXOOZZ", 1.6);
        HlxScore6.emplace("ZZOOXX", 1.6);
        HlxScore6.emplace("ZZOOXZ", 1.6);
        HlxScore6.emplace("ZXOUXZ", 1.6);
        HlxScore6.emplace("XZUOXX", 1.6);
        HlxScore6.emplace("ZXUOXZ", 1.6);
        HlxScore6.emplace("ZZOOZX", 1.5);
        HlxScore6.emplace("ZZOOZZ", 1.5);
        HlxScore6.emplace("XXOUZX", 1.5);
        HlxScore6.emplace("XXOUZZ", 1.5);
        HlxScore6.emplace("XZOUXX", 1.5);
        HlxScore6.emplace("XZOUXZ", 1.5);
        HlxScore6.emplace("ZXOUZX", 1.5);
        HlxScore6.emplace("ZXOUZZ", 1.5);
        HlxScore6.emplace("ZZOUXX", 1.5);
        HlxScore6.emplace("ZZOUXZ", 1.5);
        HlxScore6.emplace("XXUOZX", 1.5);
        HlxScore6.emplace("XXUOZZ", 1.5);
        HlxScore6.emplace("XZUOXZ", 1.5);
        HlxScore6.emplace("ZXUOZX", 1.5);
        HlxScore6.emplace("ZXUOZZ", 1.5);
        HlxScore6.emplace("ZZUOXX", 1.5);
        HlxScore6.emplace("ZZUOXZ", 1.5);
        HlxScore6.emplace("ZZUOZX", 1.25);
        HlxScore6.emplace("ZZUOZZ", 1.25);
        HlxScore6.emplace("ZZOUZX", 1.25);
        HlxScore6.emplace("ZZOUZZ", 1.25);
        HlxScore6.emplace("XZOUZX", 1.25);
        HlxScore6.emplace("XZOUZZ", 1.25);
        HlxScore6.emplace("XZUOZX", 1.25);
        HlxScore6.emplace("XZUOZZ", 1.25);
        HlxScore6.emplace("XXUUXX", 1.25);
        HlxScore6.emplace("XXUUXZ", 1.25);
        HlxScore6.emplace("ZXUUXX", 1.25);
        HlxScore6.emplace("XXUUZX", 1.25);
        HlxScore6.emplace("XXUUZZ", 1.25);
        HlxScore6.emplace("XZUUXX", 1.25);
        HlxScore6.emplace("XZUUXZ", 1.25);
        HlxScore6.emplace("XZUUZX", 0.75);
        HlxScore6.emplace("XZUUZZ", 0.75);
        HlxScore6.emplace("ZXUUXZ", 1.25);
        HlxScore6.emplace("ZXUUZX", 1.25);
        HlxScore6.emplace("ZXUUZZ", 1.25);
        HlxScore6.emplace("ZZUUXX", 1.25);
        HlxScore6.emplace("ZZUUXZ", 1.25);
        HlxScore6.emplace("ZZUUZX", 0.75);
        HlxScore6.emplace("ZZUUZZ", 0.75);
        // ReSharper restore NonLocalizedString
                
        // populate eMap
        for (int i = 0; i < EMap.size(); i++)
        {
            EMap[i] = -1; //default
        }
        EMap['K'] = 0;
        EMap['R'] = 1;
        EMap['H'] = 2;
        EMap['D'] = 3;
        EMap['E'] = 4;
        EMap['C'] = 5;
        EMap['Y'] = 6;
        }

SSRCalc3::StaticConstructor SSRCalc3::staticConstructor;

        SSRCalc3::SSRCalc3(const std::string &name, Column column)
        {
            setName(name);

            AAParams *NULLPARAM = new AAParams(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            for (int i = 0; i < AAPARAMS.size(); i++)
            {
                AAPARAMS[i] = NULLPARAM;
            }

            switch (column)
            {
                case Column::A300:
                    A300Column();
                    break;
                case Column::A100:
                    A100Column();
                    break;
            }

            delete NULLPARAM;
        }

        std::string SSRCalc3::getName() const
        {
            return privateName;
        }

        void SSRCalc3::setName(const std::string &value)
        {
            privateName = value;
        }

        void SSRCalc3::A300Column()
        {
            // a                        |   Weights for reg peptide       |  weights for short peptide      |       |         | iso-elec vals    | heli2
            // a                        | RC  | RC1  | RC2  | RN   | RN-1 | RCs  | RC1s | RC2s | RNs  |RN-1s|  krh  |  mass   | Ctrm| Ntrm| pk1  | bsc| cmu
            AAPARAMS['A'] = new AAParams(01.10, 00.35, 00.50, 00.80, -0.10, 00.80, -0.30, 00.10, 00.80, -0.50, 00.00, 071.0370, 3.55, 7.59, 00.00, 1.0, 1.2);
            AAPARAMS['C'] = new AAParams(00.45, 00.90, 00.20, -0.80, -0.50, 00.50, 00.40, 00.00, -0.80, -0.50, 00.00, 103.0090, 3.55, 7.50, 00.00, 0.0, 1.0);
            AAPARAMS['D'] = new AAParams(00.15, 00.50, 00.40, -0.50, -0.50, 00.30, 00.30, 00.70, -0.50, -0.50, 00.00, 115.0270, 4.55, 7.50, 04.05, 0.0, 1.1);
            AAPARAMS['E'] = new AAParams(00.95, 01.00, 00.00, 00.00, -0.10, 00.50, 00.10, 00.00, 00.00, -0.10, 00.00, 129.0430, 4.75, 7.70, 04.45, 0.0, 1.1);
            AAPARAMS['F'] = new AAParams(10.90, 07.50, 09.50, 10.50, 10.30, 11.10, 08.10, 09.50, 10.50, 10.30, -0.10, 147.0638, 3.55, 7.50, 00.00, 0.5, 1.0);
            AAPARAMS['G'] = new AAParams(-0.35, 00.20, 00.15, -0.90, -0.70, 00.00, 00.00, 00.10, -0.90, -0.70, 00.00, 057.0210, 3.55, 7.50, 00.00, 0.0, 0.3);
            AAPARAMS['H'] = new AAParams(-1.45, -0.10, -0.20, -1.30, -1.70, -1.00, 00.10, -0.20, -1.30, -1.70, 00.00, 137.0590, 3.55, 7.50, 05.98, 0.0, 0.6);
            AAPARAMS['I'] = new AAParams(08.00, 05.20, 06.60, 08.40, 07.70, 07.70, 05.00, 06.80, 08.40, 07.70, 00.15, 113.0840, 3.55, 7.50, 00.00, 3.5, 1.4);
            AAPARAMS['K'] = new AAParams(-2.05, -0.60, -1.50, -1.90, -1.45, -0.20, -1.40, -1.30, -2.20, -1.45, 00.00, 128.0950, 3.55, 7.50, 10.00, 0.0, 1.0);
            AAPARAMS['L'] = new AAParams(09.30, 05.55, 07.40, 09.60, 09.30, 09.20, 06.00, 07.90, 09.60, 08.70, 00.30, 113.0840, 3.55, 7.50, 00.00, 1.6, 1.6);
            AAPARAMS['M'] = new AAParams(06.20, 04.40, 05.70, 05.80, 06.00, 06.20, 05.00, 05.70, 05.80, 06.00, 00.00, 131.0400, 3.55, 7.00, 00.00, 1.8, 1.0);
            AAPARAMS['N'] = new AAParams(-0.85, 00.20, -0.20, -1.20, -1.10, -0.85, 00.20, -0.20, -1.20, -1.10, 00.00, 114.0430, 3.55, 7.50, 00.00, 0.0, 0.4);
            AAPARAMS['P'] = new AAParams(02.10, 02.10, 02.10, 00.20, 02.10, 03.00, 01.00, 01.50, 00.20, 02.10, 00.00, 097.0530, 3.55, 8.36, 00.00, 0.0, 0.3);
            AAPARAMS['Q'] = new AAParams(-0.40, -0.70, -0.20, -0.90, -1.10, -0.40, -0.80, -0.20, -0.90, -1.10, 00.00, 128.0590, 3.55, 7.50, 00.00, 0.0, 1.0);
            AAPARAMS['R'] = new AAParams(-1.40, 00.50, -1.10, -1.30, -1.10, -0.20, 00.50, -1.10, -1.20, -1.10, 00.00, 156.1010, 3.55, 7.50, 12.00, 0.0, 1.0);
            AAPARAMS['S'] = new AAParams(-0.15, 00.80, -0.10, -0.80, -1.20, -0.50, 00.40, 00.10, -0.80, -1.20, 00.00, 087.0320, 3.55, 6.93, 00.00, 0.0, 1.0);
            AAPARAMS['T'] = new AAParams(00.65, 00.80, 00.60, 00.40, 00.00, 00.60, 00.80, 00.40, 00.40, 00.00, 00.00, 101.0480, 3.55, 6.82, 00.00, 0.0, 1.0);
            AAPARAMS['V'] = new AAParams(05.00, 02.90, 03.40, 05.00, 04.20, 05.10, 02.70, 03.40, 05.00, 04.20, -0.30, 099.0680, 3.55, 7.44, 00.00, 1.4, 1.2);
            AAPARAMS['W'] = new AAParams(12.25, 11.10, 11.80, 11.00, 12.10, 12.40, 11.60, 11.80, 11.00, 12.10, 00.15, 186.0790, 3.55, 7.50, 00.00, 1.6, 1.0);
            AAPARAMS['Y'] = new AAParams(04.85, 03.70, 04.50, 04.00, 04.40, 05.10, 04.20, 04.50, 04.00, 04.40, -0.20, 163.0630, 3.55, 7.50, 10.00, 0.2, 1.0);

            AAPARAMS['B'] = new AAParams(00.15, 00.50, 00.40, -0.50, -0.50, 00.30, 00.30, 00.70, -0.50, -0.50, 00.00, 115.0270, 4.55, 7.50, 04.05, 0.0, 1.1); //?
            AAPARAMS['X'] = new AAParams(00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 000.0000, 0.00, 0.00, 00.00, 0.0, 1.0); //?
            AAPARAMS['Z'] = new AAParams(00.95, 01.00, 00.00, 00.00, -0.10, 00.50, 00.10, 00.00, 00.00, -0.10, 00.00, 129.0430, 4.75, 7.70, 04.45, 0.0, 1.1); //?
        }

        void SSRCalc3::A100Column()
        {
            // a                        |   Weights for reg peptide       |  weights for short peptide      |       |         | iso-elec vals    | heli2
            // a                        | RC  | RC1  | RC2  | RN   | RN-1 | RCs  | RC1s | RC2s | RNs  |RN-1s|  krh  |  mass   | Ctrm| Ntrm| pk1  | bsc| cmu
            AAPARAMS['A'] = new AAParams(01.02, -0.35, 00.35, 01.02, -0.20, 00.50, -0.05, 00.10, 00.50, -0.30, 00.00, 071.0370, 3.55, 7.59, 00.00, 1.0, 1.2);
            AAPARAMS['C'] = new AAParams(00.10, 00.40, 00.20, 00.10, -0.40, 00.60, 00.60, 01.00, 00.60, -0.50, 00.00, 103.0090, 3.55, 7.50, 00.00, 0.0, 1.0);
            AAPARAMS['D'] = new AAParams(00.15, 00.90, 00.60, 00.15, -0.40, 00.60, 00.30, 00.20, 00.60, -0.50, 00.00, 115.0270, 4.55, 7.50, 04.05, 0.0, 1.1);
            AAPARAMS['E'] = new AAParams(01.00, 01.00, -0.20, 01.00, -0.10, 00.70, 00.45, 00.50, 00.00, 00.25, 00.00, 129.0430, 4.75, 7.70, 04.45, 0.0, 1.1);
            AAPARAMS['F'] = new AAParams(11.67, 07.60, 09.70, 11.67, 11.50, 11.30, 08.40, 10.00, 11.30, 10.85, -0.10, 147.0638, 3.55, 7.50, 00.00, 0.5, 1.0);
            AAPARAMS['G'] = new AAParams(-0.35, 00.15, 00.15, -0.35, -0.40, 00.00, 00.15, 00.20, 00.00, -0.70, 00.00, 057.0210, 3.55, 7.50, 00.00, 0.0, 0.3);
            AAPARAMS['H'] = new AAParams(-3.00, -1.40, -1.00, -3.00, -1.90, -1.30, -1.30, -1.10, -1.30, -1.70, 00.00, 137.0590, 3.55, 7.50, 05.98, 0.0, 0.6);
            AAPARAMS['I'] = new AAParams(07.96, 04.95, 06.30, 07.96, 06.60, 07.25, 04.50, 06.50, 07.25, 07.20, 00.15, 113.0840, 3.55, 7.50, 00.00, 3.5, 1.4);
            AAPARAMS['K'] = new AAParams(-3.40, -1.85, -2.30, -2.10, -2.10, -1.75, -1.50, -1.75, -2.30, -2.50, 00.00, 128.0950, 3.55, 7.50, 10.00, 0.0, 1.0);
            AAPARAMS['L'] = new AAParams(09.40, 05.57, 07.40, 09.40, 09.30, 08.70, 05.50, 07.70, 08.70, 08.50, 00.30, 113.0840, 3.55, 7.50, 00.00, 1.6, 1.6);
            AAPARAMS['M'] = new AAParams(06.27, 05.20, 05.70, 06.27, 05.80, 06.25, 04.20, 05.70, 06.25, 05.60, 00.00, 131.0400, 3.55, 7.00, 00.00, 1.8, 1.0);
            AAPARAMS['N'] = new AAParams(-0.95, 01.20, -0.10, -0.95, -1.30, -0.65, 00.40, -0.05, -0.65, -1.20, 00.00, 114.0430, 3.55, 7.50, 00.00, 0.0, 0.4);
            AAPARAMS['P'] = new AAParams(01.85, 01.70, 01.75, 01.85, 01.20, 02.50, 01.70, 02.10, 02.50, 01.90, 00.00, 097.0530, 3.55, 8.36, 00.00, 0.0, 0.3);
            AAPARAMS['Q'] = new AAParams(-0.60, -0.50, -0.20, -0.60, -1.10, -0.40, -0.20, -0.70, -0.40, -1.30, 00.00, 128.0590, 3.55, 7.50, 00.00, 0.0, 1.0);
            AAPARAMS['R'] = new AAParams(-2.55, -1.40, -1.50, -1.10, -1.30, -1.00, 00.40, -1.00, -1.10, -1.90, 00.00, 156.1010, 3.55, 7.50, 12.00, 0.0, 1.0);
            AAPARAMS['S'] = new AAParams(-0.14, 01.10, -0.10, -0.14, -1.00, -0.40, 00.20, -0.30, -0.40, -1.20, 00.00, 087.0320, 3.55, 6.93, 00.00, 0.0, 1.0);
            AAPARAMS['T'] = new AAParams(00.64, 00.95, 00.60, 00.64, -0.10, 00.40, 00.30, 00.40, 00.40, -0.50, 00.00, 101.0480, 3.55, 6.82, 00.00, 0.0, 1.0);
            AAPARAMS['V'] = new AAParams(04.68, 02.10, 03.40, 04.68, 03.90, 04.40, 02.10, 03.00, 04.40, 04.40, -0.30, 099.0680, 3.55, 7.44, 00.00, 1.4, 1.2);
            AAPARAMS['W'] = new AAParams(13.35, 11.50, 11.80, 13.35, 13.00, 13.90, 11.80, 13.00, 13.90, 12.90, 00.15, 186.0790, 3.55, 7.50, 00.00, 1.6, 1.0);
            AAPARAMS['Y'] = new AAParams(05.35, 04.30, 05.10, 05.35, 05.00, 05.70, 05.00, 05.40, 05.70, 05.30, -0.20, 163.0630, 3.55, 7.50, 10.00, 0.2, 1.0);

            AAPARAMS['B'] = new AAParams(00.15, 00.50, 00.40, -0.50, -0.50, 00.30, 00.30, 00.70, -0.50, -0.50, 00.00, 115.0270, 4.55, 7.50, 04.05, 0.0, 1.1); //?
            AAPARAMS['X'] = new AAParams(00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 00.00, 000.0000, 0.00, 0.00, 00.00, 0.0, 1.0); //?
            AAPARAMS['Z'] = new AAParams(00.95, 01.00, 00.00, 00.00, -0.10, 00.50, 00.10, 00.00, 00.00, -0.10, 00.00, 129.0430, 4.75, 7.70, 04.45, 0.0, 1.1); //?
        }

        int SSRCalc3::getNOELECTRIC() const
        {
            return privateNOELECTRIC;
        }

        void SSRCalc3::setNOELECTRIC(int value)
        {
            privateNOELECTRIC = value;
        }

        int SSRCalc3::getNOCLUSTER() const
        {
            return privateNOCLUSTER;
        }

        void SSRCalc3::setNOCLUSTER(int value)
        {
            privateNOCLUSTER = value;
        }

        int SSRCalc3::getNODIGEST() const
        {
            return privateNODIGEST;
        }

        void SSRCalc3::setNODIGEST(int value)
        {
            privateNODIGEST = value;
        }

        int SSRCalc3::getNOSMALL() const
        {
            return privateNOSMALL;
        }

        void SSRCalc3::setNOSMALL(int value)
        {
            privateNOSMALL = value;
        }

        int SSRCalc3::getNOHELIX1() const
        {
            return privateNOHELIX1;
        }

        void SSRCalc3::setNOHELIX1(int value)
        {
            privateNOHELIX1 = value;
        }

        int SSRCalc3::getNOHELIX2() const
        {
            return privateNOHELIX2;
        }

        void SSRCalc3::setNOHELIX2(int value)
        {
            privateNOHELIX2 = value;
        }

        int SSRCalc3::getNOEHEL() const
        {
            return privateNOEHEL;
        }

        void SSRCalc3::setNOEHEL(int value)
        {
            privateNOEHEL = value;
        }

        double SSRCalc3::getUnknownScore() const
        {
            return 0;
        }

        double SSRCalc3::ScoreSequence(PeptideWithSetModifications *item)
        {
            auto seq = item->getBaseSequence(); //PTMs are not yet implemented
            double tsum3 = 0.0;
            int i;

            // Core summation

            int sze = seq.length();
            if (sze < 4) // peptide is too short ot have any retention
            {
                return tsum3;
            }
            if (sze < 10) // short peptides use short peptide retention weights
            {
                tsum3 = AAPARAMS[seq[0]]->getRC1S() + AAPARAMS[seq[1]]->getRC2S() + AAPARAMS[seq[sze - 1]]->getRCNS() + AAPARAMS[seq[sze - 2]]->getRCN2S(); // and penultimate aa

                for (i = 2; i < sze - 2; i++) // add weights for aa's in the middle
                {
                    tsum3 += AAPARAMS[seq[i]]->getRCS();
                }
            }
            else // longer peptides use regular retention weights
            {
                tsum3 = AAPARAMS[seq[0]]->getRC1() + AAPARAMS[seq[1]]->getRC2() + AAPARAMS[seq[sze - 1]]->getRCN() + AAPARAMS[seq[sze - 2]]->getRCN2(); // and penultimate aa

                for (i = 2; i < sze - 2; i++) // add weights for aa's in the middle
                {
                    tsum3 += AAPARAMS[seq[i]]->getRC();
                }
            }
            //_log.debug("Core = "+tsum3);

            // 1- smallness - adjust based on tsum score of peptides shorter than 20 aa's.
            tsum3 += Smallness(sze, tsum3);
            //_log.debug("smallness = "+tsum3);
            // 2- undigested parts
            tsum3 -= Undigested(seq);
            //_log.debug("undigested = "+tsum3);
            // 3- clusterness # NB:weighting of v1 is now done in subrtn.
            tsum3 -= Clusterness(seq);
            //_log.debug("clusterness = "+tsum3);
            // 4- proline fix
            tsum3 -= Proline(seq);
            //_log.debug("proline = "+tsum3);
            // 5- length scaling correction
            tsum3 *= Length_scale(sze);
            //_log.debug("length_scale = "+tsum3);
            // 6- total sum correction
            if (tsum3 >= 20 && tsum3 < 30)
            {
                tsum3 -= ((tsum3 - 18) * SUMSCALE1);
            }
            if (tsum3 >= 30 && tsum3 < 40)
            {
                tsum3 -= ((tsum3 - 18) * SUMSCALE2);
            }
            if (tsum3 >= 40 && tsum3 < 50)
            {
                tsum3 -= ((tsum3 - 18) * SUMSCALE3);
            }
            if (tsum3 >= 50)
            {
                tsum3 -= ((tsum3 - 18) * SUMSCALE4);
            }
            //_log.debug("total sum = "+tsum3);
            // 7- isoelectric change
            tsum3 += NewIso(seq, tsum3);
            //_log.debug("isoelectric = "+tsum3);
            // 8- helicity corrections  #NB: HELIX#SCALE-ing is now done in subrtn.
            tsum3 += Helicity1(seq);
            //_log.debug("helicity1 = "+tsum3);
            tsum3 += Helicity2(seq);
            //_log.debug("helicity2 = "+tsum3);
            tsum3 += Helectric(seq);
            //_log.debug("helectric = "+tsum3);
            return tsum3;
        }

        double SSRCalc3::Smallness(int sqlen, double tsum)
        {
            if (getNOSMALL() == 1)
            {
                return 0.0;
            }
            if (sqlen < 20 && (tsum / sqlen) < 0.9)
            {
                return 3.5 * (0.9 - (tsum / sqlen));
            }
            if (sqlen < 15 && (tsum / sqlen) > 2.8)
            {
                return 2.6 * ((tsum / sqlen) - 2.8);
            }
            return 0.0;
        }

        double SSRCalc3::Undigested(const std::string &sq)
        {
            if (getNODIGEST() == 1)
            {
                return 0.0;
            }

            char op1, op2;

            int xx = sq.length() - 1;
            char re = sq[xx];
            double csum = 0.0;

            // rightmost
            if (re == 'R' || re == 'K' || re == 'H')
            {
                op1 = sq[xx - 1]; // left by 1
                op2 = sq[xx - 2]; // left by 2
                csum = UDF21 * AAPARAMS[op1]->getUndKRH() + UDF22 * AAPARAMS[op2]->getUndKRH();
            }
            // scan through string, starting at second and ending two before left
            //    --Translator1 note:
            //      the perl code does not jibe with the comment above, and will probably need repair
            //      possibly dd should start out as 2, not 0; and should loop to xx-2, not xx.

            //      Negative indices on the perl substr function make substrings offset from right
            //      (instead of left) end of string.  The perl loop gets negative indices.  This may be a
            //      a problem.
            for (int dd = 0; dd < xx; dd++)
            {
                re = sq[dd];
                if (re == 'K' || re == 'R' || re == 'H')
                {
                    char op3, op4;
                    op1 = op2 = op3 = op4 = '\0';
                    if (dd - 1 >= 0 && dd - 1 <= xx)
                    {
                        op1 = sq[dd - 1]; //left by 1
                    }
                    if (dd - 2 >= 0 && dd - 2 <= xx)
                    {
                        op2 = sq[dd - 2]; //left by 2
                    }
                                             // ReSharper disable ConditionIsAlwaysTrueOrFalse
                    if (DUPLICATE_ORIGINAL_CODE)
                    {
                    // ReSharper restore ConditionIsAlwaysTrueOrFalse
                        if (dd - 1 < 0 && (-(dd - 1)) <= xx)
                        {
                            op1 = sq[xx + (dd - 1) + 1];
                        }
                        if (dd - 2 < 0 && (-(dd - 2)) <= xx)
                        {
                            op2 = sq[xx + (dd - 2) + 1];
                        }
                    }
                    if (dd + 1 >= 0 && dd + 1 <= xx)
                    {
                        op3 = sq[dd + 1]; //right by 1
                    }
                    if (dd + 2 >= 0 && dd + 2 <= xx)
                    {
                        op4 = sq[dd + 2]; //right by 2;
                    }

                    csum = csum + (UDF31 * (AAPARAMS[op1]->getUndKRH() + AAPARAMS[op3]->getUndKRH())) + (UDF32 * (AAPARAMS[op2]->getUndKRH() + AAPARAMS[op4]->getUndKRH()));
                }
            }
            return csum;
        }

        double SSRCalc3::Clusterness(const std::string &sq)
        {
            if (getNOCLUSTER() == 1)
            {
                return 0.0;
            }

            std::string cc = "0" + sq + "0"; // Not L10N
                                        // ReSharper disable ConditionIsAlwaysTrueOrFalse
            if (ALGORITHM_VERSION == 3)
            {
            // ReSharper restore ConditionIsAlwaysTrueOrFalse
                cc = cc.ReplaceAAs("LIW", "5"); // Not L10N
                cc = cc.ReplaceAAs("AMYV", "1"); // Not L10N
                cc = cc.ReplaceAAs("A-Z", "0"); // Not L10N
            }
            else
            // Suppress the unreachable code warning
            //C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
            #pragma warning( disable: 162 )
            {
            // ReSharper disable HeuristicUnreachableCode
                cc = cc.ReplaceAAs("LIWF", "5"); // Not L10N
                cc = cc.ReplaceAAs("MYV", "1"); // Not L10N
                cc = cc.ReplaceAAs("A-Z", "0"); // Not L10N
            }
            // ReSharper restore HeuristicUnreachableCode
            //C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
            #pragma warning( default: 162 )

            double score = 0.0;
            //
            // Translator1 note:  check on true meaning of the algorithm that defines 'occurs'
            // Should an encoded aa string such as 015101510 match pick "01510" once or twice?
            // The perl code seems to match once.  0151001510 would match twice.

            for (auto pair : CLUSTCOMB)
            {
                int occurs = 0;
                Match *m = pair.first::Match(cc);
                while (m->Success)
                {
                    occurs++;
                    m = m->NextMatch();
                }
                if (occurs > 0)
                {
                    double sk = pair.second;
                    double addit = sk * occurs;
                    score += addit;
                }
            }
            return score * KSCALE;
        }

        double SSRCalc3::Proline(const std::string &sq)
        {
            if (sq.find("PPPP") != std::string::npos) // Not L10N
            {
                return PPPPSCORE;
            }
            else if (sq.find("PPP") != std::string::npos) // Not L10N
            {
                return PPPSCORE;
            }
            else if (sq.find("PP") != std::string::npos) // Not L10N
            {
                return PPSCORE;
            }
            else
            {
                return 0.0;
            }
        }

        double SSRCalc3::Length_scale(int sqlen)
        {
            if (sqlen < SPLim)
            {
                return 1.0 + SPSFac * (SPLim - sqlen);
            }
            else if (sqlen > LPLim)
            {
                return 1.0 / (1.0 + LPSFac * (sqlen - LPLim));
            }
            else
            {
                return 1.0;
            }
        }

        double SSRCalc3::Partial_charge(double pK, double pH)
        {
            double cr = std::pow(10.0, (pK - pH));
            return cr / (cr + 1.0);
        }

        double SSRCalc3::Electric(const std::string &sq)
        {
            std::vector<int> aaCNT = {0, 0, 0, 0, 0, 0, 0};

            // Translator1 Note: this is commented out in the perl source
            // if (NOELECTRIC == 1) { return 1.0; }

            // get c and n terminus acids
            int ss = sq.length();
            char s1 = sq[0];
            char s2 = sq[ss - 1];
            double pk0 = AAPARAMS[s1]->getCT();
            double pk1 = AAPARAMS[s2]->getNT();

            // count them up
            for (int i = 0; i < ss; i++)
            {
                int index = EMap[sq[i]];
                if (index >= 0)
                {
                    aaCNT[index]++;
                }
            }

            // cycle through pH values looking for closest to zero
            // coarse pass
            double best = 0.0;
            double min = 100000;
            constexpr double step1 = 0.3;

            for (double z = 0.01; z <= 14.0; z = z + step1)
            {
                double check = CalcR(z, pk0, pk1, aaCNT);
                if (check < 0)
                {
                    check = 0 - check;
                }
                if (check < min)
                {
                    min = check;
                    best = z;
                }
            }

            double best1 = best;

            // fine pass
            min = 100000;
            for (double z = best1 - step1; z <= best1 + step1; z = z + 0.01)
            {
                double check = CalcR(z, pk0, pk1, aaCNT);
                if (check < 0)
                {
                    check = 0 - check;
                }
                if (check < min)
                {
                    min = check;
                    best = z;
                }
            }
            return best;
        }

        double SSRCalc3::CalcR(double pH, double PK0, double PK1, std::vector<int> &CNTref)
        {
            double cr0 = Partial_charge(PK0, pH) + CNTref[EMap['K']] * Partial_charge(AAPARAMS['K']->getPK(), pH) + CNTref[EMap['R']] * Partial_charge(AAPARAMS['R']->getPK(), pH) + CNTref[EMap['H']] * Partial_charge(AAPARAMS['H']->getPK(), pH) - CNTref[EMap['D']] * Partial_charge(pH, AAPARAMS['D']->getPK()) - CNTref[EMap['E']] * Partial_charge(pH, AAPARAMS['E']->getPK()) - CNTref[EMap['Y']] * Partial_charge(pH, AAPARAMS['Y']->getPK()) - Partial_charge(pH, PK1); // c terminus
                                           /*
                                           // The following was taken out of the formula for R
                                           //  - $CNTref->{C} * _partial_charge( $pH,      $PK{C} )    // cys
                                           */
            return cr0;
        }

        double SSRCalc3::NewIso(const std::string &sq, double tsum)
        {
            if (getNOELECTRIC() == 1)
            {
                return 0.0;
            }

            // compute mass
            double mass = 0.0;
            for (auto cf1 : sq)
            {
                mass += AAPARAMS[cf1]->getAMASS();
            }
            // compute isoelectric value
            double pi1 = Electric(sq);
            double lmass = 1.8014 * std::log(mass);

            // make mass correction
            double delta1 = pi1 - 19.107 + lmass;
            //apply corrected value as scaling factor

            double corr01 = 0.0;
            if (delta1 < 0.0)
            {
                corr01 = (tsum * Z01 + Z02) * NDELTAWT * delta1;
            }
            else if (delta1 > 0.0)
            {
                corr01 = (tsum * Z03 + Z04) * PDELTAWT * delta1;
            }
            return corr01;
        }

        double SSRCalc3::Heli1TermAdj(const std::string &ss1, int ix2, int sqlen)
        {
            int where = 0;

            for (int i = 0; i < ss1.length(); i++)
            {
                char m = ss1[i];
                if (m == 'O' || m == 'U')
                {
                    where = i;
                    // Suppress unreachable code warning
            //C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
            #pragma warning( disable: 162 )
                    // ReSharper disable ConditionIsAlwaysTrueOrFalse
                    if (!DUPLICATE_ORIGINAL_CODE)
                    {
                        // ReSharper restore ConditionIsAlwaysTrueOrFalse
                        // ReSharper disable HeuristicUnreachableCode
                        break;
                    }
                    // ReSharper restore HeuristicUnreachableCode
            //C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
            #pragma warning( default: 162 )
                }
            }

            where += ix2;

            if (where < 2)
            {
                return 0.20;
            }
            if (where < 3)
            {
                return 0.25;
            }
            if (where < 4)
            {
                return 0.45;
            }

            if (where > sqlen - 3)
            {
                return 0.2;
            }
            if (where > sqlen - 4)
            {
                return 0.75;
            }
            if (where > sqlen - 5)
            {
                return 0.65;
            }

            return 1.0;
        }

        double SSRCalc3::Helicity1(const std::string &sq)
        {
            if (getNOHELIX1() == 1)
            {
                return 0.0;
            }

            std::string hc = sq; //helicity coded sq

            /* Translator1 note:  notice lowercase 'z'.  This never appears in any patterns to which this
               string is compared, and will never match any helicity patterns.
            */
            hc = hc.ReplaceAAs("PHRK", "z"); // Not L10N
            hc = hc.ReplaceAAs("WFIL", "X"); // Not L10N
            hc = hc.ReplaceAAs("YMVA", "Z"); // Not L10N
            hc = hc.ReplaceAAs("DE", "O"); // Not L10N
            hc = hc.ReplaceAAs("GSPCNKQHRT", "U"); // Not L10N

            double sum = 0.0;
            int sqlen = hc.length();

            // Translator1 note: this loop should be reviewed carefully

            for (int i = 0; i < sqlen - 3; i++)
            {
                std::string hc4 = "", hc5 = "", hc6 = "";
                double sc4 = 0.0, sc5 = 0.0, sc6 = 0.0;

                if (hc.substr(i)->length() >= 6)
                {
                    hc6 = hc.substr(i, 6);
                    sc6 = 0.0;
                    if (HlxScore6.find(hc6) != HlxScore6.end())
                    {
                        sc6 = HlxScore6[hc6];
                    }
                }
                if (sc6 > 0)
                {
                    double trmAdj6 = Heli1TermAdj(hc6, i, sqlen);
                    sum += (sc6 * trmAdj6);
                    i = i + 1; //??
                    continue;
                }

                if (hc.substr(i)->length() >= 5)
                {
                    hc5 = hc.substr(i, 5);
                    sc5 = 0.0;
                    if (HlxScore5.find(hc5) != HlxScore5.end())
                    {
                        sc5 = HlxScore5[hc5];
                    }
                }
                if (sc5 > 0)
                {
                    double trmAdj5 = Heli1TermAdj(hc5, i, sqlen);
                    sum += (sc5 * trmAdj5);
                    i = i + 1; //??
                    continue;
                }

                if (hc.substr(i)->length() >= 4)
                {
                    hc4 = hc.substr(i, 4);
                    sc4 = 0.0;
                    if (HlxScore4.find(hc4) != HlxScore4.end())
                    {
                        sc4 = HlxScore4[hc4];
                    }
                }
                if (sc4 > 0)
                {
                    double trmAdj4 = Heli1TermAdj(hc4, i, sqlen);
                    sum += (sc4 * trmAdj4);
                    i = i + 1; //??
                }
            }
            return HELIX1SCALE * sum;
        }

        double SSRCalc3::EvalH2pattern(const std::string &pattern, const std::string &testsq, int posn, char etype)
        {
            char f01 = pattern[0];
            double prod1 = AAPARAMS[f01]->getH2BASCORE();
            int iss = 0;
            constexpr int OFF1 = 2;
            int acount = 1;
            char far1 = '\0';
            char far2 = '\0';

            char testAAl = testsq[OFF1 + posn];
            char testAAr = testsq[OFF1 + posn + 2];
            std::string testsqCopy = testsq.substr(OFF1 + posn + 1);
            double mult = Connector(f01, testAAl, testAAr, "--", far1, far2); // Not L10N
            prod1 = prod1 * mult;
            if (etype == '*') // Not L10N
            {
                prod1 = prod1 * 25.0;
            }
            if (mult == 0.0)
            {
                return 0.0;
            }
            for (int i = 1; i < pattern.length() - 2; i = i + 3)
            {
                std::string fpart = pattern.substr(i, 2);
                char gpart = (i + 2) < pattern.length() ? pattern[i + 2] : '\0'; // Not L10N
                double s3 = AAPARAMS[gpart]->getH2BASCORE();
                if (fpart == "--") // Not L10N
                {
                    iss = 0;
                    far1 = '\0';
                    far2 = '\0'; // Not L10N
                }
                if (fpart == "<-") // Not L10N
                {
                    iss = 1;
                    far1 = testsqCopy[i + 1];
                    far2 = '\0'; // Not L10N
                }
                if (fpart == "->") // Not L10N
                {
                    iss = -1;
                    far1 = '\0';
                    far2 = testsqCopy[i + 3]; // Not L10N
                }

                testAAl = testsqCopy[i + 1 + iss];
                testAAr = testsqCopy[i + 3 + iss];

                mult = Connector(gpart, testAAl, testAAr, fpart, far1, far2);

                if (etype == '*') // Not L10N
                {
                    if (mult != 0.0 || acount < 3)
                    {
                        prod1 = prod1 * 25.0 * s3 * mult;
                    }
                }

                if (etype == '+') // Not L10N
                {
                    prod1 = prod1 + s3 * mult;
                }

                if (mult == 0.0)
                {
                    return prod1;
                }

                acount++;
            }
            return prod1;
        }

        double SSRCalc3::Connector(char acid, char lp, char rp, const std::string &ct, char far1, char far2)
        {
            double mult = 1.0;

            if (ct.find("<-") != std::string::npos)
            {
                mult *= 0.2;
            } // Not L10N
            if (ct.find("->") != std::string::npos)
            {
                mult *= 0.1;
            } // Not L10N

            mult *= AAPARAMS[lp]->getH2CMULT();
            if (lp != rp)
            {
                mult *= AAPARAMS[rp]->getH2CMULT();
            }

            if (acid == 'A' || acid == 'Y' || acid == 'V' || acid == 'M') // Not L10N
            {
                if (lp == 'P' || lp == 'G' || rp == 'P' || rp == 'G')
                {
                    mult = 0.0; // Not L10N
                }
                if (ct.find("->") != std::string::npos || ct.find("<-") != std::string::npos)
                {
                    mult = 0.0; // Not L10N
                }
            }

            if (acid == 'L' || acid == 'W' || acid == 'F' || acid == 'I') // Not L10N
            {
                if (((lp == 'P' || lp == 'G') || (rp == 'P' || rp == 'G')) && (!ct.find("--") != std::string::npos))
                {
                    mult = 0.0; // Not L10N
                }
                if (((far1 == 'P' || far1 == 'G') || (far2 == 'P' || far2 == 'G')) && (ct.find("<-") != std::string::npos || ct.find("->") != std::string::npos))
                {
                    mult = 0.0; // Not L10N
                }
            }
            return mult;
        }

        std::vector<double> SSRCalc3::Heli2Calc(const std::string &sq)
        {
            // Translator1 note: in the original perl and translated C, this function
            // was void and returned values through double pointer arguments. Like this:
            //
            // void  heli2Calc(char *sq, double *hisc, double *gsc)
            //

            std::vector<double> ret(2);
            std::string traps; //not my()'ed in perl source
            std::string best = "";
            constexpr int llim = 50;
            double hiscore = 0.0;
            int best_pos = 0;

            if (sq.length() < 11)
            {
                ret[HISC] = 0.0;
                ret[GSC] = 0.0;
                return ret;
            }

            std::string prechop = sq;
            std::string sqCopy = sq.substr(2, sq.length() - 4);

            std::string pass1 = sqCopy.ReplaceAAs("WFILYMVA", "1"); // Not L10N
            pass1 = pass1.ReplaceAAs("GSPCNKQHRTDE", "0"); // Not L10N

            for (int i = 0; i < pass1.length(); i++)
            {
                char m = pass1[i];
                if (m == '1') // Not L10N
                {
                    std::string lc = pass1.substr(i);
                    std::string sq2 = sqCopy.substr(i);
                    std::string pat = "";
                    int zap = 0;
                    int subt = 0;

                    while (zap <= llim && subt < 2)
                    {
                        char f1 = (zap < 0 || zap >= lc.length() ? '0' : lc[zap]);
                        char f2 = (zap - 1 < 0 || zap - 1 >= lc.length() ? '0' : lc[zap - 1]); // Not L10N
                        char f3 = (zap + 1 < 0 || zap + 1 >= lc.length() ? '0' : lc[zap + 1]); // Not L10N

                        if (f1 == '1') // Not L10N
                        {
                            if (zap > 0)
                            {
                                pat += "--"; // Not L10N
                            }
                            pat += sq2.substr(zap, 1);
                        }
                        else
                        {
                            if (f2 == '1' && f1 == '0') // Not L10N
                            {
                                subt++;
                                if (subt < 2)
                                {
                                    pat += "->"; // Not L10N
                                    pat += sq2.substr(zap - 1, 1);
                                }
                            }
                            else
                            {
                                if (f3 == '1' && f1 == '0') // Not L10N
                                {
                                    subt++;
                                    if (subt < 2)
                                    {
                                        pat += "<-"; // Not L10N
                                        pat += sq2.substr(zap + 1, 1);
                                    }
                                }
                            }
                        }

                        if (f1 == '0' && f2 == '0' && f3 == '0') // Not L10N
                        {
                            zap = 1000;
                        }
                        zap += 3;
                    }

                    if (pat.length() > 4)
                    {
                        traps = prechop;
                        double skore = EvalH2pattern(pat, traps, i - 1, '*'); // Not L10N
                        if (skore >= hiscore)
                        {
                            hiscore = skore;
                            best = pat;
                            best_pos = i;
                        }
                    }
                }
            }

            if (hiscore > 0.0)
            {
                double gscore = hiscore; //not my()'ed in perl source
                traps = prechop;
                hiscore = EvalH2pattern(best, traps, best_pos - 1, '+'); // Not L10N

                ret[HISC] = hiscore;
                ret[GSC] = gscore;
                return ret;
            }

            ret[HISC] = 0.0;
            ret[GSC] = 0.0;
            return ret;
        }

        double SSRCalc3::Helicity2(const std::string &sq)
        {
            if (getNOHELIX2() == 1)
            {
                return 0.0;
            }
            std::string Bksq = sq.Backwards();
            std::vector<double> fhg = Heli2Calc(sq);
            double FwHiscor = fhg[HISC];
            double FwGscor = fhg[GSC];
            std::vector<double> rhg = Heli2Calc(Bksq);
            double BkHiscor = rhg[HISC];
            double BkGscor = rhg[GSC];
            double h2FwBk = BkGscor > FwGscor ? BkHiscor : FwHiscor;
            double lenMult = 0.0;
            if (sq.length() > 30)
            {
                lenMult = 1;
            }
            double NoPMult = 0.75;
            if (sq.find("P") != std::string::npos) // Not L10N
            {
                NoPMult = 0.0;
            }
            double h2mult = 1.0 + lenMult + NoPMult;
            return HELIX2SCALE * h2mult * h2FwBk;
        }

        double SSRCalc3::Helectric(const std::string &sq)
        {
            if (getNOEHEL() == 1 || sq.length() > 14 || sq.length() < 4)
            {
                return 0.0;
            }
            std::string mpart = sq.substr(sq.length() - 4);

            if (mpart[0] == 'D' || mpart[0] == 'E') // Not L10N
            {
                mpart = mpart.substr(1, 2);
                if (mpart.ContainsAA("PGKRH")) // Not L10N
                {
                    return 0.0;
                }
                mpart = mpart.ReplaceAAs("LI", "X"); // Not L10N
                mpart = mpart.ReplaceAAs("AVYFWM", "Z"); // Not L10N
                mpart = mpart.ReplaceAAs("GSPCNKQHRTDE", "U"); // Not L10N

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                switch (mpart)
                    // ReSharper disable NonLocalizedString
//ORIGINAL LINE: case "XX":
                if (mpart == "XX")
                {
                        return 1.0;
                }
//ORIGINAL LINE: case "ZX":
                else if (mpart == "ZX")
                {
                        return 0.5;
                }
//ORIGINAL LINE: case "XZ":
                else if (mpart == "XZ")
                {
                        return 0.5;
                }
//ORIGINAL LINE: case "ZZ":
                else if (mpart == "ZZ")
                {
                        return 0.4;
                }
//ORIGINAL LINE: case "XU":
                else if (mpart == "XU")
                {
                        return 0.4;
                }
//ORIGINAL LINE: case "UX":
                else if (mpart == "UX")
                {
                        return 0.4;
                }
//ORIGINAL LINE: case "ZU":
                else if (mpart == "ZU")
                {
                        return 0.2;
                }
//ORIGINAL LINE: case "UZ":
                else if (mpart == "UZ")
                {
                        return 0.2;
                        // ReSharper restore NonLocalizedString
                }
            }
            return 0;
        }

        double SSRCalc3::AAParams::getRC() const
        {
            return privateRC;
        }

        void SSRCalc3::AAParams::setRC(double value)
        {
            privateRC = value;
        }

        double SSRCalc3::AAParams::getRC1() const
        {
            return privateRC1;
        }

        void SSRCalc3::AAParams::setRC1(double value)
        {
            privateRC1 = value;
        }

        double SSRCalc3::AAParams::getRC2() const
        {
            return privateRC2;
        }

        void SSRCalc3::AAParams::setRC2(double value)
        {
            privateRC2 = value;
        }

        double SSRCalc3::AAParams::getRCN() const
        {
            return privateRCN;
        }

        void SSRCalc3::AAParams::setRCN(double value)
        {
            privateRCN = value;
        }

        double SSRCalc3::AAParams::getRCN2() const
        {
            return privateRCN2;
        }

        void SSRCalc3::AAParams::setRCN2(double value)
        {
            privateRCN2 = value;
        }

        double SSRCalc3::AAParams::getRCS() const
        {
            return privateRCS;
        }

        void SSRCalc3::AAParams::setRCS(double value)
        {
            privateRCS = value;
        }

        double SSRCalc3::AAParams::getRC1S() const
        {
            return privateRC1S;
        }

        void SSRCalc3::AAParams::setRC1S(double value)
        {
            privateRC1S = value;
        }

        double SSRCalc3::AAParams::getRC2S() const
        {
            return privateRC2S;
        }

        void SSRCalc3::AAParams::setRC2S(double value)
        {
            privateRC2S = value;
        }

        double SSRCalc3::AAParams::getRCNS() const
        {
            return privateRCNS;
        }

        void SSRCalc3::AAParams::setRCNS(double value)
        {
            privateRCNS = value;
        }

        double SSRCalc3::AAParams::getRCN2S() const
        {
            return privateRCN2S;
        }

        void SSRCalc3::AAParams::setRCN2S(double value)
        {
            privateRCN2S = value;
        }

        double SSRCalc3::AAParams::getUndKRH() const
        {
            return privateUndKRH;
        }

        void SSRCalc3::AAParams::setUndKRH(double value)
        {
            privateUndKRH = value;
        }

        double SSRCalc3::AAParams::getAMASS() const
        {
            return privateAMASS;
        }

        void SSRCalc3::AAParams::setAMASS(double value)
        {
            privateAMASS = value;
        }

        double SSRCalc3::AAParams::getCT() const
        {
            return privateCT;
        }

        void SSRCalc3::AAParams::setCT(double value)
        {
            privateCT = value;
        }

        double SSRCalc3::AAParams::getNT() const
        {
            return privateNT;
        }

        void SSRCalc3::AAParams::setNT(double value)
        {
            privateNT = value;
        }

        double SSRCalc3::AAParams::getPK() const
        {
            return privatePK;
        }

        void SSRCalc3::AAParams::setPK(double value)
        {
            privatePK = value;
        }

        double SSRCalc3::AAParams::getH2BASCORE() const
        {
            return privateH2BASCORE;
        }

        void SSRCalc3::AAParams::setH2BASCORE(double value)
        {
            privateH2BASCORE = value;
        }

        double SSRCalc3::AAParams::getH2CMULT() const
        {
            return privateH2CMULT;
        }

        void SSRCalc3::AAParams::setH2CMULT(double value)
        {
            privateH2CMULT = value;
        }

        SSRCalc3::AAParams::AAParams(double rc, double rc1, double rc2, double rcn, double rcn2, double rcs, double rc1s, double rc2s, double rcns, double rcn2s, double undkrh, double amass, double ct, double nt, double pk, double h2bascore, double h2cmult)
        {
            setRC(rc);
            setRC1(rc1);
            setRC2(rc2);
            setRCN(rcn);
            setRCN2(rcn2);
            setRCS(rcs);
            setRC1S(rc1s);
            setRC2S(rc2s);
            setRCNS(rcns);
            setRCN2S(rcn2s);
            setUndKRH(undkrh);
            setAMASS(amass);
            setCT(ct);
            setNT(nt);
            setPK(pk);
            setH2BASCORE(h2bascore);
            setH2CMULT(h2cmult);
        }

        std::string HelpersLocal::ReplaceAAs(std::vector<char> &s, const std::string &aas, const std::string &newValue)
        {
            StringBuilder *sb = new StringBuilder();
            bool allAAs = (aas == "A-Z"); // Not L10N
            for (auto c : s)
            {
                if (!allAAs && aas.find(c) != std::string::npos)
                {
                    sb->append(newValue);
                }
                else if (allAAs && std::isalpha(c) && std::isupper(c))
                {
                    sb->append(newValue);
                }
                else
                {
                    sb->append(c);
                }
            }

            delete sb;
            return sb->toString();
        }

        bool HelpersLocal::ContainsAA(std::vector<char> &s, const std::string &aas)
        {
            for (auto c : s)
            {
                if (aas.find(c) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
        }

        std::string HelpersLocal::Backwards(std::vector<char> &s)
        {
            StringBuilder *sb = new StringBuilder();
            for (char c : std::reverse(s.begin(), s.end()))
            {
                sb->append(c);
            }

            delete sb;
            return sb->toString();
        }
    }
}
