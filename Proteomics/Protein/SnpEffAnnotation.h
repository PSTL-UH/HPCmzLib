#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "stringhelper.h"


namespace Proteomics
{
    /// <summary>
    /// Specifications are described here: http://snpeff.sourceforge.net/VCFannotationformat_v1.0.pdf
    /// </summary>
    class SnpEffAnnotation
    {
    private:
        std::string privateAnnotation;
        std::string privateAllele;
        std::vector<std::string> privateEffects;
        std::string privatePutativeImpact;
        std::string privateGeneName;
        std::string privateGeneID;
        std::string privateFeatureType;
        std::string privateFeatureID;
        std::string privateTranscriptBiotype;
        int privateExonIntronRank = 0;
        int privateExonIntronTotal = 0;
        std::string privateHGVSNotationDnaLevel;
        std::string privateHGVSNotationProteinLevel;
        int privateOneBasedTranscriptCDNAPosition = 0;
        int privateTranscriptCDNALength = 0;
        int privateOneBasedCodingDomainSequencePosition = 0;
        int privateCodingDomainSequenceLengthIncludingStopCodon = 0;
        int privateOneBasedProteinPosition = 0;
        int privateProteinLength = 0;
        int privateDistanceToFeature = 0;
        std::vector<std::string> privateWarnings;
        int privateAminoAcidLocation = 0;
        char privateReferenceAminoAcid = '\0';
        char privateAlternateAminoAcid = '\0';
        bool privateMissense = false;
        bool privateSynonymous = false;
        bool privateFrameshiftVariant = false;
        bool privateBadTranscript = false;

        //static Regex *const HGVSProteinRegex;

        /// <summary>
        /// Original SnpEff annotation string.
        /// </summary>
    public:
        std::string getAnnotation() const;

        std::string getAllele() const;
        std::vector<std::string> getEffects() const;
        std::string getPutativeImpact() const;
        std::string getGeneName() const;
        std::string getGeneID() const;

        /// <summary>
        /// It looks like these are sometimes domains, like the ones annotated in UniProt,
        /// Otherwise, this tends to just be "transcript"
        ///
        /// Some examples:
        /// sequence_feature: can be initiator-methionine:Removed ... maybe not too helpful for proteomics, since this is assumed
        /// sequence_feature: helix:combinatorial_evidence_used_in_manual_assertion
        /// sequence_feature: nucleotide-phosphate-binding-region:ATP
        /// sequence_feature: domain:EGF-like_2
        /// sequence_feature: transmembrane-region:Transmembrane_region
        /// sequence_feature: topological-domain:Extracellular
        /// sequence_feature: modified-residue:phosphoserine
        /// </summary>
        std::string getFeatureType() const;

        /// <summary>
        /// Always seems to be the transcriptID
        /// </summary>
        std::string getFeatureID() const;

        std::string getTranscriptBiotype() const;
        int getExonIntronRank() const;
        int getExonIntronTotal() const;
        std::string getHGVSNotationDnaLevel() const;
        std::string getHGVSNotationProteinLevel() const;
        int getOneBasedTranscriptCDNAPosition() const;
        int getTranscriptCDNALength() const;
        int getOneBasedCodingDomainSequencePosition() const;
        int getCodingDomainSequenceLengthIncludingStopCodon() const;
        int getOneBasedProteinPosition() const;
        int getProteinLength() const;

        /// <summary>
        /// up/downstream: distance to first / last codon
        /// intergenic: distance to closest gene
        /// exonic: distance to closest intron boundary (+ is upstream, - is downstream)
        /// intronic: distance to closest exon boundary (+ is upstream, - is downstream)
        /// motif: distance to first base in MOTIF
        /// miRNA: distance to first base in miRNA
        /// splice_site: distance to exon-intron boundary
        /// splice_region: distance to exon-intron boundary
        /// chip seq peak: distance to summit or peak center
        /// histone mark/state: distance to summit or peak center
        /// </summary>
        int getDistanceToFeature() const;

        std::vector<std::string> getWarnings() const;

        int getAminoAcidLocation() const;
        char getReferenceAminoAcid() const;
        char getAlternateAminoAcid() const;
        bool getMissense() const;
        bool getSynonymous() const;
        bool getFrameshiftVariant() const;
        bool getBadTranscript() const;

        SnpEffAnnotation(const std::string &annotation);

    private:
        std::vector<std::string> HighPutativeImpactEffects = {"chromosome_number_variation", "exon_loss_variant", "frameshift_variant", "rare_amino_acid_variant", "splice_acceptor_variant", "splice_donor_variant", "start_lost", "stop_gained", "stop_lost", "transcript_ablation"};

        std::vector<std::string> ModeratePutativeImpactEffects = {"3_prime_UTR_truncation", "exon_loss", "5_prime_UTR_truncation", "exon_loss_variant", "coding_sequence_variant", "conservative_inframe_insertion", "conservative_inframe_deletion", "disruptive_inframe_deletion", "disruptive_inframe_insertion", "inframe_deletion", "inframe_insertion", "missense_variant", "regulatory_region_ablation", "splice_region_variant", "TFBS_ablation"};

        std::vector<std::string> NonSynonymousVariations = {"exon_loss_variant", "frameshift_variant", "rare_amino_acid_variant", "start_lost", "stop_gained", "stop_lost", "conservative_inframe_insertion", "conservative_inframe_deletion", "disruptive_inframe_deletion", "disruptive_inframe_insertion", "inframe_deletion", "inframe_insertion", "missense_variant"};

        std::vector<std::string> LowPutativeImpactEffects = {"5_prime_UTR_premature_start_codon_gain_variant", "initiator_codon_variant", "splice_region_variant", "start_retained", "stop_retained_variant", "synonymous_variant", "sequence_feature"};

        std::vector<std::string> ModifierEffects = {"3_prime_UTR_variant", "5_prime_UTR_variant", "coding_sequence_variant", "conserved_intergenic_variant", "conserved_intron_variant", "downstream_gene_variant", "exon_variant", "feature_elongation", "feature_truncation", "gene_variant", "intergenic_region", "intragenic_variant", "intron_variant", "mature_miRNA_variant", "miRNA", "NMD_transcript_variant", "non_coding_transcript_exon_variant", "non_coding_transcript_variant", "regulatory_region_amplification", "regulatory_region_variant", "TF_binding_site_variant", "TFBS_amplification", "transcript_amplification", "transcript_variant", "upstream_gene_variant"};

        std::vector<std::string> BadTranscriptWarnings = {"WARNING_TRANSCRIPT_INCOMPLETE", "WARNING_TRANSCRIPT_MULTIPLE_STOP_CODONS", "WARNING_TRANSCRIPT_NO_STOP_CODON", "WARNING_TRANSCRIPT_NO_START_CODON"};

        /// <summary>
        /// It looks like WARNING_TRANSCRIPT_INCOMPLETE, WARNING_TRANSCRIPT_MULTIPLE_STOP_CODONS,
        /// WARNING_TRANSCRIPT_NO_STOP_CODON, and WARNING_TRANSCRIPT_NO_START_CODON are relevant to this program.
        ///
        /// These are the ones that I shouldn't be translating.
        ///
        /// Could also be used for error messages regarding certain transcripts.
        /// </summary>
    public:
        std::unordered_map<std::string, std::string> SnpEffWarningDescriptions = std::unordered_map<std::string, std::string>
        {
            {"ERROR_CHROMOSOME_NOT_FOUND", "Chromosome does not exists in reference genome database."},
            {"ERROR_OUT_OF_CHROMOSOME_RANGE", "The variant’s genomic coordinate is greater than chromosome's length."},
            {"WARNING_REF_DOES_NOT_MATCH_GENOME", "This means that the ‘REF’ field in the input VCF file does not match the reference genome."},
            {"WARNING_SEQUENCE_NOT_AVAILABLE", "Reference sequence is not available, thus no inference could be performed."},
            {"WARNING_TRANSCRIPT_INCOMPLETE", "A protein coding transcript having a non­multiple of 3 length, indicating that the reference genome has missing information about this trancript."},
            {"WARNING_TRANSCRIPT_MULTIPLE_STOP_CODONS", "A protein coding transcript has two or more STOP codons in the middle of the coding sequence (CDS). This should not happen and it usually means the reference genome may have an error in this transcript."},
            {"WARNING_TRANSCRIPT_NO_START_CODON", "A protein coding transcript does not have a proper START codon. It is rare that a real transcript does not have a START codon, so this probably indicates an error or missing information in the reference genome."},
            {"WARNING_TRANSCRIPT_NO_STOP_CODON", "A protein coding transcript does not have a proper STOP codon. It is rare that a real transcript does not have a STOP codon, so this probably indicates an error or missing information in the reference genome."},
            {"INFO_REALIGN_3_PRIME", "Variant has been realigned to the most 3­-prime position within the transcript. This is usually done to to comply with HGVS specification to always report the most 3-­prime annotation."},
            {"INFO_COMPOUND_ANNOTATION", "This effect is a result of combining more than one variants."},
            {"INFO_NON_REFERENCE_ANNOTATION", "An alternative reference sequence was used to calculate this annotation."}
        };
    };
}
