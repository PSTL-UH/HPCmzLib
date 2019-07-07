#pragma once

#include <string>
#include <vector>
#include <cctype>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }


namespace Proteomics
{
    class ModificationLocalization final
    {
    public:
        static bool ModFits(Modification *attemptToLocalize, const std::string &proteinSequence, int peptideOneBasedIndex, int peptideLength, int proteinOneBasedIndex);

    private:
        static bool MotifMatches(char motifChar, char sequenceChar);
    };
}
