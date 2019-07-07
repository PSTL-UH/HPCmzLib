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

        std::vector<DigestionMotif*> DigestionMotif::ParseDigestionMotifsFromString(const std::string &motifsString)
        {
            motifsString = StringHelper::replace(StringHelper::replace(motifsString, "\"", ""), " ", "");

            // throws exception if non-supported characters are used
            if (Regex::Match(motifsString, R"([^a-zA-Z0-9|,[\]{}]+)").Success)
            {
                throw MzLibException("Unrecognized protease syntax. The digestion motif can only contain letters and {}[]|");
            }
            // throws exception if user attempts separate multiple preventing cleavages using commas
            if (Regex::Match(motifsString, R"(\[([\w]*,+[\w]*)*\])").Success)
            {
                throw MzLibException("Unrecognized protease syntax. Please create a separate motif for each sequence preventing cleavage (comma separated).");
            }
            // throws exception if user attempts separate multiple wildcard exclusions
            if (Regex::Match(motifsString, R"(\{([\w]*,+[\w]*)*\})").Success)
            {
                throw MzLibException("Unrecognized protease syntax. Please create a separate motif for each wildcard exclusion (comma separated).");
            }

            std::vector<std::string> motifStrings = StringHelper::split(motifsString, ',');
            auto motifs = std::vector<DigestionMotif*>();

            for (int i = 0; i < motifStrings.size(); i++)
            {
                std::string motifString = motifStrings[i];
                motifs.push_back(ParseDigestionMotifFromString(motifString));
            }
            return motifs;
        }

        DigestionMotif *DigestionMotif::ParseDigestionMotifFromString(const std::string &motifString)
        {
            std::string inducingCleavage;
            std::string preventingCleavage = "";
            std::string excludingWC = "";
            int cutIndex = 0;

            if (motifString.find("{") != std::string::npos && !motifString.find("}") != std::string::npos || !motifString.find("{") != std::string::npos && motifString.find("}") != std::string::npos || motifString.find("[") != std::string::npos && !motifString.find("]") != std::string::npos || !motifString.find("[") != std::string::npos && motifString.find("]") != std::string::npos)
            {
                throw MzLibException("Unrecognized protease syntax. Please close any brackets used.");
            }

            // find preventing cleavage
            if (motifString.find("[") != std::string::npos)
            {
                int start = (int)motifString.find("[") + 1;
                int end = (int)motifString.find("]");

                preventingCleavage = motifString.substr(start, end - start);
                motifString = Regex->Replace(motifString, R"(\[[a-zA-Z]+\])", "");
            }

            // finds wildcard exceptions
            if (motifString.find("{") != std::string::npos)
            {
                int start = (int)motifString.find("{") + 1;
                int end = (int)motifString.find("}");

                excludingWC = motifString.substr(start, end - start);
                if (Regex::Matches(StringHelper::toUpper(motifString), "X")->Count != excludingWC.length())
                {
                    throw MzLibException("Unrecognized protease syntax. Please have equal number of wildcards for multi-letter wildcard exclusions.");
                }
                motifString = Regex->Replace(motifString, R"(\{[a-zA-Z]+\})", "");
            }

            // finds motif cut index
            for (int j = 0; j < motifString.length(); j++)
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
            for (m = 0; m < InducingCleavage.length() && fits; m++) // handle patterns
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
                for (int n = 0; n < PreventingCleavage.length() && match; n++)
                {
                    if (location + m + n > sequence.length() || location - PreventingCleavage.length() + 1 + n < 0)
                    {
                        match = false;
                    }
                    else
                    {
                        currentResidue = CutIndex != 0 ? sequence[location + m + n] : sequence[location - PreventingCleavage.length() + 1 + n];
                        if (!PreventingCleavage[n].Equals(currentResidue))
                        {
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
            return motifChar.Equals('X') && !StringHelper::toString(sequenceChar)->Equals(ExcludeFromWildcard) || motifChar.Equals(sequenceChar) || motifChar.Equals('B') && B.Contains(sequenceChar) || motifChar.Equals('J') && J.Contains(sequenceChar) || motifChar.Equals('Z') && Z.Contains(sequenceChar);
        }
    }
}
