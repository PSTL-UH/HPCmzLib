#include "TestModFits.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationLocalization.h"

using namespace NUnit::Framework;
using namespace Proteomics;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestModFits::privateStopwatch;

    Stopwatch *TestModFits::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestModFits::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestModFits::Setup()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestModFits::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestModFits::TestModFitss()
    {
        Protein *protein = new Protein("M", "");
        int peptideOneBasedIndex = 1;
        int peptideLength = 1;
        int proteinOneBasedIndex = 1;

        ModificationMotif motif;
        ModificationMotif::TryGetMotif("M", motif);
        Modification *attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::IsTrue(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("N", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("Mx", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("Mr", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("xM", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("Nxs", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");

        protein = new Protein("MNRS", "");
        peptideOneBasedIndex = 1;
        peptideLength = 1;
        proteinOneBasedIndex = 1;
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

        ModificationMotif::TryGetMotif("Nxs", motif);
        attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");

        protein = new Protein("MNRS", "");
        peptideOneBasedIndex = 1;
        peptideLength = 1;
        proteinOneBasedIndex = 1;
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));
        peptideOneBasedIndex = 2;
        peptideLength = 1;
        proteinOneBasedIndex = 2;
        Assert::IsTrue(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));
        protein = new Protein("MNRN", "");
        Assert::IsFalse(ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

//C# TO C++ CONVERTER TODO TASK: A 'delete attemptToLocalize' statement was not added since attemptToLocalize was passed to a method or constructor. Handle memory management manually.
        delete protein;
    }

    void TestModFits::TestAmbiguousModFits(const std::string &proteinSequence, const std::string &motifString, bool result)
    {
        Protein *protein = new Protein(proteinSequence, "");
        int peptideOneBasedIndex = 1;
        int peptideLength = 1;
        int proteinOneBasedIndex = 1;
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(motifString, motif);
        Modification *attemptToLocalize = new Modification("", "", "", "", motif, "Anywhere.", nullptr, NAN, std::unordered_map<std::string, IList<std::string>>(), std::unordered_map<std::string, IList<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, List<double>>(), std::unordered_map<DissociationType, List<double>>(), "");
        Assert::AreEqual(result, ModificationLocalization::ModFits(attemptToLocalize, protein->getBaseSequence(), peptideOneBasedIndex, peptideLength, proteinOneBasedIndex));

//C# TO C++ CONVERTER TODO TASK: A 'delete attemptToLocalize' statement was not added since attemptToLocalize was passed to a method or constructor. Handle memory management manually.
        delete protein;
    }
}
