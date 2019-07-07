#pragma once

#include <string>
#include <vector>
#include "stringhelper.h"

using namespace MzLibUtil;

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class DigestionMotif
        {
        private:
            static std::vector<char> B;
            static std::vector<char> J;
            static std::vector<char> Z;

        public:
            const std::string InducingCleavage;
            const std::string PreventingCleavage;
            const int CutIndex;
            const std::string ExcludeFromWildcard;

            DigestionMotif(const std::string &inducingCleavage, const std::string &preventingCleavage, int cutIndex, const std::string &excludeFromWildcard);

            // parsing cleavage rules syntax
            static std::vector<DigestionMotif*> ParseDigestionMotifsFromString(const std::string &motifsString);

        private:
            static DigestionMotif *ParseDigestionMotifFromString(const std::string &motifString);

        public:
            bool Fits(const std::string &sequence, int location);

        private:
            bool MotifMatches(char motifChar, char sequenceChar);
        };
    }
}
