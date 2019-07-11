#include "SequenceVariantDescription.h"
#include "SnpEffAnnotation.h"
#include "stringhelper.h"

namespace Proteomics
{

    SequenceVariantDescription::SequenceVariantDescription(const std::string &description)
    {
        privateDescription = description;
        if (description == "")
        {
            return;
        }

        // Parse description into
#ifdef ORIG
        std::vector<std::string> vcfFields = description.Split({R"(\t)"}, StringSplitOptions::None);
#endif
        std::vector<std::string> vcfFields = StringHelper::split(description, '\t');

        if (vcfFields.size() < 10)
        {
            return;
        }
        privateReferenceAlleleString = vcfFields[3];
        privateAlternateAlleleString = vcfFields[4];
        privateInfo = new SnpEffAnnotation(vcfFields[7]);
#ifdef ORIG
        privateAlleleIndex = getInfo()->getAllele() == "" ? -1 :
            StringHelper::split(getAlternateAlleleString(), ',').ToList()->
            find(getInfo()->getAllele()) + 1; // reference is zero
#endif
        if ( getInfo()->getAllele() == "" ) {
            privateAlleleIndex = -1;
        }
        else {
            std::vector<std::string> temps = StringHelper::split(getAlternateAlleleString(), ',');
            auto it = std::find(temps.begin(), temps.end(), (getInfo()->getAllele()));
            privateAlleleIndex = std::distance(temps.begin(), it) + 1;
                                
        }
        privateFormat = vcfFields[8];

#ifdef ORIG
        std::vector<std::string> genotypes = Enumerable::Range(9, vcfFields.size() - 9)->Select([&] (std::any i)
        {
            vcfFields[i];
        })->ToArray();
#endif
        std::vector<std::string> genotypes;
        for ( long unsigned int i=9; i<vcfFields.size()-9; i++ ) {
            genotypes.push_back(vcfFields[i]);
        }

        // loop through genotypes for this variant (e.g. tumor and normal)
        for (int individual = 0; individual < (int) genotypes.size(); individual++)
        {
            auto genotypeFields = GenotypeDictionary(StringHelper::trim(getFormat()),
                                                     StringHelper::trim(genotypes[individual]));

            // parse genotype
            std::vector<std::string> gt;
            std::string gtString;
            std::unordered_map<std::string, std::string>::const_iterator genotypeFields_iterator = genotypeFields.find("GT");
            if (genotypeFields_iterator != genotypeFields.end())
            {
                gtString = genotypeFields_iterator->second;
                gt = StringHelper::split(gtString, '/');
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
            std::string adString;
            std::unordered_map<std::string, std::string>::const_iterator genotypeFields_iterator2 = genotypeFields.find("AD");
            if (genotypeFields_iterator2 != genotypeFields.end())
            {
                adString = genotypeFields_iterator2->second;
                ad = StringHelper::split(adString, ',');
            }
            else
            {
                adString = genotypeFields_iterator2->second;
            }

            getGenotypes().emplace(std::to_string(individual), gt);
            getAlleleDepths().emplace(std::to_string(individual), ad);
#ifdef ORIG
            getHomozygous().emplace(std::to_string(individual), gt.Distinct()->Count() == 1);
            getHeterozygous().emplace(std::to_string(individual), gt.Distinct()->Count() > 1);
#endif
            std::vector<std::string> sortedgt;
            for ( long unsigned int i=0; i<gt.size(); i++ ) {
                sortedgt.push_back(gt[i]);
            }
            std::sort(sortedgt.begin(), sortedgt.end());
            auto uniqCnt = std::unique(sortedgt.begin(), sortedgt.end()) - sortedgt.begin();
            getHomozygous().emplace(std::to_string(individual), uniqCnt == 1);
            getHeterozygous().emplace(std::to_string(individual), uniqCnt > 1);            
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

    bool SequenceVariantDescription::Equals(SequenceVariantDescription *s)
    {
        return s != nullptr && s->getDescription() == getDescription();
    }

    int SequenceVariantDescription::GetHashCode()
    {
        std::string tempVar = getDescription();
        return StringHelper::GetHashCode((tempVar != "") ? tempVar : "");
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
#ifdef ORIG
        return Enumerable::Range(0, formatSplit.size()).ToDictionary([&] (std::any x)
        {
            formatSplit[x];
        }, [&] (std::any x)
        {
            genotypeSplit[x];
        });
#endif
        std::unordered_map<std::string, std::string> vuss;
        for ( long unsigned int x=0; x<formatSplit.size(); x++ ) {
            vuss.insert({formatSplit[x], genotypeSplit[x]});
        }
        return vuss;
    }
}
