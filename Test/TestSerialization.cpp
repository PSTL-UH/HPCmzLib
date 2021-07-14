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

#ifdef USE_MPI
#include <unistd.h>
#include "mpi.h"
#endif


static void print(int index, std::string message )
{
#ifdef USE_MPI
    int rank;
    MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
    if ( rank == 0) {
        std::cout << index << message << std::endl;
    }
#else
    std::cout << index << message << std::endl;
#endif
}

int main ( int argc, char **argv) {
	int i=0;

#ifdef USE_MPI
        MPI_Init ( &argc, &argv);
        int rank, size;
        MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
        MPI_Comm_size ( MPI_COMM_WORLD, &size );

        if ( size != 2 ) {
            if ( rank == 0 ) {
                std::cout << "TestSerialization: test only works for 2 processes right now\n";
            }
            MPI_Abort ( MPI_COMM_WORLD, 1);
        }

        if ( argc > 1 ) sleep ( 20);
#endif

        print(i, ". PeriodicTableLoader");
	const std::string elfile="elements.dat";
	const std::string &elr=elfile;
	Chemistry::PeriodicTable::Load (elr);
	//UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

	print(++i, ". SerializePeptideWithSetModifications1");
	Test::TestSerialization::SerializePeptideWithSetModifications1();

	print(++i, ". SerializePeptideWithSetModifications2");
	Test::TestSerialization::SerializePeptideWithSetModifications2();

#ifdef USE_MPI
	print(++i, ". SerializePeptideWithSetModifications_MPI");
	Test::TestSerialization::SerializePeptideWithSetModifications_MPI();
#endif
        
	print(++i, ". SerializeMatchedFragmentIon");
	Test::TestSerialization::SerializeMatchedFragmentIon();

#ifdef USE_MPI
	print(++i, ". SerializeMatchedFragmentIon_MPI");
	Test::TestSerialization::SerializeMatchedFragmentIon_MPI();

        MPI_Finalize();
#endif
        
	return 0;
}

namespace Test
{
    void TestSerialization::SerializePeptideWithSetModifications1()
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
        }         

        std::filesystem::remove ( filename1);
        
        delete protein;
        delete nParams;
    }

    void TestSerialization::SerializePeptideWithSetModifications2()
    {
        std::vector<std::vector<Modification*>> initTempsForModificationPtr;
        unsigned short counterFor_initTempsForModificationPtr = 0;
        
        Protein *fiveCleavages = new Protein("MAAKCCKDDKEEKFFKGG", "fiveCleavages"); //protein with 5 K's
        std::unordered_map<std::string, Modification*> umsM1;
        std::unordered_map<std::string, Protein*> umsP;        
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

        std::filesystem::remove ( filename2);
        delete fiveCleavages;
        delete fullyDigestParams;                
    }    

#ifdef USE_MPI
    void TestSerialization::SerializePeptideWithSetModifications_MPI()
    {
        int rank;
        MPI_Comm_rank ( MPI_COMM_WORLD, &rank );

        std::vector<std::vector<Modification*>> initTempsForModificationPtr;
        unsigned short counterFor_initTempsForModificationPtr = 0;
        
        Protein *fiveCleavages = new Protein("MAAKCCKDDKEEKFFKGG", "fiveCleavages"); //protein with 5 K's
        std::unordered_map<std::string, Modification*> umsM1;
        std::unordered_map<std::string, Protein*> umsP;        
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

        size_t buf_len = 256 * fiveCleavageProductsTrypsin.size();
        char *buf = (char *) malloc ( buf_len);

        int ret = PeptideWithSetModifications::Pack (buf, buf_len, fiveCleavageProductsTrypsin);
        if ( rank == 0 ) {
            MPI_Send ( buf, buf_len, MPI_BYTE, 1, 10, MPI_COMM_WORLD);
        }
        else if ( rank == 1 ) {
            MPI_Status status;
            buf_len = 256 * fiveCleavageProductsTrypsin.size();
            char *recv_buf = (char *) malloc ( buf_len);
            
            MPI_Recv (recv_buf, buf_len, MPI_BYTE, 0, 10, MPI_COMM_WORLD, &status );
            int actual_len;
            MPI_Get_elements ( &status, MPI_BYTE, &actual_len);
            
            std::vector<PeptideWithSetModifications *> npep2;
            size_t pos;
            PeptideWithSetModifications::Unpack (recv_buf, actual_len, pos, npep2, 2 );

            std::vector<PeptideWithSetModifications *> npep3;
            size_t pos2;
            PeptideWithSetModifications::Unpack (recv_buf+pos, actual_len-pos, pos2, npep3);
            
            npep2.insert(npep2.end(), npep3.begin(), npep3.end() );
            Assert::AreEqual (fiveCleavageProductsTrypsin.size(), npep2.size() );
            for ( auto n : npep2 ) {
                n->SetNonSerializedPeptideInfo( umsM1, umsP);
            }
            
            for ( auto i = 0; i < npep2.size(); i++ ) {
                Assert::IsTrue(fiveCleavageProductsTrypsin[i]->getFullSequence() == npep2[i]->getFullSequence());
                Assert::IsTrue(fiveCleavageProductsTrypsin[i]->Equals(npep2[i]));
            }

            for ( auto pep : npep2 ){
                delete pep;
            }                
        }

        for ( auto pep: fiveCleavageProductsTrypsin ) {
            delete pep;
        }
        
        delete fiveCleavages;
        delete fullyDigestParams;                
        MPI_Barrier ( MPI_COMM_WORLD);
    }    
#endif    
    
    void TestSerialization::SerializeMatchedFragmentIon()
    {
        auto  tempVar = new NeutralTerminusFragment (FragmentationTerminus::N, 1, 1, 1);
        Product *P = new Product(ProductType::b, tempVar, 0);

        std::vector<MatchedFragmentIon *>mVec (3);
        mVec[0] = new MatchedFragmentIon(P, 1, 1, 1);
        mVec[1] = new MatchedFragmentIon(P, 2, 1, 1);
        mVec[2] = new MatchedFragmentIon(P, 3, 1, 1);
        

        char buf[256];
        size_t buf_len = 256;
        int ret = MatchedFragmentIon::Pack(buf, buf_len, mVec);
        if ( ret == -1 ) {
            std::cout<< "Buffer too small, increase to " << buf_len << " bytes \n";
        }

        std::vector<MatchedFragmentIon *>nVec;
        size_t unpack_len, unpack_len2;
        MatchedFragmentIon::Unpack(buf, buf_len, unpack_len, nVec, 2);
        Assert::AreEqual(nVec.size(), 2);

        MatchedFragmentIon *n;
        MatchedFragmentIon::Unpack(buf+unpack_len, buf_len-unpack_len, unpack_len2, &n);
        nVec.push_back(n);

        for ( auto i = 0; i < mVec.size() ; i++ ) {
            Assert::IsTrue(mVec[i]->Equals(nVec[i]));
        }

        for ( auto m: mVec ) delete m;
        for ( auto n: nVec ) delete n;
        delete P;
    }

#ifdef USE_MPI
    void TestSerialization::SerializeMatchedFragmentIon_MPI()
    {
        int rank;
        MPI_Comm_rank ( MPI_COMM_WORLD, &rank );

        auto  tempVar = new NeutralTerminusFragment (FragmentationTerminus::N, 1, 1, 1);
        Product *P = new Product(ProductType::b, tempVar, 0);
        
        std::vector<MatchedFragmentIon *>mVec (3);
        mVec[0] = new MatchedFragmentIon(P, 1, 1, 1);
        mVec[1] = new MatchedFragmentIon(P, 2, 1, 1);
        mVec[2] = new MatchedFragmentIon(P, 3, 1, 1);
        
        char buf[256];
        size_t buf_len = 256;
        int ret = MatchedFragmentIon::Pack(buf, buf_len, mVec);
        if ( ret == -1 ) {
            std::cout<< "Buffer too small, increase to " << buf_len << " bytes \n";
        }

        char recv_buf[1024];
        if ( rank == 0 ) {
            MPI_Send ( buf, buf_len, MPI_BYTE, 1, 10, MPI_COMM_WORLD);
        }
        else if ( rank == 1 ) {
            MPI_Status status;
            MPI_Recv ( recv_buf, 256, MPI_BYTE, 0, 10, MPI_COMM_WORLD, &status );
            int actual_length;
            MPI_Get_elements ( &status, MPI_BYTE, &actual_length );

            std::vector<MatchedFragmentIon *>newmVec;
            size_t len;
            MatchedFragmentIon::Unpack (recv_buf, actual_length, len, newmVec);
            Assert::AreEqual (newmVec.size(), 3 );
            for ( auto i = 0; i < newmVec.size() ; i++ ) {
                Assert::IsTrue(mVec[i]->Equals(newmVec[i]));
            }

            for ( auto m : newmVec ) {
                delete m;
            }
        }
        
        for ( auto m : mVec ) {
            delete m;
        }
        delete P;
        MPI_Barrier ( MPI_COMM_WORLD);
    }
#endif    
}
