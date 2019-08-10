#include "TestProteinProperties.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/DatabaseReference.h"
#include "../Proteomics/Protein/SpliceSite.h"
#include "../Proteomics/Protein/DisulfideBond.h"
#include "../Proteomics/Protein/ProteolysisProduct.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "Assert.h"

using namespace Proteomics;


int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);

    std::cout << ++i << ". TestHashAndEqualsProtein" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsProtein();

    std::cout << ++i << ". TestHashAndEqualsSequenceVariation" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsSequenceVariation();

    std::cout << ++i << ". TestHashAndEqualsDbRef" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsDbRef();

    std::cout << ++i << ". TestHashAndEqualsSpliceSite" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsSpliceSite();

    std::cout << ++i << ". TestHashAndEqualsDisulfide" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsDisulfide();

    std::cout << ++i << ". TestHashAndEqualsProteolysis" << std::endl;        
    Test::TestProteinProperties::TestHashAndEqualsProteolysis();

    std::cout << ++i << ". CompareProteinProperties" << std::endl;        
    Test::TestProteinProperties::CompareProteinProperties();

    return 0;
}

namespace Test
{

    void TestProteinProperties::TestHashAndEqualsProtein()
    {
        Protein *p1 = new Protein("MSEQ", "accession");
        Protein *p11 = new Protein("MSEQ", "accession");
        Assert::AreNotEqual(p1, p11); // default object hash and equals are used

	delete p11;
	delete p1;
    }

    void TestProteinProperties::TestHashAndEqualsSequenceVariation()
    {
        SequenceVariation *sv1 = new SequenceVariation(1, "MAA", "MAA", "description", {new Modification("mod")}::ToList()
        }
        });
        SequenceVariation *sv2 = new SequenceVariation(1, "MAA", "MAA", "description", {new Modification("mod")}::ToList()
        }
        });
        SequenceVariation *sv22 = new SequenceVariation(1, "MAA", "MAA", "description", {new Modification("mod")}::ToList()
        }
        });
        SequenceVariation *sv222 = new SequenceVariation(1, "MAA", "MAA", "description", {new Modification("another")}::ToList()
        }
        });
        SequenceVariation *sv3 = new SequenceVariation(1, "MAA", "MAA", "description", std::unordered_map<int, std::vector<Modification>>());
        SequenceVariation *sv4 = new SequenceVariation(1, "MAA", "MAA", nullptr, {new Modification("mod")}::ToList()
        }
        });
        SequenceVariation *sv5 = new SequenceVariation(1, nullptr, nullptr, "description", {new Modification("mod")}::ToList()
        }
        });
        SequenceVariation *sv6 = new SequenceVariation(2, "MAA", "MAA", "description", {new Modification("mod")}::ToList()
        }
        });
        Assert::AreEqual(sv1, sv2);
        Assert::AreNotEqual(sv1, sv22);
        Assert::AreNotEqual(sv1, sv222);
        Assert::AreNotEqual(sv1, sv3);
        Assert::AreNotEqual(sv1, sv4);
        Assert::AreNotEqual(sv1, sv5);
        Assert::AreNotEqual(sv1, sv6);

        delete sv6;
        delete sv5;
        delete sv4;
        delete sv3;
        delete sv222;
        delete sv22;
        delete sv2;
        delete sv1;
    }

    void TestProteinProperties::TestHashAndEqualsDbRef()
    {
        DatabaseReference *db1 = new DatabaseReference("type", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("1", "2")});
        DatabaseReference *db11 = new DatabaseReference("type", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("1", "2")});
        DatabaseReference *db2 = new DatabaseReference("type", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("1", "3")});
        DatabaseReference *db3 = new DatabaseReference("type", "id", std::vector<std::tuple<std::string, std::string>>());
        DatabaseReference *db4 = new DatabaseReference("type", "", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("1", "2")});
        DatabaseReference *db5 = new DatabaseReference("", "id", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("1", "2")});
        Assert::AreEqual(db1, db11);
        Assert::AreNotEqual(db1, db2);
        Assert::AreNotEqual(db1, db3);
        Assert::AreNotEqual(db1, db4);
        Assert::AreNotEqual(db1, db5);

	delete db5;
	delete db4;
	delete db3;
	delete db2;
	delete db11;
	delete db1;
    }

    void TestProteinProperties::TestHashAndEqualsSpliceSite()
    {
        SpliceSite *ss1 = new SpliceSite(1, 2, "description");
        SpliceSite *ss11 = new SpliceSite(1, 2, "description");
        SpliceSite *ss2 = new SpliceSite(1, 2, "");
        SpliceSite *ss3 = new SpliceSite(1, "description");
        SpliceSite *ss4 = new SpliceSite(2, "description");
        Assert::AreEqual(ss1, ss11);
        Assert::AreNotEqual(ss1, ss2);
        Assert::AreNotEqual(ss1, ss3);
        Assert::AreNotEqual(ss1, ss4);

	delete ss4;
	delete ss3;
	delete ss2;
	delete ss11;
	delete ss1;
    }

    void TestProteinProperties::TestHashAndEqualsDisulfide()
    {
        DisulfideBond *bond7 = new DisulfideBond(1, 2, "description");
        DisulfideBond *bond007 = new DisulfideBond(1, 2, "description");
        DisulfideBond *bond8 = new DisulfideBond(1, 2, "");
        DisulfideBond *bond9 = new DisulfideBond(1, "description");
        DisulfideBond *bond17 = new DisulfideBond(2, "description");
        Assert::AreEqual(bond7, bond007);
        Assert::AreNotEqual(bond007, bond8);
        Assert::AreNotEqual(bond007, bond9);
        Assert::AreNotEqual(bond007, bond17);

	delete bond17;
	delete bond9;
	delete bond8;
	delete bond007;
	delete bond7;
    }

    void TestProteinProperties::TestHashAndEqualsProteolysis()
    {
        ProteolysisProduct *pp1 = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "type");
        ProteolysisProduct *pp11 = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "type");
        ProteolysisProduct *pp2 = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "");
        ProteolysisProduct *pp3 = new ProteolysisProduct(std::make_optional(1), std::nullopt, "type");
        ProteolysisProduct *pp4 = new ProteolysisProduct(std::nullopt, std::make_optional(2), "type");
        ProteolysisProduct *pp5 = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "type");
        ProteolysisProduct *pp6 = new ProteolysisProduct(std::make_optional(2), std::make_optional(2), "type");
        Assert::AreEqual(pp1, pp11);
        Assert::AreNotEqual(pp1, pp2);
        Assert::AreNotEqual(pp1, pp3);
        Assert::AreNotEqual(pp1, pp4);
        Assert::AreNotEqual(pp1, pp5);
        Assert::AreNotEqual(pp1, pp6);

	delete pp6;
	delete pp5;
	delete pp4;
	delete pp3;
	delete pp2;
	delete pp11;
	delete pp1;
    }

    void TestProteinProperties::CompareProteinProperties()
    {
        DatabaseReference *d = new DatabaseReference("asdf", "asdfg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("bbb", "ccc")});
        DatabaseReference *dd = new DatabaseReference("asdf", "asdfg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("bbb", "ccc")});
        DatabaseReference *de = new DatabaseReference("asdf", "asdefg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("bbb", "ccc")});
        DatabaseReference *df = new DatabaseReference("asddf", "asdfg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("bbb", "ccc")});
        DatabaseReference *dg = new DatabaseReference("asdf", "asdfg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("babb", "ccc")});
        DatabaseReference *dh = new DatabaseReference("asdf", "asdfg", std::vector<std::tuple<std::string, std::string>> {std::tuple<std::string, std::string>("bbb", "cccf")});
        Assert::True(dd->Equals(d));
        Assert::False(de->Equals(d));
        Assert::False(df->Equals(d));
        Assert::False(dg->Equals(d));
        Assert::False(dh->Equals(d));
        Assert::AreEqual(5, {d, dd, de, df, dg, dh}->Count);

        SequenceVariation *s = new SequenceVariation(1, "hello", "hey", "hi");
        SequenceVariation *sv = new SequenceVariation(1, "hello", "hey", "hi");
        SequenceVariation *sss = new SequenceVariation(2, "hallo", "hey", "hi");
        SequenceVariation *ssss = new SequenceVariation(1, "hello", "heyy", "hi");
        SequenceVariation *sssss = new SequenceVariation(1, "hello", "hey", "hii");
        Assert::True(s->Equals(sv));
        Assert::False(s->Equals(sss));
        Assert::False(s->Equals(ssss));
        Assert::False(s->Equals(sssss));
        Assert::AreEqual(4, {s, sv, sss, ssss, sssss}->Count);

        DisulfideBond *b = new DisulfideBond(1, "hello");
        DisulfideBond *bb = new DisulfideBond(1, "hello");
        DisulfideBond *bbb = new DisulfideBond(1, 2, "hello");
        DisulfideBond *bbbb = new DisulfideBond(1, 2, "hello");
        DisulfideBond *ba = new DisulfideBond(1, 3, "hello");
        DisulfideBond *baa = new DisulfideBond(2, 2, "hello");
        DisulfideBond *baaa = new DisulfideBond(1, 2, "hallo");
        Assert::AreEqual(b, bb);
        Assert::AreEqual(bbb, bbbb);
        Assert::AreNotEqual(b, bbb);
        Assert::AreNotEqual(ba, bbb);
        Assert::AreNotEqual(baa, bbb);
        Assert::AreNotEqual(baaa, bbb);
        Assert::AreEqual(5, {b, bb, bbb, bbbb, ba, baa, baaa}->Count);

        ProteolysisProduct *pp = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hello");
        ProteolysisProduct *paaa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hello");
        ProteolysisProduct *p = new ProteolysisProduct(std::nullopt, std::nullopt, "hello");
        ProteolysisProduct *ppp = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "hello");
        ProteolysisProduct *pa = new ProteolysisProduct(std::make_optional(2), std::make_optional(1), "hello");
        ProteolysisProduct *paa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hallo");
        Assert::AreEqual(pp, paaa);
        Assert::AreNotEqual(p, pp);
        Assert::AreNotEqual(pp, ppp);
        Assert::AreNotEqual(pp, pa);
        Assert::AreNotEqual(pp, paa);
        Assert::AreEqual(5, {p, pp, ppp, pa, paa, paaa}->Count);

	delete paa;
	delete pa;
	delete ppp;
	delete p;
	delete paaa;
	delete pp;
	delete baaa;
	delete baa;
	delete ba;
	delete bbbb;
	delete bbb;
	delete bb;
	delete b;
	delete sssss;
	delete ssss;
	delete sss;
	delete sv;
	delete s;
	delete dh;
	delete dq;
	delete df;
	delete de;
	delete dd;
	delete d;
    }
}
