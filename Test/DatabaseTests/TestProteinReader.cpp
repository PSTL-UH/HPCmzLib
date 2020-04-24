#include "TestProteinReader.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../Proteomics/Modifications/ModificationMotif.h"
#include "../../Proteomics/Protein/DatabaseReference.h"
#include "../../Proteomics/Protein/Protein.h"
#include "../../Proteomics/Protein/ProteolysisProduct.h"
#include "../../Proteomics/Protein/SequenceVariation.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/PtmListLoader.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestProteinReader::privateStopwatch;
std::vector<Modification*> TestProteinReader::UniProtPtms;

    Stopwatch *TestProteinReader::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestProteinReader::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestProteinReader::SetUpModifications()
    {
        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));
        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);
        UniProtPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();
    }

    void TestProteinReader::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestProteinReader::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestProteinReader::MergeACoupleProteins()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("A", motif);
        Protein *p = new Protein("ASEQUENCE", "id", isContaminant: false, isDecoy: false, name: "name", fullName: "full_name", geneNames: {std::tuple<std::string, std::string>("gene", "name")},
        databaseReferences: std::vector<DatabaseReference*>
        {
            new DatabaseReference("ref", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("type", "property")})
        },
        sequenceVariations: {new SequenceVariation(1, 2, "A", "B", "var")},
        proteolysisProducts: {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "prod")},
        oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {
                1, {new Modification("mod", "", "type", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")}
            }
        });

        Protein *p2 = new Protein("ASEQUENCE", "id", isContaminant: false, isDecoy: false, name: "name", fullName: "full_name", geneNames: {std::tuple<std::string, std::string>("gene", "name")},
        databaseReferences: std::vector<DatabaseReference*>
        {
            new DatabaseReference("ref", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("type", "property")})
        },
        sequenceVariations: {new SequenceVariation(1, 2, "A", "B", "var")},
        proteolysisProducts: {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "prod")},
        oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {
                1, {new Modification("mod", "", "type", "", motif, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")}
            }
        });

        std::vector<Protein*> merged = ProteinDbLoader::MergeProteins(std::vector<Protein*> {p, p2}).ToList();
        Assert::AreEqual(1, merged.size());
        Assert::AreEqual(1, merged.front().DatabaseReferences->Count());
        Assert::AreEqual(1, merged.front().GeneNames->Count());
        Assert::AreEqual(1, merged.front().SequenceVariations->Count());
        Assert::AreEqual(1, merged.front().ProteolysisProducts->Count());
        Assert::AreNotEqual(p->getOneBasedPossibleLocalizedModifications().First()->Value->First(), p2->getOneBasedPossibleLocalizedModifications().First()->Value->First());
        Assert::AreEqual(1, merged.front().OneBasedPossibleLocalizedModifications->Count());
        Assert::AreEqual(2, merged.front().OneBasedPossibleLocalizedModifications::First()->Value->Count);

//C# TO C++ CONVERTER TODO TASK: A 'delete p2' statement was not added since p2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }

    void TestProteinReader::XmlTest()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml.xml)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        Assert::AreEqual('M', ok[0][0]);
        Assert::AreEqual('M', ok[1][0]);

        Assert::AreEqual("P62805|H4_HUMAN|Histone H4", ok[0]->getFullDescription());
        Assert::AreEqual("DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFullDescription());
        Assert::AreEqual("ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Id);
        Assert::AreEqual("protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Properties->First().Item1);
        Assert::AreEqual("ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Properties->First().Item2);
        Assert::AreEqual(42, ok[0]->getGeneNames().size()());
        Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t)
        {
            return t->Item1 == "primary";
        })->Count());
        Assert::AreEqual("HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t)
        {
            return t->Item1 == "primary";
        }).First().Item2);
        Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }));
        Assert::AreEqual(0, ok[0]->getDisulfideBonds().size()());
        Assert::AreEqual(1, ok[0]->getSequenceVariations().size()());
        Assert::AreEqual(1, ok[1]->getSequenceVariations().size()()); // decoys get the same sequence variations
        Assert::AreEqual(64, ok[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(64, ok[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreNotEqual(ok[0]->getSequenceVariations().front().Description, ok[1]->getSequenceVariations().front().Description); //decoys and target variations don't have the same desc.
        Assert::AreEqual("Homo sapiens", ok[1]->getOrganism());
    }

    void TestProteinReader::DisulfideXmlTest()
    {
        Dictionary<std::string, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(disulfidetests.xml)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        Assert::AreEqual('M', ok[0][0]);
        Assert::AreEqual('M', ok[1][0]);

        Assert::AreEqual(3, ok[0]->getDisulfideBonds().size()());
        Assert::AreEqual('C', ok[0]->getBaseSequence()[ok[0]->getDisulfideBonds().front().OneBasedBeginPosition - 1]);
        Assert::AreEqual('C', ok[0]->getBaseSequence()[ok[0]->getDisulfideBonds().front().OneBasedEndPosition - 1]);
        Assert::AreEqual(31, ok[0]->getDisulfideBonds().front().OneBasedBeginPosition);
        Assert::AreEqual(94, ok[0]->getDisulfideBonds().front().OneBasedEndPosition);
        Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).OneBasedBeginPosition);
        Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).OneBasedEndPosition);

        Assert::AreEqual(3, ok[1]->getDisulfideBonds().size()());
        Assert::AreEqual('C', ok[1]->getBaseSequence()[ok[1]->getDisulfideBonds().front().OneBasedBeginPosition - 1]);
        Assert::AreEqual('C', ok[1]->getBaseSequence()[ok[1]->getDisulfideBonds().front().OneBasedEndPosition - 1]);
        Assert::AreEqual(16, ok[1]->getDisulfideBonds().front().OneBasedBeginPosition);
        Assert::AreEqual(79, ok[1]->getDisulfideBonds().front().OneBasedEndPosition);
        Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).OneBasedBeginPosition);
        Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).OneBasedEndPosition);
        Assert::AreNotEqual(ok[0]->getDisulfideBonds().front().Description, ok[1]->getDisulfideBonds().front().Description); //decoys and target disulfide bonds don't have the same desc.
    }

    void TestProteinReader::XmlTest_2entry()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        // proteolysis products check
        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any d)
            {
                return d->OneBasedBeginPosition == nullptr || d::OneBasedBeginPosition > 0;
            });
        }));
        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any d)
            {
                return d->OneBasedEndPosition == nullptr || d::OneBasedEndPosition <= p->Length;
            });
        }));

        // base sequence check
        Assert::False(ok.All([&] (std::any p)
        {
            p::BaseSequence->Contains(" ");
        }));
        Assert::False(ok.All([&] (std::any p)
        {
            p::BaseSequence->Contains("\t");
        }));
        Assert::False(ok.All([&] (std::any p)
        {
            p::BaseSequence->Contains("\n");
        }));

        // GoTerm checks
        std::vector<Protein*> targets = ok.Where([&] (std::any p)
        {
            !p::IsDecoy;
        }).ToList();
        Assert::AreEqual(2, targets.size());
        Assert::AreEqual(1, targets[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "EnsemblFungi";
        }));
        Assert::AreEqual(1, targets[1]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "EnsemblFungi";
        }));
    }

    void TestProteinReader::XmlGzTest()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml.xml.gz)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        Assert::AreEqual('M', ok[0][0]);
        Assert::AreEqual('M', ok[1][0]);

        Assert::AreEqual("P62805|H4_HUMAN|Histone H4", ok[0]->getFullDescription());
        Assert::AreEqual("DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFullDescription());
        Assert::AreEqual("ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Id);
        Assert::AreEqual("protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Properties->First().Item1);
        Assert::AreEqual("ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }).Properties->First().Item2);
        Assert::AreEqual(42, ok[0]->getGeneNames().size()());
        Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t)
        {
            return t->Item1 == "primary";
        })->Count());
        Assert::AreEqual("HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t)
        {
            return t->Item1 == "primary";
        }).First().Item2);
        Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "Ensembl";
        }));
    }

    void TestProteinReader::XmlFunkySequenceTest()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(fake_h4.xml)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        Assert::AreEqual("S", ok[0]->getBaseSequence()->substr(0, 1));
        Assert::AreEqual("G", ok[1]->getBaseSequence()->substr(0, 1));

        Assert::AreEqual('S', ok[0][0]);
        Assert::AreEqual('G', ok[1][0]);
    }

    void TestProteinReader::XmlModifiedStartTest()
    {
        std::unordered_map<string, Modification> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(modified_start.xml)"), true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

        Assert::AreEqual("M", ok[0]->getBaseSequence()->substr(0, 1)); //the original protein sequence in the original order starts with 'M'
        Assert::AreEqual("M", ok[1]->getBaseSequence()->substr(0, 1)); //the decoy protein sequence in the reverse order from the original still starts with 'M'
        Assert::AreEqual(1, ok[1]->getOneBasedPossibleLocalizedModifications()[1].size()); //the initial methionine of the decoy still has the mod that it's supposed to have.
    }

    void TestProteinReader::FastaTest()
    {
        std::vector<string> a;
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(fasta.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotNameRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

        Assert::AreEqual("P62805", prots.front().Accession);
        Assert::AreEqual("H4_HUMAN", prots.front()->Name);
        Assert::AreEqual("Histone H4", prots.front()->FullName);
        Assert::AreEqual("HIST1H4A", prots.front().GeneNames::First().Item2);
        Assert::AreEqual("Homo sapiens", prots.front().Organism);
    }

    void TestProteinReader::BadFastaTest()
    {
        std::vector<string> a;
        ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bad4.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);
        Assert::AreEqual(1, a->Count);
        std::vector<string> b;
        ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bad3.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, b);
        Assert::AreEqual(2, b->Count);
        std::vector<string> c;
        ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(blank.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, c);
        Assert::AreEqual(1, c->Count);
    }

    void TestProteinReader::Load_fasta_handle_tooHigh_indices()
    {
        std::vector<string> a;
        auto p = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bad.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);
    }

    void TestProteinReader::Read_xml_mod_collision()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("S", motif);
        auto nice = std::vector<Modification*>
        {
            new Modification("N-acetylserine", "", "one", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), ""),
            new Modification("N-acetylserine", "", "two", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")
        };

        Dictionary<std::string, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml.xml)"), true, DecoyType::Reverse, UniProtPtms.Concat(nice), false, std::vector<std::string>(), un);

        Assert::True(ok[0]->getOneBasedPossibleLocalizedModifications().Any([&] (std::any kv)
        {
            return kv->Value->Count > 1;
        }));

        std::vector<std::string> myOriginalIds = ok[0]->getOneBasedPossibleLocalizedModifications()[2]->Select([&] (std::any i)
        {
            i::OriginalId;
        }).ToList();

        Assert::True(std::find(myOriginalIds.begin(), myOriginalIds.end(), "N-acetylserine") != myOriginalIds.end());
    }

    void TestProteinReader::Read_xml_exclude_mods(const std::string &excludeString, bool isExcluded)
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);

        auto nice = std::vector<Modification*>
        {
            new Modification("N-acetylserine", "", "exclude_me", "", motif, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), ""),
            new Modification("N-acetylserine", "", "exclude_me_not", "", motif, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")
        };

        Assert::That(nice[0]->getValidModification());

        Dictionary<std::string, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml.xml)"), true, DecoyType::Reverse, nice, false, std::vector<std::string> {excludeString}, un);

        std::vector<std::string> modTypes;
        for (auto entry : ok2[0]->getOneBasedPossibleLocalizedModifications())
        {
            modTypes.AddRange(entry.second->Select([&] (std::any m)
            {
                m::ModificationType;
            }).ToList()->Distinct());
        }
        Assert::AreEqual(isExcluded, std::find(modTypes.begin(), modTypes.end(), "exclude_me") != modTypes.end());
        Assert::AreEqual(!isExcluded, std::find(modTypes.begin(), modTypes.end(), "exclude_me_not") != modTypes.end());
    }

    void TestProteinReader::CompareOxidationWithAndWithoutCf()
    {
        std::string aString = R"(ID   Methionine (R)-sulfoxide
AC   PTM-0480
FT   MOD_RES
TG   Methionine.
PA   Amino acid side chain.
PP   Anywhere.
CF   O1
MM   15.994915
MA   16.00
LC   Intracellular localisation.
TR   Eukaryota; taxId:2759 (Eukaryota).
KW   Oxidation.
DR   RESID; AA0581.
DR   PSI-MOD; MOD:00720.
//)";
        std::vector<(Modification, string)> errorsA;
        auto a = PtmListLoader::ReadModsFromString(aString, errorsA).front();

        std::string bString = R"(ID   Oxidation of M
TG   M
PP   Anywhere.
MT   Common Variable
CF   O1
//)";
        std::vector<(Modification, string)> errorsB;
        auto b = PtmListLoader::ReadModsFromString(bString, errorsB).front();

        Assert::IsTrue(std::abs(static_cast<double>((dynamic_cast<Modification*>(a))->getMonoisotopicMass()) - static_cast<double>((dynamic_cast<Modification*>(b))->getMonoisotopicMass())) < 1e-6);
        Assert::IsTrue(std::abs(static_cast<double>((dynamic_cast<Modification*>(a))->getMonoisotopicMass()) - static_cast<double>((dynamic_cast<Modification*>(b))->getMonoisotopicMass())) > 1e-7);
    }

    void TestProteinReader::TestReverseDecoyXML()
    {
        auto nice = std::vector<Modification*>();
        Dictionary<std::string, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(disulfidetests.xml)"), true, DecoyType::Reverse, nice, false, std::vector<std::string> {"exclude_me"}, un);

        Assert::AreEqual("MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
        Assert::AreEqual("MNCYNELQYLSCISTCCQDVIGRKQRAVELALTQLDGPSGGLELQEVQPDEVERRSKPTYFFGREGCVLYLAEVLHPGCLHQKVFAQTPKPEWLALLALLPLFHVLLA", ok2[1]->getBaseSequence());
        Assert::AreEqual(ok2[0]->getDisulfideBonds().size()(), ok2[1]->getDisulfideBonds().size()());
        Assert::AreEqual(ok2[0]->getProteolysisProducts().size()(), ok2[1]->getProteolysisProducts().size()());
        for (auto bond : ok2[0]->getDisulfideBonds())
        {
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
        }
        for (auto bond : ok2[1]->getDisulfideBonds())
        {
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
        }
    }

    void TestProteinReader::TestSlideDecoyXML()
    {
        auto nice = std::vector<Modification*>();
        Dictionary<std::string, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(disulfidetests.xml)"), true, DecoyType::Slide, nice, false, std::vector<std::string> {"exclude_me"}, un);

        Assert::AreEqual("MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
        Assert::AreEqual("MTKAEVLQLLAGLHLVHALYAVLGVRFFPYLPLSARWVPDPQQEFLKLHGCPPDLQELLLLVCREKGGFVTQKCRSECELPQVEQYENGCSNGLLYTSAIETACQDRI", ok2[1]->getBaseSequence());
        Assert::AreEqual(ok2[0]->getDisulfideBonds().size()(), ok2[1]->getDisulfideBonds().size()());
        Assert::AreEqual(ok2[0]->getProteolysisProducts().size()(), ok2[1]->getProteolysisProducts().size()());
        for (int i = 0; i < ok2[0]->getProteolysisProducts().size()(); i++)
        {
            Assert::AreEqual(ok2[0]->getProteolysisProducts()->ToArray()[i].OneBasedBeginPosition, ok2[1]->getProteolysisProducts()->ToArray()[i].OneBasedBeginPosition);
            Assert::AreEqual(ok2[0]->getProteolysisProducts()->ToArray()[i].OneBasedEndPosition, ok2[1]->getProteolysisProducts()->ToArray()[i].OneBasedEndPosition);
        }
        for (auto bond : ok2[0]->getDisulfideBonds())
        {
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
        }
        for (auto bond : ok2[1]->getDisulfideBonds())
        {
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
        }
    }

    void TestProteinReader::TestReverseDecoyFasta()
    {
        std::vector<string> a;
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(fasta.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

        Assert::AreEqual("MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
        Assert::AreEqual("MGGFGYLTRGQRKLAYVVDMATVTKRKAHETYTVADRIVNELFVKLVGRTEEYILGSIRKVGGRRALRRIAPKTIGQINDRLVKRHRKAGGKGLGKGGKGRGS", prots[1]->getBaseSequence());
    }

    void TestProteinReader::TestSlideDecoyFasta()
    {
        std::vector<string> a;
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(fasta.fasta)"), true, DecoyType::Slide, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

        Assert::AreEqual("MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
        Assert::AreEqual("MVRRRNAQGIGKGAGRKLRRSGGVGRGSKLLYKEGRKVHKKFLEDVIRGATTPTIHRKAKRVGAKDIVGAIKEQTRGLLGVGLGNFIYDTVGYRELAYRVTMT", prots[1]->getBaseSequence());
    }
}
