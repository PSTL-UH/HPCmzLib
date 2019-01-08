#include "Peptide.h"
#include "Residue.h"
#include "OldSchoolModificationWithMultiplePossibilities.h"


namespace Proteomics {

    Peptide::Peptide() {
    }

    Peptide::Peptide(const std::string &sequence) : AminoAcidPolymer(sequence) {
    }

    Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer) : Peptide(aminoAcidPolymer, true) {
    }

    Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, bool includeModifications) : AminoAcidPolymer(aminoAcidPolymer, includeModifications) {
        setParent(aminoAcidPolymer);
        setStartResidue(0);
        setEndResidue(getLength() - 1);
    }

    Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length) : Peptide(aminoAcidPolymer, firstResidue, length, true) {
    }

    Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length, bool includeModifications) : AminoAcidPolymer(aminoAcidPolymer, firstResidue, length, includeModifications) {
        setParent(aminoAcidPolymer);
        setStartResidue(firstResidue);
        setEndResidue(firstResidue + length - 1);
        setPreviousResidue(aminoAcidPolymer->GetResidue(getStartResidue() - 1));
        setNextResidue(aminoAcidPolymer->GetResidue(getEndResidue() + 1));
    }

    int Peptide::getStartResidue() const {
        return privateStartResidue;
    }

    void Peptide::setStartResidue(int value) {
        privateStartResidue = value;
    }

    int Peptide::getEndResidue() const {
        return privateEndResidue;
    }

    void Peptide::setEndResidue(int value) {
        privateEndResidue = value;
    }

    AminoAcidPolymer *Peptide::getParent() const {
        return privateParent;
    }

    void Peptide::setParent(AminoAcidPolymer *value) {
        privateParent = value;
    }

    Residue *Peptide::getPreviousResidue() const {
        return privatePreviousResidue;
    }

    void Peptide::setPreviousResidue(Residue *value) {
        privatePreviousResidue = value;
    }

    Residue *Peptide::getNextResidue() const {
        return privateNextResidue;
    }

    void Peptide::setNextResidue(Residue *value) {
        privateNextResidue = value;
    }

    std::vector<Peptide*> Peptide::GenerateAllModificationCombinations() {
        // Get all the modifications that are isotopologues
        auto isotopologues = GetUniqueModifications<ModificationWithMultiplePossibilitiesCollection*>()->ToArray();

        // Base condition, no more isotopologues to make, so just return
        if (isotopologues.size() < 1) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield break;
        }

        // Grab the the first isotopologue
        ModificationWithMultiplePossibilitiesCollection *isotopologue = isotopologues[0];

        // Loop over each modification in the isotopologue
        for (auto mod : isotopologue) {
            // Create a clone of the peptide, cloning modifications as well.
            Peptide *peptide = new Peptide(this);

            // Replace the base isotopologue mod with the specific version
            peptide->ReplaceModification(isotopologue, mod);

            // There were more than one isotopologue, so we must go deeper
            if (isotopologues.size() > 1) {
                // Call the same rotuine on the newly generate peptide that has one less isotopologue
                for (auto subpeptide : peptide->GenerateAllModificationCombinations()) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return subpeptide;
                }
            }
            else {
                // Return this peptide
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return peptide;
            }

            delete peptide;
        }
    }

    Peptide *Peptide::GetSubPeptide(int firstResidue, int length) {
        return new Peptide(this, firstResidue, length);
    }
}
