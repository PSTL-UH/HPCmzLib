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
                //Edgar: not sure what they try to test here, why the two objects should not be equal.
		Assert::IsFalse(p1->Equals(p11)); // default object hash and equals are used

                Assert::AreEqual(p1->GetHashCode(), p11->GetHashCode() );
		delete p11;
		delete p1;
	}

	void TestProteinProperties::TestHashAndEqualsSequenceVariation()
	{

            auto mod1 = new Modification ("mod");
            std::vector<Modification *> svmod1 = {mod1};
            auto tmpmap1 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap1->emplace(2, svmod1);
            SequenceVariation *sv1 = new SequenceVariation(1, "MAA", "MAA", "description", *tmpmap1);

            auto mod2 = new Modification ("mod");
            std::vector<Modification *> svmod2 = {mod2};
            auto tmpmap2 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap2->emplace(2, svmod2);
            SequenceVariation *sv2 = new SequenceVariation(1, "MAA", "MAA", "description", *tmpmap2);
            
            auto mod22 = new Modification ("mod");
            std::vector<Modification *> svmod22 = {mod22};
            auto tmpmap22 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap22->emplace(3, svmod22);
            SequenceVariation *sv22 = new SequenceVariation(1, "MAA", "MAA", "description", *tmpmap22);
            
            auto mod222 = new Modification ("another");
            std::vector<Modification *> svmod222 = {mod222};
            auto tmpmap222 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap222->emplace(2, svmod222);
            SequenceVariation *sv222 = new SequenceVariation(1, "MAA", "MAA", "description", *tmpmap222);

            auto tmpmap3 = new std::unordered_map<int, std::vector<Modification *>>;
            SequenceVariation *sv3 = new SequenceVariation(1, "MAA", "MAA", "description", *tmpmap3);

            auto mod4 = new Modification ("mod");
            std::vector<Modification *> svmod4 = {mod4};
            auto tmpmap4 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap4->emplace(2, svmod4);
            SequenceVariation *sv4 = new SequenceVariation(1, "MAA", "MAA", "", *tmpmap4);
            
            auto mod5 = new Modification ("mod");
            std::vector<Modification *> svmod5 = {mod5};
            auto tmpmap5 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap5->emplace(2, svmod5);
            SequenceVariation *sv5 = new SequenceVariation(1, "", "", "description", *tmpmap5);
            
            auto mod6 = new Modification ("mod");
            std::vector<Modification *> svmod6 = {mod6};
            auto tmpmap6 = new std::unordered_map<int, std::vector<Modification *>>;
            tmpmap6->emplace(2, svmod6);
            SequenceVariation *sv6 = new SequenceVariation(2, "MAA", "MAA", "description", *tmpmap6);
            
            Assert::IsTrue(sv1->Equals( sv2));
            Assert::IsFalse(sv1->Equals( sv22));
            Assert::IsFalse(sv1->Equals( sv222));
            Assert::IsFalse(sv1->Equals( sv3));
            Assert::IsFalse(sv1->Equals( sv4));
            Assert::IsFalse(sv1->Equals( sv5));
            Assert::IsFalse(sv1->Equals( sv6));
            
            
            delete sv6;
            delete sv5;
            delete sv4;
            delete sv3;
            delete sv222;
            delete sv22;
            delete sv2;
            delete sv1;

            delete mod1;
            delete mod2;
            delete mod22;
            delete mod222;
            delete mod4;
            delete mod5;
            delete mod6;
                        
            delete tmpmap1;
            delete tmpmap2;
            delete tmpmap22;
            delete tmpmap222;
            delete tmpmap3;
            delete tmpmap4;
            delete tmpmap5;
            delete tmpmap6;
            
        }
    
	void TestProteinProperties::TestHashAndEqualsDbRef()
	{
		std::vector<std::tuple<std::string, std::string>> tempdb1;
		tempdb1.push_back(std::tuple<std::string, std::string>("1", "2"));
		DatabaseReference *db1 = new DatabaseReference("type", "id", tempdb1);

		std::vector<std::tuple<std::string, std::string>> tempdb11;
		tempdb11.push_back(std::tuple<std::string, std::string>("1", "2"));
		DatabaseReference *db11 = new DatabaseReference("type", "id", tempdb11);

                std::vector<std::tuple<std::string, std::string>> tempdb2;
		tempdb2.push_back(std::tuple<std::string, std::string>("1", "3"));
		DatabaseReference *db2 = new DatabaseReference("type", "id",  tempdb2);

                std::vector<std::tuple<std::string, std::string>> tempdb3;
		DatabaseReference *db3 = new DatabaseReference("type", "id", tempdb3);

		std::vector<std::tuple<std::string, std::string>> tempdb4;
                tempdb4.push_back(std::tuple<std::string, std::string>("1", "2"));
		DatabaseReference *db4 = new DatabaseReference("type", "",  tempdb4);

                std::vector<std::tuple<std::string, std::string>> tempdb5;
                tempdb5.push_back(std::tuple<std::string, std::string>("1", "2"));
		DatabaseReference *db5 = new DatabaseReference("", "id", tempdb5);

		Assert::IsTrue(db1->Equals( db11));
		Assert::IsFalse(db1->Equals( db2));
		Assert::IsFalse(db1->Equals( db3));
                Assert::IsFalse(db1->Equals( db4));
                Assert::IsFalse(db1->Equals( db5));

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
		Assert::IsTrue(ss1->Equals( ss11));
		Assert::IsFalse(ss1->Equals( ss2));
		Assert::IsFalse(ss1->Equals( ss3));
		Assert::IsFalse(ss1->Equals( ss4));

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
		Assert::IsTrue(bond7->Equals( bond007));
		Assert::IsFalse(bond007->Equals( bond8));
		Assert::IsFalse(bond007->Equals( bond9));
		Assert::IsFalse(bond007->Equals( bond17));

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
		Assert::IsTrue(pp1->Equals( pp11));
		Assert::IsFalse(pp1->Equals( pp2));
		Assert::IsFalse(pp1->Equals( pp3));
		Assert::IsFalse(pp1->Equals( pp4));
		Assert::IsFalse(pp1->Equals( pp5));
		Assert::IsFalse(pp1->Equals( pp6));

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
		std::vector<std::tuple<std::string, std::string>> tempd;
		tempd.push_back(std::tuple<std::string, std::string>("bbb", "ccc"));
		DatabaseReference *d = new DatabaseReference("asdf", "asdfg", tempd);

		std::vector<std::tuple<std::string, std::string>> tempdd;
		tempdd.push_back(std::tuple<std::string, std::string>("bbb", "ccc"));
		DatabaseReference *dd = new DatabaseReference("asdf", "asdfg", tempdd);

                std::vector<std::tuple<std::string, std::string>> tempde;
		tempde.push_back(std::tuple<std::string, std::string>("bbb", "ccc"));
		DatabaseReference *de = new DatabaseReference("asdf", "asdefg",  tempde);

                std::vector<std::tuple<std::string, std::string>> tempdf;
		tempdf.push_back(std::tuple<std::string, std::string>("bbb", "ccc"));
		DatabaseReference *df = new DatabaseReference("asddf", "asdfg", tempdf);

                std::vector<std::tuple<std::string, std::string>> tempdg;
		tempdg.push_back(std::tuple<std::string, std::string>("babb", "ccc"));
		DatabaseReference *dg = new DatabaseReference("asdf", "asdfg", tempdg);

                std::vector<std::tuple<std::string, std::string>> tempdh;
		tempdh.push_back(std::tuple<std::string, std::string>("bbb", "cccf"));
		DatabaseReference *dh = new DatabaseReference("asdf", "asdfg", tempdh);

		Assert::IsTrue(dd->Equals(d));
		Assert::IsFalse(de->Equals(d));
		Assert::IsFalse(df->Equals(d));
		Assert::IsFalse(dg->Equals(d));
		Assert::IsFalse(dh->Equals(d));
//{d, dd, de, df, dg, dh}->Count
//Think this line is supposed to return 6
//Inserting 6 into below IsTrue
//              Assert::IsTrue(5, 6);
//Edgar: what they try to test here is that if you combine all of those databasereferences into a Hash (i.e. unordered_map), only 5 of the 6 should be visible, since one is a duplicate of another, and an unordered_map enforces that every key is unique.
// Not doing that right now.
                
		std::vector<std::unordered_map<int, std::vector<Modification*>>> tempModsForSequenceVariation;
		for (int i = 0; i < 5; i++) {
			tempModsForSequenceVariation.push_back(std::unordered_map<int, std::vector<Modification*>>());
		}
		SequenceVariation *s = new SequenceVariation(1, "hello", "hey", "hi", tempModsForSequenceVariation[0]);
		SequenceVariation *sv = new SequenceVariation(1, "hello", "hey", "hi", tempModsForSequenceVariation[1]);
		SequenceVariation *sss = new SequenceVariation(2, "hallo", "hey", "hi", tempModsForSequenceVariation[2]);
		SequenceVariation *ssss = new SequenceVariation(1, "hello", "heyy", "hi", tempModsForSequenceVariation[3]);
		SequenceVariation *sssss = new SequenceVariation(1, "hello", "hey", "hii", tempModsForSequenceVariation[4]);
		Assert::IsTrue(s->Equals(sv));
		Assert::IsFalse(s->Equals(sss));
		Assert::IsFalse(s->Equals(ssss));
		Assert::IsFalse(s->Equals(sssss));
//{s, sv, sss, ssss, sssss}->Count
//Think this line is supposed to return 5
//Inserting 5 into below IsTrue
//		Assert::AreEqual(4, 5);

		DisulfideBond *b = new DisulfideBond(1, "hello");
		DisulfideBond *bb = new DisulfideBond(1, "hello");
		DisulfideBond *bbb = new DisulfideBond(1, 2, "hello");
		DisulfideBond *bbbb = new DisulfideBond(1, 2, "hello");
		DisulfideBond *ba = new DisulfideBond(1, 3, "hello");
		DisulfideBond *baa = new DisulfideBond(2, 2, "hello");
		DisulfideBond *baaa = new DisulfideBond(1, 2, "hallo");
		Assert::IsTrue(b->Equals( bb));
		Assert::IsTrue(bbb->Equals( bbbb));
                Assert::IsFalse(b->Equals( bbb));
                Assert::IsFalse(ba->Equals( bbb));
		Assert::IsFalse(baa->Equals( bbb));
                Assert::IsFalse(baaa->Equals( bbb));
//{b, bb, bbb, bbbb, ba, baa, baaa}->Count
//Think this line is supposed to return 7
//inserting 7 into below AreEqual
//		Assert::AreEqual(5, 7);

		ProteolysisProduct *pp = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hello");
		ProteolysisProduct *paaa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hello");
		ProteolysisProduct *p = new ProteolysisProduct(std::nullopt, std::nullopt, "hello");
		ProteolysisProduct *ppp = new ProteolysisProduct(std::make_optional(1), std::make_optional(2), "hello");
		ProteolysisProduct *pa = new ProteolysisProduct(std::make_optional(2), std::make_optional(1), "hello");
		ProteolysisProduct *paa = new ProteolysisProduct(std::make_optional(1), std::make_optional(1), "hallo");
		Assert::IsTrue(pp->Equals( paaa));
		Assert::IsFalse(p->Equals( pp));
		Assert::IsFalse(pp->Equals( ppp));
		Assert::IsFalse(pp->Equals( pa));
		Assert::IsFalse(pp->Equals( paa));
//{p, pp, ppp, pa, paa, paaa}->Count
//Think this line is supposed to return 6
//Inserting 6 into below AreEqual
//		Assert::AreEqual(5, 6);

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
		delete dg;
		delete df;
		delete de;
		delete dd;
		delete d;
	}
}
