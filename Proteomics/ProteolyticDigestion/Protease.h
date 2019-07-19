#pragma once

#include "CleavageSpecificity.h"
#include "InitiatorMethionineBehavior.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <any>
#include <optional>
#include "exceptionhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { namespace ProteolyticDigestion { class DigestionMotif; } }
#include "DigestionMotif.h"
namespace Proteomics { class Protein; }

namespace Proteomics { namespace ProteolyticDigestion { class ProteolyticPeptide; } }
//#include "ProteolyticPeptide.h"

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class Protease
        {
        private:
            std::string privateName;
            Proteomics::ProteolyticDigestion::CleavageSpecificity privateCleavageSpecificity = static_cast<Proteomics::ProteolyticDigestion::CleavageSpecificity>(0);
            std::string privatePsiMsAccessionNumber;
            std::string privatePsiMsName;
            std::vector<DigestionMotif*> privateDigestionMotifs;

        public:
            Protease(const std::string &name, Proteomics::ProteolyticDigestion::CleavageSpecificity cleavageSpecificity, const std::string &psiMSAccessionNumber, const std::string &psiMSName, std::vector<DigestionMotif*> &motifList);

                std::string getName() const;
                Proteomics::ProteolyticDigestion::CleavageSpecificity getCleavageSpecificity() const;
                std::string getPsiMsAccessionNumber() const;
                std::string getPsiMsName() const;
                std::vector<DigestionMotif*> getDigestionMotifs() const;

                std::string ToString();
                bool Equals(Protease *a);
                int GetHashCode();

                Proteomics::ProteolyticDigestion::CleavageSpecificity GetCleavageSpecificity(const std::string &proteinSequence, int startIndex, int endIndex);

            /// <summary>
            /// Gets intervals of a protein sequence that will result from digestion by this protease.
            /// </summary>
            /// <param name="protein"></param>
            /// <param name="maximumMissedCleavages"></param>
            /// <param name="initiatorMethionineBehavior"></param>
            /// <param name="minPeptidesLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
            std::vector<ProteolyticPeptide*> GetUnmodifiedPeptides(Protein *protein, int maximumMissedCleavages, InitiatorMethionineBehavior initiatorMethionineBehavior, int minPeptidesLength, int maxPeptidesLength);

            /// <summary>
            /// Gets the indices after which this protease will cleave a given protein sequence
            /// </summary>
            /// <param name="proteinSequence"></param>
            /// <returns></returns>
            std::vector<int> GetDigestionSiteIndices(const std::string &proteinSequence);

            /// <summary>
            /// Retain N-terminal residue?
            /// </summary>
            /// <param name="oneBasedCleaveAfter"></param>
            /// <param name="initiatorMethionineBehavior"></param>
            /// <param name="nTerminus"></param>
            /// <returns></returns>
            static bool Retain(int oneBasedCleaveAfter, InitiatorMethionineBehavior initiatorMethionineBehavior, char nTerminus);

            /// <summary>
            /// Cleave N-terminal residue?
            /// </summary>
            /// <param name="oneBasedCleaveAfter"></param>
            /// <param name="initiatorMethionineBehavior"></param>
            /// <param name="nTerminus"></param>
            /// <returns></returns>
            static bool Cleave(int oneBasedCleaveAfter, InitiatorMethionineBehavior initiatorMethionineBehavior, char nTerminus);

            /// <summary>
            /// Is length of given peptide okay, given minimum and maximum?
            /// </summary>
            /// <param name="peptideLength"></param>
            /// <param name="minPeptidesLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
            static bool OkayLength(std::optional<int> peptideLength, std::optional<int> minPeptidesLength, std::optional<int> maxPeptidesLength);

            /// <summary>
            /// Gets protein intervals for digestion by this specific protease.
            /// </summary>
            /// <param name="protein"></param>
            /// <param name="initiatorMethionineBehavior"></param>
            /// <param name="maximumMissedCleavages"></param>
            /// <param name="minPeptidesLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
        private:
            std::vector<ProteolyticPeptide*> FullDigestion(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior, int maximumMissedCleavages, int minPeptidesLength, int maxPeptidesLength);

            /// <summary>
            /// Gets the protein intervals based on semiSpecific digestion rules
            /// This is the classic, slow semi-specific digestion that generates each semi-specific peptide pre-search
            /// </summary>
            /// <param name="protein"></param>
            /// <param name="initiatorMethionineBehavior"></param>
            /// <param name="maximumMissedCleavages"></param>
            /// <param name="minPeptidesLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
            std::vector<ProteolyticPeptide*> SemiProteolyticDigestion(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior, int maximumMissedCleavages, int minPeptidesLength, int maxPeptidesLength);

            /// <summary>
            /// Get protein intervals for fixed termini.
            /// This is used for the classic, slow semi-proteolytic cleavage that generates each semi-specific peptides pre-search.
            /// </summary>
            /// <param name="nTerminusProtein"></param>
            /// <param name="cTerminusProtein"></param>
            /// <param name="protein"></param>
            /// <param name="cleave"></param>
            /// <param name="minPeptidesLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
            static std::vector<ProteolyticPeptide*> FixedTermini(int nTerminusProtein, int cTerminusProtein, Protein *protein, bool cleave, bool retain, int minPeptidesLength, int maxPeptidesLength, std::unordered_set<int> &localOneBasedIndicesToCleaveAfter);

            /// <summary>
            /// Is length of given peptide okay, given minimum?
            /// </summary>
            /// <param name="peptideLength"></param>
            /// <param name="minPeptidesLength"></param>
            /// <returns></returns>
            static bool OkayMinLength(std::optional<int> peptideLength, std::optional<int> minPeptidesLength);

            /// <summary>
            /// Is length of given peptide okay, given maximum?
            /// </summary>
            /// <param name="peptideLength"></param>
            /// <param name="maxPeptidesLength"></param>
            /// <returns></returns>
            static bool OkayMaxLength(std::optional<int> peptideLength, std::optional<int> maxPeptidesLength);
        };
    }
}
