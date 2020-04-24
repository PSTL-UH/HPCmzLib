#include "TestVariantProtein.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../Proteomics/Protein/Protein.h"
#include "../../Proteomics/Protein/SequenceVariation.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/ProteinDbWriter.h"
#include "../../Proteomics/Modifications/ModificationMotif.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestVariantProtein::privateStopwatch;
std::vector<Modification*> TestVariantProtein::UniProtPtms;

    Stopwatch *TestVariantProtein::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestVariantProtein::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestVariantProtein::SetUpModifications()
    {
        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));
        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);
        UniProtPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();
    }

    void TestVariantProtein::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestVariantProtein::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestVariantProtein::VariantProtein()
    {
        Protein *p = new Protein("MAAA", "accession");
        Protein *v = new Protein("MAVA", p, {new SequenceVariation(3, "A", "V", "desc", std::unordered_map<int, std::vector<Modification>>())}, nullptr, nullptr, nullptr);
        Assert::AreEqual(p, v->getNonVariantProtein());

        delete v;
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }

    void TestVariantProtein::VariantXml()
    {
        std::string file = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "SeqVar.xml");
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> variantProteins = ProteinDbLoader::LoadProteinXML(file, true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);

        Assert::AreEqual(5, variantProteins.front().NonVariantProtein::SequenceVariations->Count());
        Assert::AreEqual(1, variantProteins.size()); // there is only one unique amino acid change
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein::BaseSequence, variantProteins.front().BaseSequence);
        Assert::AreEqual('C', variantProteins.front().NonVariantProtein::BaseSequence[116]);
        Assert::AreEqual('Y', variantProteins.front().BaseSequence[116]);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->Name, variantProteins.front()->Name);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->FullName, variantProteins.front()->FullName);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein::Accession, variantProteins.front().Accession);

        std::vector<PeptideWithSetModifications*> peptides = variantProteins.SelectMany([&] (std::any vp)
        {
            DigestionParams tempVar();
            vp::Digest(&tempVar, nullptr, nullptr);
        }).ToList();
    }

    void TestVariantProtein::SeqVarXmlTest()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "seqvartests.xml"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        auto target = ok.First([&] (std::any p)
        {
            !p::IsDecoy;
        });
        Protein *decoy = ok.Where([&] (std::any p)
        {
            return p::IsDecoy && p::SequenceVariations->Count() > 0;
        }).First();

        Assert::AreEqual('M', target[0]);
        Assert::AreEqual('M', decoy[0]);
        std::vector<SequenceVariation*> targetVariants = target->SequenceVariations.ToList();
        std::vector<SequenceVariation*> decoyVariants = decoy->getSequenceVariations().ToList();
        Assert::AreEqual(targetVariants.size(), decoyVariants.size());

        // starting methionine, but there's more
        Assert::AreEqual("MPEQA", targetVariants.front().OriginalSequence);
        Assert::AreEqual("MP", targetVariants.front().VariantSequence);
        Assert::AreEqual(1, targetVariants.front().OneBasedBeginPosition);
        Assert::AreEqual(5, targetVariants.front().OneBasedEndPosition);
        Assert::AreEqual("AQEP", decoy->getSequenceVariations().front().OriginalSequence); // methionine will be at the front, so clipped off of the variant
        Assert::AreEqual("P", decoy->getSequenceVariations().front().VariantSequence);
        Assert::AreEqual(target->Length - 3, decoy->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(target->Length, decoy->getSequenceVariations().front().OneBasedEndPosition);

        // start loss
        Assert::AreEqual("MPEQA", targetVariants[1]->getOriginalSequence());
        Assert::AreEqual("P", decoyVariants[1]->getVariantSequence());
        Assert::AreEqual(1, targetVariants[1]->getOneBasedBeginPosition());
        Assert::AreEqual(5, targetVariants[1]->getOneBasedEndPosition());
        Assert::AreEqual("AQEP", decoy->getSequenceVariations().front().OriginalSequence); // methionine will be at the front, so clipped off of the variant
        Assert::AreEqual("P", decoy->getSequenceVariations().front().VariantSequence);
        Assert::AreEqual(target->Length - 3, decoy->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(target->Length, decoy->getSequenceVariations().front().OneBasedEndPosition);

        for (auto s : targetVariants)
        {
            Assert::AreEqual(s->getOriginalSequence(), target->BaseSequence->substr(s->getOneBasedBeginPosition() - 1, s->getOneBasedEndPosition() - s->getOneBasedBeginPosition() + 1));
        }
        for (auto s : decoyVariants)
        {
            Assert::AreEqual(s->getOriginalSequence(), decoy->getBaseSequence().substr(s->getOneBasedBeginPosition() - 1, s->getOneBasedEndPosition() - s->getOneBasedBeginPosition() + 1));
        }
        Assert::AreNotEqual(target->SequenceVariations.First().Description, decoy->getSequenceVariations().front().Description); //decoys and target variations don't have the same desc.
    }

    void TestVariantProtein::LoadSeqVarModifications(const std::string &databaseName, int modIdx, int reversedModIdx)
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", databaseName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        auto target = proteins[0];
        Assert::AreEqual(1, target->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(modIdx, target->getOneBasedPossibleLocalizedModifications().Single().Key);
        Assert::AreEqual(1, target->getAppliedSequenceVariations().size()());
        Assert::AreEqual(modIdx, target->getAppliedSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, target->getSequenceVariations().size()());
        Assert::AreEqual(modIdx, target->getSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, target->getSequenceVariations().Single().OneBasedModifications->Count);
        Assert::AreEqual(modIdx, target->getSequenceVariations().Single().OneBasedModifications.Single().Key); //PEP[mod]TID, MEP[mod]TID
        auto decoy = proteins[1];
        Assert::AreEqual(1, decoy->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(reversedModIdx, decoy->getOneBasedPossibleLocalizedModifications().Single().Key); //DITP[mod]EP, MDITP[mod]E
        Assert::AreEqual(1, decoy->getAppliedSequenceVariations().size()());
        Assert::AreEqual(reversedModIdx, decoy->getAppliedSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, decoy->getSequenceVariations().size()());
        Assert::AreEqual(reversedModIdx, decoy->getSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, decoy->getSequenceVariations().Single().OneBasedModifications->Count);
        Assert::AreEqual(reversedModIdx, decoy->getSequenceVariations().Single().OneBasedModifications.Single().Key);

        std::string rewriteDbName = StringHelper::formatSimple("{0}rewrite.xml", Path::GetFileNameWithoutExtension(databaseName));
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteins.Where([&] (std::any p)
        {
            !p::IsDecoy;
        }).ToList(), FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName));
        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        target = proteins[0];
        Assert::AreEqual(1, target->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(modIdx, target->getOneBasedPossibleLocalizedModifications().Single().Key);
        Assert::AreEqual(1, target->getAppliedSequenceVariations().size()());
        Assert::AreEqual(modIdx, target->getAppliedSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, target->getSequenceVariations().size()());
        Assert::AreEqual(modIdx, target->getSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, target->getSequenceVariations().Single().OneBasedModifications->Count);
        Assert::AreEqual(modIdx, target->getSequenceVariations().Single().OneBasedModifications.Single().Key);
        decoy = proteins[1];
        Assert::AreEqual(1, decoy->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(reversedModIdx, decoy->getOneBasedPossibleLocalizedModifications().Single().Key);
        Assert::AreEqual(1, decoy->getAppliedSequenceVariations().size()());
        Assert::AreEqual(reversedModIdx, decoy->getAppliedSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, decoy->getSequenceVariations().size()());
        Assert::AreEqual(reversedModIdx, decoy->getSequenceVariations().Single().OneBasedBeginPosition);
        Assert::AreEqual(1, decoy->getSequenceVariations().Single().OneBasedModifications->Count);
        Assert::AreEqual(reversedModIdx, decoy->getSequenceVariations().Single().OneBasedModifications.Single().Key);
    }

    void TestVariantProtein::ReverseDecoyProteolysisProducts(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx)
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", databaseName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        auto target = proteins[0];
        Assert::AreEqual(1, target->getProteolysisProducts().size()());
        Assert::AreEqual(beginIdx, target->getProteolysisProducts().Single().OneBasedBeginPosition); //P[start]EPTI[end]D, M[start]EPTI[end]D
        Assert::AreEqual(endIdx, target->getProteolysisProducts().Single().OneBasedEndPosition);
        auto decoy = proteins[1];
        Assert::AreEqual(1, decoy->getProteolysisProducts().size()());
        Assert::AreEqual(reversedBeginIdx, decoy->getProteolysisProducts().Single().OneBasedBeginPosition); //DI[start]TPEP[end], M[start]DITP[end]E
        Assert::AreEqual(reversedEndIdx, decoy->getProteolysisProducts().Single().OneBasedEndPosition);

        std::string rewriteDbName = StringHelper::formatSimple("{0}rewrite.xml", Path::GetFileNameWithoutExtension(databaseName));
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteins.Where([&] (std::any p)
        {
            !p::IsDecoy;
        }).ToList(), FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName));
        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        target = proteins[0];
        Assert::AreEqual(1, target->getProteolysisProducts().size()());
        Assert::AreEqual(beginIdx, target->getProteolysisProducts().Single().OneBasedBeginPosition);
        Assert::AreEqual(endIdx, target->getProteolysisProducts().Single().OneBasedEndPosition);
        decoy = proteins[1];
        Assert::AreEqual(1, decoy->getProteolysisProducts().size()());
        Assert::AreEqual(reversedBeginIdx, decoy->getProteolysisProducts().Single().OneBasedBeginPosition);
        Assert::AreEqual(reversedEndIdx, decoy->getProteolysisProducts().Single().OneBasedEndPosition);
    }

    void TestVariantProtein::ReverseDecoyDisulfideBonds(const std::string &databaseName, int beginIdx, int reversedBeginIdx, const std::string &reversedSequence, int endIdx, int reversedEndIdx)
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", databaseName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        auto target = proteins[0];
        Assert::AreEqual(1, target->getDisulfideBonds().size()());
        Assert::AreEqual(beginIdx, target->getDisulfideBonds().Single().OneBasedBeginPosition); //PC[start]PC[end]ID, MC[start]PC[end]ID
        Assert::AreEqual(endIdx, target->getDisulfideBonds().Single().OneBasedEndPosition);
        auto decoy = proteins[1];
        Assert::AreEqual(1, decoy->getDisulfideBonds().size()());
        Assert::AreEqual(reversedSequence, decoy->getBaseSequence());
        Assert::AreEqual(reversedBeginIdx, decoy->getDisulfideBonds().Single().OneBasedBeginPosition); //DIC[start]PC[end]P, MDIC[start]PC[end]
        Assert::AreEqual(reversedEndIdx, decoy->getDisulfideBonds().Single().OneBasedEndPosition);

        std::string rewriteDbName = StringHelper::formatSimple("{0}rewrite.xml", Path::GetFileNameWithoutExtension(databaseName));
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteins.Where([&] (std::any p)
        {
            !p::IsDecoy;
        }).ToList(), FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName));
        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        target = proteins[0];
        Assert::AreEqual(1, target->getDisulfideBonds().size()());
        Assert::AreEqual(beginIdx, target->getDisulfideBonds().Single().OneBasedBeginPosition);
        Assert::AreEqual(endIdx, target->getDisulfideBonds().Single().OneBasedEndPosition);
        decoy = proteins[1];
        Assert::AreEqual(1, decoy->getDisulfideBonds().size()());
        Assert::AreEqual(reversedBeginIdx, decoy->getDisulfideBonds().Single().OneBasedBeginPosition);
        Assert::AreEqual(reversedEndIdx, decoy->getDisulfideBonds().Single().OneBasedEndPosition);
    }

    void TestVariantProtein::ReverseDecoySpliceSites(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx)
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", databaseName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        auto target = proteins[0];
        Assert::AreEqual(1, target->getSpliceSites().size()());
        Assert::AreEqual(beginIdx, target->getSpliceSites().Single().OneBasedBeginPosition); //PE[start]P[end]TID, ME[start]P[start]TID, PE[site]PTID, ME[site]PTID, P[site]EPTID, M[site]EPTID
        Assert::AreEqual(endIdx, target->getSpliceSites().Single().OneBasedEndPosition);
        auto decoy = proteins[1];
        Assert::AreEqual(1, decoy->getSpliceSites().size()());
        Assert::AreEqual(reversedBeginIdx, decoy->getSpliceSites().Single().OneBasedBeginPosition); //DITP[start]E[end]P, MDITP[start]E[end], DITPE[site]P, MDITPE[site], DITPEP[site], M[site]DITPE
        Assert::AreEqual(reversedEndIdx, decoy->getSpliceSites().Single().OneBasedEndPosition);

        std::string rewriteDbName = StringHelper::formatSimple("{0}rewrite.xml", Path::GetFileNameWithoutExtension(databaseName));
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteins.Where([&] (std::any p)
        {
            !p::IsDecoy;
        }).ToList(), FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName));
        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", rewriteDbName), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        target = proteins[0];
        Assert::AreEqual(1, target->getSpliceSites().size()());
        Assert::AreEqual(beginIdx, target->getSpliceSites().Single().OneBasedBeginPosition);
        Assert::AreEqual(endIdx, target->getSpliceSites().Single().OneBasedEndPosition);
        decoy = proteins[1];
        Assert::AreEqual(1, decoy->getSpliceSites().size()());
        Assert::AreEqual(reversedBeginIdx, decoy->getSpliceSites().Single().OneBasedBeginPosition);
        Assert::AreEqual(reversedEndIdx, decoy->getSpliceSites().Single().OneBasedEndPosition);
    }

    void TestVariantProtein::HomozygousVariantsAtVariedDepths(const std::string &filename, int minVariantDepth, int appliedCount)
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", filename), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications, -1, 4, minVariantDepth);
        Assert::AreEqual(1, proteins.size());
        Assert::AreEqual(18, proteins[0]->getSequenceVariations().size()()); // some redundant
        Assert::AreEqual(18, proteins[0]->getSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(appliedCount, proteins[0]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(appliedCount, proteins[0]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(1, proteins[0]->GetVariantProteins().size());
        auto variantProteins = proteins[0]->GetVariantProteins();
    }

    void TestVariantProtein::AppliedVariants()
    {
        ModificationMotif motifP;
        ModificationMotif::TryGetMotif("P", motifP);
        Modification *mp = new Modification("mod", "", "type", "", motifP, "Anywhere.", nullptr, std::make_optional(42.01), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::vector<SequenceVariation*> tempVar;
        tempVar.new SequenceVariation(4, 4, "P", "V", R"(1\t50000000\t.\tA\tG\t.\tPASS\tANN=G||||||||||||||||\tGT:AD:DP\t1/1:30,30:30)", nullptr);
        std::vector<SequenceVariation*> tempVar2;
        tempVar2.new SequenceVariation(4, 5, "PT", "KT", R"(1\t50000000\t.\tA\tG\t.\tPASS\tANN=G||||||||||||||||\tGT:AD:DP\t1/1:30,30:30)", nullptr);
        std::vector<SequenceVariation*> tempVar3;
        tempVar3.new SequenceVariation(4, 4, "P", "PPP", R"(1\t50000000\t.\tA\tG\t.\tPASS\tANN=G||||||||||||||||\tGT:AD:DP\t1/1:30,30:30)", nullptr);
        std::vector<SequenceVariation*> tempVar4;
        tempVar4.new SequenceVariation(4, 6, "PPP", "P", R"(1\t50000000\t.\tA\tG\t.\tPASS\tANN=G||||||||||||||||\tGT:AD:DP\t1/1:30,30:30)", nullptr);
        std::vector<SequenceVariation*> tempVar5;
        tempVar5.new SequenceVariation(4, 4, "P", "PPP", R"(1\t50000000\t.\tA\tG\t.\tPASS\tANN=G||||||||||||||||\tGT:AD:DP\t1/1:30,30:30)", {mp}::ToList()
        }
        });
        std::vector<Protein*> proteinsWithSeqVars =
        {
            new Protein("MPEPTIDE", "protein1", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), tempVar, std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), ""),
            new Protein("MPEPTIDE", "protein2", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), tempVar2, std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), ""),
            new Protein("MPEPTIDE", "protein3", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), tempVar3, std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), ""),
            new Protein("MPEPPPTIDE", "protein3", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), tempVar4, std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), ""),
            new Protein("MPEPTIDE", "protein3", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), tempVar5, std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "")
        };
        auto proteinsWithAppliedVariants = proteinsWithSeqVars.SelectMany([&] (std::any p)
        {
            p::GetVariantProteins();
        }).ToList();
        auto proteinsWithAppliedVariants2 = proteinsWithSeqVars.SelectMany([&] (std::any p)
        {
            p::GetVariantProteins();
        }).ToList(); // should be stable
        std::string xml = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "AppliedVariants.xml");
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteinsWithSeqVars, xml);
        std::unordered_map<string, Modification> un;
        auto proteinsWithAppliedVariants3 = ProteinDbLoader::LoadProteinXML(xml, true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);

        auto listArray = std::vector<std::vector<std::any>> {proteinsWithAppliedVariants, proteinsWithAppliedVariants2, proteinsWithAppliedVariants3};
        for (int dbIdx = 0; dbIdx < listArray.size(); dbIdx++)
        {
            // sequences
            Assert::AreEqual("MPEVTIDE", listArray[dbIdx][0].BaseSequence);
            Assert::AreEqual("MPEKTIDE", listArray[dbIdx][1].BaseSequence);
            Assert::AreEqual("MPEPPPTIDE", listArray[dbIdx][2].BaseSequence);
            Assert::AreEqual("MPEPTIDE", listArray[dbIdx][3].BaseSequence);
            Assert::AreEqual("MPEPPPTIDE", listArray[dbIdx][4].BaseSequence);
            Assert::AreEqual(5, listArray[dbIdx][4].OneBasedPossibleLocalizedModifications::Single().Key);

            // SAV
            Assert::AreEqual(4, listArray[dbIdx][0].AppliedSequenceVariations::Single().OneBasedBeginPosition);
            Assert::AreEqual(4, listArray[dbIdx][0].AppliedSequenceVariations::Single().OneBasedEndPosition);

            // MNV
            Assert::AreEqual(4, listArray[dbIdx][1].AppliedSequenceVariations::Single().OneBasedBeginPosition);
            Assert::AreEqual(5, listArray[dbIdx][1].AppliedSequenceVariations::Single().OneBasedEndPosition);

            // insertion
            Assert::AreEqual(4, listArray[dbIdx][2].AppliedSequenceVariations::Single().OneBasedBeginPosition);
            Assert::AreEqual(6, listArray[dbIdx][2].AppliedSequenceVariations::Single().OneBasedEndPosition);

            // deletion
            Assert::AreEqual(4, listArray[dbIdx][3].AppliedSequenceVariations::Single().OneBasedBeginPosition);
            Assert::AreEqual(4, listArray[dbIdx][3].AppliedSequenceVariations::Single().OneBasedEndPosition);
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete mp' statement was not added since mp was passed to a method or constructor. Handle memory management manually.
    }

    void TestVariantProtein::StopGained()
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "StopGained.xml"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        Assert::AreEqual(2, proteins.size());
        Assert::AreEqual(1, proteins[0]->getSequenceVariations().size()()); // some redundant
        Assert::AreEqual(1, proteins[0]->getSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(0, proteins[0]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(0, proteins[0]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(191, proteins[0]->getLength());
        Assert::AreEqual('Q', proteins[0][161 - 1]);
        Assert::AreEqual(161 - 1, proteins[1]->getLength());
        Assert::AreNotEqual(proteins[0]->getLength(), proteins[1]->getLength());

        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "StopGained.xml"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications, -1, 4, 400);
        Assert::AreEqual(1, proteins.size());
        Assert::AreEqual(1, proteins[0]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(1, proteins[0]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(161 - 1, proteins[0]->getLength());
    }

    void TestVariantProtein::MultipleAlternateAlleles()
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "MultipleAlternateAlleles.xml"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        Assert::AreEqual(2, proteins.size());
        Assert::AreEqual(2, proteins[0]->getSequenceVariations().size()()); // some redundant
        Assert::AreEqual(2, proteins[0]->getSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes

        Assert::IsTrue(proteins[0]->getSequenceVariations().All([&] (std::any v)
        {
            return v->OneBasedBeginPosition == 63;
        })); // there are two alternate alleles (1 and 2), but only 2 is in the genotype, so only that's applied
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(72, proteins[0]->getLength());
        Assert::AreEqual(72, proteins[1]->getLength());
        Assert::AreEqual('K', proteins[0][63 - 1]);
        Assert::AreEqual('R', proteins[1][63 - 1]);

        proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "MultipleAlternateAlleles.xml"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications, -1, 4, 10);
        Assert::AreEqual(1, proteins.size());
        Assert::AreEqual(0, proteins[0]->getAppliedSequenceVariations().size()()); // some redundant
        Assert::AreEqual(0, proteins[0]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual('K', proteins[0][63 - 1]); // reference only
    }

    void TestVariantProtein::MultipleAlternateFrameshifts()
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "MultipleAlternateFrameshifts.xml"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        Assert::AreEqual(2, proteins.size());
        Assert::AreEqual(3, proteins[0]->getSequenceVariations().size()()); // some redundant
        Assert::AreEqual(3, proteins[0]->getSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes

        Assert::IsTrue(proteins[0]->getSequenceVariations().All([&] (std::any v)
        {
            return v->OneBasedBeginPosition == 471;
        })); // there are two alternate alleles (1 and 2), but only 2 is in the genotype, so only that's applied
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations().size()()); // some redundant
        auto applied = proteins[1]->getAppliedSequenceVariations().Single();
        Assert::AreEqual("KDKRATGRIKS", applied->VariantSequence);
        Assert::AreEqual(403 - 11, applied->OriginalSequence->Length - applied->VariantSequence->Length);
        Assert::AreEqual(1, proteins[1]->getAppliedSequenceVariations()->Select([&] (std::any v)
        {
            v::SimpleString();
        }).Distinct()->Count()); // unique changes
        Assert::AreEqual(873, proteins[0]->getLength());
        Assert::AreEqual(873 - 403 + 11, proteins[1]->getLength());
    }

    void TestVariantProtein::VariantSymbolWeirdnessXml()
    {
        std::string file = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "SeqVarSymbolWeirdness.xml");
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> variantProteins = ProteinDbLoader::LoadProteinXML(file, true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);
        Assert::AreEqual(12, variantProteins.front().NonVariantProtein::SequenceVariations->Count());
        Assert::AreEqual(2, variantProteins.front().NonVariantProtein::SequenceVariations->Count([&] (std::any v)
        {
            v::Description->Heterozygous.Any([&] (std::any kv)
            {
                kv->Value;
            });
        }));

        Assert::AreEqual(1, variantProteins.size()); // Should be 2^2 from combinitorics of heterozygous, but the giant indels overwrite them
        Assert::AreEqual(0, variantProteins.Where([&] (std::any v)
        {
            return v->BaseSequence == variantProteins.front().NonVariantProtein::BaseSequence;
        })->Count()); // Homozygous variations are included
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->Name, variantProteins.front()->Name);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->FullName, variantProteins.front()->FullName);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein::Accession, variantProteins.front().Accession);

        std::vector<PeptideWithSetModifications*> peptides = variantProteins.SelectMany([&] (std::any vp)
        {
            DigestionParams tempVar();
            vp::Digest(&tempVar, nullptr, nullptr);
        }).ToList();
    }

    void TestVariantProtein::VariantSymbolWeirdness2Xml()
    {
        std::string file = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "SeqVarSymbolWeirdness2.xml");
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> variantProteins = ProteinDbLoader::LoadProteinXML(file, true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);

        Assert::AreEqual(1, variantProteins.front().NonVariantProtein::SequenceVariations->Count());
        Assert::AreEqual(2, variantProteins.size()); // there is only one unique amino acid change
        Assert::AreEqual(1, variantProteins.Where([&] (std::any v)
        {
            return v->BaseSequence == variantProteins.front().NonVariantProtein::BaseSequence;
        })->Count());
        auto variantProteinRef = variantProteins.front();
        auto variantProteinAlt = variantProteins.back();
        Assert::AreEqual('R', variantProteins.front().NonVariantProtein::BaseSequence[2386]);
        Assert::AreEqual('R', variantProteinRef->BaseSequence[2386]);
        Assert::AreEqual('H', variantProteinAlt->BaseSequence[2386]);
        Assert::AreEqual(variantProteins.front().NonVariantProtein->Name, variantProteinRef->Name);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->Name, variantProteinAlt->Name);
        Assert::AreEqual(variantProteins.front().NonVariantProtein->FullName, variantProteinRef->FullName);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein->FullName, variantProteinAlt->FullName);
        Assert::AreEqual(variantProteins.front().NonVariantProtein::Accession, variantProteinRef->Accession);
        Assert::AreNotEqual(variantProteins.front().NonVariantProtein::Accession, variantProteinAlt->Accession);
        std::vector<PeptideWithSetModifications*> peptides = variantProteins.SelectMany([&] (std::any vp)
        {
            DigestionParams tempVar();
            vp::Digest(&tempVar, nullptr, nullptr);
        }).ToList();
    }

    void TestVariantProtein::IndelDecoyError()
    {
        std::string file = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "IndelDecoy.xml");
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> variantProteins = ProteinDbLoader::LoadProteinXML(file, true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), un);
        Assert::AreEqual(8, variantProteins.size());
        auto indelProtein = variantProteins[2];
        Assert::AreNotEqual(indelProtein->getAppliedSequenceVariations().Single().OriginalSequence->Length, indelProtein->getAppliedSequenceVariations().Single().VariantSequence->Length);
        Assert::AreNotEqual(indelProtein->getNonVariantProtein()->getLength(), variantProteins[2]->getLength());
        auto decoyIndelProtein = variantProteins[5];
        Assert::AreNotEqual(decoyIndelProtein->getAppliedSequenceVariations().Single().OriginalSequence->Length, decoyIndelProtein->getAppliedSequenceVariations().Single().VariantSequence->Length);
        Assert::AreNotEqual(decoyIndelProtein->getNonVariantProtein()->getLength(), variantProteins[2]->getLength());
        Assert::AreEqual(indelProtein->getLength() - indelProtein->getAppliedSequenceVariations().Single().OneBasedBeginPosition, decoyIndelProtein->getAppliedSequenceVariations().Single().OneBasedBeginPosition);
        auto variantSeq = indelProtein->getAppliedSequenceVariations().Single().VariantSequence.ToCharArray();
        Array::Reverse(variantSeq);
        Assert::AreEqual(std::string(variantSeq), decoyIndelProtein->getAppliedSequenceVariations().Single().VariantSequence);
    }

    void TestVariantProtein::IndelDecoyVariants()
    {
        std::string file = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "DecoyVariants.xml");
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> variantProteins = ProteinDbLoader::LoadProteinXML(file, true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), un);
        int i = 0;
        Assert::AreEqual(4, variantProteins.size());
        Assert::AreEqual(3, variantProteins[0]->getAppliedSequenceVariations().size()); // homozygous variations
        Assert::AreEqual(4, variantProteins[1]->getAppliedSequenceVariations().size()); // plus one heterozygous variation
        Assert::AreEqual("M", variantProteins[0]->getAppliedSequenceVariations().back().OriginalSequence);
        Assert::AreEqual(1646, variantProteins[0]->getAppliedSequenceVariations().back().OneBasedBeginPosition);
        Assert::AreEqual("V", variantProteins[0]->getAppliedSequenceVariations().back().VariantSequence);
        Assert::AreEqual("M", variantProteins[2]->getAppliedSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(variantProteins[0]->getLength() - 1646 + 2, variantProteins[2]->getAppliedSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual("V", variantProteins[2]->getAppliedSequenceVariations().front().VariantSequence);
    }
}
