#include "AminoAcidPolymer.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "Residue.h"
#include "../Chemistry/ChemicalFormula.h"
#include "ChemicalFormulaTerminus.h"
#include "Fragment.h"
#include "DigestionPoint.h"
#include "Interfaces/IProtease.h"
#include "../Chemistry/Isotope.h"
#include "../MzLibUtil/MzLibException.h"
#include "ChemicalFormulaFragment.h"
#include "OldSchoolModification.h"
#include "ModificationCollection.h"
#include "ChemicalFormulaModification.h"

include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {

    AminoAcidPolymer::AminoAcidPolymer() : AminoAcidPolymer(ChemicalFormula::ParseFormula("H")) {
    }

    AminoAcidPolymer::AminoAcidPolymer(const std::string &sequence) : AminoAcidPolymer(ChemicalFormula::ParseFormula("H")) {
    }

    AminoAcidPolymer::AminoAcidPolymer(const std::string &sequence, IHasChemicalFormula *nTerm, IHasChemicalFormula *cTerm) {
        setMonoisotopicMass(0);
        setLength(sequence.length());
        residues = std::vector<Residue*>(getLength());
        setNTerminus(nTerm);
        setCTerminus(cTerm);
        ParseSequence(sequence);
    }

    AminoAcidPolymer::AminoAcidPolymer(AminoAcidPolymer *aminoAcidPolymer, bool includeModifications) : AminoAcidPolymer(aminoAcidPolymer, 0, aminoAcidPolymer->getLength(), includeModifications) {
    }

    AminoAcidPolymer::AminoAcidPolymer(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length, bool includeModifications) {
        setLength(length);
        residues = std::vector<Residue*>(length);

        bool isNterm = firstResidue == 0;
        bool isCterm = length + firstResidue == aminoAcidPolymer->getLength();

        _nTerminus = isNterm ? aminoAcidPolymer->getNTerminus() : new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("H"));
        _cTerminus = isCterm ? aminoAcidPolymer->getCTerminus() : new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("OH"));

        double monoMass = _nTerminus->getMonoisotopicMass() + _cTerminus->getMonoisotopicMass();

        std::vector<Residue*> otherAminoAcids = aminoAcidPolymer->residues;

        if (includeModifications && aminoAcidPolymer->ContainsModifications()) {
            _modifications = std::vector<IHasMass*>(length + 2);
            for (int i = 0; i < length; i++) {
                auto aa = otherAminoAcids[i + firstResidue];
                residues[i] = aa;
                monoMass += aa->getMonoisotopicMass();

                IHasMass *mod = aminoAcidPolymer->_modifications[i + firstResidue + 1];
                if (mod == nullptr) {
                    continue;
                }

                _modifications[i + 1] = mod;
                monoMass += mod->getMonoisotopicMass();
            }
        }
        else {
            for (int i = 0, j = firstResidue; i < length; i++, j++) {
                auto aa = otherAminoAcids[j];
                residues[i] = aa;
                monoMass += aa->getMonoisotopicMass();
            }
        }

        setMonoisotopicMass(monoMass);

        if (includeModifications) {
            if (isNterm) {
                setNTerminusModification(aminoAcidPolymer->getNTerminusModification());
            }

            if (isCterm) {
                setCTerminusModification(aminoAcidPolymer->getCTerminusModification());
            }
        }
    }

    ReadOnlyCollection<IHasMass*> *AminoAcidPolymer::getModifications() const {
        return new ReadOnlyCollection<IHasMass*>(_modifications);
    }

    IHasChemicalFormula *AminoAcidPolymer::getCTerminus() const {
        return _cTerminus;
    }

    void AminoAcidPolymer::setCTerminus(IHasChemicalFormula *value) {
        ReplaceTerminus(_cTerminus, value);
    }

    IHasChemicalFormula *AminoAcidPolymer::getNTerminus() const {
        return _nTerminus;
    }

    void AminoAcidPolymer::setNTerminus(IHasChemicalFormula *value) {
        ReplaceTerminus(_nTerminus, value);
    }

    int AminoAcidPolymer::getLength() const {
        return privateLength;
    }

    void AminoAcidPolymer::setLength(int value) {
        privateLength = value;
    }

    double AminoAcidPolymer::getMonoisotopicMass() const {
        return privateMonoisotopicMass;
    }

    void AminoAcidPolymer::setMonoisotopicMass(double value) {
        privateMonoisotopicMass = value;
    }

    std::string AminoAcidPolymer::getBaseLeucineSequence() const {
        return StringHelper::replace(getBaseSequence(), L'I', L'L');
    }

    std::string AminoAcidPolymer::getBaseSequence() const {
        return std::string(residues.Select([&] (std::any aa) {
            aa::Letter;
        })->ToArray());
    }

    IHasMass *AminoAcidPolymer::getCTerminusModification() const {
        return GetModification(getLength() + 1);
    }

    void AminoAcidPolymer::setCTerminusModification(IHasMass *value) {
        ReplaceMod(getLength() + 1, value);
    }

    IHasMass *AminoAcidPolymer::getNTerminusModification() const {
        return GetModification(0);
    }

    void AminoAcidPolymer::setNTerminusModification(IHasMass *value) {
        ReplaceMod(0, value);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::GetSiteDeterminingFragments(AminoAcidPolymer *peptideA, AminoAcidPolymer *peptideB, FragmentTypes types) {
        std::unordered_set<Proteomics::Fragment*> aFrags(peptideA->Fragment(types));
        aFrags.SymmetricExceptWith(peptideB->Fragment(types));
        return aFrags;
    }

    std::vector<DigestionPointAndLength*> AminoAcidPolymer::GetDigestionPointsAndLengths(const std::string &sequence, std::vector<IProtease*> &proteases, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
        std::vector<int> indices = GetCleavageIndexes(sequence, proteases).ToArray();

        bool includeMethionineCut = methionineInitiator && sequence[0] == L'M';

        int indiciesCount = indices.size() - 1;

        for (int missedCleavages = 0; missedCleavages <= maxMissedCleavages; missedCleavages++) {
            int max = indiciesCount - missedCleavages;
            int offset = missedCleavages + 1;
            for (int i = 0; i < max; i++) {
                int len = indices[i + offset] - indices[i];

                // Case for initiator methionine
                if (indices[i] == -1 && includeMethionineCut) {
                    int newLength = len - 1;
                    if (newLength >= minLength && newLength <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return new DigestionPointAndLength(1, newLength);
                        if (semiDigestion) {
                            for (int j = 1; j < newLength; j++) {
                                if (j >= minLength && j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                    yield return new DigestionPointAndLength(1, j);
                                }
                            }
                        }
                    }
                }

                if (len < minLength || len > maxLength) {
                    continue;
                }

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return new DigestionPointAndLength(indices[i] + 1, len);
                if (semiDigestion) {
                    for (int j = 1; j < len; j++) {
                        if (len - j >= minLength && len - j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            yield return new DigestionPointAndLength(indices[i] + 1 + j, len - j);
                        }
                        if (j >= minLength && j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            yield return new DigestionPointAndLength(indices[i] + 1, j);
                        }
                    }
                }
            }
        }
    }

    std::vector<int> AminoAcidPolymer::GetCleavageIndexes(const std::string &sequence, std::vector<IProtease*> &proteases) {
        return GetCleavageIndexes(sequence, proteases, true);
    }

    std::vector<int> AminoAcidPolymer::GetCleavageIndexes(const std::string &sequence, std::vector<IProtease*> &proteases, bool includeTermini) {
        // Combine all the proteases digestion sites
        std::set<int> locations;
        for (IProtease *protease : proteases.Where([&] (std::any protease) {
            return protease != nullptr;
        })) {
            locations.UnionWith(protease::GetDigestionSites(sequence));
        }

        if (!includeTermini) {
            return locations;
        }

        locations.insert(-1);
        locations.insert(sequence.length() - 1);

        return locations;
    }

    std::vector<std::string> AminoAcidPolymer::Digest(const std::string &sequence, std::vector<IProtease*> &proteases, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
        return GetDigestionPointsAndLengths(sequence, proteases, maxMissedCleavages, minLength, maxLength, methionineInitiator, semiDigestion).Select([&] (std::any points) {
            sequence.substr(points::Index, points->Length);
        });
    }

    std::vector<std::string> AminoAcidPolymer::Digest(AminoAcidPolymer *sequence, IProtease *protease) {
        return Digest(sequence, protease, 3, 1, std::numeric_limits<int>::max(), true, false);
    }

    std::vector<std::string> AminoAcidPolymer::Digest(AminoAcidPolymer *polymer, IProtease *protease, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
        return Digest(polymer->getBaseSequence(), {protease}, maxMissedCleavages, minLength, maxLength, methionineInitiator, semiDigestion);
    }

    Residue *AminoAcidPolymer::GetResidue(int position) {
        if (position < 0 || position >= getLength()) {
            return nullptr;
        }
        return residues[position];
    }

    bool AminoAcidPolymer::Contains(char residue) {
        return residues.Any([&] (std::any aa) {
            aa::Letter->Equals(residue);
        });
    }

    bool AminoAcidPolymer::Contains(Residue *residue) {
        return residues.Contains(residue);
    }

    std::string AminoAcidPolymer::GetSequenceWithModifications() {
        return GetSequenceWithModifications(false);
    }

    std::string AminoAcidPolymer::GetSequenceWithModifications(bool leucineSequence) {
        if (_modifications.empty()) {
            return (leucineSequence) ? getBaseLeucineSequence() : getBaseSequence();
        }

        StringBuilder *modSeqSb = new StringBuilder(getLength());

        IHasMass *mod;

        // Handle N-Terminus Modification
        if ((mod = _modifications[0]) != nullptr && mod->getMonoisotopicMass() > 0) {
            modSeqSb->append(L'[');
            modSeqSb->append(mod);
            modSeqSb->append("]-");
        }

        // Handle Amino Acid Residues
        for (int i = 0; i < getLength(); i++) {
            if (leucineSequence && residues[i]->getLetter() == L'I') {
                modSeqSb->append(L'L');
            }
            else {
                modSeqSb->append(residues[i]->getLetter());
            }

            // Handle Amino Acid Modification (1-based)
            if ((mod = _modifications[i + 1]) != nullptr && mod->getMonoisotopicMass() > 0) {
                modSeqSb->append(L'[');
                modSeqSb->append(mod);
                modSeqSb->append(L']');
            }
        }

        // Handle C-Terminus Modification
        if ((mod = _modifications[getLength() + 1]) != nullptr && mod->getMonoisotopicMass() > 0) {
            modSeqSb->append("-[");
            modSeqSb->append(mod);
            modSeqSb->append(L']');
        }

        delete modSeqSb;
        return modSeqSb->toString();
    }

    int AminoAcidPolymer::ResidueCount() {
        return getLength();
    }

    int AminoAcidPolymer::ResidueCount(Residue *aminoAcid) {
        return aminoAcid == nullptr ? 0 : residues.Count([&] (std::any aar) {
            aar->Equals(aminoAcid);
        });
    }

    int AminoAcidPolymer::ResidueCount(char residueLetter) {
        return residues.Count([&] (std::any aar) {
            aar::Letter->Equals(residueLetter);
        });
    }

    int AminoAcidPolymer::ResidueCount(char residueLetter, int index, int length) {
        return residues.SubArray(index, length)->Count([&] (std::any aar) {
            aar::Letter->Equals(residueLetter);
        });
    }

    int AminoAcidPolymer::ResidueCount(Residue *aminoAcid, int index, int length) {
        return residues.SubArray(index, length)->Count([&] (std::any aar) {
            aar->Equals(aminoAcid);
        });
    }

    int AminoAcidPolymer::ElementCountWithIsotopes(const std::string &element) {
        // Residues count
        int count = residues.Sum([&] (std::any aar) {
            aar::ThisChemicalFormula::CountWithIsotopes(element);
        });
        // Modifications count (if the mod is a IHasChemicalFormula)
        if (_modifications.size() > 0) {
            count += _modifications.Where([&] (std::any mod) {
                dynamic_cast<IHasChemicalFormula*>(mod) != nullptr;
            }).Cast<IHasChemicalFormula*>().Sum([&] (std::any mod) {
                mod::ThisChemicalFormula::CountWithIsotopes(element);
            });
        }

        count += ChemicalFormula::ParseFormula("H2O")->CountWithIsotopes(element);
        return count;
    }

    int AminoAcidPolymer::SpecificIsotopeCount(Isotope *isotope) {
        // Residues count
        int count = residues.Sum([&] (std::any aar) {
            aar::ThisChemicalFormula::CountSpecificIsotopes(isotope);
        });
        // Modifications count (if the mod is a IHasChemicalFormula)
        if (_modifications.size() > 0) {
            count += _modifications.Where([&] (std::any mod) {
                dynamic_cast<IHasChemicalFormula*>(mod) != nullptr;
            }).Cast<IHasChemicalFormula*>().Sum([&] (std::any mod) {
                mod::ThisChemicalFormula::CountSpecificIsotopes(isotope);
            });
        }
        return count;
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::GetSiteDeterminingFragments(AminoAcidPolymer *other, FragmentTypes type) {
        return GetSiteDeterminingFragments(this, other, type);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types) {
        return Fragment(types, false);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, bool calculateChemicalFormula) {
        return Fragment(types, 1, getLength() - 1, calculateChemicalFormula);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int number) {
        return Fragment(types, number, false);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int number, bool calculateChemicalFormula) {
        return Fragment(types, number, number, calculateChemicalFormula);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int minIndex, int maxIndex) {
        return Fragment(types, minIndex, maxIndex, false);
    }

    std::vector<Proteomics::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int minIndex, int maxIndex, bool calculateChemicalFormula) {
        for (FragmentTypes type : types::GetIndividualFragmentTypes()) {
            bool isChemicalFormula = calculateChemicalFormula;
            ChemicalFormula *capFormula = type::GetIonCap();
            bool isCTerminal = type::GetTerminus() == Terminus::C;

            double monoMass = capFormula->getMonoisotopicMass();
            ChemicalFormula *formula = new ChemicalFormula(capFormula);

            IHasChemicalFormula *terminus = isCTerminal ? getCTerminus() : getNTerminus();
            monoMass += terminus->getMonoisotopicMass();
            if (isChemicalFormula) {
                formula->Add(terminus);
            }

            bool first = true;
            bool hasMod = _modifications.size() > 0;

            for (int i = 0; i <= maxIndex; i++) {
                int aaIndex = isCTerminal ? getLength() - i : i - 1;

                // Handle the terminus mods first in a special case
                IHasMass *mod;
                if (first) {
                    first = false;
                    if (hasMod) {
                        mod = _modifications[aaIndex + 1];
                        if (mod != nullptr) {
                            monoMass += mod->getMonoisotopicMass();
                            if (isChemicalFormula) {
//C# TO C++ CONVERTER TODO TASK: C++ has no equivalent to C# pattern variables in 'is' expressions:
//ORIGINAL LINE: if (mod is IHasChemicalFormula modFormula)
                                if (dynamic_cast<IHasChemicalFormula*>(mod) != nullptr modFormula) {
                                    formula->Add(modFormula);
                                }
                                else {
                                    isChemicalFormula = false;
                                }
                            }
                        }
                    }
                    continue;
                }

                monoMass += residues[aaIndex]->getMonoisotopicMass();
                formula->Add(residues[aaIndex]);

                if (hasMod) {
                    mod = _modifications[aaIndex + 1];

                    if (mod != nullptr) {
                        monoMass += mod->getMonoisotopicMass();
                        if (isChemicalFormula) {
//C# TO C++ CONVERTER TODO TASK: C++ has no equivalent to C# pattern variables in 'is' expressions:
//ORIGINAL LINE: if (mod is IHasChemicalFormula modFormula)
                            if (dynamic_cast<IHasChemicalFormula*>(mod) != nullptr modFormula) {
                                formula->Add(modFormula);
                            }
                            else {
                                isChemicalFormula = false;
                            }
                        }
                    }
                }

                if (i < minIndex) {
                    continue;
                }

                if (isChemicalFormula) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new ChemicalFormulaFragment(type, i, formula, this);
                }
                else {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new Fragment(type, i, monoMass, this);
                }
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete formula' statement was not added since formula was passed to a method or constructor. Handle memory management manually.
        }
    }

    bool AminoAcidPolymer::ContainsModifications() {
        return _modifications.size() > 0 && _modifications.Any([&] (std::any m) {
            return m != nullptr;
        });
    }

template<typename T>
    ISet<T> *AminoAcidPolymer::GetUniqueModifications() {
        static_assert(std::is_base_of<IHasMass, T>::value, "T must inherit from IHasMass");

        std::unordered_set<T> uniqueMods;

        if (_modifications.empty()) {
            return uniqueMods;
        }

        for (auto mod : _modifications) {
            if (dynamic_cast<T>(mod) != nullptr) {
                uniqueMods.insert(static_cast<T>(mod));
            }
        }
        return uniqueMods;
    }

    int AminoAcidPolymer::ModificationCount() {
        return _modifications.empty() ? 0 : _modifications.Count([&] (std::any mod) {
            return mod != nullptr;
        });
    }

    IHasMass *AminoAcidPolymer::GetModification(int residueNumber) {
        return _modifications.empty() ? nullptr : _modifications[residueNumber];
    }

    void AminoAcidPolymer::SetModification(IHasMass *modification, Terminus terminus) {
        if ((terminus & Terminus::N) == Terminus::N) {
            setNTerminusModification(modification);
        }

        if ((terminus & Terminus::C) == Terminus::C) {
            setCTerminusModification(modification);
        }
    }

    int AminoAcidPolymer::SetModification(IHasMass *modification, ModificationSites sites) {
        int count = 0;

        if ((sites & ModificationSites::NPep) == ModificationSites::NPep) {
            setNTerminusModification(modification);
            count++;
        }

        for (int i = 0; i < getLength(); i++) {
            ModificationSites site = residues[i]->getSite();
            if ((sites & site) == site) {
                ReplaceMod(i + 1, modification);
                count++;
            }
        }

        if ((sites & ModificationSites::PepC) == ModificationSites::PepC) {
            setCTerminusModification(modification);
            count++;
        }

        return count;
    }

    int AminoAcidPolymer::SetModification(IHasMass *modification, char letter) {
        int count = 0;
        for (int i = 0; i < getLength(); i++) {
            if (!letter.Equals(residues[i]->getLetter())) {
                continue;
            }

            ReplaceMod(i + 1, modification);
            count++;
        }

        return count;
    }

    int AminoAcidPolymer::SetModification(IHasMass *modification, Residue *residue) {
        int count = 0;
        for (int i = 0; i < getLength(); i++) {
            if (!residue->getLetter().Equals(residues[i]->getLetter())) {
                continue;
            }
            ReplaceMod(i + 1, modification);
            count++;
        }
        return count;
    }

    void AminoAcidPolymer::SetModification(IHasMass *modification, int residueNumber) {
        if (residueNumber > getLength() || residueNumber < 1) {
            throw MzLibException(std::string::Format(CultureInfo::InvariantCulture, "Residue number not in the correct range: [{0}-{1}] you specified: {2}", 1, getLength(), residueNumber));
        }

        ReplaceMod(residueNumber, modification);
    }

    void AminoAcidPolymer::SetModifications(std::vector<OldSchoolModification*> &modifications) {
        for (auto mod : modifications) {
            SetModification(mod, mod->getSites());
        }
    }

    void AminoAcidPolymer::SetModification(OldSchoolModification *mod) {
        SetModification(mod, mod->getSites());
    }

    void AminoAcidPolymer::SetModification(IHasMass *mod, std::vector<int> &residueNumbers) {
        for (int residueNumber : residueNumbers) {
            SetModification(mod, {residueNumber});
        }
    }

    int AminoAcidPolymer::ReplaceModification(IHasMass *oldMod, IHasMass *newMod) {
        if (oldMod == nullptr) {
            throw MzLibException("Cannot replace a null modification");
        }

        int count = 0;
        for (int i = 0; i < getLength() + 2; i++) {
            IHasMass *mod = GetModification(i);
            if (mod == nullptr || !oldMod->Equals(mod)) {
                continue;
            }

            ReplaceMod(i, newMod);
            count++;
        }
        return count;
    }

    int AminoAcidPolymer::AddModification(IHasMass *modification, Terminus terminus) {
        IHasMass *currentMod;
        int count = 0;

        if ((terminus & Terminus::N) == Terminus::N) {
            currentMod = getNTerminusModification();
            ModificationCollection tempVar({currentMod, modification});
            setNTerminusModification(currentMod == nullptr ? modification : &tempVar);
            count++;
        }

        if ((terminus & Terminus::C) == Terminus::C) {
            currentMod = getCTerminusModification();
            ModificationCollection tempVar2({currentMod, modification});
            setCTerminusModification(currentMod == nullptr ? modification : &tempVar2);
            count++;
        }
        return count;
    }

    int AminoAcidPolymer::AddModification(OldSchoolModification *modification) {
        return AddModification(modification, modification->getSites());
    }

    int AminoAcidPolymer::AddModification(IHasMass *modification, ModificationSites sites) {
        if (_modifications.empty()) {
            _modifications = std::vector<IHasMass*>(getLength() + 2);
        }

        int count = 0;
        IHasMass *currentMod;
        if ((sites & ModificationSites::NPep) == ModificationSites::NPep) {
            currentMod = getNTerminusModification();
            ModificationCollection tempVar({currentMod, modification});
            setNTerminusModification(currentMod == nullptr ? modification : &tempVar);
            count++;
        }

        for (int i = 0; i < getLength(); i++) {
            ModificationSites site = residues[i]->getSite();
            if ((sites & site) == site) {
                currentMod = _modifications[i + 1];
                ModificationCollection tempVar2({currentMod, modification});
                ReplaceMod(i + 1, currentMod == nullptr ? modification : &tempVar2);
                count++;
            }
        }

        if ((sites & ModificationSites::PepC) == ModificationSites::PepC) {
            currentMod = getCTerminusModification();
            ModificationCollection tempVar3({currentMod, modification});
            setCTerminusModification(currentMod == nullptr ? modification : &tempVar3);
            count++;
        }

        return count;
    }

    void AminoAcidPolymer::AddModification(IHasMass *modification, int location) {
        IHasMass *currentMod = GetModification(location);
        ModificationCollection tempVar({currentMod, modification});
        ReplaceMod(location, currentMod == nullptr ? modification : &tempVar);
    }

    void AminoAcidPolymer::ClearModifications(Terminus terminus) {
        if ((terminus & Terminus::N) == Terminus::N) {
            setNTerminusModification(nullptr);
        }

        if ((terminus & Terminus::C) == Terminus::C) {
            setCTerminusModification(nullptr);
        }
    }

    void AminoAcidPolymer::ClearModifications(ModificationSites sites) {
        if ((sites & ModificationSites::NPep) == ModificationSites::NPep || (sites & ModificationSites::NProt) == ModificationSites::NProt) {
            ReplaceMod(0, nullptr);
        }

        for (int i = 0; i < getLength(); i++) {
            int modIndex = i + 1;

            if (_modifications[modIndex] == nullptr) {
                continue;
            }

            ModificationSites curSite = residues[i]->getSite();

            if ((curSite & sites) == curSite) {
                ReplaceMod(modIndex, nullptr);
            }
        }

        if ((sites & ModificationSites::PepC) == ModificationSites::PepC || (sites & ModificationSites::ProtC) == ModificationSites::ProtC) {
            ReplaceMod(getLength() + 1, nullptr);
        }
    }

    void AminoAcidPolymer::ClearModifications() {
        if (!ContainsModifications()) {
            return;
        }

        for (int i = 0; i <= getLength() + 1; i++) {
            if (_modifications[i] == nullptr) {
                continue;
            }

            setMonoisotopicMass(getMonoisotopicMass() - _modifications[i]->getMonoisotopicMass());
            _modifications[i] = nullptr;
        }
    }

    void AminoAcidPolymer::ClearModifications(IHasMass *mod) {
        for (int i = 0; i <= getLength() + 1; i++) {
            if (!mod->Equals(_modifications[i])) {
                continue;
            }

            setMonoisotopicMass(getMonoisotopicMass() - mod->getMonoisotopicMass());
            _modifications[i] = nullptr;
        }
    }

    ChemicalFormula *AminoAcidPolymer::GetChemicalFormula() {
        auto formula = new ChemicalFormula();

        // Handle Modifications
        if (ContainsModifications()) {
            for (int i = 0; i < getLength() + 2; i++) {
                if (_modifications[i] == nullptr) {
                    continue;
                }

                IHasChemicalFormula *chemMod = dynamic_cast<IHasChemicalFormula*>(_modifications[i]);

                if (chemMod == nullptr) {
                    delete formula;
                    throw MzLibException("Modification " + _modifications[i] + " does not have a chemical formula!");
                }

                formula->Add(chemMod->getThisChemicalFormula());
            }
        }

        // Handle N-Terminus
        formula->Add(getNTerminus()->getThisChemicalFormula());

        // Handle C-Terminus
        formula->Add(getCTerminus()->getThisChemicalFormula());

        // Handle Amino Acid Residues
        for (int i = 0; i < getLength(); i++) {
            formula->Add(residues[i]->getThisChemicalFormula());
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete formula' statement was not added since formula was used in a 'return' or 'throw' statement.
        return formula;
    }

    std::string AminoAcidPolymer::ToString() {
        return GetSequenceWithModifications();
    }

    int AminoAcidPolymer::GetHashCode() {
        return getBaseSequence().GetHashCode();
    }

    bool AminoAcidPolymer::Equals(std::any obj) {
        AminoAcidPolymer *aap = dynamic_cast<AminoAcidPolymer*>(obj);
        return aap != nullptr && Equals(aap);
    }

    bool AminoAcidPolymer::Equals(AminoAcidPolymer *other) {
        if (other == nullptr || getLength() != other->getLength() || !getNTerminus()->getThisChemicalFormula()->Equals(other->getNTerminus()->getThisChemicalFormula()) || !getCTerminus()->getThisChemicalFormula()->Equals(other->getCTerminus()->getThisChemicalFormula())) {
            return false;
        }

        bool containsMod = ContainsModifications();

        if (containsMod != other->ContainsModifications()) {
            return false;
        }

        for (int i = 0; i <= getLength() + 1; i++) {
            if (containsMod && !Equals(_modifications[i], other->_modifications[i])) {
                return false;
            }

            if (i == 0 || i == getLength() + 1) {
                continue; // uneven arrays, so skip these two conditions
            }

            if (!residues[i - 1]->Equals(other->residues[i - 1])) {
                return false;
            }
        }
        return true;
    }

    void AminoAcidPolymer::ReplaceTerminus(IHasChemicalFormula *&terminus, IHasChemicalFormula *value) {
        if (terminus != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() - terminus->getMonoisotopicMass());
        }

        terminus = value;

        if (value != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() + value->getMonoisotopicMass());
        }
    }

    void AminoAcidPolymer::ReplaceMod(int index, IHasMass *mod) {
        // No error checking here as all validation will occur before this method is call. This is to prevent
        // unneeded bounds checking

        if (_modifications.empty()) {
            _modifications = std::vector<IHasMass*>(getLength() + 2);
        }

        IHasMass *oldMod = _modifications[index]; // Get the mod at the index, if present

        if (Equals(mod, oldMod)) {
            return; // Same modifications, no change is required
        }

        if (oldMod != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() - oldMod->getMonoisotopicMass()); // remove the old mod mass
        }

        _modifications[index] = mod;

        if (mod != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() + mod->getMonoisotopicMass()); // add the new mod mass
        }
    }

    void AminoAcidPolymer::ParseSequence(const std::string &sequence) {
        bool inMod = false;
        bool cterminalMod = false; // n or c terminal modification
        int index = 0;

        double monoMass = 0;

        StringBuilder *modSb = new StringBuilder(10);
        for (auto letter : sequence) {
            if (inMod) {
                if (letter == L']') {
                    inMod = false; // end the modification phase

                    std::string modString = modSb->toString();
                    modSb->clear();
                    IHasMass *modification;
                    try {
                        modification = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(modString));
                    }
                    catch (const MzLibException &e1) {
                        double mass;
                        if (double::TryParse(modString, mass)) {
                            modification = new ModWithOnlyMass(mass);
                        }
                        else {
                            delete modification;
                            delete modSb;
                            throw MzLibException("Unable to correctly parse the following modification: " + modString);
                        }
                    }

                    monoMass += modification->getMonoisotopicMass();

                    if (_modifications.empty()) {
                        _modifications = std::vector<IHasMass*>(getLength() + 2);
                    }

                    if (cterminalMod) {
                        _modifications[index + 1] = modification;
                    }
                    else {
                        _modifications[index] = modification;
                    }

                    cterminalMod = false;

                    delete modification;
                }
                else {
                    modSb->append(letter);
                }
            }
            else {
                //char upperletter = char.ToUpper(letter); // moved to amino acid dictionary
                Residue residue;
                if (Residue::TryGetResidue(letter, residue)) {
                    residues[index++] = residue;
                    monoMass += residue::MonoisotopicMass;
                }
                else {
                    switch (letter) {
                        case L'[': // start of a modification
                            inMod = true;
                            break;

                        case L'-': // End of an n-terminus mod or start of a c-terminus mod
                            cterminalMod = (index > 0);
                            break;

                        default:

                            delete modSb;
                            throw MzLibException(std::string::Format(CultureInfo::InvariantCulture, "Amino Acid Letter {0} does not exist in the Amino Acid Dictionary. {0} is also not a valid character", letter));
                    }
                }
            }
        }

        if (inMod) {
            delete modSb;
            throw MzLibException("Couldn't find the closing ] for a modification in this sequence: " + sequence);
        }

        setLength(index);
        setMonoisotopicMass(getMonoisotopicMass() + monoMass);
        Array::Resize(residues, getLength());
        if (_modifications.size() > 0) {
            Array::Resize(_modifications, getLength() + 2);
        }

        delete modSb;
    }

    AminoAcidPolymer::ModWithOnlyMass::ModWithOnlyMass(double mass) : mass(mass) {
    }

    double AminoAcidPolymer::ModWithOnlyMass::getMonoisotopicMass() const {
        return mass;
    }

    std::string AminoAcidPolymer::ModWithOnlyMass::ToString() {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        return mass.ToString(CultureInfo::InvariantCulture);
    }
}
