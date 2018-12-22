#include "TestProteomicsReadWrite.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/ModificationWithLocation.h"
#include "../Proteomics/TerminusLocalization.h"
#include "../Proteomics/Protein.h"
#include "../UsefulProteomicsDatabases/DecoyType.h"
#include "../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../UsefulProteomicsDatabases/ProteinDbWriter.h"
#include "../Proteomics/ModificationWithMass.h"
#include "../Proteomics/DatabaseReference.h"
#include "../Proteomics/DisulfideBond.h"
#include "../Proteomics/SequenceVariation.h"
#include "../Proteomics/ProteolysisProduct.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {

    void TestProteomicsReadWrite::Test_read_write_read_xml() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml2.xml)"), true, DecoyType::None, nice, false, nullptr, un);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml2.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i) {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::AreEqual(9, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"GO";
        }));
        Assert::AreEqual(3, ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"GO";
        }).Properties->Count());
        Assert::AreEqual(3, ok[0]->getGeneNames().size()());
        Assert::AreEqual(L"primary", ok[0]->getGeneNames().front().Item1);
        Assert::AreEqual(L"JJJ1", ok[0]->getGeneNames().front().Item2);
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml2.xml)"), ok[0]->getDatabaseFilePath());
        Assert::AreEqual(9, ok2[0]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"GO";
        }));
        Assert::AreEqual(3, ok2[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"GO";
        }).Properties->Count());
        Assert::AreEqual(3, ok2[0]->getGeneNames().size()());
        Assert::AreEqual(L"primary", ok2[0]->getGeneNames().front().Item1);
        Assert::AreEqual(L"JJJ1", ok2[0]->getGeneNames().front().Item2);
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml2.xml)"), ok2[0]->getDatabaseFilePath());
        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
    }

    void TestProteomicsReadWrite::Test_read_Ensembl_pepAllFasta() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_fullName_expression, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_gene_expression);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.xml)"));
        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.xml)"), true, DecoyType::None, nice, false, nullptr, un);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i) {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::AreEqual(L"ENSP00000381386", ok[0]->getAccession());
        Assert::AreEqual(L"ENSP00000215773", ok[1]->getAccession());
        Assert::AreEqual(L"ENSG00000099977", ok[0]->getGeneNames().front().Item2);
        Assert::AreEqual(L"ENSG00000099977", ok[1]->getGeneNames().front().Item2);
        Assert::AreEqual(L"pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok[0]->getFullName());
        Assert::AreEqual(L"pep:known chromosome:GRCh37:22:24313554:24322019:-1 gene:ENSG00000099977 transcript:ENST00000350608 gene_biotype:protein_coding transcript_biotype:protein_coding", ok[1]->getFullName());
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_ensembl.pep.all.fasta)"), ok[0]->getDatabaseFilePath());

        Assert::AreEqual(L"ENSP00000381386", ok2[0]->getAccession());
        Assert::AreEqual(L"ENSP00000215773", ok2[1]->getAccession());
        Assert::AreEqual(L"ENSG00000099977", ok2[0]->getGeneNames().front().Item2);
        Assert::AreEqual(L"ENSG00000099977", ok2[1]->getGeneNames().front().Item2);
        Assert::AreEqual(L"pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[0]->getFullName());
        Assert::AreEqual(L"pep:known chromosome:GRCh37:22:24313554:24322019:-1 gene:ENSG00000099977 transcript:ENST00000350608 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[1]->getFullName());
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.xml)"), ok2[0]->getDatabaseFilePath());

        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
    }

    void TestProteomicsReadWrite::Test_read_write_read_fasta() {
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_fullName_expression, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_gene_expression);
        ProteinDbWriter::WriteFastaDatabase(ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.fasta)"), L" ");
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_fullName_expression, ProteinDbLoader::ensembl_accession_expression, ProteinDbLoader::ensembl_gene_expression);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i) {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));

        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any prod) {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
    }

    void TestProteomicsReadWrite::Test_accession_regex_weird() {
        Regex *bad = new Regex(LR"(/()/)");
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, bad, bad, bad, bad);
        ProteinDbWriter::WriteFastaDatabase(ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.fasta)"), L" ");
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, bad, bad, bad, bad);

        Assert::AreEqual(L"ENSP00000381386 pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok[0]->getAccession());
        Assert::AreEqual(L"ENSP00000381386 pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[0]->getAccession());
        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i) {
//C# TO C++ CONVERTER TODO TASK: A 'delete bad' statement was not added since bad was passed to a method or constructor. Handle memory management manually.
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));

//C# TO C++ CONVERTER TODO TASK: A 'delete bad' statement was not added since bad was passed to a method or constructor. Handle memory management manually.
    }

    void TestProteomicsReadWrite::Test_write_with_custom_mods() {
        ModificationMotif m1;
        ModificationMotif::TryGetMotif(L"S", m1);
        ModificationMotif m2;
        ModificationMotif::TryGetMotif(L"T", m2);
        ModificationMotif motiff;
        ModificationMotif::TryGetMotif(L"X", motiff);

        auto nice = std::vector<Modification*> {
            new ModificationWithLocation(L"fayk", L"mt", motiff,TerminusLocalization::Any,nullptr),
            new ModificationWithLocation(L"Phosphoserine", L"mt", m1,TerminusLocalization::Any,nullptr),
            new ModificationWithLocation(L"Phosphothreonine", L"mt", m2,TerminusLocalization::Any,nullptr)
        };

        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"K", motif);
        ModificationWithMass *m = new ModificationWithMass(L"mod", L"mt", motif, TerminusLocalization::Any, 1, , = nullptr, std::vector<double> {-1});

        std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>> new_mods = {
        {
                L"P53863", {std::tuple<int, Modification*>(2, m)}
        }
        };

        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);
        auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(new_mods, ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml2.xml)"));
        Assert::AreEqual(1, newModResEntries.size());
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i) {
//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::AreEqual(2, ok[0]->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(3, ok2[0]->getOneBasedPossibleLocalizedModifications().size());

//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
    }

    void TestProteomicsReadWrite::Test_getptms_from_mzLibxml_without_prep() {
        std::vector<Modification*> ok = ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(cRAP_databaseGPTMD.xml)"));
        Assert::AreEqual(70, ok.size());
    }

    void TestProteomicsReadWrite::AnotherTest() {
        std::vector<ModificationWithMass*> variableModifications;
        std::vector<ModificationWithMass*> fixedModifications;

        // Generate data for files
        Protein *ParentProtein = new Protein(L"MPEPTIDEKANTHE", L"accession1", std::vector<std::tuple<std::wstring, std::wstring>>(), std::unordered_map<int, std::vector<Modification*>>(), nullptr, L"name1", L"fullname1", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<DisulfideBond*>());

        std::vector<ProteolysisProduct*> pp = {new ProteolysisProduct(std::make_optional(4), std::make_optional(8), L"chain")};
        Protein *proteinWithChain = new Protein(L"MAACNNNCAA", L"accession3", std::vector<std::tuple<std::wstring, std::wstring>>(), std::unordered_map<int, std::vector<Modification*>>(), pp, L"name2", L"fullname2", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<DisulfideBond*>());

        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), {ParentProtein, proteinWithChain}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(fdsfsd.xml)"));

//C# TO C++ CONVERTER TODO TASK: A 'delete proteinWithChain' statement was not added since proteinWithChain was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ParentProtein' statement was not added since ParentProtein was passed to a method or constructor. Handle memory management manually.
    }

    void TestProteomicsReadWrite::TestEmptyProteins() {
        Protein *p1 = new Protein(L"SEQENCE", L"p1");
        Assert::AreEqual(L"p1||", p1->getFullDescription());
        Protein *p2 = new Protein(L"SEQENCE", L"p2", , = nullptr, = nullptr, L"namep2");

        auto proteinListToWrite = std::vector<Protein*> {p1, p2};

        // Generate data for files
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), proteinListToWrite, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(differentlyConstuctedProteins.xml)"));

        std::vector<std::wstring> modTypesToExclude;
        std::vector<Modification*> allKnownModifications;
        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(differentlyConstuctedProteins.xml)"), true, DecoyType::None, allKnownModifications, false, modTypesToExclude, un);
        Assert::AreEqual(p1->getAccession(), ok[0]->getAccession());
        Assert::AreEqual(p2->getAccession(), ok[1]->getAccession());
        Assert::AreEqual(p1->getName(), ok[0]->getName());
        Assert::AreEqual(p2->getName(), ok[1]->getName());

        delete p2;
        delete p1;
    }

    void TestProteomicsReadWrite::TestFullProteinReadWrite() {
        Modification *mod = new Modification(L"mod1", L"modType1");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"E", motif);
        ModificationWithLocation *mod2 = new ModificationWithLocation(L"mod2", L"modType1", motif, TerminusLocalization::Any, nullptr);
        ModificationMotif motif3;
        ModificationMotif::TryGetMotif(L"N", motif3);
        ModificationWithMass *mod3 = new ModificationWithMass(L"mod3", L"modType1", motif3, TerminusLocalization::Any, 10, nullptr, nullptr, nullptr);

        std::vector<std::tuple<std::wstring, std::wstring>> gene_names = {std::tuple<std::wstring, std::wstring>(L"a", L"b")};
        std::unordered_map<int, std::vector<Modification*>> oneBasedModifications = {
        {
                3, {mod}
        }, {
                4, {mod2}
            }, {
                5, {mod3}
            }
        };
        std::vector<ProteolysisProduct*> proteolysisProducts = {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), L"propeptide")};

        std::wstring name = L"testName";

        std::wstring full_name = L"testFullName";

        std::vector<DatabaseReference*> databaseReferences = {new DatabaseReference(L"type1", L"id1", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"e1", L"e2")})};

        std::vector<SequenceVariation*> sequenceVariations = {
            new SequenceVariation(3,L"Q", L"N", L"replace Q by N"),
            new SequenceVariation(3,4,L"QE", L"NN", L"replace QE by NN")
        };

        std::vector<DisulfideBond*> disulfideBonds = {
            new DisulfideBond(1, L"ds1"),
            new DisulfideBond(2, 3, L"ds2")
        };

        Protein *p1 = new Protein(L"SEQENCE", L"a1", gene_names, oneBasedModifications, proteolysisProducts, name, full_name, false, true, databaseReferences, sequenceVariations, disulfideBonds, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(bnueiwhf.xml)"));

        // Generate data for files
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), {p1}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(bnueiwhf.xml)"));

        std::vector<std::wstring> modTypesToExclude;
        std::vector<Modification*> allKnownModifications;
        Dictionary<std::wstring, Modification*> unknownModifications;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(bnueiwhf.xml)"), true, DecoyType::None, allKnownModifications, true, modTypesToExclude, unknownModifications);
        Assert::AreEqual(p1->getAccession(), ok[0]->getAccession());
        Assert::AreEqual(p1->getBaseSequence(), ok[0]->getBaseSequence());
        Assert::AreEqual(p1->getDatabaseReferences().front().Id, ok[0]->getDatabaseReferences().front().Id);
        Assert::AreEqual(p1->getDatabaseReferences().front().Properties->First().Item1, ok[0]->getDatabaseReferences().front().Properties->First().Item1);
        Assert::AreEqual(p1->getDatabaseReferences().front().Properties->First().Item2, ok[0]->getDatabaseReferences().front().Properties->First().Item2);
        Assert::AreEqual(p1->getDatabaseReferences().front().Type, ok[0]->getDatabaseReferences().front().Type);

        Assert::AreEqual(p1->getDisulfideBonds().front().Description, ok[0]->getDisulfideBonds().front().Description);
        Assert::AreEqual(p1->getDisulfideBonds().front().OneBasedBeginPosition, ok[0]->getDisulfideBonds().front().OneBasedBeginPosition);
        Assert::AreEqual(p1->getDisulfideBonds().front().OneBasedEndPosition, ok[0]->getDisulfideBonds().front().OneBasedEndPosition);
        Assert::AreEqual(p1->getDisulfideBonds().back().Description, ok[0]->getDisulfideBonds().back().Description);
        Assert::AreEqual(p1->getDisulfideBonds().back().OneBasedBeginPosition, ok[0]->getDisulfideBonds().back().OneBasedBeginPosition);
        Assert::AreEqual(p1->getDisulfideBonds().back().OneBasedEndPosition, ok[0]->getDisulfideBonds().back().OneBasedEndPosition);

        Assert::AreEqual(p1->getFullDescription(), ok[0]->getFullDescription());
        Assert::AreEqual(p1->getFullName(), ok[0]->getFullName());
        Assert::AreEqual(p1->getGeneNames(), ok[0]->getGeneNames());
        Assert::AreEqual(p1->getIsContaminant(), ok[0]->getIsContaminant());
        Assert::AreEqual(p1->getIsDecoy(), ok[0]->getIsDecoy());
        Assert::AreEqual(p1->getLength(), ok[0]->getLength());
        Assert::AreEqual(p1->getName(), ok[0]->getName());
        Assert::AreEqual(p1->getDatabaseFilePath(), ok[0]->getDatabaseFilePath());
        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications()[3][0], ok[0]->getOneBasedPossibleLocalizedModifications()[3][0]);
        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications()[3][0]->id, ok[0]->getOneBasedPossibleLocalizedModifications()[3][0].id);
        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications()[3][0]->modificationType, ok[0]->getOneBasedPossibleLocalizedModifications()[3][0].modificationType);

        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications()[4][0]->id, ok[0]->getOneBasedPossibleLocalizedModifications()[4][0].id);
        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications()[4][0]->modificationType, ok[0]->getOneBasedPossibleLocalizedModifications()[4][0].modificationType);
        Assert::AreEqual((dynamic_cast<ModificationWithLocation*>(p1->getOneBasedPossibleLocalizedModifications()[4][0]))->linksToOtherDbs, (dynamic_cast<ModificationWithLocation*>(ok[0]->getOneBasedPossibleLocalizedModifications()[4][0]))->linksToOtherDbs);
        Assert::AreEqual((dynamic_cast<ModificationWithLocation*>(p1->getOneBasedPossibleLocalizedModifications()[4][0]))->motif, (dynamic_cast<ModificationWithLocation*>(ok[0]->getOneBasedPossibleLocalizedModifications()[4][0]))->motif);
        Assert::AreEqual((dynamic_cast<ModificationWithLocation*>(p1->getOneBasedPossibleLocalizedModifications()[4][0]))->terminusLocalization, (dynamic_cast<ModificationWithLocation*>(ok[0]->getOneBasedPossibleLocalizedModifications()[4][0]))->terminusLocalization);

        Assert::AreEqual((dynamic_cast<ModificationWithMass*>(p1->getOneBasedPossibleLocalizedModifications()[5][0]))->diagnosticIons, (dynamic_cast<ModificationWithMass*>(ok[0]->getOneBasedPossibleLocalizedModifications()[5][0]))->diagnosticIons);
        Assert::AreEqual((dynamic_cast<ModificationWithMass*>(p1->getOneBasedPossibleLocalizedModifications()[5][0]))->neutralLosses, (dynamic_cast<ModificationWithMass*>(ok[0]->getOneBasedPossibleLocalizedModifications()[5][0]))->neutralLosses);
        Assert::AreEqual((dynamic_cast<ModificationWithMass*>(p1->getOneBasedPossibleLocalizedModifications()[5][0]))->monoisotopicMass, (dynamic_cast<ModificationWithMass*>(ok[0]->getOneBasedPossibleLocalizedModifications()[5][0]))->monoisotopicMass);

        Assert::AreEqual(p1->getProteolysisProducts().front().OneBasedBeginPosition, ok[0]->getProteolysisProducts().front().OneBasedBeginPosition);
        Assert::AreEqual(p1->getProteolysisProducts().front().OneBasedEndPosition, ok[0]->getProteolysisProducts().front().OneBasedEndPosition);
        Assert::AreEqual(p1->getProteolysisProducts().front().Type, ok[0]->getProteolysisProducts().front().Type);

        Assert::AreEqual(p1->getSequenceVariations().front().Description, ok[0]->getSequenceVariations().front().Description);
        Assert::AreEqual(p1->getSequenceVariations().front().OneBasedBeginPosition, ok[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(p1->getSequenceVariations().front().OneBasedEndPosition, ok[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(p1->getSequenceVariations().front().OriginalSequence, ok[0]->getSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(p1->getSequenceVariations().front().VariantSequence, ok[0]->getSequenceVariations().front().VariantSequence);
        Assert::AreEqual(p1->getSequenceVariations().back().Description, ok[0]->getSequenceVariations().back().Description);
        Assert::AreEqual(p1->getSequenceVariations().back().OneBasedBeginPosition, ok[0]->getSequenceVariations().back().OneBasedBeginPosition);
        Assert::AreEqual(p1->getSequenceVariations().back().OneBasedEndPosition, ok[0]->getSequenceVariations().back().OneBasedEndPosition);
        Assert::AreEqual(p1->getSequenceVariations().back().OriginalSequence, ok[0]->getSequenceVariations().back().OriginalSequence);
        Assert::AreEqual(p1->getSequenceVariations().back().VariantSequence, ok[0]->getSequenceVariations().back().VariantSequence);

//C# TO C++ CONVERTER TODO TASK: A 'delete p1' statement was not added since p1 was passed to a method or constructor. Handle memory management manually.
        delete mod3;
        delete mod2;
        delete mod;
    }

    void TestProteomicsReadWrite::TestReadWriteSeqVars() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml.xml)"), true, DecoyType::None, nice, false, nullptr, un);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_xml.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);

        Assert::AreEqual(ok[0]->getSequenceVariations().size()(), ok2[0]->getSequenceVariations().size()());
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedBeginPosition, ok2[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedEndPosition, ok2[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().Description, ok2[0]->getSequenceVariations().front().Description);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OriginalSequence, ok2[0]->getSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().VariantSequence, ok2[0]->getSequenceVariations().front().VariantSequence);
    }

    void TestProteomicsReadWrite::TestReadWriteSeqVars2() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(seqvartests.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_seqvartests.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(rewrite_seqvartests.xml)"), true, DecoyType::None, nice, false, std::vector<std::wstring>(), un);

        Assert::AreEqual(ok[0]->getSequenceVariations().size()(), ok2[0]->getSequenceVariations().size()());
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedBeginPosition, ok2[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedEndPosition, ok2[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().Description, ok2[0]->getSequenceVariations().front().Description);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OriginalSequence, ok2[0]->getSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().VariantSequence, ok2[0]->getSequenceVariations().front().VariantSequence);
    }
}
