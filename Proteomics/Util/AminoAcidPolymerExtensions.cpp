#include "AminoAcidPolymerExtensions.h"
#include "../AminoAcidPolymer.h"


namespace Proteomics {

    double AminoAcidPolymerExtensions::GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences) {
        return GetSequenceCoverageFraction(baseSequence, sequences, true);
    }

    double AminoAcidPolymerExtensions::GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences, bool useLeucineSequence) {
        std::vector<int> counts = baseSequence->GetSequenceCoverage(sequences, useLeucineSequence);
        return (static_cast<double>(counts.Count([&] (std::any x) {
            return x > 0;
        }))) / baseSequence->getLength();
    }

    std::vector<int> AminoAcidPolymerExtensions::GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences) {
        return GetSequenceCoverage(baseSequence, sequences, true);
    }

    std::vector<int> AminoAcidPolymerExtensions::GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &allPolymers, bool useLeucineSequence) {
        std::vector<int> bits(baseSequence->getLength());

        std::wstring masterSequence = useLeucineSequence ? baseSequence->getBaseLeucineSequence() : baseSequence->getBaseSequence();

        for (auto polymer : allPolymers) {
            std::wstring seq = useLeucineSequence ? polymer->getBaseLeucineSequence() : polymer->getBaseSequence();

            int startIndex = 0;
            while (true) {
                int index = (int)masterSequence.find(seq, startIndex, StringComparison::Ordinal);

                if (index < 0) {
                    break;
                }

                for (int aa = index; aa < index + polymer->getLength(); aa++) {
                    bits[aa]++;
                }

                startIndex = index + 1;
            }
        }
        return bits;
    }
}
