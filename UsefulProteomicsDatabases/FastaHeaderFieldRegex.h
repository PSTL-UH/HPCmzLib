#pragma once

#include <string>


namespace UsefulProteomicsDatabases
{
    class FastaHeaderFieldRegex
    {
    private:
        std::string privateFieldName;
        Regex *privateRegex;
        int privateMatch = 0;
        int privateGroup = 0;

    public:
        FastaHeaderFieldRegex(const std::string &fieldName, const std::string &regularExpression, int match, int group);

        std::string getFieldName() const;

        Regex *getRegex() const;

        int getMatch() const;

        int getGroup() const;
    };
}
