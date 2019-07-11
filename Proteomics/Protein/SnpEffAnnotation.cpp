#include "SnpEffAnnotation.h"


namespace Proteomics
{

    // Regex *const SnpEffAnnotation::HGVSProteinRegex = new Regex(R"((p\.)([A-Z][a-z][a-z])(\d+)([A-Z][a-z][a-z]))");

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
        privateAnnotation = isSnpEffAnnotation ? annotation.substr(4) : annotation;
        if (!isSnpEffAnnotation)
        {
            return;
        }
        std::vector<std::string> a = StringHelper::split(getAnnotation(), '|');
        privateAllele = a[0];
        privateEffects = StringHelper::split(a[1], '&');
        privatePutativeImpact = a[2];
        privateGeneName = a[3];
        privateGeneID = a[4];
        privateFeatureType = a[5];
        privateFeatureID = a[6];
        privateTranscriptBiotype = a[7];
        int x;

#ifdef ORIG        
        if (StringHelper::split(a[8], '/')->length() > 0 && int::TryParse(StringHelper::split(a[8], '/')[0], x))
        {
            privateExonIntronRank = x;
        }
#endif
        std::vector<std::string> v8 = StringHelper::split(a[8], '/');
        if ( v8.size() > 0 && (x = std::stoi(v8[0])) ){
            privateExonIntronRank = x;
        }
            
        int y;
#ifdef ORIG
        if (StringHelper::split(a[8], '/')->length() > 1 && int::TryParse(StringHelper::split(a[8], '/')[1], y))
        {
            privateExonIntronTotal = y;
        }
#endif
        if ( v8.size() > 1 && (y = std::stoi(v8[1])) ){
            privateExonIntronTotal = y;
        }
        
        privateHGVSNotationDnaLevel = a[9];
        privateHGVSNotationProteinLevel = a[10];

#ifdef ORIG
        if (StringHelper::split(a[11], '/')->length() > 0 && int::TryParse(StringHelper::split(a[11], '/')[0], x))
        {
            privateOneBasedTranscriptCDNAPosition = x;
        }
        if (StringHelper::split(a[11], '/')->length() > 1 && int::TryParse(StringHelper::split(a[11], '/')[1], y))
        {
            privateTranscriptCDNALength = y;
        }
#endif
        std::vector<std::string> v11 = StringHelper::split(a[11], '/');
        if ( v11.size() > 0 && (x = std::stoi(v11[0])) ){
            privateOneBasedTranscriptCDNAPosition = x;
        }
        if ( v11.size() > 1 && (x = std::stoi(v11[1])) ){
            privateTranscriptCDNALength = y;
        }

#ifdef ORIG
        if (StringHelper::split(a[12], '/')->length() > 0 && int::TryParse(StringHelper::split(a[12], '/')[0], x))
        {
            privateOneBasedCodingDomainSequencePosition = x;
        }
        if (StringHelper::split(a[12], '/')->length() > 1 && int::TryParse(StringHelper::split(a[12], '/')[1], y))
        {
            privateCodingDomainSequenceLengthIncludingStopCodon = y;
        }
#endif
        std::vector<std::string> v12 = StringHelper::split(a[12], '/');
        if ( v12.size() > 0 && (x = std::stoi(v12[0])) ){
            privateOneBasedCodingDomainSequencePosition = x;
        }
        if ( v12.size() > 1 && (x = std::stoi(v12[1])) ){
            privateCodingDomainSequenceLengthIncludingStopCodon = y;
        }

#ifdef ORIG
        if (StringHelper::split(a[13], '/')->length() > 0 && int::TryParse(StringHelper::split(a[13], '/')[0], x))
        {
            privateOneBasedProteinPosition = x;
        }
        if (StringHelper::split(a[13], '/')->length() > 1 && int::TryParse(StringHelper::split(a[13], '/')[1], y))
        {
            privateProteinLength = y;
        }
#endif
        std::vector<std::string> v13 = StringHelper::split(a[13], '/');
        if ( v13.size() > 0 && (x = std::stoi(v13[0])) ){
            privateOneBasedProteinPosition = x;
        }
        if ( v13.size() > 1 && (x = std::stoi(v13[1])) ){
            privateProteinLength = y;
        }

        if ( (y = std::stoi(a[14])) )
        {
            privateDistanceToFeature = y;
        }
        privateWarnings = StringHelper::split(a[15], '&');

#ifdef ORIG
        privateMissense = getEffects().Any([&] (std::any eff)
        {
            return eff == "missense_variant";
        });
#endif
        for ( auto eff : getEffects() ) {
            if ( eff == "missense_variant" ) {
                privateMissense = true;
            }
        }

#ifdef ORIG
        privateSynonymous = !getEffects().Any([&] (std::any eff)
        {
            NonSynonymousVariations.Contains(eff);
        });
#endif
        for ( auto eff : getEffects() ) {
            for ( auto bff : NonSynonymousVariations ) {
                auto found = bff.find(eff);
                if ( found !=std::string::npos ) {                    
                    privateSynonymous = true;
                    break;
                }
            }
        }
        
#ifdef ORIG
        privateFrameshiftVariant = getEffects().Contains("frameshift_variant");
#endif
        for ( auto eff : getEffects() ) {
            if ( eff == "frameshift_variant" ) {
                 privateFrameshiftVariant= true;
            }
        }

#ifdef ORIG
        privateBadTranscript = getWarnings().Any([&] (std::any w)
        {
            BadTranscriptWarnings.Contains(w);
        });
#endif
        for ( auto w: getWarnings() ) {
            for ( auto n: BadTranscriptWarnings ) {
                auto found = n.find(w);
                if ( found != std::string::npos) {
                    privateBadTranscript = true;
                    break;
                }
            }
        }
        
    }
}
