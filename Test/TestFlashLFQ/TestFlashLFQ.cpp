#include "TestFlashLFQ.h"
#include "../FlashLFQ/SpectraFileInfo.h"
#include "../FlashLFQ/ProteinGroup.h"
#include "../FlashLFQ/Identification.h"
#include "../FlashLFQ/FlashLfqEngine.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../Test/FakeMsDataFile.h"
#include "../MzML/Mzml.h"
#include "../MzML/MzmlMethods.h"

using namespace IO::MzML;

#include "Assert.h"
#include "Quantiles.h"



int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);

    std::cout << ++i << ". TestFlashLfq" << std::endl;        
    Test::TestFlashLFQ::TestFlashLfq();

    std::cout << ++i << ". TestFlashLfqNormalization" << std::endl;
    Test::TestFlashLFQ::TestFlashLfqNormalization();

    std::cout << ++i << ". TestFlashLfqMergeResults" << std::endl;        
    Test::TestFlashLFQ::TestFlashLfqMergeResults();
    
    std::cout << ++i << ". TestFlashLfqAdvancedProteinQuant" << std::endl;        
    Test::TestFlashLFQ::TestFlashLfqAdvancedProteinQuant();    
    
    std::cout << ++i << ". TestFlashLfqMatchBetweenRuns " << std::endl;        
    Test::TestFlashLFQ::TestFlashLfqMatchBetweenRuns();

#ifdef LATER
    std::cout << ++i << ". TestFlashLfqMatchBetweenRunsProteinQuant " << std::endl;        
    Test::TestFlashLFQ::TestFlashLfqMatchBetweenRunsProteinQuant();

    std::cout << ++i << ". TestPeakSplittingLeft " << std::endl;        
    Test::TestFlashLFQ::TestPeakSplittingLeft();

    std::cout << ++i << ". TestPeakSplittingRight " << std::endl;        
    Test::TestFlashLFQ::TestPeakSplittingRight();

    std::cout << ++i << ". TestPeakSplittingRightWithEmptyScan " << std::endl;        
    Test::TestFlashLFQ::TestPeakSplittingRightWithEmptyScan();

    std::cout << ++i << ". TestToString TestPeakSplittingLeftWithEmptyScan " << std::endl;        
    Test::TestFlashLFQ::TestPeakSplittingLeftWithEmptyScan();

    std::cout << ++i << ".  TestToString " << std::endl;        
    Test::TestFlashLFQ::TestToString();

    std::cout << ++i << ". TestNotFound " << std::endl;        
    Test::TestFlashLFQ::TestNotFound();

    std::cout << ++i << ". TestMergePeaks " << std::endl;        
    Test::TestFlashLFQ::TestMergePeaks();

    std::cout << ++i << ". TestAmbiguous " << std::endl;        
    Test::TestFlashLFQ::TestAmbiguous();

    std::cout << ++i << ". TestPeakMerging " << std::endl;        
    Test::TestFlashLFQ::TestPeakMerging();

    std::cout << ++i << ". TestMatchBetweenRunsWithNoIdsInCommon " << std::endl;        
    Test::TestFlashLFQ::TestMatchBetweenRunsWithNoIdsInCommon();
#endif    

    return 0;
}


namespace Test
{

    void TestFlashLFQ::TestFlashLfq()
    {
        // get the raw file paths
        std::string testdir=std::experimental::filesystem::current_path().string();

        SpectraFileInfo *raw = new SpectraFileInfo(testdir+"/sliced-raw.raw", "a", 0, 0, 0);
        SpectraFileInfo *mzml = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 0, 1, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup *> v1 = {pg};
        std::vector<ProteinGroup *> v2 = {pg};
        std::vector<ProteinGroup *> v3 = {pg};
        std::vector<ProteinGroup *> v4 = {pg};
        Identification *id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v1 );
        Identification *id2 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v2 );
        Identification *id3 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v3 );
        Identification *id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v4 );

        // create the FlashLFQ engine
        std::vector<FlashLFQ::Identification*> iv = {id1, id2, id3, id4 };
        FlashLfqEngine *engine = new FlashLfqEngine(iv, true, false, false, 10.0, 5.0, 5.0, false,
                                                    2, false, true, true, "", 2.5, -1);

        // run the engine
        auto results = engine->Run();

        // check raw results
        // EDGAR: can not handle raw files right now, only mzml
        Assert::IsTrue(results->Peaks[raw].size() == 1);
        if ( results->Peaks[raw].size() > 0 ) {
            Assert::IsTrue(results->Peaks[raw].front()->Intensity > 0);
            Assert::IsTrue(!results->Peaks[raw].front()->IsMbrPeak);
            Assert::IsTrue(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(raw) > 0);
            Assert::IsTrue(results->ProteinGroups["MyProtein"]->GetIntensity(raw) > 0);
        }
        else {
            std::cout << "NOTE: Not running raw file tests.\n";
        }

        // check mzml results
        Assert::IsTrue(results->Peaks[mzml].size() == 1);
        Assert::IsTrue(results->Peaks[mzml].front()->Intensity > 0);
        Assert::IsTrue(!results->Peaks[mzml].front()->IsMbrPeak);
        Assert::IsTrue(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(mzml) > 0);
        Assert::IsTrue(results->ProteinGroups["MyProtein"]->GetIntensity(mzml) > 0);

        // check that condition normalization worked
        int int1 = static_cast<int>(std::round(results->Peaks[mzml].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        //int int2 = static_cast<int>(std::round(results->Peaks[raw].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        //Assert::IsTrue(int1 == int2);

        // test peak output
        results->WriteResults( testdir+"/peaks.tsv", testdir+"/modSeq.tsv", testdir+"/protein.tsv");

        delete engine;
        delete id4;
        delete id3;
        delete id2;
        delete id1;
        delete pg;
        delete mzml;
        delete raw;
    }


    void TestFlashLFQ::TestFlashLfqNormalization()
    {
        // ********************************* check biorep normalization *********************************
        // get the raw file paths
        std::string testdir=std::experimental::filesystem::current_path().string();

        SpectraFileInfo *raw = new SpectraFileInfo(testdir+"/sliced-raw.raw", "a", 0, 0, 0);
        SpectraFileInfo *mzml = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 1, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup *> v1 = {pg};
        std::vector<ProteinGroup *> v2 = {pg};
        Identification *id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v1 );
        Identification *id2 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v2 );

        // create the FlashLFQ engine
        std::vector<FlashLFQ::Identification*> iv = {id1, id2};
        FlashLfqEngine tempVar(iv, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, true, "", 2.5, -1);
        auto results = (&tempVar)->Run();

        // check that biorep normalization worked
        int int1 = static_cast<int>(std::round(results->Peaks[mzml].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        //int int2 = static_cast<int>(std::round(results->Peaks[raw].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::IsTrue(int1 > 0);
        //Assert::IsTrue(int1 == int2);

        // ********************************* check condition normalization *********************************
        raw = new SpectraFileInfo(testdir+"/sliced-raw.raw", "a", 0, 0, 0);
        mzml = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "b", 0, 0, 0);

        std::vector<ProteinGroup *> v3 = {pg};
        std::vector<ProteinGroup *> v4 = {pg};
        Identification *id3 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v3 );
        Identification *id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v4 );

        std::vector<FlashLFQ::Identification*> iv2 = {id3, id4};
        FlashLfqEngine tempVar2(iv2, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, true, "", 2.5, -1);
        results = (&tempVar2)->Run();

        int int3 = static_cast<int>(std::round(results->Peaks[mzml].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        //int int4 = static_cast<int>(std::round(results->Peaks[raw].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::IsTrue(int3 > 0);
        //Assert::IsTrue(int3 == int4);

        // ********************************* check techrep normalization *********************************
        raw = new SpectraFileInfo( testdir+"/sliced-raw.raw", "a", 0, 0, 0);
        mzml = new SpectraFileInfo( testdir+"/sliced-mzml.mzml", "a", 0, 1, 0);

        std::vector<ProteinGroup *> v5 = {pg};
        std::vector<ProteinGroup *> v6 = {pg};
        Identification *id5 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v5 );
        Identification *id6 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v6 );
        
        std::vector<FlashLFQ::Identification*> iv3 = {id5, id6};
        FlashLfqEngine tempVar3(iv3, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, true, "", 2.5, -1);
        results = (&tempVar3)->Run();

        int int5 = static_cast<int>(std::round(results->Peaks[mzml].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        //int int6 = static_cast<int>(std::round(results->Peaks[raw].front()->Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::IsTrue(int5 > 0);
        //Assert::IsTrue(int5 == int6);

        Assert::IsTrue(int1 == int3);
        Assert::IsTrue(int1 == int5);

        // ********************************* check fraction normalization *********************************
        //raw = new SpectraFileInfo(testdir+"/sliced-raw.raw", "a", 0, 0, 0);
        //auto raw2 = new SpectraFileInfo(testdir+"/sliced-raw.raw", "a", 0, 0, 1);
        // Replacing the raw files by the mzml files.
        raw = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 0, 0, 0);
        auto raw2 = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 0, 0, 1);
        mzml = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 1, 0, 0);
        auto mzml2 = new SpectraFileInfo(testdir+"/sliced-mzml.mzml", "a", 1, 0, 1);

        std::vector<ProteinGroup *> v7 = {pg};
        std::vector<ProteinGroup *> v8 = {pg};
        std::vector<ProteinGroup *> v9 = {pg};
        std::vector<ProteinGroup *> v10 = {pg};
        id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v7 );
        id2 = new Identification(raw2, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v8 );
        id3 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v9 );
        id4 = new Identification(mzml2, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v10 );

        std::vector<FlashLFQ::Identification*> iv4 = {id1, id2, id3, id4 };
        FlashLfqEngine tempVar4(iv4, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, true, "", 2.5, -1);
        results = (&tempVar4)->Run();

        //int int7 = static_cast<int>(BankersRounding::round(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(raw) + results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(raw2)));
        int int8 = static_cast<int>(BankersRounding::round(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(mzml) + results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(mzml2)));
        Assert::IsTrue(int8 > 0);
        //Assert::IsTrue(int7 == int8);

        delete id4;
        delete id3;
        delete id2;
        delete id1;
        delete pg;
        delete mzml2;
        delete mzml;
        delete raw;

    }
    
    
    void TestFlashLFQ::TestFlashLfqMergeResults()
    {

        std::string testdir=std::experimental::filesystem::current_path().string();

        SpectraFileInfo *rawA = new SpectraFileInfo(testdir+ "/sliced-raw.raw", "a", 0, 0, 0);
        SpectraFileInfo *mzmlA = new SpectraFileInfo(testdir+ "/sliced-mzml.mzml", "a", 0, 1, 0);

        // create some PSMs
        auto pgA = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup *> v1 = {pgA};
        std::vector<ProteinGroup *> v2 = {pgA};
        std::vector<ProteinGroup *> v3 = {pgA};
        std::vector<ProteinGroup *> v4 = {pgA};
        Identification *id1A = new Identification(rawA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v1);
        Identification *id2A = new Identification(rawA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v2);
        Identification *id3A = new Identification(mzmlA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v3);
        Identification *id4A = new Identification(mzmlA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v4);

        // create the FlashLFQ engine
        std::vector<Identification*> vI1 = {id1A, id2A, id3A, id4A};
        FlashLfqEngine *engineA = new FlashLfqEngine(vI1);

        // run the engine
        auto resultsA = engineA->Run();

        SpectraFileInfo *rawB = new SpectraFileInfo(testdir+ "/sliced-raw.raw", "b", 0, 0, 0);
        SpectraFileInfo *mzmlB = new SpectraFileInfo(testdir+ "/sliced-mzml.mzml", "b", 0, 1, 0);

        // create some PSMs
        auto pgB = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup *> v5 = {pgB};
        std::vector<ProteinGroup *> v6 = {pgB};
        std::vector<ProteinGroup *> v7 = {pgB};
        std::vector<ProteinGroup *> v8 = {pgB};
        Identification *id1 = new Identification(rawB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v5);
        Identification *id2 = new Identification(rawB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v6);
        Identification *id3 = new Identification(mzmlB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, v7);
        Identification *id4 = new Identification(mzmlB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, v8);

        // create the FlashLFQ engine
        std::vector<Identification*> vI2 = {id1, id2, id3, id4};
        FlashLfqEngine *engineB = new FlashLfqEngine(vI2);

        // run the engine
        auto resultsB = engineB->Run();

        resultsA->MergeResultsWith(resultsB);
        // On Linux without raw files, the correct result is 2, not 4. Verified it by running
        // the C# version of the code
        //Assert::AreEqual(4, (int)resultsA->Peaks.size());
        Assert::AreEqual(2, (int)resultsA->Peaks.size());
        Assert::AreEqual(1, (int)resultsA->PeptideModifiedSequences.size());
        Assert::AreEqual(1, (int)resultsA->ProteinGroups.size());
        Assert::AreEqual(4, (int)resultsA->SpectraFiles.size());

        delete engineB;
        delete id4;
        delete id3;
        delete id2;
        delete id1;
        delete pgB;
        delete mzmlB;
        delete rawB;

        delete engineA;
        delete id4A;
        delete id3A;
        delete id2A;
        delete id1A;
        delete pgA;
        delete mzmlA;
        delete rawA;
    }


    void TestFlashLFQ::TestFlashLfqAdvancedProteinQuant()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::vector<std::string> filesToWrite = {"mzml_1", "mzml_2"};
        std::vector<std::string> pepSequences = {"PEPTIDE", "MYPEPTIDE", "VVVVVPEPTIDE"};
        std::vector<std::vector<double>> amounts =
            {
                {1000000, 1000000, 1000000},
                {2000000, 2000000, 900000}
            };
        //Loaders::LoadElements(testdir+ "/elements.dat"));
        
        // generate mzml files (3 peptides each)
        for (int f = 0; f < filesToWrite.size(); f++)
        {
            // 1 MS1 scan per peptide
            std::vector<MsDataScan*> scans(3);
            
            for (int p = 0; p < (int)pepSequences.size(); p++)
            {
                Proteomics::AminoAcidPolymer::Peptide tempVar(pepSequences[p]);
                ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
                IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
                std::vector<double> mz;
                for ( auto v: dist->getMasses() ) {
                    mz.push_back(Chemistry:: ClassExtensions::ToMz(v, 1));
                }
                std::vector<double> intensities;
                double intensities_sum=0.0;
                for ( auto v: dist->getIntensities() ) {
                    intensities.push_back(v * amounts[f][p]);
                    intensities_sum += (v * amounts[f][p]);
                }
                std::vector<std::vector<double>> noiseData;
                std::string nativeId = "scan=" + std::to_string(p+1);
                scans[p] = new MsDataScan(new MzSpectrum(mz, intensities, false), p+1, 1, true,
                                          Polarity::Positive, 1.0 + (p / 10.0), new MzRange(400, 1600),
                                          "f",  MZAnalyzerType::Orbitrap, intensities_sum,
                                          std::make_optional(1.0), noiseData, nativeId);
            }
            FakeMsDataFile tempVar2(scans);
            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar2,
                                                                   testdir+"/"+filesToWrite[f] + ".mzML",
                                                                   false);
        }
        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(testdir+"/"+ filesToWrite[0] + ".mzML", "a", 0, 0, 0);
        SpectraFileInfo *file2 = new SpectraFileInfo(testdir+"/"+ filesToWrite[1] + ".mzML", "a", 1, 0, 0);
        
        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup*> v1 = {pg};
        std::vector<ProteinGroup*> v2 = {pg};
        std::vector<ProteinGroup*> v3 = {pg};
        std::vector<ProteinGroup*> v4 = {pg};
        std::vector<ProteinGroup*> v5 = {pg};
        std::vector<ProteinGroup*> v6 = {pg};
    
        Identification *id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", 799.35996, 1.01, 1, v1);
        Identification *id2 = new Identification(file1, "MYPEPTIDE", "MYPEPTIDE", 1093.46377, 1.11, 1, v2);
        Identification *id3 = new Identification(file1, "VVVVVPEPTIDE", "VVVVVPEPTIDE", 1294.70203, 1.21, 1, v3);

        Identification *id4 = new Identification(file2, "PEPTIDE", "PEPTIDE", 799.35996, 1.01, 1, v4);
        Identification *id5 = new Identification(file2, "MYPEPTIDE", "MYPEPTIDE", 1093.46377, 1.11, 1, v5);
        Identification *id6 = new Identification(file2, "VVVVVPEPTIDE", "VVVVVPEPTIDE", 1294.70203, 1.21, 1, v6);

        // create the FlashLFQ engine
        std::vector<Identification*> vI1 = {id1, id2, id3, id4, id5, id6};
        FlashLfqEngine *engine = new FlashLfqEngine(vI1, false, true, false, 10.0, 5.0, 5.0, false, 2,
                                                    false, true, true, "", 2.5, -1);

        // run the engine
        auto results = engine->Run();

        // third peptide should be low-weighted
        // protein should be ~sum of first two peptide intensities (a little lower, because some smaller isotope peaks get skipped)
        double file1ProteinIntensity = results->ProteinGroups["MyProtein"]->GetIntensity(file1);
        Assert::IsTrue(file1ProteinIntensity < 2e6);
        Assert::IsTrue(file1ProteinIntensity > 1e6);

        double file2ProteinIntensity = results->ProteinGroups["MyProtein"]->GetIntensity(file2);
        Assert::IsTrue(file2ProteinIntensity < 4e6);
        Assert::IsTrue(file2ProteinIntensity > 3e6);

        delete engine;
        delete id6;
        delete id5;
        delete id4;
        delete id3;
        delete id2;
        delete id1;
        delete pg;
        delete file2;
        delete file1;
    }

    void TestFlashLFQ::TestFlashLfqMatchBetweenRuns()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::vector<std::string> filesToWrite = {"mzml_1", "mzml_2"};
        std::vector<std::string> pepSequences = {"PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV"};
        double intensity = 1e6;

        std::vector<double> file1Rt = {1.01, 1.02, 1.03, 1.04, 1.05};
        std::vector<double> file2Rt = {1.015, 1.030, 1.039, 1.050, 1.065};

        //Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml files (5 peptides each)
        for (int f = 0; f < (int)filesToWrite.size(); f++) {
            // 1 MS1 scan per peptide
            std::vector<MsDataScan*> scans(5);

            for (int p = 0; p < (int)pepSequences.size(); p++) {
                Proteomics::AminoAcidPolymer::Peptide tempVar(pepSequences[p]);
                ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
                IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
                std::vector<double> mz;
                for ( auto v: dist->getMasses() ) {
                    mz.push_back(Chemistry:: ClassExtensions::ToMz(v, 1));
                }
                std::vector<double> intensities;
                double intensities_sum=0.0;
                for ( auto v: dist->getIntensities() ) {
                    intensities.push_back( v * intensity);
                    intensities_sum += (v*intensity);
                }
                double rt;
                if (f == 0) {
                    rt = file1Rt[p];
                }
                else {
                    rt = file2Rt[p];
                }
                // add the scan
                auto tempVar2 = new MzSpectrum (mz, intensities, false);
                auto tempVar3 = new MzRange  (400, 1600);
                std::vector<std::vector<double>> noiseData;
                std::string nativeId = "scan=" + std::to_string((p+1));
                scans[p] = new MsDataScan( tempVar2, p + 1, 1, true, Polarity::Positive, rt, tempVar3,
                                           "f", MZAnalyzerType::Orbitrap, 
                                           intensities_sum, std::make_optional(1.0), noiseData,
                                           nativeId);
            }
            // write the .mzML
            FakeMsDataFile tempVar4(scans);
            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, testdir+"/"+ filesToWrite[f] + ".mzML", false);
        }

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(testdir+"/"+filesToWrite[0] + ".mzML", "a", 0, 0, 0);
        SpectraFileInfo *file2 = new SpectraFileInfo(testdir+"/"+ filesToWrite[1] + ".mzML", "a", 1, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        std::vector<ProteinGroup*> v1 = {pg};
        std::vector<ProteinGroup*> v2 = {pg};
        std::vector<ProteinGroup*> v3 = {pg};
        std::vector<ProteinGroup*> v4 = {pg};
        std::vector<ProteinGroup*> v5 = {pg};
        std::vector<ProteinGroup*> v6 = {pg};
        std::vector<ProteinGroup*> v7 = {pg};
        std::vector<ProteinGroup*> v8 = {pg};
        std::vector<ProteinGroup*> v9 = {pg};
        Proteomics::AminoAcidPolymer::Peptide tempVar5("PEPTIDE");
        Identification *id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", (&tempVar5)->getMonoisotopicMass(), file1Rt[0] + 0.001, 1, v1);
        Proteomics::AminoAcidPolymer::Peptide tempVar6("PEPTIDEV");
        Identification *id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", (&tempVar6)->getMonoisotopicMass(), file1Rt[1] + 0.001, 1, v2);
        Proteomics::AminoAcidPolymer::Peptide tempVar7("PEPTIDEVV");
        Identification *id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", (&tempVar7)->getMonoisotopicMass(), file1Rt[2] + 0.001, 1, v3);
        Proteomics::AminoAcidPolymer::Peptide tempVar8("PEPTIDEVVV");
        Identification *id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", (&tempVar8)->getMonoisotopicMass(), file1Rt[3] + 0.001, 1, v4);
        Proteomics::AminoAcidPolymer::Peptide tempVar9("PEPTIDEVVVV");
        Identification *id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", (&tempVar9)->getMonoisotopicMass(), file1Rt[4] + 0.001, 1, v5);

        Proteomics::AminoAcidPolymer::Peptide tempVar10("PEPTIDE");
        Identification *id6 = new Identification(file2, "PEPTIDE", "PEPTIDE", (&tempVar10)->getMonoisotopicMass(), file2Rt[0] + 0.001, 1, v6);
        Proteomics::AminoAcidPolymer::Peptide tempVar11("PEPTIDEV");
        Identification *id7 = new Identification(file2, "PEPTIDEV", "PEPTIDEV", (&tempVar11)->getMonoisotopicMass(), file2Rt[1] + 0.001, 1, v7);
        // missing ID 8 - MBR feature
        Proteomics::AminoAcidPolymer::Peptide tempVar12("PEPTIDEVVV");
        Identification *id9 = new Identification(file2, "PEPTIDEVVV", "PEPTIDEVVV", (&tempVar12)->getMonoisotopicMass(), file2Rt[3] + 0.001, 1, v8);
        Proteomics::AminoAcidPolymer::Peptide tempVar13("PEPTIDEVVVV");
        Identification *id10 = new Identification(file2, "PEPTIDEVVVV", "PEPTIDEVVVV", (&tempVar13)->getMonoisotopicMass(), file2Rt[4] + 0.001, 1, v9);

        // create the FlashLFQ engine
        std::vector<Identification*> vI1 = {id1, id2, id3, id4, id5, id6, id7, id9, id10};
        FlashLfqEngine *engine = new FlashLfqEngine(vI1, false, false, true);
        // run the engine
        auto results = engine->Run();

        Assert::IsTrue((int)results->Peaks[file2].size() == 5);
        int count=0;
        for ( auto p: results->Peaks[file2] ) {
            if (  p->IsMbrPeak ) {
                count++;                
            }
        }
        Assert::IsTrue(count == 1 );

        
        ChromatographicPeak *peak=nullptr;
        for ( auto p: results->Peaks[file2] ) {
            if ( p->IsMbrPeak ) {
                peak = p;
                break;
            }
        }

        ChromatographicPeak* otherFilePeak=nullptr;
        for ( auto p: results->Peaks[file1] ) {
            if (  p->getIdentifications().front()->BaseSequence == peak->getIdentifications().front()->BaseSequence ) {
                otherFilePeak = p;
                break;
            }
        }

        Assert::IsTrue(results->Peaks[file1].size() == 5);
        count=0;
        for ( auto p: results->Peaks[file1] ) {
            if (  p->IsMbrPeak ) {
                count++;                
            }
        }
        Assert::IsTrue( count == 0 );        
        Assert::IsTrue(peak->Intensity > 0);
        Assert::IsTrue(peak->Intensity == otherFilePeak->Intensity);
        std::cout << peak->Intensity << std::endl;

        Assert::IsTrue(results->ProteinGroups["MyProtein"]->GetIntensity(file1) > 0);
        Assert::IsTrue(results->ProteinGroups["MyProtein"]->GetIntensity(file2) > 0);
        std::cout << results->ProteinGroups["MyProtein"]->GetIntensity(file1) << std::endl;
        std::cout << results->ProteinGroups["MyProtein"]->GetIntensity(file2) << std::endl;
        
        delete engine;
        delete pg;
        delete id1;
        delete id2;
        delete id3;
        delete id4;
        delete id5;
        delete id6;
        delete id7;
        delete id9;
        delete id10;
        delete file1;
        delete file2;
    }

#ifdef LATER            

    void TestFlashLFQ::TestFlashLfqMatchBetweenRunsProteinQuant()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
                
        std::vector<std::string> filesToWrite = {"mzml_1", "mzml_2"};
        std::vector<std::string> pepSequences = {"PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV"};
        double intensity = 1e6;

        std::vector<double> file1Rt = {1.01, 1.02, 1.03, 1.04, 1.05};
        std::vector<double> file2Rt = {1.015, 1.030, 1.036, 1.050, 1.065};

        //Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml files (5 peptides each)
        for (int f = 0; f < filesToWrite.size(); f++) {
            // 1 MS1 scan per peptide
            std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(5);

            for (int p = 0; p < pepSequences.size(); p++) {
                Proteomics::AminoAcidPolymer::Peptide tempVar(pepSequences[p]);
                ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
                IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
                std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                        v::ToMz(1);
                    })->ToArray();
                std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                        return v * intensity;
                    })->ToArray();
                double rt;
                if (f == 0) {
                    rt = file1Rt[p];
                }
                else {
                    rt = file2Rt[p];
                }

                // add the scan
                MzSpectrum tempVar2(mz, intensities, false);
                MzRange tempVar3(400, 1600);
                scans[p] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: p + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: rt, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(p + 1));
            }

            // write the .mzML
            FakeMsDataFile tempVar4(scans);
            IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[f] + ".mzML"), false);
        }

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
        SpectraFileInfo *file2 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[1] + ".mzML"), "b", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        auto myMbrProteinGroup = new ProteinGroup("MyMbrProtein", "MbrGene", "org");
        Proteomics::AminoAcidPolymer::Peptide tempVar5("PEPTIDE");
        Identification *id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", (&tempVar5)->getMonoisotopicMass(), file1Rt[0] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar6("PEPTIDEV");
        Identification *id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", (&tempVar6)->getMonoisotopicMass(), file1Rt[1] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar7("PEPTIDEVV");
        Identification *id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", (&tempVar7)->getMonoisotopicMass(), file1Rt[2] + 0.001, 1, std::vector<ProteinGroup*> {myMbrProteinGroup});
        Proteomics::AminoAcidPolymer::Peptide tempVar8("PEPTIDEVVV");
        Identification *id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", (&tempVar8)->getMonoisotopicMass(), file1Rt[3] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar9("PEPTIDEVVVV");
        Identification *id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", (&tempVar9)->getMonoisotopicMass(), file1Rt[4] + 0.001, 1, std::vector<ProteinGroup*> {pg});

        Proteomics::AminoAcidPolymer::Peptide tempVar10("PEPTIDE");
        Identification *id6 = new Identification(file2, "PEPTIDE", "PEPTIDE", (&tempVar10)->getMonoisotopicMass(), file2Rt[0] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar11("PEPTIDEV");
        Identification *id7 = new Identification(file2, "PEPTIDEV", "PEPTIDEV", (&tempVar11)->getMonoisotopicMass(), file2Rt[1] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        // missing ID 8 - MBR feature
        Proteomics::AminoAcidPolymer::Peptide tempVar12("PEPTIDEVVV");
        Identification *id9 = new Identification(file2, "PEPTIDEVVV", "PEPTIDEVVV", (&tempVar12)->getMonoisotopicMass(), file2Rt[3] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar13("PEPTIDEVVVV");
        Identification *id10 = new Identification(file2, "PEPTIDEVVVV", "PEPTIDEVVVV", (&tempVar13)->getMonoisotopicMass(), file2Rt[4] + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // test with top3 protein quant engine
        FlashLfqEngine *engine = new FlashLfqEngine({id1, id2, id3, id4, id5, id6, id7, id9, id10}, matchBetweenRuns: true);
        auto results = engine->Run();

        Assert::That(results->ProteinGroups["MyMbrProtein"].GetIntensity(file1) > 0);
        Assert::That(results->ProteinGroups["MyMbrProtein"].GetIntensity(file2) == 0);

        // test with advanced protein quant engine
        engine = new FlashLfqEngine({id1, id2, id3, id4, id5, id6, id7, id9, id10}, matchBetweenRuns: true, advancedProteinQuant: true);
        results = engine->Run();

        Assert::That(results->ProteinGroups["MyMbrProtein"].GetIntensity(file1) > 0);
        Assert::That(results->ProteinGroups["MyMbrProtein"].GetIntensity(file2) == 0);

        delete engine;
        delete pg;
        delete id1;
        delete id2;
        delete id3;
        delete id4;
        delete id5;
        delete id6;
        delete id7;
        delete id8;
        delete id9;
        delete id10;
        delete file1;
        delete file2;
        delete myMbrProteinGroup;
    }

    void TestFlashLFQ::TestPeakSplittingLeft()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file

        // 1 MS1 scan per peptide
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(10);
        std::vector<double> intensityMultipliers = {1, 3, 1, 1, 3, 5, 10, 5, 3, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.7 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.6);
        Assert::That(peak->SplitRT == 1.3);
        Assert::That(!peak->IsotopicEnvelopes.Any([&] (std::any p) {
                    return p::IndexedPeak::RetentionTime < 1.3;
                }));
        Assert::That(peak->IsotopicEnvelopes->Count == 6);

        delete engine;
        delete id1;
        delete pg;
        delete file1;
    }

    void TestFlashLFQ::TestPeakSplittingRight()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file

        // 1 MS1 scan per peptide
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(10);
        std::vector<double> intensityMultipliers = {1, 3, 5, 10, 5, 3, 1, 1, 3, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.3 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.3);
        Assert::That(peak->SplitRT == 1.6);
        Assert::That(!peak->IsotopicEnvelopes.Any([&] (std::any p) {
                    return p::IndexedPeak::RetentionTime > 1.6;
                }));
        Assert::That(peak->IsotopicEnvelopes->Count == 6);

        delete engine;
        delete id1;
        delete pg1;
        delete file1;
    }

    void TestFlashLFQ::TestPeakSplittingRightWithEmptyScan()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file

        // 1 MS1 scan per peptide
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(10);
        std::vector<double> intensityMultipliers = {1, 3, 5, 10, 5, 3, 1, 1, 3, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            if (s == 7) {
                mz = {401.0};
                intensities = {1000.0};
            }

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.3 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.3);
        Assert::That(peak->SplitRT == 1.6);
        Assert::That(!peak->IsotopicEnvelopes.Any([&] (std::any p) {
                    return p::IndexedPeak::RetentionTime > 1.6;
                }));
        Assert::That(peak->IsotopicEnvelopes->Count == 6);

        delete engine;
        delete id1;
        delete pg;
        delete file1;
    }
    
    void TestFlashLFQ::TestPeakSplittingLeftWithEmptyScan()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file

        // 1 MS1 scan per peptide
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(10);
        std::vector<double> intensityMultipliers = {1, 3, 1, 1, 3, 5, 10, 5, 3, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            if (s == 2) {
                mz = {401.0};
                intensities = {1000.0};
            }

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.3 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.6);
        Assert::That(peak->SplitRT == 1.3);
        Assert::That(!peak->IsotopicEnvelopes.Any([&] (std::any p) {
                    return p::IndexedPeak::RetentionTime < 1.3;
                }));
        Assert::That(peak->IsotopicEnvelopes->Count == 6);

        delete engine;
        delete id1;
        delete pg;
        delete file1;
    }

    void TestFlashLFQ::TestToString()
    {
        // many of these are just to check that the ToString methods don't cause crashes
        auto indexedPeak = new IndexedMassSpectralPeak(1.0, 2.0, 4, 5.0);
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::That(indexedPeak->ToString()->Equals("1.000; 4"));

        auto spectraFile = new SpectraFileInfo("myFullPath", "", 0, 0, 0);
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string spectraString = spectraFile->ToString();

        auto proteinGroup = new ProteinGroup("Accession", "Gene", "Organism");
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string pgString = proteinGroup->ToString(std::vector<SpectraFileInfo*> {spectraFile});

        auto identification = new Identification(spectraFile, "PEPTIDE", "PEPTIDE", 1.0, 2.0, 3, std::vector<ProteinGroup*> {proteinGroup});
        std::string idString = identification->ToString();

        auto chromPeak = new ChromatographicPeak(identification, false, spectraFile);
        std::string chromPeakString = chromPeak->ToString();
        chromPeak->CalculateIntensityForThisFeature(true);
        std::string peakAfterCalculatingIntensity = chromPeak->ToString();

        delete chromPeak;
        delete identification;
        delete proteinGroup;
        delete spectraFile;
        delete indexedPeak;
        
    }

    void TestFlashLFQ::TestNotFound()
    {
        Peptide *p = new Peptide("Seq", true);
        SpectraFileInfo tempVar("", "", 0, 0, 0);
        auto notFound = p->GetDetectionType(&tempVar);
        Assert::That(notFound == DetectionType::NotDetected);

        delete p;        
    }

    void TestFlashLFQ::TestMergePeaks()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(5);
        std::vector<double> intensityMultipliers = {1, 3, 1, 1, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            if (s == 2 || s == 3) {
                mz = {401.0};
                intensities = {1000.0};
            }

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.1 + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar6(peptide);
        Identification *id2 = new Identification(file1, peptide, peptide, (&tempVar6)->getMonoisotopicMass(), 1.4 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1, id2});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(results->Peaks.First()->Value->Count == 1);
        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.1);

        delete engine;
        delete id1;
        delete id2;
        delete pg;
        delete file1;
    }

    void TestFlashLFQ::TestAmbiguous()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        // get the raw file paths
        SpectraFileInfo *mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 0, 1, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id3 = new Identification(mzml, "EGFQVADGPLRY", "EGFQVADGPLRY", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        Identification *id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id3, id4});

        // run the engine
        auto results = engine->Run();

        Assert::That(results->Peaks[mzml]->Count == 1);
        Assert::That(results->Peaks[mzml].First()->Intensity > 0);
        Assert::That(!results->Peaks[mzml].First()->IsMbrPeak);
        Assert::That(results->Peaks[mzml].First()->NumIdentificationsByFullSeq == 2);
        Assert::That(results->PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(mzml) == 0);
        Assert::That(results->PeptideModifiedSequences["EGFQVADGPLRY"].GetIntensity(mzml) == 0);
        Assert::That(results->ProteinGroups["MyProtein"].GetIntensity(mzml) == 0);

        // test peak output
        results->WriteResults(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(peaks.tsv)"), FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(modSeq.tsv)"), FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(protein.tsv)"));

        delete engine;
        delete id3;
        delete id4;
        delete pg;
        delete mzml;
    }
    
    void TestFlashLFQ::TestPeakMerging()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::string fileToWrite = "myMzml.mzML";
        std::string peptide = "PEPTIDE";
        double intensity = 1e6;

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml file

        // 1 MS1 scan per peptide
        std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(10);
        std::vector<double> intensityMultipliers = {1, 3, 5, 10, 5, 3, 1, 1, 1, 1};

        for (int s = 0; s < scans.size(); s++) {
            Proteomics::AminoAcidPolymer::Peptide tempVar(peptide);
            ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
            IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
            std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                    v::ToMz(1);
                })->ToArray();
            std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                    return v * intensity * intensityMultipliers[s];
                })->ToArray();

            if (s == 7 || s == 8) {
                mz = {401.0};
                intensities = {1000.0};
            }

            // add the scan
            MzSpectrum tempVar2(mz, intensities, false);
            MzRange tempVar3(400, 1600);
            scans[s] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(s + 1));
        }

        // write the .mzML
        FakeMsDataFile tempVar4(scans);
        IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), false);

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, fileToWrite), "", 0, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5(peptide);
        Identification *id1 = new Identification(file1, peptide, peptide, (&tempVar5)->getMonoisotopicMass(), 1.3 + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar6(peptide);
        Identification *id2 = new Identification(file1, peptide, peptide, (&tempVar6)->getMonoisotopicMass(), 1.9 + 0.001, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine(std::vector<Identification*> {id1, id2});

        // run the engine
        auto results = engine->Run();
        ChromatographicPeak *peak = results->Peaks.First()->Value->First();

        Assert::That(peak->Apex.IndexedPeak->RetentionTime == 1.3);
        Assert::That(peak->IsotopicEnvelopes->Count == 8);
        Assert::That(results->Peaks.First()->Value->Count == 1);

        delete engine;
        delete id1;
        delete id2;
        delete pg;
        delete file1;
    }

    void TestFlashLFQ::TestMatchBetweenRunsWithNoIdsInCommon()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::vector<std::string> filesToWrite = {"mzml_1", "mzml_2"};
        std::vector<std::string> pepSequences = {"PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV"};
        double intensity = 1e6;

        std::vector<double> file1Rt = {1.01, 1.02, 1.03, 1.04, 1.05};
        std::vector<double> file2Rt = {1.015, 1.030, 1.036, 1.050, 1.065};

        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml files (5 peptides each)
        for (int f = 0; f < filesToWrite.size(); f++) {
            // 1 MS1 scan per peptide
            std::vector<MsDataScan*> scans = std::vector<MsDataScan*>(5);

            for (int p = 0; p < pepSequences.size(); p++) {
                Proteomics::AminoAcidPolymer::Peptide tempVar(pepSequences[p]);
                ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
                IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
                std::vector<double> mz = dist->Masses->Select([&] (std::any v) {
                        v::ToMz(1);
                    })->ToArray();
                std::vector<double> intensities = dist->Intensities->Select([&] (std::any v) {
                        return v * intensity;
                    })->ToArray();
                double rt;
                if (f == 0) {
                    rt = file1Rt[p];
                }
                else {
                    rt = file2Rt[p];
                }

                // add the scan
                MzSpectrum tempVar2(mz, intensities, false);
                MzRange tempVar3(400, 1600);
                scans[p] = new MsDataScan(massSpectrum: &tempVar2, oneBasedScanNumber: p + 1, msnOrder: 1, isCentroid: true, polarity: Polarity::Positive, retentionTime: rt, scanWindowRange: &tempVar3, scanFilter: "f", mzAnalyzer: MZAnalyzerType::Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + std::to_string(p + 1));
            }

            // write the .mzML
            FakeMsDataFile tempVar4(scans);
            IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar4, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[f] + ".mzML"), false);
        }

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
        SpectraFileInfo *file2 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[1] + ".mzML"), "a", 1, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        auto myMbrProteinGroup = new ProteinGroup("MyMbrProtein", "MbrGene", "org");
        auto myMbrProteinGroup = new ProteinGroup("MyMbrProtein", "MbrGene", "org");

        Proteomics::AminoAcidPolymer::Peptide tempVar5("PEPTIDE");
        Identification *id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", (&tempVar5)->getMonoisotopicMass(), file1Rt[0] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar6("PEPTIDEV");
        Identification *id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", (&tempVar6)->getMonoisotopicMass(), file1Rt[1] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar7("PEPTIDEVV");
        Identification *id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", (&tempVar7)->getMonoisotopicMass(), file1Rt[2] + 0.001, 1, std::vector<ProteinGroup*> {myMbrProteinGroup});
        Proteomics::AminoAcidPolymer::Peptide tempVar8("PEPTIDEVVV");
        Identification *id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", (&tempVar8)->getMonoisotopicMass(), file1Rt[3] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar9("PEPTIDEVVVV");
        Identification *id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", (&tempVar9)->getMonoisotopicMass(), file1Rt[4] + 0.001, 1, std::vector<ProteinGroup*> {pg});

        Proteomics::AminoAcidPolymer::Peptide tempVar10("PEPTIED");
        Identification *id6 = new Identification(file2, "PEPTIED", "PEPTIED", (&tempVar10)->getMonoisotopicMass(), file2Rt[0] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar11("PEPTIEDV");
        Identification *id7 = new Identification(file2, "PEPTIEDV", "PEPTIEDV", (&tempVar11)->getMonoisotopicMass(), file2Rt[1] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        // missing ID 8 - MBR feature
        Proteomics::AminoAcidPolymer::Peptide tempVar12("PEPTIEDVVV");
        Identification *id9 = new Identification(file2, "PEPTIEDVVV", "PEPTIEDVVV", (&tempVar12)->getMonoisotopicMass(), file2Rt[3] + 0.001, 1, std::vector<ProteinGroup*> {pg});
        Proteomics::AminoAcidPolymer::Peptide tempVar13("PEPTIEDVVVV");
        Identification *id10 = new Identification(file2, "PEPTIEDVVVV", "PEPTIEDVVVV", (&tempVar13)->getMonoisotopicMass(), file2Rt[4] + 0.001, 1, std::vector<ProteinGroup*> {pg});

        FlashLfqEngine *engine = new FlashLfqEngine({id1, id2, id3, id4, id5, id6, id7, id9, id10}, matchBetweenRuns: true);
        auto results = engine->Run();

        // no assertions - just don't crash

        delete engine;
        delete id1;
        delete id2;
        delete id3;
        delete id4;
        delete id5;
        delete id6;
        delete id7;
        delete id8;
        delete id9;
        delete id10;
        delete file1;
        delete file2;
        delete pg;
        delete myMbrProteinGroup;    
    }
#endif
}
