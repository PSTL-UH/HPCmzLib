#include "FastaHeaderFieldRegex.h"


namespace UsefulProteomicsDatabases
{

    FastaHeaderFieldRegex::FastaHeaderFieldRegex(const std::string &fieldName, const std::string &regularExpression, int match, int group)
    {
        FieldName = fieldName;
        Regex = new Regex(regularExpression);
        Match = match;
        Group = group;
    }

    std::string FastaHeaderFieldRegex::getFieldName() const
    {
        return privateFieldName;
    }

    Regex *FastaHeaderFieldRegex::getRegex() const
    {
        return privateRegex;
    }

    int FastaHeaderFieldRegex::getMatch() const
    {
        return privateMatch;
    }

    int FastaHeaderFieldRegex::getGroup() const
    {
        return privateGroup;
    }
}
