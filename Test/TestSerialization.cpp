#include <bits/stdc++.h>

#include "TestSerialization.h"
#include "MzLibAssert.h"
#include "Sort.h"

#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "../Proteomics/Proteomics.h"

using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;


int main () {
	int i=0;
	std::cout << i << ". PeriodicTableLoader" << std::endl;    
	const std::string elfile="elements.dat";
	const std::string &elr=elfile;
	Chemistry::PeriodicTable::Load (elr);
	//	UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

	std::cout << ++i << ". SerializePeptideWithSetModifications\n";
	Test::TestSerialization::SerializePeptideWithSetModifications();

	std::cout << ++i << ". SerializeMatchedFragmentIon\n";
	Test::TestSerialization::SerializeMatchedFragmentIon();
        
	return 0;
}

namespace Test
{
    void TestSerialization::SerializePeptideWithSetModifications()
    {
        
        Protein *protein = new Protein("MQLLRCFSIFSVIASVLAQELTTICEQIPSPTLESTPYSLSTTTILANGKAMQGVFEYYKSVTFVSNCGSHPSTTSKGSPINTQYVF", "P32781");
        DigestionParams *nParams = new DigestionParams("trypsin", 2, 7, 50, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                       CleavageSpecificity::Semi, FragmentationTerminus::N);
        std::vector<Modification*> vm1, vm2;
        PeptideWithSetModifications* pep1=nullptr;
        std::vector<PeptideWithSetModifications*> peps1 = protein->Digest(nParams, vm1, vm2);
        for ( auto p: peps1 ) {
            if ( p != nullptr ) {
                pep1 = p;
                break;
            }
        }
        
        if ( pep1 == nullptr ) {
            std::cout << "No matching peptide found, aborting " << std::endl;
            exit(-1);
        }
        std::string filename1 = "pepout.txt";
        PeptideWithSetModifications::Serialize ( filename1,  pep1 );

        PeptideWithSetModifications *npep1=nullptr;            
        std::unordered_map<std::string, Modification*> umsM1;
        std::unordered_map<std::string, Protein*> umsP;
        umsP[protein->getAccession()] =  protein;
        PeptideWithSetModifications::Deserialize (filename1, npep1 );
        npep1->SetNonSerializedPeptideInfo( umsM1, umsP);
        
        if (pep1 != nullptr || npep1 != nullptr) {
            Assert::IsTrue(pep1->getFullSequence() == npep1->getFullSequence());
            Assert::IsTrue(pep1->getDigestionParams()->Equals(npep1->getDigestionParams()));
            Assert::IsTrue(pep1->Equals(npep1));
            //Assert::IsTrue(pep1->GetHashCode() != npep1->GetHashCode());
        } 

        
        std::vector<std::vector<Modification*>> initTempsForModificationPtr;
        unsigned short counterFor_initTempsForModificationPtr = 0;
        
        Protein *fiveCleavages = new Protein("MAAKCCKDDKEEKFFKGG", "fiveCleavages"); //protein with 5 K's
        umsP[fiveCleavages->getAccession()] = fiveCleavages;
        std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesInducingClevage =
            {std::tuple<std::string, FragmentationTerminus>("K",FragmentationTerminus::C)};
        std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesPreventingClevage;
        
        //make two identical proteases, but one is fully specific and one is semi specific
        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("K|");
        Protease *trypsinForTestNonAndSemiSpecificDigests = new Protease("trypsinForTestNonAndSemiSpecificDigests",
                                                                         CleavageSpecificity::Full, "asdf", "asdf", motifList);
        Protease *semiTrypsinForTestNonAndSemiSpecificDigests = new Protease("semitrypsinForTestNonAndSemiSpecificDigests",
                                                                             CleavageSpecificity::Semi, "asdf", "asdf", motifList);
        
        //add these made up proteases to the dictionary
        ProteaseDictionary::insert(trypsinForTestNonAndSemiSpecificDigests->getName(),
                                   trypsinForTestNonAndSemiSpecificDigests);
        ProteaseDictionary::insert(semiTrypsinForTestNonAndSemiSpecificDigests->getName(),
                                   semiTrypsinForTestNonAndSemiSpecificDigests);
        
        //Digest with the full
        DigestionParams *fullyDigestParams = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2);
        initTempsForModificationPtr.push_back(std::vector<Modification*>());
        initTempsForModificationPtr.push_back(std::vector<Modification*>());
        std::vector<PeptideWithSetModifications*> fiveCleavageProductsTrypsin = fiveCleavages->Digest(
            fullyDigestParams,
            initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
            initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
        
        std::string filename2 = "pepout2.txt";
        PeptideWithSetModifications::Serialize (filename2, fiveCleavageProductsTrypsin);

        std::vector<PeptideWithSetModifications *> npep2;
        PeptideWithSetModifications::Deserialize (filename2, npep2 );

        Assert::AreEqual (fiveCleavageProductsTrypsin.size(), npep2.size() );
        for ( auto n : npep2 ) {
            n->SetNonSerializedPeptideInfo( umsM1, umsP);
        }

        for ( auto i = 0; i < npep2.size(); i++ ) {
            Assert::IsTrue(fiveCleavageProductsTrypsin[i]->getFullSequence() == npep2[i]->getFullSequence());
            Assert::IsTrue(fiveCleavageProductsTrypsin[i]->Equals(npep2[i]));
        }

        std::filesystem::remove ( filename1);
        std::filesystem::remove ( filename2);
        
        delete protein;
        delete fiveCleavages;
        delete nParams;
        delete fullyDigestParams;        
    }

    void TestSerialization::SerializeMatchedFragmentIon()
    {
        auto  tempVar = new NeutralTerminusFragment (FragmentationTerminus::N, 1, 1, 1);
        Product *P = new Product(ProductType::b, tempVar, 0);
        MatchedFragmentIon *m = new MatchedFragmentIon(P, 1, 1, 1);
        char buf[512];
        size_t buf_len = 512;
        int ret = MatchedFragmentIon::Pack(buf, &buf_len, m);
        if ( ret == -1 ) {
            std::cout<< "Buffer too small, increase to " << buf_len << " bytes \n";
        }

        MatchedFragmentIon *n;
        MatchedFragmentIon::Unpack(buf, buf_len, &n);

        Assert::IsTrue(m->Equals(n));

        delete m;
        delete P;

    }
    
}
