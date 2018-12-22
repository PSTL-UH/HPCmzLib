#include "TestProteinReader.h"
#include "../Proteomics/DatabaseReference.h"
#include "../Proteomics/SequenceVariation.h"
#include "../Proteomics/DisulfideBond.h"
#include "../Proteomics/ProteolysisProduct.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/ModificationWithMass.h"
#include "../Proteomics/Protein.h"
#include "../Proteomics/TerminusLocalization.h"
#include "../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../Proteomics/ModificationWithLocation.h"
#include "../UsefulProteomicsDatabases/DecoyType.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {

    void TestProteinReader::Compare_protein_properties() {
        DatabaseReference *d = new DatabaseReference(L"asdf", L"asdfg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"bbb", L"ccc")});
        DatabaseReference *dd = new DatabaseReference(L"asdf", L"asdfg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"bbb", L"ccc")});
        DatabaseReference *de = new DatabaseReference(L"asdf", L"asdefg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"bbb", L"ccc")});
        DatabaseReference *df = new DatabaseReference(L"asddf", L"asdfg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"bbb", L"ccc")});
        DatabaseReference *dg = new DatabaseReference(L"asdf", L"asdfg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"babb", L"ccc")});
        DatabaseReference *dh = new DatabaseReference(L"asdf", L"asdfg", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"bbb", L"cccf")});
        Assert::True(dd->Equals(d));
        Assert::False(de->Equals(d));
        Assert::False(df->Equals(d));
        Assert::False(dg->Equals(d));
        Assert::False(dh->Equals(d));
        Assert::AreEqual(5, {d, dd, de, df, dg, dh}->Count);

        SequenceVariation *s = new SequenceVariation(1, L"hello", L"hey", L"hi");
        SequenceVariation *sv = new SequenceVariation(1, L"hello", L"hey", L"hi");
        SequenceVariation *sss = new SequenceVariation(2, L"hallo", L"hey", L"hi");
        SequenceVariation *ssss = new SequenceVariation(1, L"hello", L"heyy", L"hi");
        SequenceVariation *sssss = new SequenceVariation(1, L"hello", L"hey", L"hii");
        Assert::True(s->Equals(sv));
        Assert::False(s->Equals(sss));
        Assert::False(s->Equals(ssss));
        Assert::False(s->Equals(sssss));
        Assert::AreEqual(4, {s, sv, sss, ssss, sssss}->Count);

        DisulfideBond *b = new DisulfideBond(1, L"hello");
        DisulfideBond *bb = new DisulfideBond(1, L"hello");
        DisulfideBond *bbb = new DisulfideBond(1, 2, L"hello");
        DisulfideBond *bbbb = new DisulfideBond(1, 2, L"hello");
        DisulfideBond *ba = new DisulfideBond(1, 3, L"hello");
        DisulfideBond *baa = new DisulfideBond(2, 2, L"hello");
        DisulfideBond *baaa = new DisulfideBond(1, 2, L"hallo");
        Assert::AreEqual(b, bb);
        Assert::AreEqual(bbb, bbbb);
        Assert::AreNotEqual(b, bbb);
        Assert::AreNotEqual(ba, bbb);
        Assert::AreNotEqual(baa, bbb);
        Assert::AreNotEqual(baaa, bbb);
        Assert::AreEqual(5, {b, bb, bbb, bbbb, ba, baa, baaa}->Count);

        ProteolysisProduct *pp = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), L"hello");
        ProteolysisProduct *paaa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), L"hello");
        ProteolysisProduct *p = new ProteolysisProduct(std::nullopt, std::nullopt, L"hello");
        ProteolysisProduct *ppp = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), L"hello");
        ProteolysisProduct *pa = new ProteolysisProduct(std::make_optional(2), std::make_optional(1), L"hello");
        ProteolysisProduct *paa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), L"hallo");
        Assert::AreEqual(pp, paaa);
        Assert::AreNotEqual(p, pp);
        Assert::AreNotEqual(pp, ppp);
        Assert::AreNotEqual(pp, pa);
        Assert::AreNotEqual(pp, paa);
        Assert::AreEqual(5, {p, pp, ppp, pa, paa, paaa}->Count);

//C# TO C++ CONVERTER TODO TASK: A 'delete paa' statement was not added since paa was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pa' statement was not added since pa was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ppp' statement was not added since ppp was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete paaa' statement was not added since paaa was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp' statement was not added since pp was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete baaa' statement was not added since baaa was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete baa' statement was not added since baa was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ba' statement was not added since ba was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bbbb' statement was not added since bbbb was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bbb' statement was not added since bbb was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bb' statement was not added since bb was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sssss' statement was not added since sssss was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ssss' statement was not added since ssss was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sss' statement was not added since sss was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv' statement was not added since sv was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete s' statement was not added since s was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete dh' statement was not added since dh was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete dg' statement was not added since dg was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete df' statement was not added since df was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete de' statement was not added since de was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete dd' statement was not added since dd was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete d' statement was not added since d was passed to a method or constructor. Handle memory management manually.
    }

    void TestProteinReader::Merge_a_couple_proteins() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"A", motif);
        Protein *p = new Protein(L"ASEQUENCE", L"id", {std::tuple<std::wstring, std::wstring>(L"gene", L"name")},
        std::unordered_map<int, std::vector<Modification*>> {
        {
                1, {new ModificationWithMass(L"mod", L"type", motif, TerminusLocalization::Any, 1, nullptr, nullptr, nullptr)}
        }
        },
        {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), L"prod")},
        L"name", L"full_name", false, false, std::vector<DatabaseReference*> {
            new DatabaseReference(L"ref", L"id", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"type", L"property")})
        },
        std::vector<SequenceVariation*> {new SequenceVariation(1, 2, L"A", L"B", L"var")});

        Protein *p2 = new Protein(L"ASEQUENCE", L"id", {std::tuple<std::wstring, std::wstring>(L"gene", L"name")},
        std::unordered_map<int, std::vector<Modification*>> {
        {
                1, {new ModificationWithMass(L"mod2", L"type", motif, TerminusLocalization::Any, 10, nullptr, nullptr, nullptr)}
        }
        },
        {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), L"prod")},
        L"name", L"full_name", false, false, std::vector<DatabaseReference*> {
            new DatabaseReference(L"ref", L"id", std::vector<std::tuple<std::wstring, std::wstring>> {std::tuple<std::wstring, std::wstring>(L"type", L"property")})
        },
        std::vector<SequenceVariation*> {new SequenceVariation(1, 2, L"A", L"B", L"var")});

        std::vector<Protein*> merged = ProteinDbLoader::Merge_proteins(std::vector<Protein*> {p, p2}).ToList();
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

    void TestProteinReader::XmlTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'M', ok[0][0]);
        Assert::AreEqual(L'M', ok[1][0]);

        Assert::AreEqual(L"P62805|H4_HUMAN|Histone H4", ok[0]->getFullDescription());
        Assert::AreEqual(L"DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFullDescription());
        Assert::AreEqual(L"ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Id);
        Assert::AreEqual(L"protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Properties->First().Item1);
        Assert::AreEqual(L"ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Properties->First().Item2);
        Assert::AreEqual(42, ok[0]->getGeneNames().size()());
        Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t) {
            return t->Item1 == L"primary";
        })->Count());
        Assert::AreEqual(L"HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t) {
            return t->Item1 == L"primary";
        }).First().Item2);
        Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }));
        Assert::AreEqual(0, ok[0]->getDisulfideBonds().size()());
        Assert::AreEqual(1, ok[0]->getSequenceVariations().size()());
        Assert::AreEqual(1, ok[1]->getSequenceVariations().size()()); // decoys get the same sequence variations
        Assert::AreEqual(64, ok[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(64, ok[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreNotEqual(ok[0]->getSequenceVariations().front().Description, ok[1]->getSequenceVariations().front().Description); //decoys and target variations don't have the same desc.
    }

    void TestProteinReader::SeqVarXmlTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(seqvartests.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'M', ok[0][0]);
        Assert::AreEqual(L'M', ok[1][0]);
        std::vector<SequenceVariation*> seqvar0 = ok[0]->getSequenceVariations().ToList();
        std::vector<SequenceVariation*> seqvar1 = ok[1]->getSequenceVariations().ToList();
        Assert::AreEqual(seqvar0.size() + 1, seqvar1.size());
        Assert::AreEqual(L'M', ok[0]->getSequenceVariations().front().OriginalSequence[0]);
        Assert::AreEqual(L'M', ok[0]->getSequenceVariations().front().VariantSequence[0]);
        Assert::AreEqual(L'A', ok[1]->getSequenceVariations().front().OriginalSequence[0]);
        Assert::AreEqual(L'P', ok[1]->getSequenceVariations().front().VariantSequence[0]);
        Assert::AreEqual(L'M', seqvar0[1]->getOriginalSequence()[0]);
        Assert::AreEqual(L"", seqvar1[1]->getVariantSequence());
        for (auto s : seqvar0) {
            Assert::AreEqual(s->getOriginalSequence(), ok[0]->getBaseSequence()->substr(s->getOneBasedBeginPosition() - 1, s->getOneBasedEndPosition() - s->getOneBasedBeginPosition() + 1));
        }
        for (auto s : seqvar1) {
            Assert::AreEqual(s->getOriginalSequence(), ok[1]->getBaseSequence()->substr(s->getOneBasedBeginPosition() - 1, s->getOneBasedEndPosition() - s->getOneBasedBeginPosition() + 1));
        }
        Assert::AreNotEqual(ok[0]->getSequenceVariations().front().Description, ok[1]->getSequenceVariations().front().Description); //decoys and target variations don't have the same desc.
    }

    void TestProteinReader::DisulfideXmlTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(disulfidetests.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'M', ok[0][0]);
        Assert::AreEqual(L'M', ok[1][0]);

        Assert::AreEqual(3, ok[0]->getDisulfideBonds().size()());
        Assert::AreEqual(31, ok[0]->getDisulfideBonds().front().OneBasedBeginPosition);
        Assert::AreEqual(94, ok[0]->getDisulfideBonds().front().OneBasedEndPosition);
        Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).OneBasedBeginPosition);
        Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).OneBasedEndPosition);

        Assert::AreEqual(3, ok[1]->getDisulfideBonds().size()());
        Assert::AreEqual(79, ok[1]->getDisulfideBonds().front().OneBasedBeginPosition);
        Assert::AreEqual(16, ok[1]->getDisulfideBonds().front().OneBasedEndPosition);
        Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).OneBasedBeginPosition);
        Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).OneBasedEndPosition);
        Assert::AreNotEqual(ok[0]->getDisulfideBonds().front().Description, ok[1]->getDisulfideBonds().front().Description); //decoys and target disulfide bonds don't have the same desc.
    }

    void TestProteinReader::XmlTest_2entry() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml2.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any d) {
                return d->OneBasedBeginPosition == nullptr || d::OneBasedBeginPosition > 0;
            });
        }));

        Assert::True(ok.All([&] (std::any p) {
            p::ProteolysisProducts::All([&] (std::any d) {
                return d->OneBasedEndPosition == nullptr || d::OneBasedEndPosition <= p->Length;
            });
        }));

        Assert::False(ok.All([&] (std::any p) {
            p::BaseSequence->Contains(L" ");
        }));
        Assert::False(ok.All([&] (std::any p) {
            p::BaseSequence->Contains(L"\t");
        }));
        Assert::False(ok.All([&] (std::any p) {
            p::BaseSequence->Contains(L"\n");
        }));

        //GoTerm checks
        std::vector<Protein*> targets = ok.Where([&] (std::any p) {
            !p::IsDecoy;
        }).ToList();
        Assert::AreEqual(2, targets.size());
        Assert::AreEqual(1, targets[0]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"EnsemblFungi";
        }));
        Assert::AreEqual(1, targets[1]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"EnsemblFungi";
        }));
    }

    void TestProteinReader::XmlGzTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml.xml.gz)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'M', ok[0][0]);
        Assert::AreEqual(L'M', ok[1][0]);

        Assert::AreEqual(L"P62805|H4_HUMAN|Histone H4", ok[0]->getFullDescription());
        Assert::AreEqual(L"DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFullDescription());
        Assert::AreEqual(L"ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Id);
        Assert::AreEqual(L"protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Properties->First().Item1);
        Assert::AreEqual(L"ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }).Properties->First().Item2);
        Assert::AreEqual(42, ok[0]->getGeneNames().size()());
        Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t) {
            return t->Item1 == L"primary";
        })->Count());
        Assert::AreEqual(L"HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t) {
            return t->Item1 == L"primary";
        }).First().Item2);
        Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef) {
            return dbRef->Type == L"Ensembl";
        }));
    }

    void TestProteinReader::XmlFunkySequenceTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(fake_h4.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'S', ok[0][0]);
        Assert::AreEqual(L'G', ok[1][0]);
    }

    void TestProteinReader::XmlModifiedStartTest() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"fayk", L"mt", motif,TerminusLocalization::Any,nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(modified_start.xml)"), true, DecoyType::Reverse, nice, false, nullptr, un);

        Assert::AreEqual(L'M', ok[0][0]);
        Assert::AreEqual(L'M', ok[1][0]);
        Assert::AreEqual(1, ok[1]->getOneBasedPossibleLocalizedModifications()[1].size());
    }

    void TestProteinReader::FastaTest() {
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(fasta.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_fullName_expression, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_gene_expression);
        Assert::AreEqual(L"P62805", prots.front().Accession);
        Assert::AreEqual(L"H4_HUMAN Histone H4", prots.front()->FullName);
        Assert::AreEqual(L"HIST1H4A", prots.front().GeneNames::First().Item2);
    }

    void TestProteinReader::Load_fasta_handle_tooHigh_indices() {
        ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(bad.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_fullName_expression, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_gene_expression);
    }

    void TestProteinReader::Read_xml_mod_collision() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {
            new ModificationWithLocation(L"N-acetylserine", L"one", motif, TerminusLocalization::Any, nullptr),
            new ModificationWithLocation(L"N-acetylserine", L"two", motif, TerminusLocalization::Any, nullptr)
        };

        Dictionary<std::wstring, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml.xml)"), true, DecoyType::Reverse, nice, false, std::vector<std::wstring>(), un);
        Assert::True(ok[0]->getOneBasedPossibleLocalizedModifications().Any([&] (std::any kv) {
            return kv->Value->Count > 1;
        }));
        Assert::True(ok[0]->getOneBasedPossibleLocalizedModifications()[2]->Select([&] (std::any m) {
            m::id;
        })->Contains(L"N-acetylserine"));
    }

    void TestProteinReader::Read_xml_exclude_mods() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"X", motif);
        auto nice = std::vector<Modification*> {new ModificationWithLocation(L"N-acetylserine", L"exclude_me", motif, TerminusLocalization::Any, nullptr)};

        Dictionary<std::wstring, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(xml.xml)"), true, DecoyType::Reverse, nice, false, std::vector<std::wstring> {L"exclude_me"}, un);
        Assert::False(ok2[0]->getOneBasedPossibleLocalizedModifications()[2]->Select([&] (std::any m) {
            m::id;
        })->Contains(L"N-acetylserine"));
    }

    void TestProteinReader::CompareOxidationWithAndWithoutCf() {
        std::wstring aString = LR"(ID   Methionine (R)-sulfoxide
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
        auto a = PtmListLoader::ReadModsFromString(aString).front();

        std::wstring bString = LR"(ID   Oxidation of M
TG   M
PP   Anywhere.
MT   Common Variable
CF   O1
//)";
        auto b = PtmListLoader::ReadModsFromString(bString).front();

        Assert::IsTrue(std::abs((dynamic_cast<ModificationWithMass*>(a))->monoisotopicMass - (dynamic_cast<ModificationWithMass*>(b))->monoisotopicMass) < 1e-6);
        Assert::IsTrue(std::abs((dynamic_cast<ModificationWithMass*>(a))->monoisotopicMass - (dynamic_cast<ModificationWithMass*>(b))->monoisotopicMass) > 1e-7);
    }

    void TestProteinReader::TestKeywordAugmentation() {
        std::wstring bString = LR"(ID   Oxidation
TG   M or R
PP   Anywhere.
MT   Common Variable
CF   O1
//)";
        auto a = PtmListLoader::ReadModsFromString(bString).front();
        auto b = PtmListLoader::ReadModsFromString(bString).back();

        Assert::AreEqual(L"Oxidation on M", a->id);
        Assert::AreEqual(L"Oxidation", (dynamic_cast<ModificationWithMass*>(a))->keywords.front());
        Assert::AreEqual(L"Oxidation on R", b->id);
        Assert::AreEqual(L"Oxidation", (dynamic_cast<ModificationWithMass*>(b))->keywords.front());
    }

    void TestProteinReader::TestReverseDecoyXML() {
        auto nice = std::vector<Modification*>();
        Dictionary<std::wstring, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(disulfidetests.xml)"), true, DecoyType::Reverse, nice, false, std::vector<std::wstring> {L"exclude_me"}, un);
        Assert::AreEqual(L"MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
        Assert::AreEqual(L"MNCYNELQYLSCISTCCQDVIGRKQRAVELALTQLDGPSGGLELQEVQPDEVERRSKPTYFFGREGCVLYLAEVLHPGCLHQKVFAQTPKPEWLALLALLPLFHVLLA", ok2[1]->getBaseSequence());
        Assert::AreEqual(ok2[0]->getDisulfideBonds().size()(), ok2[1]->getDisulfideBonds().size()());
        Assert::AreEqual(ok2[0]->getProteolysisProducts().size()(), ok2[1]->getProteolysisProducts().size()());
        for (auto bond : ok2[0]->getDisulfideBonds()) {
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], L'C');
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], L'C');
        }
        for (auto bond : ok2[1]->getDisulfideBonds()) {
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], L'C');
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], L'C');
        }
    }

    void TestProteinReader::TestSlideDecoyXML() {
        auto nice = std::vector<Modification*>();
        Dictionary<std::wstring, Modification*> un;
        auto ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(disulfidetests.xml)"), true, DecoyType::Slide, nice, false, std::vector<std::wstring> {L"exclude_me"}, un);
        Assert::AreEqual(L"MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
        Assert::AreEqual(L"MTKAEVLQLLAGLHLVHALYAVLGVRFFPYLPLSARWVPDPQQEFLKLHGCPPDLQELLLLVCREKGGFVTQKCRSECELPQVEQYENGCSNGLLYTSAIETACQDRI", ok2[1]->getBaseSequence());
        Assert::AreEqual(ok2[0]->getDisulfideBonds().size()(), ok2[1]->getDisulfideBonds().size()());
        Assert::AreEqual(ok2[0]->getProteolysisProducts().size()(), ok2[1]->getProteolysisProducts().size()());
        for (int i = 0; i < ok2[0]->getProteolysisProducts().size()(); i++) {
            Assert::AreEqual(ok2[0]->getProteolysisProducts()->ToArray()[i].OneBasedBeginPosition, ok2[1]->getProteolysisProducts()->ToArray()[i].OneBasedBeginPosition);
            Assert::AreEqual(ok2[0]->getProteolysisProducts()->ToArray()[i].OneBasedEndPosition, ok2[1]->getProteolysisProducts()->ToArray()[i].OneBasedEndPosition);
        }
        for (auto bond : ok2[0]->getDisulfideBonds()) {
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], L'C');
            Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], L'C');
        }
        for (auto bond : ok2[1]->getDisulfideBonds()) {
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], L'C');
            Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], L'C');
        }
    }

    void TestProteinReader::TestReverseDecoyFasta() {
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(fasta.fasta)"), true, DecoyType::Reverse, false, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_fullName_expression, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_gene_expression);
        Assert::AreEqual(L"MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
        Assert::AreEqual(L"MGGFGYLTRGQRKLAYVVDMATVTKRKAHETYTVADRIVNELFVKLVGRTEEYILGSIRKVGGRRALRRIAPKTIGQINDRLVKRHRKAGGKGLGKGGKGRGS", prots[1]->getBaseSequence());
    }

    void TestProteinReader::TestSlideDecoyFasta() {
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(fasta.fasta)"), true, DecoyType::Slide, false, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_fullName_expression, ProteinDbLoader::uniprot_accession_expression, ProteinDbLoader::uniprot_gene_expression);
        Assert::AreEqual(L"MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
        Assert::AreEqual(L"MVRRRNAQGIGKGAGRKLRRSGGVGRGSKLLYKEGRKVHKKFLEDVIRGATTPTIHRKAKRVGAKDIVGAIKEQTRGLLGVGLGNFIYDTVGYRELAYRVTMT", prots[1]->getBaseSequence());
    }
}
