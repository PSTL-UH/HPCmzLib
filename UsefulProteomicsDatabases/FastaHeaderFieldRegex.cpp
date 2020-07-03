#include "FastaHeaderFieldRegex.h"


namespace UsefulProteomicsDatabases
{

    FastaHeaderFieldRegex::FastaHeaderFieldRegex(const std::string &fieldName,
                                                 const std::string &regularExpression,
                                                 int match, int group)
    {
        privateFieldName = fieldName;
        privateRegex = new std::regex(regularExpression);
        privateMatch = match;
        privateGroup = group;
    }

    std::string FastaHeaderFieldRegex::getFieldName() const
    {
        return privateFieldName;
    }

    std::regex *FastaHeaderFieldRegex::getRegex() const
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
