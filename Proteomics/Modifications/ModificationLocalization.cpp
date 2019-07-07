#include "ModificationLocalization.h"
#include "Modification.h"


namespace Proteomics
{

    bool ModificationLocalization::ModFits(Modification *attemptToLocalize, const std::string &proteinSequence, int peptideOneBasedIndex, int peptideLength, int proteinOneBasedIndex)
    {
        // First find the capital letter...
        auto motif = attemptToLocalize->getTarget();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        auto motifStartLocation = (int)motif->ToString()->find(motif->ToString()->First([&] (std::any b)
        {
            std::isupper(b);
        }));

        // Look up starting at and including the capital letter
        auto proteinToMotifOffset = proteinOneBasedIndex - motifStartLocation - 1;
        auto indexUp = 0;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        while (indexUp < motif->ToString()->length())
        {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            if (indexUp + proteinToMotifOffset < 0 || indexUp + proteinToMotifOffset >= proteinSequence.length() || !MotifMatches(motif->ToString()[indexUp], proteinSequence[indexUp + proteinToMotifOffset]))
            {
                return false;
            }
            indexUp++;
        }
        if (attemptToLocalize->getLocationRestriction() == "N-terminal." && proteinOneBasedIndex > 2)
        {
            return false;
        }
        if (attemptToLocalize->getLocationRestriction() == "Peptide N-terminal." && peptideOneBasedIndex > 1)
        {
            return false;
        }
        if (attemptToLocalize->getLocationRestriction() == "C-terminal." && proteinOneBasedIndex < proteinSequence.length())
        {
            return false;
        }
        if (attemptToLocalize->getLocationRestriction() == "Peptide C-terminal." && peptideOneBasedIndex < peptideLength)
        {
            return false;
        }

        // I guess Anywhere. and Unassigned. are true since how do you localize anywhere or unassigned.

        return true;
    }

    bool ModificationLocalization::MotifMatches(char motifChar, char sequenceChar)
    {
        char upperMotifChar = std::toupper(motifChar);
        return upperMotifChar.Equals('X') || upperMotifChar.Equals(sequenceChar) || upperMotifChar.Equals('B') && {'D', 'N'}->Contains(sequenceChar) || upperMotifChar.Equals('J') && {'I', 'L'}->Contains(sequenceChar) || upperMotifChar.Equals('Z') && {'E', 'Q'}->Contains(sequenceChar);
    }
}
