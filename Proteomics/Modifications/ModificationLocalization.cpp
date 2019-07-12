#include "ModificationLocalization.h"
#include "Modification.h"


namespace Proteomics
{

    bool ModificationLocalization::ModFits(Modification *attemptToLocalize, const std::string &proteinSequence, int peptideOneBasedIndex, int peptideLength, int proteinOneBasedIndex)
    {
        // First find the capital letter...
        auto motif = attemptToLocalize->getTarget();
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
#ifdef ORIG
        auto motifStartLocation = (int) motif->ToString()->find(motif->ToString()->First([&] (std::any b)
        {
            std::isupper(b);
        }));
#endif
        int motifStartLocation;
        std::string motifstring = motif->ToString();
        for ( int i; i < (int) motifstring.length(); i++ )
        {
            if ( std::isupper(motifstring[i])){
                motifStartLocation = i;
                break;
            }
        }
    

        // Look up starting at and including the capital letter
        auto proteinToMotifOffset = proteinOneBasedIndex - motifStartLocation - 1;
        auto indexUp = 0;
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        int upper = motifstring.length();
        while (indexUp < upper)
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            if (indexUp + proteinToMotifOffset < 0 ||
                indexUp + proteinToMotifOffset >= (int) proteinSequence.length() ||
                !MotifMatches(motifstring[indexUp], proteinSequence[indexUp + proteinToMotifOffset]))
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
        if (attemptToLocalize->getLocationRestriction() == "C-terminal." && proteinOneBasedIndex < (int)proteinSequence.length())
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
#ifdef ORIG
        return upperMotifChar.Equals('X') || upperMotifChar.Equals(sequenceChar) || upperMotifChar.Equals('B') && {'D', 'N'}->Contains(sequenceChar) || upperMotifChar.Equals('J') && {'I', 'L'}->Contains(sequenceChar) || upperMotifChar.Equals('Z') && {'E', 'Q'}->Contains(sequenceChar);
#endif
        bool containsD = sequenceChar == 'D' ? true : false;
        bool containsN = sequenceChar == 'N' ? true : false;
        bool containsI = sequenceChar == 'I' ? true : false;
        bool containsL = sequenceChar == 'L' ? true : false;
        bool containsE = sequenceChar == 'E' ? true : false;
        bool containsQ = sequenceChar == 'Q' ? true : false;
        return upperMotifChar == 'X'       ||
            upperMotifChar == sequenceChar ||
            (upperMotifChar == 'B' && (containsD || containsN )) ||
            (upperMotifChar == 'J' && (containsI || containsL )) ||
            (upperMotifChar == 'Z' && (containsE || containsQ ));

    }
}
