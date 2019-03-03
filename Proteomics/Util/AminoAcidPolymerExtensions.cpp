#include "AminoAcidPolymerExtensions.h"
#include "../AminoAcidPolymer.h"


namespace Proteomics {

    double AminoAcidPolymerExtensions::GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences) {
        return GetSequenceCoverageFraction(baseSequence, sequences, true);
    }

    double AminoAcidPolymerExtensions::GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences, bool useLeucineSequence) {
//        std::vector<int> counts = baseSequence->GetSequenceCoverage(sequences, useLeucineSequence);
        std::vector<int> counts = GetSequenceCoverage(baseSequence, sequences, useLeucineSequence);
        int counter=0;
        for ( auto x : counts )  {
            if ( x > 0 ) {
                counter++;
            }
        }
        return (static_cast<double>(counter)/baseSequence->getLength());
    }

    std::vector<int> AminoAcidPolymerExtensions::GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences) {
        return GetSequenceCoverage(baseSequence, sequences, true);
    }

    std::vector<int> AminoAcidPolymerExtensions::GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &allPolymers, bool useLeucineSequence) {
        std::vector<int> bits(baseSequence->getLength());

        std::string masterSequence = useLeucineSequence ? baseSequence->getBaseLeucineSequence() : baseSequence->getBaseSequence();

        for (auto polymer : allPolymers) {
            std::string seq = useLeucineSequence ? polymer->getBaseLeucineSequence() : polymer->getBaseSequence();

            int startIndex = 0;
            while (true) {
//                int index = (int)masterSequence.find(seq, startIndex, StringComparison::Ordinal);
                int index = (int)masterSequence.find(seq, startIndex);

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
