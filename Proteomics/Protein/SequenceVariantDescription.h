#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <any>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class SnpEffAnnotation; }


namespace Proteomics
{
    class SequenceVariantDescription
    {
    private:
        std::string privateDescription;
        std::string privateReferenceAlleleString;
        std::string privateAlternateAlleleString;
        SnpEffAnnotation *privateInfo;
        std::string privateFormat;
        std::unordered_map<std::string, bool> privateHomozygous = std::unordered_map<std::string, bool>();
        std::unordered_map<std::string, bool> privateHeterozygous = std::unordered_map<std::string, bool>();
        std::unordered_map<std::string, std::vector<std::string>> privateGenotypes = std::unordered_map<std::string, std::vector<std::string>>();
        std::unordered_map<std::string, std::vector<std::string>> privateAlleleDepths = std::unordered_map<std::string, std::vector<std::string>>();
        int privateAlleleIndex = 0;

    public:
        SequenceVariantDescription(const std::string &description);

        std::string getDescription() const;
        std::string getReferenceAlleleString() const;
        std::string getAlternateAlleleString() const;
        SnpEffAnnotation *getInfo() const;
        std::string getFormat() const;
        std::unordered_map<std::string, bool> getHomozygous() const;
        std::unordered_map<std::string, bool> getHeterozygous() const;
        std::unordered_map<std::string, std::vector<std::string>> getGenotypes() const;
        std::unordered_map<std::string, std::vector<std::string>> getAlleleDepths() const;
        int getAlleleIndex() const;

        /// <summary>
        /// Returns original string for the description
        /// </summary>
        /// <returns></returns>
        std::string ToString() override;

        bool Equals(std::any obj) override;

        int GetHashCode() override;

        /// <summary>
        /// Gets a dictionary of the format (key) and fields (value) for a genotype
        /// </summary>
        /// <param name="format"></param>
        /// <param name="genotype"></param>
        /// <returns></returns>
        static std::unordered_map<std::string, std::string> GenotypeDictionary(const std::string &format, const std::string &genotype);
    };
}
