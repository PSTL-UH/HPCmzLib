#include "TestIsolation.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "FakeMsDataFile.h"
#include "../MzLibUtil/Tolerance.h"
#include "Sort.h"
#include "MzLibAssert.h"


int main ( int argc, char **argv )
{
    int i=0;
    
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

    std::cout << ++i << ". TestDistribtion" << std::endl;    
    Test::TestIsolation::TestDistribution();

#ifdef LATER    
    std::cout << ++i << ". TestCoIsolation" << std::endl;    
    Test::TestIsolation::TestCoIsolation();

    std::cout << ++i << ". TestCoIsolationDifferentCharge" << std::endl;    
    Test::TestIsolation::TestCoIsolationDifferentCharge();
#endif

    return 0;
}

    
namespace Test
{

    void TestIsolation::TestDistribution()
    {
        // Testcase abstracted from MzSpectrum static constructor, which produced wrong results
        // in the C++ code for a number of Averagenies. Using 402 as the testcase here.
        double averageC = 4.9384;
        double averageH = 7.7583;
        double averageO = 1.4773;
        double averageN = 1.3577;
        double averageS = 0.0417;
        double fineRes = 0.125;
        double minRes = 1e-8;
        
        double averagineMultiplier = (402 + 1) / 2.0;
        ChemicalFormula *chemicalFormula = new ChemicalFormula();
        chemicalFormula->Add(PeriodicTable::GetElement("C"), FloatingPointToInteger::ToInt32(averageC * averagineMultiplier));
        chemicalFormula->Add(PeriodicTable::GetElement("H"), FloatingPointToInteger::ToInt32(averageH * averagineMultiplier));
        chemicalFormula->Add(PeriodicTable::GetElement("O"), FloatingPointToInteger::ToInt32(averageO * averagineMultiplier));
        chemicalFormula->Add(PeriodicTable::GetElement("N"), FloatingPointToInteger::ToInt32(averageN * averagineMultiplier));
        chemicalFormula->Add(PeriodicTable::GetElement("S"), FloatingPointToInteger::ToInt32(averageS * averagineMultiplier));

        IsotopicDistribution *ye = IsotopicDistribution::GetDistribution(chemicalFormula, fineRes, minRes);
        auto masses = ye->getMasses();
        auto intensities = ye->getIntensities();

        Assert::AreEqual(41, (int)masses.size());
        Assert::AreEqual(41, (int)intensities.size());
        
        Sort::SortPairs ( intensities, masses, intensities.size() );
        std::reverse (intensities.begin(), intensities.end());
        std::reverse (masses.begin(), masses.end() );

        std::vector<double> correctMasses = {
            22387.3674872345, 22388.3698277475, 22386.3651216507, 22389.3721449407,
            22385.3627291326, 22390.3744404439, 22384.3603076703, 22391.3767157654,
            22392.3789723397, 22383.3578550999, 22393.3812114936, 22382.3553691138,
            22394.3834344607, 22381.3528471741, 22395.3856424326, 22396.3878364508,
            22380.3502865626, 22397.3900176352, 22379.3476844339, 22398.3921869075,
            22399.394345375,  22378.3450374768, 22400.396493421, 22401.3986327855,
            22377.3423423287, 22402.4007652116, 22403.4028886327, 22376.3395954309,
            22404.4050071897, 22405.4071384615, 22406.4092496712, 22375.336792184,
            22407.4113563587, 22408.4134225559, 22409.415395882, 22374.3339286164,
            22410.4174286062, 22411.4191270467, 22412.4191901848, 22413.4214475477,
            22414.4232805687
        };

        for ( auto i=0; i < correctMasses.size(); i++ ) {
            if ( i < masses.size() ) 
                Assert::AreEqual ( masses[i], correctMasses[i], 1e-9);
        }
        
        std::vector<double> correctIntensities = {
            0.101160406328188,    0.0998481702818441,   0.0959607944582527,   0.0927261419919309,
            0.0847459988533179,   0.0813643833084005,   0.0692105466566187,   0.0677086140079536,
            0.0536102193090286,   0.0518521714685017,   0.0405045279575001,   0.0352908625750592,
            0.0292775773487979,   0.0215573069381014,   0.0202932861770423,   0.0135165926825222,
            0.0116375795320892,   0.00866772649669881,  0.00544071787689993,  0.00536067724396436,
            0.00320254821647334,  0.00214238911722909,  0.0018508489488471,   0.00103613039291182,
            0.000682373968256481, 0.000562533128459472, 0.0002965507785107,   0.000164878341442621,
            0.000151916364739082, 7.56662849828277E-05, 3.66978748742802E-05, 2.6877248426516E-05,
            1.7307470110462E-05,  7.94432474207946E-06, 3.53140276858043E-06, 2.21775955601881E-06,
            1.49644014916668E-06, 6.05425090334263E-07, 2.08063164152774E-07, 6.90000928179403E-08,
            1.13476945437662E-08
        };

        for ( auto i=0; i < correctIntensities.size(); i++ ) {
            if ( i < intensities.size() ) 
                Assert::AreEqual ( intensities[i], correctIntensities[i], 1e-9);
        }

    }

#ifdef LATER
    void TestIsolation::TestCoIsolation()
    {
        Peptide *pep1 = new Peptide("AAAAAA");
        Peptide *pep2 = new Peptide("AAA[H]AAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<MsDataScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Concat(dist2->getMasses())->OrderBy([&] (std::any b)
        {
        delete pep2;
        delete pep1;
            return b;
        })->Select([&] (std::any b)
        {
            b::ToMz(1);
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzSpectrum *MS1 = new MzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, false, Polarity::Positive, 1.0, &tempVar, "first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzSpectrum *MS2 = new MzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;
        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, false, Polarity::Positive, 2.0, &tempVar2, "second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "", std::make_optional(selectedIonMz), std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), std::make_optional(DissociationType::HCD), std::make_optional(1), std::nullopt);

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = myMsDataFile->GetAllScansList().back();

        int maxAssumedChargeState = 1;
        Tolerance *massTolerance = Tolerance::ParseToleranceString("10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->OneBasedPrecursorScanNumber->Value)->MassSpectrum, 1, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(2, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::monoisotopicMass::ToMz(b::charge).ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::monoisotopicMass::ToMz(b::charge).ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }

    void TestIsolation::TestCoIsolationDifferentCharges()
    {
        Peptide *pep1 = new Peptide("AAAAAA");
        Peptide *pep2 = new Peptide("AAAAAAA[H21]AAAAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<MsDataScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Select([&] (std::any b)
        {
            b::ToMz(1);
        }).Concat(dist2->getMasses().Select([&] (std::any b)
        {
            b::ToMz(2);
        }))->OrderBy([&] (std::any b)
        {
        delete pep2;
        delete pep1;
            return b;
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzSpectrum *MS1 = new MzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, false, Polarity::Positive, 1.0, &tempVar, "first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzSpectrum *MS2 = new MzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;

        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, false, Polarity::Positive, 2.0, &tempVar2, "second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "", std::make_optional(selectedIonMz), std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), std::make_optional(DissociationType::HCD), std::make_optional(1), std::nullopt);

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = myMsDataFile->GetAllScansList().back();

        int maxAssumedChargeState = 2;
        Tolerance *massTolerance = Tolerance::ParseToleranceString("10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->OneBasedPrecursorScanNumber->Value)->MassSpectrum, 1, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 2;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }
#endif
}
