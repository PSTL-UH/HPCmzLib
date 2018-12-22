#include "TestMzML.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "FakeMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScanWithPrecursor.h"
#include "../MassSpectrometry/MzSpectra/IMzPeak.h"
#include "../MassSpectrometry/MzSpectra/IMzSpectrum.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/IMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScan.h"
#include "../Proteomics/Peptide.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/ChemicalFormulaModification.h"
#include "../Proteomics/ModificationSites.h"
#include "../Proteomics/FragmentTypes.h"
#include "../MzIdentML/mzIdentML.Generated.MzIdentMLType.h"
#include "../MzIdentML/mzIdentML.Generated.DataCollectionType.h"
#include "../MzIdentML/mzIdentML.Generated.AnalysisDataType.h"
#include "../MzIdentML/mzIdentML.Generated.SpectrumIdentificationListType.h"
#include "../MzIdentML/mzIdentML.Generated.SpectrumIdentificationResultType.h"
#include "../MzIdentML/mzIdentML.Generated.SpectrumIdentificationItemType.h"
#include "../MzIdentML/mzIdentML.Generated.CVParamType.h"
#include "../MzIdentML/mzIdentML.Generated.IonTypeType.h"
#include "../MzIdentML/mzIdentML.Generated.FragmentArrayType.h"
#include "../MzIdentML/mzIdentML.Generated.PeptideEvidenceRefType.h"
#include "../MzIdentML/mzIdentML.Generated.InputsType.h"
#include "../MzIdentML/mzIdentML.Generated.SpectraDataType.h"
#include "../MzIdentML/mzIdentML.Generated.FileFormatType.h"
#include "../MzIdentML/mzIdentML.Generated.SequenceCollectionType.h"
#include "../MzIdentML/mzIdentML.Generated.PeptideEvidenceType.h"
#include "../MzIdentML/mzIdentML.Generated.PeptideType.h"
#include "../MzIdentML/mzIdentML.Generated.ModificationType.h"
#include "../MzIdentML/mzIdentML.Generated.DBSequenceType.h"
#include "../Proteomics/Modification.h"
#include "../MzIdentML/mzIdentML.Generated.AnalysisProtocolCollectionType.h"
#include "../MzIdentML/mzIdentML.Generated.SpectrumIdentificationProtocolType.h"
#include "../MzIdentML/MzidIdentifications.h"
#include "../MzIdentML/mzIdentML110.Generated.MzIdentMLType.h"
#include "../MzIdentML/mzIdentML110.Generated.DataCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.AnalysisDataType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationListType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationResultType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationItemType.h"
#include "../MzIdentML/mzIdentML110.Generated.CVParamType.h"
#include "../MzIdentML/mzIdentML110.Generated.IonTypeType.h"
#include "../MzIdentML/mzIdentML110.Generated.FragmentArrayType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideEvidenceRefType.h"
#include "../MzIdentML/mzIdentML110.Generated.InputsType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectraDataType.h"
#include "../MzIdentML/mzIdentML110.Generated.FileFormatType.h"
#include "../MzIdentML/mzIdentML110.Generated.SequenceCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideEvidenceType.h"
#include "../MzIdentML/mzIdentML110.Generated.PeptideType.h"
#include "../MzIdentML/mzIdentML110.Generated.ModificationType.h"
#include "../MzIdentML/mzIdentML110.Generated.DBSequenceType.h"
#include "../MzIdentML/mzIdentML110.Generated.AnalysisProtocolCollectionType.h"
#include "../MzIdentML/mzIdentML110.Generated.SpectrumIdentificationProtocolType.h"
#include "../Proteomics/Fragment.h"
#include "../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
using namespace MzIdentML;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void TestMzML::AnotherMzMLtest() {
        std::vector<IMzmlScan*> scans(4);

        std::vector<double> intensities1 = {1};
        std::vector<double> mz1 = {50};
        MzmlMzSpectrum *massSpec1 = new MzmlMzSpectrum(mz1, intensities1, false);
        MzRange tempVar(1, 100);
        scans[0] = new MzmlScan(1, massSpec1, 1, true, Polarity::Positive, 1, &tempVar, L"f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, L"1");

        std::vector<double> intensities2 = {1};
        std::vector<double> mz2 = {30};
        MzmlMzSpectrum *massSpec2 = new MzmlMzSpectrum(mz2, intensities2, false);
        MzRange tempVar2(1, 100);
        scans[1] = new MzmlScanWithPrecursor(2, massSpec2, 2, true, Polarity::Positive, 2, &tempVar2, L"f", MZAnalyzerType::Orbitrap, massSpec2->getSumOfAllY(), 50, std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), DissociationType::CID, std::make_optional(1), std::nullopt, std::nullopt, L"2");

        std::vector<double> intensities3 = {1};
        std::vector<double> mz3 = {50};
        MzmlMzSpectrum *massSpec3 = new MzmlMzSpectrum(mz3, intensities3, false);
        MzRange tempVar3(1, 100);
        scans[2] = new MzmlScan(3, massSpec3, 1, true, Polarity::Positive, 1, &tempVar3, L"f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, L"3");

        std::vector<double> intensities4 = {1};
        std::vector<double> mz4 = {30};
        MzmlMzSpectrum *massSpec4 = new MzmlMzSpectrum(mz4, intensities4, false);
        MzRange tempVar4(1, 100);
        scans[3] = new MzmlScanWithPrecursor(4, massSpec4, 2, true, Polarity::Positive, 2, &tempVar4, L"f", MZAnalyzerType::Orbitrap, massSpec2->getSumOfAllY(), 50, std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), DissociationType::CID, std::make_optional(3), std::nullopt, std::nullopt, L"4");

        FakeMsDataFile *f = new FakeMsDataFile(scans);

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"what.mzML"), false);

        Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"what.mzML"));

        auto scanWithPrecursor = dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(ok->Last([&] (std::any b) {
            dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(b) != nullptr;
        }));

        Assert::AreEqual(3, scanWithPrecursor->getOneBasedPrecursorScanNumber());

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec4' statement was not added since massSpec4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec3' statement was not added since massSpec3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestMzML::DifferentAnalyzersTest() {
        std::vector<IMzmlScan*> scans(2);

        std::vector<double> intensities1 = {1};
        std::vector<double> mz1 = {50};
        MzmlMzSpectrum *massSpec1 = new MzmlMzSpectrum(mz1, intensities1, false);
        MzRange tempVar(1, 100);
        scans[0] = new MzmlScan(1, massSpec1, 1, true, Polarity::Positive, 1, &tempVar, L"f", MZAnalyzerType::Orbitrap, massSpec1->getSumOfAllY(), std::nullopt, L"1");

        std::vector<double> intensities2 = {1};
        std::vector<double> mz2 = {30};
        MzmlMzSpectrum *massSpec2 = new MzmlMzSpectrum(mz2, intensities2, false);
        MzRange tempVar2(1, 100);
        scans[1] = new MzmlScanWithPrecursor(2, massSpec2, 2, true, Polarity::Positive, 2, &tempVar2, L"f", MZAnalyzerType::IonTrap3D, massSpec2->getSumOfAllY(), 50, std::nullopt, std::nullopt, std::make_optional(50), std::make_optional(1), DissociationType::CID, std::make_optional(1), std::nullopt, std::nullopt, L"2");

        FakeMsDataFile *f = new FakeMsDataFile(scans);

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(f, FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"asdfefsf.mzML"), false);

        Mzml *ok = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"asdfefsf.mzML"));

        Assert::AreEqual(MZAnalyzerType::Orbitrap, ok->front().MzAnalyzer);
        Assert::AreEqual(MZAnalyzerType::IonTrap3D, ok->back().MzAnalyzer);

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec2' statement was not added since massSpec2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete massSpec1' statement was not added since massSpec1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestMzML::Setup() {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(LR"(elements.dat)");
    }

    void TestMzML::LoadMzmlTest() {
        Mzml *a = Mzml::LoadAllStaticData(LR"(tiny.pwiz.1.1.mzML)");

        auto ya = a->GetOneBasedScan(1)->MassSpectrum;
        Assert::AreEqual(15, ya->Size);
        auto ya2 = a->GetOneBasedScan(2)->MassSpectrum;
        Assert::AreEqual(10, ya2->Size);
        auto ya3 = a->GetOneBasedScan(3)->MassSpectrum;
        Assert::AreEqual(0, ya3->Size);
        auto ya4 = a->GetOneBasedScan(4)->MassSpectrum;
        Assert::AreEqual(15, ya4->Size);

        IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *ok = a;

        Assert::AreEqual(1, ok->GetClosestOneBasedSpectrumNumber(5));
    }

    void TestMzML::LoadMzmlAnotherTest() {
        Mzml *a = Mzml::LoadAllStaticData(LR"(small.pwiz.1.1.mzML)");
        Assert::AreEqual(19914, a->front().MassSpectrum.Size);
        Assert::AreEqual(485, a->First([&] (std::any bb) {
            return bb->MsnOrder == 2;
        }).MassSpectrum.Size);
        double basePeak = a->front().MassSpectrum.YofPeakWithHighestY;
        Assert::AreEqual(42, a->front().MassSpectrum.YArray->Count([&] (std::any bb) {
            return bb >= 0.1 * basePeak;
        }));

        Mzml *b = Mzml::LoadAllStaticData(LR"(small.pwiz.1.1.mzML)", std::make_optional(400));
        Assert::AreEqual(400, b->front().MassSpectrum.Size);
        Assert::AreEqual(400, b->First([&] (std::any bb) {
            return bb->MsnOrder == 2;
        }).MassSpectrum.Size);

        Mzml *c = Mzml::LoadAllStaticData(LR"(small.pwiz.1.1.mzML)", , std::make_optional(0.1));
        Assert::AreEqual(42, c->front().MassSpectrum.Size);
        Assert::AreEqual(6, c->First([&] (std::any bb) {
            return bb->MsnOrder == 2;
        }).MassSpectrum.Size);

        Mzml *d = Mzml::LoadAllStaticData(LR"(small.pwiz.1.1.mzML)", , std::make_optional(0.1), false);
        Assert::AreEqual(19914, d->front().MassSpectrum.Size);
        Assert::AreEqual(6, d->First([&] (std::any bb) {
            return bb->MsnOrder == 2;
        }).MassSpectrum.Size);

        Mzml *e = Mzml::LoadAllStaticData(LR"(small.pwiz.1.1.mzML)", , std::make_optional(0.1), , false);
        Assert::AreEqual(42, e->front().MassSpectrum.Size);
        Assert::AreEqual(485, e->First([&] (std::any bb) {
            return bb->MsnOrder == 2;
        }).MassSpectrum.Size);
    }

    void TestMzML::LoadMzmlFromConvertedMGFTest() {
        Mzml *a = Mzml::LoadAllStaticData(LR"(tester.mzML)");

        auto ya = a->GetOneBasedScan(1)->MassSpectrum;
        Assert::AreEqual(192, ya->Size);
        auto ya2 = a->GetOneBasedScan(3)->MassSpectrum;
        Assert::AreEqual(165, ya2->Size);
        auto ya3 = a->GetOneBasedScan(5)->MassSpectrum;
        Assert::AreEqual(551, ya3->Size);
        auto ya4 = a->GetOneBasedScan(975)->MassSpectrum;
        Assert::AreEqual(190, ya4->Size);

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, L"CreateFileFromConvertedMGF.mzML", false);

        Mzml *b = Mzml::LoadAllStaticData(LR"(CreateFileFromConvertedMGF.mzML)");

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(b, L"CreateFileFromConvertedMGF2.mzML", false);
    }

    void TestMzML::WriteMzmlTest() {
        auto peptide = new Peptide(L"GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        OldSchoolChemicalFormulaModification *carbamidomethylationOfCMod = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(L"H3C2NO"), L"carbamidomethylation of C", ModificationSites::C);
        peptide->AddModification(carbamidomethylationOfCMod);

        MzmlMzSpectrum *MS1 = CreateSpectrum(peptide->GetChemicalFormula(), 300, 2000, 1);

        MzmlMzSpectrum *MS2 = CreateMS2spectrum(peptide->Fragment(FragmentTypes::b | FragmentTypes::y, true), 100, 1500);

        std::vector<IMzmlScan*> Scans(2);
        MzRange tempVar(300, 2000);
        Scans[0] = new MzmlScan(1, MS1, 1, false, Polarity::Positive, 1.0, &tempVar, L" first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::make_optional(1), L"1");

        MzRange tempVar2(100, 1500);
        Scans[1] = new MzmlScanWithPrecursor(2, MS2, 2, false, Polarity::Positive, 2.0, &tempVar2, L" second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), 1134.26091302033, std::make_optional(3), std::make_optional(0.141146966879759), std::make_optional(1134.3), std::make_optional(1), DissociationType::Unknown, std::make_optional(1), std::make_optional(1134.26091302033), std::make_optional(1), L"2");

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto oldFirstValue = myMsDataFile->GetOneBasedScan(1)->MassSpectrum.FirstX;

        auto secondScan = dynamic_cast<IMsDataScanWithPrecursor<MzmlMzSpectrum*>*>(myMsDataFile->GetOneBasedScan(2));
        Assert::AreEqual(1, secondScan->getIsolationRange()->Maximum - secondScan->getIsolationRange()->Minimum);

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(myMsDataFile, L"argh.mzML", false);

        Mzml *okay = Mzml::LoadAllStaticData(LR"(argh.mzML)");
        okay->GetOneBasedScan(2);

        Assert::AreEqual(1, okay->GetClosestOneBasedSpectrumNumber(1));
        Assert::AreEqual(2, okay->GetClosestOneBasedSpectrumNumber(2));

        auto newFirstValue = okay->GetOneBasedScan(1)->MassSpectrum.FirstX;
        Assert::AreEqual(oldFirstValue, newFirstValue, 1e-9);

        auto secondScan2 = dynamic_cast<IMsDataScanWithPrecursor<MzmlMzSpectrum*>*>(okay->GetOneBasedScan(2));

        Assert::AreEqual(1, secondScan2->getIsolationRange()->Maximum - secondScan2->getIsolationRange()->Minimum);

        secondScan2->MassSpectrum.ReplaceXbyApplyingFunction([&] (a) {
            44;
        });
        Assert::AreEqual(44, secondScan2->MassSpectrum.LastX);

//C# TO C++ CONVERTER TODO TASK: A 'delete myMsDataFile' statement was not added since myMsDataFile was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete carbamidomethylationOfCMod' statement was not added since carbamidomethylationOfCMod was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestMzML::MzidTest() {
        XmlSerializer *_indexedSerializer = new XmlSerializer(mzIdentML::Generated::MzIdentMLType::typeid);
        auto _mzid = new mzIdentML::Generated::MzIdentMLType();
        mzIdentML::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID(L"spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML::Generated::CVParamType *tempVar6 = new mzIdentML::Generated::CVParamType();
        tempVar6->setaccession(L"MS:1002354");
        tempVar6->setvalue(L"0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML::Generated::IonTypeType*>(1);
        mzIdentML::Generated::IonTypeType *tempVar7 = new mzIdentML::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML::Generated::FragmentArrayType *tempVar8 = new mzIdentML::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref(L"PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->passThreshold = true;

        mzIdentML::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML::Generated::SpectraDataType*>(1));
        mzIdentML::Generated::SpectraDataType *tempVar11 = new mzIdentML::Generated::SpectraDataType();
        mzIdentML::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML::Generated::CVParamType();
        .FileFormat::cvParam->name = L"mzML format";
        mzIdentML::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML::Generated::PeptideEvidenceType*>(1));
        mzIdentML::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setisDecoy(false);
        tempVar14->setpeptide_ref(L"P_1");
        tempVar14->setdBSequence_ref(L"DB_1");
        tempVar14->setid(L"PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML::Generated::PeptideType*>(1));
        mzIdentML::Generated::PeptideType *tempVar15 = new mzIdentML::Generated::PeptideType();
        tempVar15->setid(L"P_1");
        tempVar15->setPeptideSequence(L"GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML::Generated::DBSequenceType*>(1));
        mzIdentML::Generated::DBSequenceType *tempVar16 = new mzIdentML::Generated::DBSequenceType();
        tempVar16->setid(L"DB_1");
        tempVar16->setname(L"Protein name");
        tempVar16->setaccession(L"ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML::Generated::ModificationType *tempVar17 = new mzIdentML::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML::Generated::CVParamType *tempVar18 = new mzIdentML::Generated::CVParamType();
        tempVar18->setaccession(L"MS:1001460");
        tempVar18->setname(L"unknown modification");
        tempVar18->setvalue(L"Carbamidomethyl");
        tempVar18->setcvRef(L"PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML::Generated::CVParamType *tempVar21 = new mzIdentML::Generated::CVParamType();
        tempVar21->setunitName(L"dalton");
        tempVar21->setvalue(L"0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML::Generated::CVParamType*>(1);
        mzIdentML::Generated::CVParamType *tempVar22 = new mzIdentML::Generated::CVParamType();
        tempVar22->setunitName(L"dalton");
        tempVar22->setvalue(L"0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter(L"myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications(L"myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual(L"MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual(L"PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual(L"Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual(L"spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual(L"GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual(L"Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual(L"ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual(L"2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual(L"34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    void TestMzML::Mzid110Test() {
        XmlSerializer *_indexedSerializer = new XmlSerializer(mzIdentML110::Generated::MzIdentMLType::typeid);
        auto _mzid = new mzIdentML110::Generated::MzIdentMLType();
        mzIdentML110::Generated::DataCollectionType tempVar();
        _mzid->setDataCollection(&tempVar);
        mzIdentML110::Generated::AnalysisDataType tempVar2();
        _mzid->getDataCollection()->setAnalysisData(&tempVar2);
        _mzid->getDataCollection()->getAnalysisData()->setSpectrumIdentificationList(std::vector<mzIdentML110::Generated::SpectrumIdentificationListType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationListType *tempVar3 = new mzIdentML110::Generated::SpectrumIdentificationListType();
        tempVar3->setSpectrumIdentificationResult(std::vector<mzIdentML110::Generated::SpectrumIdentificationResultType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0] = tempVar3;
        mzIdentML110::Generated::SpectrumIdentificationResultType *tempVar4 = new mzIdentML110::Generated::SpectrumIdentificationResultType();
        tempVar4->setspectrumID(L"spectrum 2");
        tempVar4->setSpectrumIdentificationItem(std::vector<mzIdentML110::Generated::SpectrumIdentificationItemType*>(50));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0] = tempVar4;
        mzIdentML110::Generated::SpectrumIdentificationItemType *tempVar5 = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        tempVar5->setexperimentalMassToCharge(1134.2609130203 + 0.000001 * 1134.2609130203 + 0.000001);
        tempVar5->setcalculatedMassToCharge(1134.26091302033);
        tempVar5->setcalculatedMassToChargeSpecified(true);
        tempVar5->setchargeState(3);
        mzIdentML110::Generated::CVParamType *tempVar6 = new mzIdentML110::Generated::CVParamType();
        tempVar6->setaccession(L"MS:1002354");
        tempVar6->setvalue(L"0.05");
        tempVar5->setcvParam({tempVar6});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0] = tempVar5;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[1] = new mzIdentML110::Generated::SpectrumIdentificationItemType();
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->Fragmentation = std::vector<mzIdentML110::Generated::IonTypeType*>(1);
        mzIdentML110::Generated::IonTypeType *tempVar7 = new mzIdentML110::Generated::IonTypeType();
        tempVar7->setFragmentArray(std::vector<mzIdentML110::Generated::FragmentArrayType*>(1));
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0] = tempVar7;
        mzIdentML110::Generated::FragmentArrayType *tempVar8 = new mzIdentML110::Generated::FragmentArrayType();
        tempVar8->setvalues({200, 300, 400});
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].Fragmentation[0].FragmentArray[0] = tempVar8;
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0]->PeptideEvidenceRef = std::vector<mzIdentML110::Generated::PeptideEvidenceRefType*>(1);
        mzIdentML110::Generated::PeptideEvidenceRefType *tempVar9 = new mzIdentML110::Generated::PeptideEvidenceRefType();
        tempVar9->setpeptideEvidence_ref(L"PE_1");
        _mzid->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[0].SpectrumIdentificationItem[0].PeptideEvidenceRef[0] = tempVar9;
        mzIdentML110::Generated::InputsType tempVar10();
        _mzid->getDataCollection()->setInputs(&tempVar10);
        _mzid->getDataCollection()->getInputs()->setSpectraData(std::vector<mzIdentML110::Generated::SpectraDataType*>(1));
        mzIdentML110::Generated::SpectraDataType *tempVar11 = new mzIdentML110::Generated::SpectraDataType();
        mzIdentML110::Generated::FileFormatType tempVar12();
        tempVar11->setFileFormat(&tempVar12);
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0] = tempVar11;
        _mzid->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat->cvParam = new mzIdentML110::Generated::CVParamType();
        .FileFormat::cvParam->name = L"mzML format";
        mzIdentML110::Generated::SequenceCollectionType tempVar13();
        _mzid->setSequenceCollection(&tempVar13);
        _mzid->getSequenceCollection()->setPeptideEvidence(std::vector<mzIdentML110::Generated::PeptideEvidenceType*>(1));
        mzIdentML110::Generated::PeptideEvidenceType *tempVar14 = new mzIdentML110::Generated::PeptideEvidenceType();
        tempVar14->setendSpecified(true);
        tempVar14->setstartSpecified(true);
        tempVar14->setisDecoy(false);
        tempVar14->setstart(2);
        tempVar14->setend(34);
        tempVar14->setdBSequence_ref(L"DB_1");
        tempVar14->setpeptide_ref(L"P_1");
        tempVar14->setid(L"PE_1");
        _mzid->getSequenceCollection()->getPeptideEvidence()[0] = tempVar14;
        _mzid->getSequenceCollection()->setPeptide(std::vector<mzIdentML110::Generated::PeptideType*>(1));
        mzIdentML110::Generated::PeptideType *tempVar15 = new mzIdentML110::Generated::PeptideType();
        tempVar15->setid(L"P_1");
        tempVar15->setPeptideSequence(L"GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR");
        tempVar15->setModification(std::vector<mzIdentML110::Generated::ModificationType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0] = tempVar15;
        _mzid->getSequenceCollection()->setDBSequence(std::vector<mzIdentML110::Generated::DBSequenceType*>(1));
        mzIdentML110::Generated::DBSequenceType *tempVar16 = new mzIdentML110::Generated::DBSequenceType();
        tempVar16->setid(L"DB_1");
        tempVar16->setname(L"Protein name");
        tempVar16->setaccession(L"ACCESSION");
        _mzid->getSequenceCollection()->getDBSequence()[0] = tempVar16;
        mzIdentML110::Generated::ModificationType *tempVar17 = new mzIdentML110::Generated::ModificationType();
        tempVar17->setlocationSpecified(true);
        tempVar17->setlocation(17);
        tempVar17->setmonoisotopicMassDeltaSpecified(true);
        tempVar17->setmonoisotopicMassDelta(57.02146373);
        tempVar17->setcvParam(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0] = tempVar17;
        mzIdentML110::Generated::CVParamType *tempVar18 = new mzIdentML110::Generated::CVParamType();
        tempVar18->setaccession(L"MS:1001460");
        tempVar18->setname(L"unknown modification");
        tempVar18->setvalue(L"Carbamidomethyl");
        tempVar18->setcvRef(L"PSI-MS");
        _mzid->getSequenceCollection()->getPeptide()[0]->Modification[0].cvParam[0] = tempVar18;
        mzIdentML110::Generated::AnalysisProtocolCollectionType tempVar19();
        _mzid->setAnalysisProtocolCollection(&tempVar19);
        _mzid->getAnalysisProtocolCollection()->setSpectrumIdentificationProtocol(std::vector<mzIdentML110::Generated::SpectrumIdentificationProtocolType*>(1));
        mzIdentML110::Generated::SpectrumIdentificationProtocolType *tempVar20 = new mzIdentML110::Generated::SpectrumIdentificationProtocolType();
        tempVar20->setParentTolerance(std::vector<mzIdentML110::Generated::CVParamType*>(1));
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0] = tempVar20;
        mzIdentML110::Generated::CVParamType *tempVar21 = new mzIdentML110::Generated::CVParamType();
        tempVar21->setunitName(L"dalton");
        tempVar21->setvalue(L"0.1");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance[0] = tempVar21;
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance = std::vector<mzIdentML110::Generated::CVParamType*>(1);
        mzIdentML110::Generated::CVParamType *tempVar22 = new mzIdentML110::Generated::CVParamType();
        tempVar22->setunitName(L"dalton");
        tempVar22->setvalue(L"0.01");
        _mzid->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance[0] = tempVar22;
        TextWriter *writer = new StreamWriter(L"myIdentifications.mzid");
        _indexedSerializer->Serialize(writer, _mzid);
        writer->Close();

        auto identifications = new MzidIdentifications(L"myIdentifications.mzid");

        Assert::AreEqual(1134.26091302033, identifications->CalculatedMassToCharge(0, 0));
        Assert::AreEqual(3, identifications->ChargeState(0, 0));
        Assert::AreEqual(1, identifications->getCount());
        Assert::AreEqual(1134.26091302033 + 0.000001 * 1134.2609130203 + 0.000001, identifications->ExperimentalMassToCharge(0, 0), 1e-10);
        Assert::IsFalse(identifications->IsDecoy(0, 0));
        Assert::AreEqual(L"MS:1001460", identifications->ModificationAcession(0, 0, 0));
        Assert::AreEqual(L"PSI-MS", identifications->ModificationDictionary(0, 0, 0));
        Assert::AreEqual(L"Carbamidomethyl", identifications->ModificationValue(0, 0, 0));
        Assert::AreEqual(17, identifications->ModificationLocation(0, 0, 0));
        Assert::AreEqual(57.02146373, identifications->ModificationMass(0, 0, 0));
        Assert::AreEqual(L"spectrum 2", identifications->Ms2SpectrumID(0));
        Assert::AreEqual(1, identifications->NumModifications(0, 0));
        Assert::AreEqual(L"GPEAPPPALPAGAPPPCTAVTSDHLNSLLGNILR", identifications->PeptideSequenceWithoutModifications(0, 0));
        Assert::AreEqual(0.1, identifications->getParentTolerance()->getValue());
        Assert::AreEqual(0.01, identifications->getFragmentTolerance()->getValue());
        Assert::AreEqual(.05, identifications->QValue(0, 0));
        Assert::AreEqual(L"Protein name", identifications->ProteinFullName(0, 0));
        Assert::AreEqual(L"ACCESSION", identifications->ProteinAccession(0, 0));
        Assert::AreEqual({200, 300, 400}, identifications->MatchedIons(0, 0, 0));
        Assert::AreEqual(3, identifications->MatchedIonCounts(0, 0, 0));
        Assert::AreEqual(L"2", identifications->StartResidueInProtein(0, 0));
        Assert::AreEqual(L"34", identifications->EndResidueInProtein(0, 0));
        Assert::AreEqual(2, identifications->NumPSMsFromScan(0));

        delete identifications;
//C# TO C++ CONVERTER TODO TASK: A 'delete writer' statement was not added since writer was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete _mzid' statement was not added since _mzid was passed to a method or constructor. Handle memory management manually.
        delete _indexedSerializer;
    }

    MzmlMzSpectrum *TestMzML::CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2) {
        std::vector<double> allMasses;
        std::vector<double> allIntensities;
        for (auto f : fragments) {
            auto spec = CreateSpectrum(f->getThisChemicalFormula(), v1, v2, 2);
            for (int i = 0; i < spec->getSize(); i++) {
                allMasses.push_back(spec->getXArray()[i]);
                allIntensities.push_back(spec->getYArray()[i]);
            }
        }
        auto allMassesArray = allMasses.ToArray();
        auto allIntensitiessArray = allIntensities.ToArray();

        Array::Sort(allMassesArray, allIntensitiessArray);
        return new MzmlMzSpectrum(allMassesArray, allIntensitiessArray, false);
    }

    MzmlMzSpectrum *TestMzML::CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge) {
        IsotopicDistribution *isodist = IsotopicDistribution::GetDistribution(f, 0.1);

        return new MzmlMzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);
        //massSpectrum1 = massSpectrum1.FilterByNumberOfMostIntense(5);

        //var chargeToLookAt = minCharge;
        //var correctedSpectrum = massSpectrum1.NewSpectrumApplyFunctionToX(s => s.ToMz(chargeToLookAt));

        //List<double> allMasses = new List<double>();
        //List<double> allIntensitiess = new List<double>();

        //while (correctedSpectrum.FirstX > lowerBound)
        //{
        //    foreach (var thisPeak in correctedSpectrum)
        //    {
        //        if (thisPeak.Mz > lowerBound && thisPeak.Mz < upperBound)
        //        {
        //            allMasses.Add(thisPeak.Mz);
        //            allIntensitiess.Add(thisPeak.Intensity);
        //        }
        //    }
        //    chargeToLookAt += 1;
        //    correctedSpectrum = massSpectrum1.NewSpectrumApplyFunctionToX(s => s.ToMz(chargeToLookAt));
        //}

        //var allMassesArray = allMasses.ToArray();
        //var allIntensitiessArray = allIntensitiess.ToArray();

        //Array.Sort(allMassesArray, allIntensitiessArray);

        //return new MzmlMzSpectrum(allMassesArray, allIntensitiessArray, false);
    }
}
