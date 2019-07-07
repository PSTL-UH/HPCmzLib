#include "SnpEffAnnotation.h"


namespace Proteomics
{

Regex *const SnpEffAnnotation::HGVSProteinRegex = new Regex(R"((p\.)([A-Z][a-z][a-z])(\d+)([A-Z][a-z][a-z]))");

    std::string SnpEffAnnotation::getAnnotation() const
    {
        return privateAnnotation;
    }

    std::string SnpEffAnnotation::getAllele() const
    {
        return privateAllele;
    }

    std::vector<std::string> SnpEffAnnotation::getEffects() const
    {
        return privateEffects;
    }

    std::string SnpEffAnnotation::getPutativeImpact() const
    {
        return privatePutativeImpact;
    }

    std::string SnpEffAnnotation::getGeneName() const
    {
        return privateGeneName;
    }

    std::string SnpEffAnnotation::getGeneID() const
    {
        return privateGeneID;
    }

    std::string SnpEffAnnotation::getFeatureType() const
    {
        return privateFeatureType;
    }

    std::string SnpEffAnnotation::getFeatureID() const
    {
        return privateFeatureID;
    }

    std::string SnpEffAnnotation::getTranscriptBiotype() const
    {
        return privateTranscriptBiotype;
    }

    int SnpEffAnnotation::getExonIntronRank() const
    {
        return privateExonIntronRank;
    }

    int SnpEffAnnotation::getExonIntronTotal() const
    {
        return privateExonIntronTotal;
    }

    std::string SnpEffAnnotation::getHGVSNotationDnaLevel() const
    {
        return privateHGVSNotationDnaLevel;
    }

    std::string SnpEffAnnotation::getHGVSNotationProteinLevel() const
    {
        return privateHGVSNotationProteinLevel;
    }

    int SnpEffAnnotation::getOneBasedTranscriptCDNAPosition() const
    {
        return privateOneBasedTranscriptCDNAPosition;
    }

    int SnpEffAnnotation::getTranscriptCDNALength() const
    {
        return privateTranscriptCDNALength;
    }

    int SnpEffAnnotation::getOneBasedCodingDomainSequencePosition() const
    {
        return privateOneBasedCodingDomainSequencePosition;
    }

    int SnpEffAnnotation::getCodingDomainSequenceLengthIncludingStopCodon() const
    {
        return privateCodingDomainSequenceLengthIncludingStopCodon;
    }

    int SnpEffAnnotation::getOneBasedProteinPosition() const
    {
        return privateOneBasedProteinPosition;
    }

    int SnpEffAnnotation::getProteinLength() const
    {
        return privateProteinLength;
    }

    int SnpEffAnnotation::getDistanceToFeature() const
    {
        return privateDistanceToFeature;
    }

    std::vector<std::string> SnpEffAnnotation::getWarnings() const
    {
        return privateWarnings;
    }

    int SnpEffAnnotation::getAminoAcidLocation() const
    {
        return privateAminoAcidLocation;
    }

    char SnpEffAnnotation::getReferenceAminoAcid() const
    {
        return privateReferenceAminoAcid;
    }

    char SnpEffAnnotation::getAlternateAminoAcid() const
    {
        return privateAlternateAminoAcid;
    }

    bool SnpEffAnnotation::getMissense() const
    {
        return privateMissense;
    }

    bool SnpEffAnnotation::getSynonymous() const
    {
        return privateSynonymous;
    }

    bool SnpEffAnnotation::getFrameshiftVariant() const
    {
        return privateFrameshiftVariant;
    }

    bool SnpEffAnnotation::getBadTranscript() const
    {
        return privateBadTranscript;
    }

    SnpEffAnnotation::SnpEffAnnotation(const std::string &annotation)
    {
        bool isSnpEffAnnotation = StringHelper::startsWith(annotation, "ANN=") || StringHelper::startsWith(annotation, "EFF=");
        Annotation = isSnpEffAnnotation ? annotation.substr(4) : annotation;
        if (!isSnpEffAnnotation)
        {
            return;
        }
        std::vector<std::string> a = StringHelper::split(getAnnotation(), '|');
        Allele = a[0];
        Effects = StringHelper::split(a[1], '&');
        PutativeImpact = a[2];
        GeneName = a[3];
        GeneID = a[4];
        FeatureType = a[5];
        FeatureID = a[6];
        TranscriptBiotype = a[7];
        int x;
        if (StringHelper::split(a[8], '/')->length() > 0 && int::TryParse(StringHelper::split(a[8], '/')[0], x))
        {
            ExonIntronRank = x;
        }
        int y;
        if (StringHelper::split(a[8], '/')->length() > 1 && int::TryParse(StringHelper::split(a[8], '/')[1], y))
        {
            ExonIntronTotal = y;
        }
        HGVSNotationDnaLevel = a[9];
        HGVSNotationProteinLevel = a[10];
        if (StringHelper::split(a[11], '/')->length() > 0 && int::TryParse(StringHelper::split(a[11], '/')[0], x))
        {
            OneBasedTranscriptCDNAPosition = x;
        }
        if (StringHelper::split(a[11], '/')->length() > 1 && int::TryParse(StringHelper::split(a[11], '/')[1], y))
        {
            TranscriptCDNALength = y;
        }
        if (StringHelper::split(a[12], '/')->length() > 0 && int::TryParse(StringHelper::split(a[12], '/')[0], x))
        {
            OneBasedCodingDomainSequencePosition = x;
        }
        if (StringHelper::split(a[12], '/')->length() > 1 && int::TryParse(StringHelper::split(a[12], '/')[1], y))
        {
            CodingDomainSequenceLengthIncludingStopCodon = y;
        }
        if (StringHelper::split(a[13], '/')->length() > 0 && int::TryParse(StringHelper::split(a[13], '/')[0], x))
        {
            OneBasedProteinPosition = x;
        }
        if (StringHelper::split(a[13], '/')->length() > 1 && int::TryParse(StringHelper::split(a[13], '/')[1], y))
        {
            ProteinLength = y;
        }
        if (int::TryParse(a[14], y))
        {
            DistanceToFeature = y;
        }
        Warnings = StringHelper::split(a[15], '&');

        Missense = getEffects().Any([&] (std::any eff)
        {
            return eff == "missense_variant";
        });
        Synonymous = !getEffects().Any([&] (std::any eff)
        {
            NonSynonymousVariations.Contains(eff);
        });
        FrameshiftVariant = getEffects().Contains("frameshift_variant");
        BadTranscript = getWarnings().Any([&] (std::any w)
        {
            BadTranscriptWarnings.Contains(w);
        });
    }
}
