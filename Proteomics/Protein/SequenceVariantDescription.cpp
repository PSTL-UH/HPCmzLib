#include "SequenceVariantDescription.h"
#include "SnpEffAnnotation.h"


namespace Proteomics
{

    SequenceVariantDescription::SequenceVariantDescription(const std::string &description)
    {
        Description = description;
        if (description == "")
        {
            return;
        }

        // Parse description into
        std::vector<std::string> vcfFields = description.Split({R"(\t)"}, StringSplitOptions::None);
        if (vcfFields.size() < 10)
        {
            return;
        }
        ReferenceAlleleString = vcfFields[3];
        AlternateAlleleString = vcfFields[4];
        Info = new SnpEffAnnotation(vcfFields[7]);
        AlleleIndex = getInfo()->getAllele() == "" ? -1 : StringHelper::split(getAlternateAlleleString(), ',').ToList()->find(getInfo()->getAllele()) + 1; // reference is zero
        Format = vcfFields[8];
        std::vector<std::string> genotypes = Enumerable::Range(9, vcfFields.size() - 9)->Select([&] (std::any i)
        {
            vcfFields[i];
        })->ToArray();

        // loop through genotypes for this variant (e.g. tumor and normal)
        for (int individual = 0; individual < genotypes.size(); individual++)
        {
            auto genotypeFields = GenotypeDictionary(StringHelper::trim(getFormat()), StringHelper::trim(genotypes[individual]));

            // parse genotype
            std::vector<std::string> gt;
            string gtString;
            std::unordered_map<std::string, std::string>::const_iterator genotypeFields_iterator = genotypeFields.find("GT");
            if (genotypeFields_iterator != genotypeFields.end())
            {
                gtString = genotypeFields_iterator->second;
                gt = gtString->Split('/');
            }
            else
            {
                gtString = genotypeFields_iterator->second;
            }
            if (gt.empty())
            {
                continue;
            }

            // parse allele depth (might be null, technically, but shouldn't be in most use cases)
            std::vector<std::string> ad;
            string adString;
            std::unordered_map<std::string, std::string>::const_iterator genotypeFields_iterator = genotypeFields.find("AD");
            if (genotypeFields_iterator != genotypeFields.end())
            {
                adString = genotypeFields_iterator->second;
                ad = adString->Split(',');
            }
            else
            {
                adString = genotypeFields_iterator->second;
            }

            getGenotypes().emplace(std::to_string(individual), gt);
            getAlleleDepths().emplace(std::to_string(individual), ad);
            getHomozygous().emplace(std::to_string(individual), gt.Distinct()->Count() == 1);
            getHeterozygous().emplace(std::to_string(individual), gt.Distinct()->Count() > 1);
        }
    }

    std::string SequenceVariantDescription::getDescription() const
    {
        return privateDescription;
    }

    std::string SequenceVariantDescription::getReferenceAlleleString() const
    {
        return privateReferenceAlleleString;
    }

    std::string SequenceVariantDescription::getAlternateAlleleString() const
    {
        return privateAlternateAlleleString;
    }

    SnpEffAnnotation *SequenceVariantDescription::getInfo() const
    {
        return privateInfo;
    }

    std::string SequenceVariantDescription::getFormat() const
    {
        return privateFormat;
    }

    std::unordered_map<std::string, bool> SequenceVariantDescription::getHomozygous() const
    {
        return privateHomozygous;
    }

    std::unordered_map<std::string, bool> SequenceVariantDescription::getHeterozygous() const
    {
        return privateHeterozygous;
    }

    std::unordered_map<std::string, std::vector<std::string>> SequenceVariantDescription::getGenotypes() const
    {
        return privateGenotypes;
    }

    std::unordered_map<std::string, std::vector<std::string>> SequenceVariantDescription::getAlleleDepths() const
    {
        return privateAlleleDepths;
    }

    int SequenceVariantDescription::getAlleleIndex() const
    {
        return privateAlleleIndex;
    }

    std::string SequenceVariantDescription::ToString()
    {
        return getDescription();
    }

    bool SequenceVariantDescription::Equals(std::any obj)
    {
        SequenceVariantDescription *s = dynamic_cast<SequenceVariantDescription*>(obj);
        return s != nullptr && s->getDescription() == getDescription();
    }

    int SequenceVariantDescription::GetHashCode()
    {
        std::string tempVar = getDescription();
        return ((tempVar != nullptr) ? tempVar : "")->GetHashCode();
    }

    std::unordered_map<std::string, std::string> SequenceVariantDescription::GenotypeDictionary(const std::string &format, const std::string &genotype)
    {
        std::unordered_map<std::string, std::string> genotypeDict;
        std::vector<std::string> formatSplit = StringHelper::split(format, ':');
        std::vector<std::string> genotypeSplit = StringHelper::split(genotype, ':');
        if (formatSplit.size() != genotypeSplit.size())
        {
            throw std::invalid_argument("Genotype format: " + format + " and genotype: " + genotype + " do not match -- they're not the same length");
        }
        return Enumerable::Range(0, formatSplit.size()).ToDictionary([&] (std::any x)
        {
            formatSplit[x];
        }, [&] (std::any x)
        {
            genotypeSplit[x];
        });
    }
}
