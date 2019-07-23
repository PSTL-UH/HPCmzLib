#include "TestProteinProperties.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/DatabaseReference.h"
#include "../Proteomics/Protein/SpliceSite.h"
#include "../Proteomics/Protein/DisulfideBond.h"
#include "../Proteomics/Protein/ProteolysisProduct.h"

using namespace NUnit::Framework;
using namespace Proteomics;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestProteinProperties::privateStopwatch;

    Stopwatch *TestProteinProperties::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestProteinProperties::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestProteinProperties::Setup()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestProteinProperties::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestProteinProperties::TestHashAndEqualsProtein()
    {
        Protein *p1 = new Protein("MSEQ", "accession");
        Protein *p11 = new Protein("MSEQ", "accession");
        Assert::AreNotEqual(p1, p11); // default object hash and equals are used

//C# TO C++ CONVERTER TODO TASK: A 'delete p11' statement was not added since p11 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p1' statement was not added since p1 was passed to a method or constructor. Handle memory management manually.
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

//C# TO C++ CONVERTER TODO TASK: A 'delete sv6' statement was not added since sv6 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv5' statement was not added since sv5 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv4' statement was not added since sv4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv3' statement was not added since sv3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv222' statement was not added since sv222 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv22' statement was not added since sv22 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv2' statement was not added since sv2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete sv1' statement was not added since sv1 was passed to a method or constructor. Handle memory management manually.
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

//C# TO C++ CONVERTER TODO TASK: A 'delete db5' statement was not added since db5 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete db4' statement was not added since db4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete db3' statement was not added since db3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete db2' statement was not added since db2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete db11' statement was not added since db11 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete db1' statement was not added since db1 was passed to a method or constructor. Handle memory management manually.
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

//C# TO C++ CONVERTER TODO TASK: A 'delete ss4' statement was not added since ss4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ss3' statement was not added since ss3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ss2' statement was not added since ss2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ss11' statement was not added since ss11 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete ss1' statement was not added since ss1 was passed to a method or constructor. Handle memory management manually.
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

//C# TO C++ CONVERTER TODO TASK: A 'delete bond17' statement was not added since bond17 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bond9' statement was not added since bond9 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bond8' statement was not added since bond8 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bond007' statement was not added since bond007 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete bond7' statement was not added since bond7 was passed to a method or constructor. Handle memory management manually.
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

//C# TO C++ CONVERTER TODO TASK: A 'delete pp6' statement was not added since pp6 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp5' statement was not added since pp5 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp4' statement was not added since pp4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp3' statement was not added since pp3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp2' statement was not added since pp2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp11' statement was not added since pp11 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pp1' statement was not added since pp1 was passed to a method or constructor. Handle memory management manually.
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
}
