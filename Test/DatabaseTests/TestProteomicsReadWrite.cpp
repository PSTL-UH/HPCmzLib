#include "TestProteomicsReadWrite.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../Proteomics/Modifications/ModificationMotif.h"
#include "../../Proteomics/Protein/Protein.h"
#include "../../Proteomics/Protein/DatabaseReference.h"
#include "../../Proteomics/Protein/DisulfideBond.h"
#include "../../Proteomics/Protein/SequenceVariation.h"
#include "../../Proteomics/Protein/ProteolysisProduct.h"
#include "../../MassSpectrometry/Enums/DissociationType.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/ProteinDbWriter.h"
#include "../../UsefulProteomicsDatabases/FastaHeaderFieldRegex.h"
#include "../../UsefulProteomicsDatabases/PtmListLoader.h"

#include "Assert.h"
#include <experimental/filesystem>

using namespace MassSpectrometry;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;


int main ( int argc, char **argv )
{
    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

#ifdef LATER
    std::cout << ++i << ". ReadXmlNulls" << std::endl;
    Test::TestProteomicsReadWrite::ReadXmlNulls();

    std::cout << ++i << ". Test_readUniProtXML_writeProteinXml" << std::endl;    
    Test::TestProteomicsReadWrite::Test_readUniProtXML_writeProteinXml();
#endif

    std::cout << ++i << ". Test_read_Ensembl_pepAllFasta" << std::endl;    
    Test::TestProteomicsReadWrite::Test_read_Ensembl_pepAllFasta();
    
    std::cout << ++i << ". FastaTest" << std::endl;    
    Test::TestProteomicsReadWrite::FastaTest();

    std::cout << ++i << ". Test_read_write_read_fasta" << std::endl;    
    Test::TestProteomicsReadWrite::Test_read_write_read_fasta();

#ifdef LATER
    std::cout << ++i << ". Test_read_xml_write_read_fasta" << std::endl;    
    Test::TestProteomicsReadWrite::Test_read_xml_write_read_fasta();

    std::cout << ++i << ". Test_accession_regex_weird" << std::endl;    
    Test::TestProteomicsReadWrite::Test_accession_regex_weird();

    std::cout << ++i << ". Test_write_with_custom_mods" << std::endl;    
    Test::TestProteomicsReadWrite::Test_write_with_custom_mods();
#endif
    
    std::cout << ++i << ". AnotherTest" << std::endl;    
    Test::TestProteomicsReadWrite::AnotherTest();

#ifdef LATER
    std::cout << ++i << ". TestEmptyProteins" << std::endl;    
    Test::TestProteomicsReadWrite::TestEmptyProteins();

    std::cout << ++i << ". TestFullProteinReadWrite" << std::endl;    
    Test::TestProteomicsReadWrite::TestFullProteinReadWrite();

    std::cout << ++i << ". TestReadWriteSeqVars" << std::endl;    
    Test::TestProteomicsReadWrite::TestReadWriteSeqVars();

    std::cout << ++i << ". TestReadWriteSeqVars2" << std::endl;    
    Test::TestProteomicsReadWrite::TestReadWriteSeqVars2();

    std::cout << ++i << ". TestModificationGeneralToString" << std::endl;    
    Test::TestProteomicsReadWrite::TestModificationGeneralToString();

    std::cout << ++i << ". TestModificationGeneral_Equals" << std::endl;    
    Test::TestProteomicsReadWrite::TestModificationGeneral_Equals();

    std::cout << ++i << ". Test_CustumPrunedDatabaseWriteAndRead" << std::endl;    
    Test::TestProteomicsReadWrite::Test_CustumPrunedDatabaseWriteAndRead();
#endif
    return 0;
}

namespace Test
{
    
#ifdef LATER
    void TestProteomicsReadWrite::ReadXmlNulls()
    {
        Dictionary<std::string, Modification*> un;
        auto ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);
    }

    void TestProteomicsReadWrite::Test_readUniProtXML_writeProteinXml()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);
        auto nice = std::vector<Modification*> {new Modification(
                "fayk", "", "mt", "", motif,
                "Anywhere.", nullptr, std::make_optional(10),
                std::unordered_map<std::string, std::vector<std::string>>(),
                std::unordered_map<std::string, std::vector<std::string>>(),
                std::vector<std::string>(),
                std::unordered_map<DissociationType,
                std::vector<double>>(),
                std::unordered_map<DissociationType, std::vector<double>>(), "")};

        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));
        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);
        auto uniprotPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();

        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), true, DecoyType::None, uniprotPtms.Concat(nice), false, std::vector<std::string>(), un);
        Protein *zero = ok[0];
        Protein *one = ok[1];
        std::unordered_map<int, std::vector<Modification*>> zero_mods = dynamic_cast<std::unordered_map<int, std::vector<Modification*>*>*>(zero->getOneBasedPossibleLocalizedModifications());
        std::unordered_map<int, std::vector<Modification*>> one_mods = dynamic_cast<std::unordered_map<int, std::vector<Modification*>*>*>(one->getOneBasedPossibleLocalizedModifications());

        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml2.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::AreEqual(9, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "GO";
        }));
        Assert::AreEqual(1, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "GeneID";
        }));
        Assert::AreEqual(3, ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "GO";
        }).Properties->Count());
        Assert::AreEqual(3, ok[0]->getGeneNames().size()());
        Assert::AreEqual("primary", ok[0]->getGeneNames().front().Item1);
        Assert::AreEqual("JJJ1", ok[0]->getGeneNames().front().Item2);
        Assert::AreEqual("Saccharomyces cerevisiae (strain ATCC 204508 / S288c)", ok[0]->getOrganism());
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), ok[0]->getDatabaseFilePath());
        Assert::AreEqual(9, ok2[0]->getDatabaseReferences().size()([&] (std::any dbRef)
        {
            return dbRef->Type == "GO";
        }));
        Assert::AreEqual(3, ok2[0]->getDatabaseReferences().First([&] (std::any dbRef)
        {
            return dbRef->Type == "GO";
        }).Properties->Count());
        Assert::AreEqual(3, ok2[0]->getGeneNames().size()());
        Assert::AreEqual("primary", ok2[0]->getGeneNames().front().Item1);
        Assert::AreEqual("JJJ1", ok2[0]->getGeneNames().front().Item2);
        Assert::AreEqual("Saccharomyces cerevisiae (strain ATCC 204508 / S288c)", ok2[0]->getOrganism());
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml2.xml)"), ok2[0]->getDatabaseFilePath());
        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
    }
#endif
   
    void TestProteomicsReadWrite::Test_read_Ensembl_pepAllFasta()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        ModificationMotif* motif;
        ModificationMotif::TryGetMotif("X", &motif);
        Modification* mod = new Modification("fayk", "", "mt", "", motif, "Anywhere.", nullptr,
                                    std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(),
                                    std::unordered_map<std::string, std::vector<std::string>>(),
                                    std::vector<std::string>(), std::unordered_map<DissociationType,
                                    std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> nice = {mod};

        std::vector<std::string> a;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta( testdir + "/test_ensembl.pep.all.fasta", true,
                                                                      DecoyType::None, false,
                                                                      ProteinDbLoader::EnsemblAccessionRegex,
                                                                      ProteinDbLoader::EnsemblFullNameRegex,
                                                                      ProteinDbLoader::EnsemblAccessionRegex,
                                                                      ProteinDbLoader::EnsemblGeneNameRegex, nullptr, a);

#ifdef LATER
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), ok,
                                          testdir + "/rewrite_test_ensembl.pep.all.xml" );
        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(testdir + "/rewrite_test_ensembl.pep.all.xml", true,
            DecoyType::None, nice, false, std::vector<std::string>(), un);
        
        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
#endif

        std::string s = "ENSP00000381386";
        Assert::AreEqual(s, ok[0]->getAccession());

        s = "ENSP00000215773";
        Assert::AreEqual(s, ok[1]->getAccession());

        s = "ENSG00000099977";
        Assert::AreEqual(s, std::get<1>(ok[0]->getGeneNames().front()));

        s = "ENSG00000099977";
        Assert::AreEqual(s, std::get<1>(ok[1]->getGeneNames().front()));

        s = "pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding";
        Assert::AreEqual(s, ok[0]->getFullName());

        s = "pep:known chromosome:GRCh37:22:24313554:24322019:-1 gene:ENSG00000099977 transcript:ENST00000350608 gene_biotype:protein_coding transcript_biotype:protein_coding";
        Assert::AreEqual(s, ok[1]->getFullName());

        s = testdir + "/test_ensembl.pep.all.fasta";            
        Assert::AreEqual(s, ok[0]->getDatabaseFilePath());

#ifdef LATER
        Assert::AreEqual("ENSP00000381386", ok2[0]->getAccession());
        Assert::AreEqual("ENSP00000215773", ok2[1]->getAccession());
        Assert::AreEqual("ENSG00000099977", ok2[0]->getGeneNames().front().Item2);
        Assert::AreEqual("ENSG00000099977", ok2[1]->getGeneNames().front().Item2);
        Assert::AreEqual("pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[0]->getFullName());
        Assert::AreEqual("pep:known chromosome:GRCh37:22:24313554:24322019:-1 gene:ENSG00000099977 transcript:ENST00000350608 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[1]->getFullName());
        Assert::AreEqual(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_test_ensembl.pep.all.xml)"), ok2[0]->getDatabaseFilePath());
#endif
        for ( auto p: ok ) {
            for ( auto prod : p->getProteolysisProducts() ) {
                Assert::IsTrue (!prod->getOneBasedBeginPosition().has_value() ||
                                prod->getOneBasedBeginPosition().value() > 0 &&
                                prod->getOneBasedBeginPosition().value() <= p->getLength());
                Assert::IsTrue (!prod->getOneBasedEndPosition().has_value() ||
                                prod->getOneBasedEndPosition().value() > 0 &&
                                prod->getOneBasedEndPosition().value() <= p->getLength());
            }
        }

#ifdef LATER
        for ( auto p: ok2 ) {
            for ( auto prod: p->getProteolysisProducts() ) {
                Assert::IsTrue (!prod->getOneBasedBeginPosition().has_value() ||
                                prod->getOneBasedBeginPosition().value() > 0 &&
                                prod->getOneBasedBeginPosition().value() <= p->getLength());
                Assert::IsTrue (!prod->getOneBasedEndPosition().has_value() ||
                                prod->getOneBasedEndPosition().value() > 0 &&
                                prod->getOneBasedEndPosition().value() <= p->getLength());
            }
        }
#endif
        
    }
    
    void TestProteomicsReadWrite::FastaTest()
    {
        std::vector<std::string> a;
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(testdir + "/fasta.fasta", true,
            DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex,
            ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotNameRegex,
            ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);
        ProteinDbWriter::WriteFastaDatabase(prots, testdir +"/rewrite_fasta.fasta", "|");

        std::vector<std::string> un;
        std::vector<Protein*> prots2 = ProteinDbLoader::LoadProteinFasta(testdir + "/rewrite_fasta.fasta", true,
            DecoyType::None, false, ProteinDbLoader::UniprotAccessionRegex,
            ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotNameRegex,
            ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, un);

        std::string s = "P62805";
        Assert::AreEqual(s, prots.front()->getAccession() );
        Assert::AreEqual(s, prots2.front()->getAccession());
        
        s = "H4_HUMAN";
        Assert::AreEqual(s, prots.front()->getName());
        Assert::AreEqual(s, prots2.front()->getName());

        s = "Histone H4";
        Assert::AreEqual(s,  prots.front()->getFullName());
        Assert::AreEqual(s, prots2.front()->getFullName());

        s = "HIST1H4A";
        Assert::AreEqual(s, std::get<1>(prots.front()->getGeneNames().front()));
        Assert::AreEqual(s, std::get<1>(prots2.front()->getGeneNames().front()));

        s = "Homo sapiens";
        Assert::AreEqual(s, prots.front()->getOrganism());
        Assert::AreEqual(s, prots2.front()->getOrganism());
    }

    void TestProteomicsReadWrite::Test_read_write_read_fasta()
    {
        std::vector<std::string> a;
        std::string testdir=std::experimental::filesystem::current_path().string();
        
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta(testdir + "/test_ensembl.pep.all.fasta", true,
            DecoyType::None, false, ProteinDbLoader::EnsemblAccessionRegex,
            ProteinDbLoader::EnsemblFullNameRegex, ProteinDbLoader::EnsemblAccessionRegex,
            ProteinDbLoader::EnsemblGeneNameRegex, nullptr, a);
        ProteinDbWriter::WriteFastaDatabase(ok, testdir + "/rewrite_test_ensembl.pep.all.fasta", " ");
        std::vector<std::string> b;
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinFasta(testdir + "/rewrite_test_ensembl.pep.all.fasta",
            true, DecoyType::None, false, ProteinDbLoader::EnsemblAccessionRegex,
            ProteinDbLoader::EnsemblFullNameRegex, ProteinDbLoader::EnsemblAccessionRegex,
            ProteinDbLoader::EnsemblGeneNameRegex, nullptr, b);

        Assert::AreEqual(ok.size(), ok2.size());
#ifdef ORIG
        Assert::IsTrue(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
#endif
        for ( auto i=0; i< ok.size(); i++ ) {
            Assert::IsTrue(ok[i]->getBaseSequence() == ok2[i]->getBaseSequence());
        }
        
#ifdef ORIG
        Assert::IsTrue(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedBeginPosition == nullptr ||
                    prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));

        Assert::IsTrue(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedEndPosition == nullptr ||
                    prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));

#endif
        for ( auto p: ok ) {
            for ( auto prod: p->getProteolysisProducts() ) {
                Assert::IsTrue (!prod->getOneBasedBeginPosition().has_value() ||
                                prod->getOneBasedBeginPosition().value() > 0 &&
                                prod->getOneBasedBeginPosition().value() <= p->getLength());
                Assert::IsTrue (!prod->getOneBasedEndPosition().has_value() ||
                                prod->getOneBasedEndPosition().value() > 0 &&
                                prod->getOneBasedEndPosition().value() <= p->getLength());
            }
        }
        
        for ( auto p: ok2 ) {
            for ( auto prod: p->getProteolysisProducts() ) {
                Assert::IsTrue (!prod->getOneBasedBeginPosition().has_value() ||
                                prod->getOneBasedBeginPosition().value() > 0 &&
                                prod->getOneBasedBeginPosition().value() <= p->getLength());
                Assert::IsTrue (!prod->getOneBasedEndPosition().has_value() ||
                                prod->getOneBasedEndPosition().value() > 0 &&
                                prod->getOneBasedEndPosition().value() <= p->getLength());
            }
        }
    }

#ifdef LATER
    void TestProteomicsReadWrite::Test_read_xml_write_read_fasta()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);
        auto nice = std::vector<Modification*> {new Modification("fayk", "", "mt", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")};

        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);
        ProteinDbWriter::WriteFastaDatabase(ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml_test.fasta)"), "|");
        std::vector<string> b;
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml_test.fasta)"), true, DecoyType::None, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotNameRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, b);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getName() == ok2[i]->getName();
        }));
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getOrganism() == ok2[i]->getOrganism();
        }));
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getGeneNames().front()->Item2 == ok2[i]->getGeneNames().front().Item2;
        }));

        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedBeginPosition == nullptr || prod::OneBasedBeginPosition > 0 && prod::OneBasedBeginPosition <= p->Length;
            });
        }));
        Assert::True(ok2.All([&] (std::any p)
        {
            p::ProteolysisProducts::All([&] (std::any prod)
            {
                return prod->OneBasedEndPosition == nullptr || prod::OneBasedEndPosition > 0 && prod::OneBasedEndPosition <= p->Length;
            });
        }));
    }

    void TestProteomicsReadWrite::Test_accession_regex_weird()
    {
        FastaHeaderFieldRegex *bad = new FastaHeaderFieldRegex("", R"(/()/)", 0, 1);
        std::vector<string> a;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, bad, bad, bad, bad, bad, a);
        ProteinDbWriter::WriteFastaDatabase(ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_test_ensembl.pep.all.fasta)"), " ");
        std::vector<string> b;
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinFasta(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_test_ensembl.pep.all.fasta)"), true, DecoyType::None, false, bad, bad, bad, bad, bad, b);

        Assert::AreEqual("ENSP00000381386 pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok[0]->getAccession());
        Assert::AreEqual("ENSP00000381386 pep:known chromosome:GRCh37:22:24313554:24316773:-1 gene:ENSG00000099977 transcript:ENST00000398344 gene_biotype:protein_coding transcript_biotype:protein_coding", ok2[0]->getAccession());
        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));

        delete bad;
    }

    void TestProteomicsReadWrite::Test_write_with_custom_mods()
    {
        ModificationMotif m1;
        ModificationMotif::TryGetMotif("S", m1);
        ModificationMotif m2;
        ModificationMotif::TryGetMotif("T", m2);
        ModificationMotif motiff;
        ModificationMotif::TryGetMotif("X", motiff);

        auto nice = std::vector<Modification*>
        {
            new Modification("fayk", "", "mt", "", motiff, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), ""),
            new Modification("Phosphoserine", "", "mt", "", m1, "Anywhere.", nullptr, std::make_optional(80), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), ""),
            new Modification("Phosphothreonine", "", "mt", "", m2, "Anywhere.", nullptr, std::make_optional(80), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")
        };

        ModificationMotif motif;
        ModificationMotif::TryGetMotif("K", motif);
        Modification *m = new Modification("mod", "", "mt", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                DissociationType::AnyActivationType, {-1}
            }
        },
        std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> new_mods =
        {
            {
                "P53863", {std::tuple<int, Modification*>(2, m)}
            }
        };

        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));
        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);
        auto uniprotPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();

        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml2.xml)"), true, DecoyType::None, uniprotPtms.Concat(nice), false, std::vector<std::string>(), un);
        auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(new_mods, ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml2.xml)"));
        Assert::AreEqual(1, newModResEntries.size());
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml2.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);

        Assert::AreEqual(ok.size(), ok2.size());
        Assert::True(Enumerable::Range(0, ok.size()).All([&] (std::any i)
        {
            return ok[i]->getBaseSequence() == ok2[i]->getBaseSequence();
        }));
        Assert::AreEqual(2, ok[0]->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(3, ok2[0]->getOneBasedPossibleLocalizedModifications().size());

        delete m;
    }
#endif
    
    void TestProteomicsReadWrite::AnotherTest()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<Modification*> variableModifications;
        std::vector<Modification*> fixedModifications;

        // Generate data for files
        Protein *ParentProtein = new Protein("MPEPTIDEKANTHE", "accession1", "organism",
                                             std::vector<std::tuple<std::string, std::string>>(),
                                             std::unordered_map<int, std::vector<Modification*>>(),
                                             std::vector<ProteolysisProduct*>(),
                                             "name1", "fullname1" );

        std::vector<ProteolysisProduct*> pp = {new ProteolysisProduct(std::make_optional(4), std::make_optional(8), "chain")};
        Protein *proteinWithChain = new Protein("MAACNNNCAA", "accession3", "organism",
                                                std::vector<std::tuple<std::string, std::string>>(),
                                                std::unordered_map<int, std::vector<Modification*>>(),
                                                pp, "name2", "fullname2" );

        std::unordered_map<std::string, ModDbTuple_set> tempvar;
        std::vector<::Protein*> protvec = {ParentProtein, proteinWithChain}; 
        ProteinDbWriter::WriteXmlDatabase( tempvar,
                                          protvec,
                                          testdir + "/fdsfsd.xml" );

        delete proteinWithChain;
        delete ParentProtein;
    }

#ifdef ORIG
    void TestProteomicsReadWrite::TestEmptyProteins()
    {
        Protein *p1 = new Protein("SEQENCE", "p1");
        Assert::AreEqual("p1||", p1->getFullDescription());
        Protein *p2 = new Protein("SEQENCE", "p2", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "namep2", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");

        auto proteinListToWrite = std::vector<Protein*> {p1, p2};

        // Generate data for files
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification>>>(), proteinListToWrite, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(differentlyConstuctedProteins.xml)"));

        std::vector<std::string> modTypesToExclude;
        std::vector<Modification*> allKnownModifications;
        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(differentlyConstuctedProteins.xml)"), true, DecoyType::None, allKnownModifications, false, modTypesToExclude, un);
        Assert::AreEqual(p1->getAccession(), ok[0]->getAccession());
        Assert::AreEqual(p2->getAccession(), ok[1]->getAccession());
        Assert::AreEqual(p1->getName(), ok[0]->getName());
        Assert::AreEqual(p2->getName(), ok[1]->getName());

        delete p2;
        delete p1;
    }

    void TestProteomicsReadWrite::TestFullProteinReadWrite()
    {
        Modification *mod = new Modification("mod1", "", "modType1", "", nullptr, "", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("E", motif);
        Modification *mod2 = new Modification("mod2 on E", "", "modType1", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        ModificationMotif motif3;
        ModificationMotif::TryGetMotif("N", motif3);
        Modification *mod3 = new Modification("mod3 on N", "", "modType1", "", motif3, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::vector<std::tuple<std::string, std::string>> gene_names = {std::tuple<std::string, std::string>("a", "b")};
        std::unordered_map<int, std::vector<Modification*>> oneBasedModifications =
        {
            {
                3, {mod}
            },
            {
                4, {mod2}
            },
            {
                5, {mod3}
            }
        };
        std::vector<ProteolysisProduct*> proteolysisProducts = {new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "propeptide")};

        std::string name = "testName";

        std::string full_name = "testFullName";

        std::vector<DatabaseReference*> databaseReferences = {new DatabaseReference("type1", "id1", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("e1", "e2")})};

        std::vector<SequenceVariation*> sequenceVariations =
        {
            new SequenceVariation(3,"Q", "N", "replace Q by N"),
            new SequenceVariation(3,4,"QE", "NN", "replace QE by NN")
        };

        std::vector<DisulfideBond*> disulfideBonds =
        {
            new DisulfideBond(1, "ds1"),
            new DisulfideBond(2, 3, "ds2")
        };

        Protein *p1 = new Protein("SEQENCE", "a1", geneNames: gene_names, oneBasedModifications: oneBasedModifications, proteolysisProducts: proteolysisProducts, name: name, fullName: full_name, isDecoy: false, isContaminant: true, databaseReferences: databaseReferences, sequenceVariations: sequenceVariations, disulfideBonds: disulfideBonds, databaseFilePath: FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bnueiwhf.xml)"));

        // Generate data for files
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {p1}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bnueiwhf.xml)"));

        std::vector<std::string> modTypesToExclude;
        std::vector<Modification*> allKnownModifications;
        Dictionary<std::string, Modification*> unknownModifications;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(bnueiwhf.xml)"), true, DecoyType::None, allKnownModifications, true, modTypesToExclude, unknownModifications);
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
        Assert::AreEqual(p1->getOrganism(), ok[0]->getOrganism());
        Assert::AreEqual(p1->getDatabaseFilePath(), ok[0]->getDatabaseFilePath());
        Assert::AreEqual(1, p1->getOneBasedPossibleLocalizedModifications().Keys->Count);
        Assert::AreEqual(1, ok[0]->getOneBasedPossibleLocalizedModifications()->Keys->Count);
        Assert::AreEqual(p1->getOneBasedPossibleLocalizedModifications().Keys->First(), ok[0]->getOneBasedPossibleLocalizedModifications()->Keys->First());
        Assert::IsTrue(p1->getOneBasedPossibleLocalizedModifications()[5][0]->Equals(ok[0]->getOneBasedPossibleLocalizedModifications()[5][0]));

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

        delete p1;
        delete mod3;
        delete mod2;
        delete mod;
    }

    void TestProteomicsReadWrite::TestReadWriteSeqVars()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);
        auto nice = std::vector<Modification*> {new Modification("fayk", "", "mt", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")};

        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(xml.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_xml.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);

        Assert::AreEqual(ok[0]->getSequenceVariations().size()(), ok2[0]->getSequenceVariations().size()());
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedBeginPosition, ok2[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedEndPosition, ok2[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().Description, ok2[0]->getSequenceVariations().front().Description);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OriginalSequence, ok2[0]->getSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().VariantSequence, ok2[0]->getSequenceVariations().front().VariantSequence);
    }

    void TestProteomicsReadWrite::TestReadWriteSeqVars2()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);
        auto nice = std::vector<Modification*> {new Modification("fayk", "", "mt", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "")};

        Dictionary<std::string, Modification*> un;
        std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(seqvartests.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), ok, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_seqvartests.xml)"));
        std::vector<Protein*> ok2 = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(rewrite_seqvartests.xml)"), true, DecoyType::None, nice, false, std::vector<std::string>(), un);

        Assert::AreEqual(ok[0]->getSequenceVariations().size()(), ok2[0]->getSequenceVariations().size()());
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedBeginPosition, ok2[0]->getSequenceVariations().front().OneBasedBeginPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OneBasedEndPosition, ok2[0]->getSequenceVariations().front().OneBasedEndPosition);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().Description, ok2[0]->getSequenceVariations().front().Description);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().OriginalSequence, ok2[0]->getSequenceVariations().front().OriginalSequence);
        Assert::AreEqual(ok[0]->getSequenceVariations().front().VariantSequence, ok2[0]->getSequenceVariations().front().VariantSequence);
    }

    void TestProteomicsReadWrite::TestModificationGeneralToString()
    {
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", "CommonBiological.txt"), errors).ToList();
        std::vector<char> myChar = {'"'};

        std::string output = a.front().ToString();
        Assert::AreEqual(output.TrimStart(myChar)->TrimEnd(myChar), "ID   4-carboxyglutamate on E\r\nMT   Biological\r\nTG   E\r\nPP   Anywhere.\r\nCF   CO2\r\nMM   43.989829\r\n");
    }

    void TestProteomicsReadWrite::TestModificationGeneral_Equals()
    {
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", "CommonBiological.txt"), errors).ToList();
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", "CommonBiological.txt"), errors).ToList();

        Assert::IsTrue(a.front()->Equals(b.front()));
    }

    void TestProteomicsReadWrite::Test_CustumPrunedDatabaseWriteAndRead()
    {
        ModificationMotif K;
        ModificationMotif::TryGetMotif("K", K);
        ModificationMotif R;
        ModificationMotif::TryGetMotif("R", R);

        Modification *acOnK = new Modification("Acetyl", "", "testModType", "", K, "Anywhere.", nullptr, std::make_optional(42), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        Modification *meOnK = new Modification("Methyl", "", "testModType", "", K, "Anywhere.", nullptr, std::make_optional(14), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        Modification *meOnR = new Modification("Methyl", "", "testModType", "", R, "Anywhere.", nullptr, std::make_optional(14), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> obm;
        obm.emplace(1, std::vector<Modification*> {acOnK});
        obm.emplace(2, std::vector<Modification*> {meOnK});
        obm.emplace(3, std::vector<Modification*> {meOnR});

        Protein *p = new Protein("KKR", "accession", "", std::vector<std::tuple<std::string, std::string>>(), obm, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "");
        std::vector<Protein*> pList = {p};

        std::string outputFileName = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", R"(redundant.xml)");
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), pList, outputFileName);

        Dictionary<std::string, Modification*> proteinXmlModList;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(outputFileName, true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), proteinXmlModList);

        Assert::AreEqual(3, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size()());

        delete p;
        delete meOnR;
        delete meOnK;
        delete acOnK;
    }

#endif
}
