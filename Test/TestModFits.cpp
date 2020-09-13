#include "TestModFits.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationLocalization.h"

#include "MzLibAssert.h"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;


int main ( int argc, char **argv )
{
    int i=0;
    
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
    std::cout << ++i << ". TestModFitss" << std::endl;
    Test::TestModFits::TestModFitss();

    //[TestCase("M", "X", true)]
    std::cout << ++i << ". TestAmbiguousModFits(M, X, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("M", "X", true);

    //[TestCase("M", "J", false)]
    std::cout << ++i << ". TestAmbiguousModFits(M, J, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("M", "J", true);

    //[TestCase("I", "J", true)]
    std::cout << ++i << ". TestAmbiguousModFits(I, J, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("I", "J", true);

    //[TestCase("L", "X", true)]
    std::cout << ++i << ". TestAmbiguousModFits(L, X, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("L", "X", true);

    //[TestCase("M", "B", false)]
    std::cout << ++i << ". TestAmbiguousModFits(M, B, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("M", "B", true);

    //[TestCase("D", "B", true)]
    std::cout << ++i << ". TestAmbiguousModFits(D, B, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("D", "B", true);

    //[TestCase("N", "B", true)]
    std::cout << ++i << ". TestAmbiguousModFits(N, B, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("N", "B", true);

    //[TestCase("M", "Z", false)]
    std::cout << ++i << ". TestAmbiguousModFits(M, Z, false)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("M", "Z", false);

    //[TestCase("E", "Z", true)]
    std::cout << ++i << ". TestAmbiguousModFits(E, Z, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("E", "Z", true);

    //[TestCase("Q", "Z", true)] 
    std::cout << ++i << ". TestAmbiguousModFits(Q, Z, true)" << std::endl;
    Test::TestModFits::TestAmbiguousModFits("Q", "Z", true);

    return 0;
}
    
namespace Test
{
    void TestModFits::TestModFitss()
    {
        Protein *protein = new Protein("M", "");
        int peptideOneBasedIndex = 1;
        int peptideLength = 1;
        int proteinOneBasedIndex = 1;

        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("M", &motif);
        Modification *attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                                           std::vector<std::string>(),
                                                           std::unordered_map<DissociationType, std::vector<double>>(),
                                                           std::unordered_map<DissociationType, std::vector<double>>(), "");

        Assert::IsTrue(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                         peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        ModificationMotif::TryGetMotif("N", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");

        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        
        ModificationMotif::TryGetMotif("Mx", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        
        ModificationMotif::TryGetMotif("Mr", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        ModificationMotif::TryGetMotif("xM", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        
        ModificationMotif::TryGetMotif("Nxs", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, 
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");

        protein = new Protein("MNRS", "");
        peptideOneBasedIndex = 1;
        peptideLength = 1;
        proteinOneBasedIndex = 1;
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;
        
        ModificationMotif::TryGetMotif("Nxs", &motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::unordered_map<std::string, std::vector<std::string>>(),
                                             std::vector<std::string>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(),
                                             std::unordered_map<DissociationType, std::vector<double>>(), "");

        protein = new Protein("MNRS", "");
        peptideOneBasedIndex = 1;
        peptideLength = 1;
        proteinOneBasedIndex = 1;
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));
        delete attemptToLocalize;

        peptideOneBasedIndex = 2;
        peptideLength = 1;
        proteinOneBasedIndex = 2;
        Assert::IsTrue(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                         peptideLength, proteinOneBasedIndex));
        protein = new Protein("MNRN", "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex,
                                                          peptideLength, proteinOneBasedIndex));

        delete attemptToLocalize;
        delete protein;
    }

    void TestModFits::TestAmbiguousModFits(const std::string &proteinSequence, const std::string &motifString, bool result)
    {
        Protein *protein = new Protein(proteinSequence, "");
        int peptideOneBasedIndex = 1;
        int peptideLength = 1;
        int proteinOneBasedIndex = 1;
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif(motifString, &motif);
        Modification *attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN,
                                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                                           std::vector<std::string>(),
                                                           std::unordered_map<DissociationType, std::vector<double>>(),
                                                           std::unordered_map<DissociationType, std::vector<double>>(), "");
        Assert::AreEqual(result, ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(),
                                                                   peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        delete attemptToLocalize;
        delete protein;
    }
}
