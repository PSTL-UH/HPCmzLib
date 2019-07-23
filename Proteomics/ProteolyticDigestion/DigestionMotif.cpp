#include <regex>

#include "DigestionMotif.h"
#include "../../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

std::vector<char> DigestionMotif::B = {'D', 'N'};
std::vector<char> DigestionMotif::J = {'I', 'L'};
std::vector<char> DigestionMotif::Z = {'E', 'Q'};

        DigestionMotif::DigestionMotif(const std::string &inducingCleavage, const std::string &preventingCleavage, int cutIndex, const std::string &excludeFromWildcard) : InducingCleavage(inducingCleavage), PreventingCleavage(preventingCleavage), CutIndex(cutIndex), ExcludeFromWildcard(excludeFromWildcard)
        {
        }

        std::vector<DigestionMotif*> DigestionMotif::ParseDigestionMotifsFromString(std::string motifsString)
        {
            motifsString = StringHelper::replace(StringHelper::replace(motifsString, "\"", ""), " ", "");
            
            // throws exception if non-supported characters are used
            std::regex reg1(R"([^a-zA-Z0-9|,[\]{}]+)");
            std::smatch rm1;
            if (std::regex_match(motifsString, rm1, reg1) )
            {
                throw MzLibException("Unrecognized protease syntax. The digestion motif can only contain letters and {}[]|");
            }
            // throws exception if user attempts separate multiple preventing cleavages using commas
            std::regex reg2 (R"(\[([\w]*,+[\w]*)*\])");
            if (std::regex_match(motifsString, rm1, reg2) )
            {
                throw MzLibException("Unrecognized protease syntax. Please create a separate motif for each sequence preventing cleavage (comma separated).");
            }
            // throws exception if user attempts separate multiple wildcard exclusions
            std::regex reg3 (R"(\{([\w]*,+[\w]*)*\})");
            if (std::regex_match(motifsString, rm1, reg3 ))
            {
                throw MzLibException("Unrecognized protease syntax. Please create a separate motif for each wildcard exclusion (comma separated).");
            }

            std::vector<std::string> motifStrings = StringHelper::split(motifsString, ',');
            auto motifs = std::vector<DigestionMotif*>();

            for (int i = 0; i < (int)motifStrings.size(); i++)
            {
                std::string motifString = motifStrings[i];
                motifs.push_back(ParseDigestionMotifFromString(motifString));
            }
            return motifs;
        }

        DigestionMotif *DigestionMotif::ParseDigestionMotifFromString(std::string motifString)
        {
            std::string inducingCleavage;
            std::string preventingCleavage = "";
            std::string excludingWC = "";
            int cutIndex = 0;

            if ( (motifString.find("{") != std::string::npos && motifString.find("}") == std::string::npos) ||
                 (motifString.find("{") == std::string::npos && motifString.find("}") != std::string::npos) ||
                 (motifString.find("[") != std::string::npos && motifString.find("]") == std::string::npos) ||
                 (motifString.find("[") == std::string::npos && motifString.find("]") != std::string::npos))
            {
                throw MzLibException("Unrecognized protease syntax. Please close any brackets used.");
            }

            // find preventing cleavage
            if (motifString.find("[") != std::string::npos)
            {
                int start = (int)motifString.find("[") + 1;
                int end = (int)motifString.find("]");

                preventingCleavage = motifString.substr(start, end - start);
#ifdef ORIG
                motifString = Regex->Replace(motifString, R"(\[[a-zA-Z]+\])", "");
#endif
                std::regex reg (R"(\[[a-zA-Z]+\])");
                motifString = std::regex_replace(motifString, reg, "");
            }

            // finds wildcard exceptions
            if (motifString.find("{") != std::string::npos)
            {
                int start = (int)motifString.find("{") + 1;
                int end = (int)motifString.find("}");

                excludingWC = motifString.substr(start, end - start);
#ifdef ORIG
                if (Regex::Matches(StringHelper::toUpper(motifString), "X")->Count != excludingWC.length()){}
#endif
                std::string upperMotifString = StringHelper::toUpper(motifString);
                std::regex reg ("X");
                std::smatch sm;
                std::sregex_iterator match(upperMotifString.begin(), upperMotifString.end(), reg);
                std::sregex_iterator reg_end;
                int count=0;
                for ( ; match != reg_end; ++match) {
                    count++;
                }
                if ( count != (int) excludingWC.length())
                {
                    throw MzLibException("Unrecognized protease syntax. Please have equal number of wildcards for multi-letter wildcard exclusions.");
                }
                std::regex reg2 (R"(\[[a-zA-Z]+\])");
                motifString = std::regex_replace(motifString, reg2, "");
            }

            // finds motif cut index
            for (int j = 0; j < (int)motifString.length(); j++)
            {
                if (motifString[j] == '|')
                {
                    cutIndex = j;
                    break;
                }
            }

            motifString = StringHelper::replace(motifString, "|", "");
            inducingCleavage = motifString;

            return new DigestionMotif(inducingCleavage, preventingCleavage, cutIndex, excludingWC);
        }

        bool DigestionMotif::Fits(const std::string &sequence, int location)
        {
            bool fits = true;
            char currentResidue;
            int m;

            // check for inducing cleavage
            for (m = 0; m < (int)InducingCleavage.length() && fits; m++) // handle patterns
            {
                currentResidue = sequence[location + m];
                if (!MotifMatches(InducingCleavage[m], currentResidue))
                {
                    fits = false;
                }
            }

            // check for preventing cleavage
            if (fits && PreventingCleavage != "")
            {
                bool match = true;
                for (int n = 0; n < (int)PreventingCleavage.length() && match; n++)
                {
                    if (location + m + n > (int)sequence.length() || location - (int)PreventingCleavage.length() + 1 + n < 0)
                    {
                        match = false;
                    }
                    else
                    {
                        currentResidue = CutIndex != 0 ? sequence[location + m + n] : sequence[location - PreventingCleavage.length() + 1 + n];

#ifdef ORIG
                        if (! PreventingCleavage[n].Equals(currentResidue)){}
#endif
                        if ( PreventingCleavage.c_str()[n] != currentResidue) {
                            match = false;
                        }
                    }
                }

                fits = match ? false : true;
            }

            return fits;
        }

        bool DigestionMotif::MotifMatches(char motifChar, char sequenceChar)
        {
#ifdef ORIG
            return motifChar.Equals('X')                                           &&
                !StringHelper::toString(sequenceChar)->Equals(ExcludeFromWildcard) ||
                motifChar.Equals(sequenceChar)                                     ||
                motifChar.Equals('B') && B.Contains(sequenceChar)                  ||
                motifChar.Equals('J') && J.Contains(sequenceChar)                  ||
                motifChar.Equals('Z') && Z.Contains(sequenceChar);
#endif
            bool BContains = (B[0] == sequenceChar) || (B[1] == sequenceChar);
            bool JContains = (J[0] == sequenceChar) || (J[1] == sequenceChar);
            bool ZContains = (Z[0] == sequenceChar) || (Z[1] == sequenceChar);
            return (motifChar == 'X'                                               &&
                    (ExcludeFromWildcard.find(sequenceChar) == std::string::npos)) ||
                motifChar == sequenceChar                                     ||
                (motifChar == 'B' && BContains)                               ||
                (motifChar == 'J' && JContains)                               ||
                (motifChar == 'Z' && ZContains);
        }
    }
}
