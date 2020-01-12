#pragma once

#include <string>
#include <unordered_set>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class SpectraFileInfo; }
namespace FlashLFQ { class ProteinGroup; }


//namespace Chemistry { class ChemicalFormula; }
#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

namespace FlashLFQ
{
    class Identification
    {
    public:
        const std::string BaseSequence;
        const std::string ModifiedSequence;
        const double ms2RetentionTimeInMinutes;
        const double monoisotopicMass;
        SpectraFileInfo *const fileInfo;
        const int precursorChargeState;
        //C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which
        // allows modification of internal state:
        //ORIGINAL LINE: public readonly HashSet<ProteinGroup> proteinGroups;
        std::unordered_set<ProteinGroup*> proteinGroups;
        ChemicalFormula *const OptionalChemicalFormula;
        const bool UseForProteinQuant;
        double massToLookFor = 0;

        virtual ~Identification()
        {
            //delete fileInfo;
            //delete OptionalChemicalFormula;
        }

        Identification(SpectraFileInfo *fileInfo, const std::string &BaseSequence,
                       const std::string &ModifiedSequence,
                       double monoisotopicMass, double ms2RetentionTimeInMinutes,
                       int chargeState, std::vector<ProteinGroup*> &proteinGroups,
                       ChemicalFormula *optionalChemicalFormula = nullptr,
                       bool useForProteinQuant = true);

        std::string ToString();
    };
}
