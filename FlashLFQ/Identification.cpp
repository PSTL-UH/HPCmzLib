#include "Identification.h"
#include "SpectraFileInfo.h"
#include "ProteinGroup.h"
#include "../Chemistry/ChemicalFormula.h"

using namespace Chemistry;

namespace FlashLFQ
{

    Identification::Identification(SpectraFileInfo *fileInfo, const std::string &BaseSequence,
                                   const std::string &ModifiedSequence, double monoisotopicMass,
                                   double ms2RetentionTimeInMinutes, int chargeState,
                                   std::vector<ProteinGroup*> &ProteinGroups,
                                   ChemicalFormula *optionalChemicalFormula, bool useForProteinQuant) :
        BaseSequence(BaseSequence),
        ModifiedSequence(ModifiedSequence), ms2RetentionTimeInMinutes(ms2RetentionTimeInMinutes),
        monoisotopicMass(monoisotopicMass), fileInfo(fileInfo),
        precursorChargeState(chargeState),
        OptionalChemicalFormula(optionalChemicalFormula),
        UseForProteinQuant(useForProteinQuant)
    {
        for ( auto v: ProteinGroups ) {
            proteinGroups.insert(v);
        }

    }

    std::string Identification::ToString()
    {
        return ModifiedSequence;
    }
}
