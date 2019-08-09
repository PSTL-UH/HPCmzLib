#include "AminoAcidPolymer.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "Residue.h"
#include "../Chemistry/ChemicalFormula.h"
#include "ChemicalFormulaTerminus.h"
#include "Fragment.h"
#include "DigestionPoint.h"
#include "IProtease.h"
#include "../Chemistry/Isotope.h"
#include "../MzLibUtil/MzLibException.h"
#include "ChemicalFormulaFragment.h"
#include "OldSchoolModification.h"
#include "ModificationCollection.h"
#include "ChemicalFormulaModification.h"
#include "../Modifications/Modification.h"

#include <iostream>
#include <stdio.h>
#include <bitset>

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {

    namespace AminoAcidPolymer {
        AminoAcidPolymer::AminoAcidPolymer() : AminoAcidPolymer("", new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("H")), new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("OH")) ) {
    }

        AminoAcidPolymer::AminoAcidPolymer(const std::string &sequence) : AminoAcidPolymer(sequence, new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("H")), new ChemicalFormulaTerminus(ChemicalFormula::ParseFormula("OH")) ) {
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
            _modifications = std::vector<IHasMass*>(length + 2, nullptr);
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

    std::vector<IHasMass*> *AminoAcidPolymer::getModifications() const {
        return new std::vector<IHasMass*>(_modifications);
    }

    IHasChemicalFormula *AminoAcidPolymer::getCTerminus() const {
        return _cTerminus;
    }

    void AminoAcidPolymer::setCTerminus(IHasChemicalFormula *value) {
        ReplaceTerminus(&_cTerminus, value);
    }

    IHasChemicalFormula *AminoAcidPolymer::getNTerminus() const {
        return _nTerminus;
    }

    void AminoAcidPolymer::setNTerminus(IHasChemicalFormula *value) {
        ReplaceTerminus(&_nTerminus, value);
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
        //return StringHelper::replace(getBaseSequence(), std::to_string('I'), std::to_string('L'));
        std::string str = getBaseSequence();
        std::string from = "I";
        std::string to="L";
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); 
        }
        return str;
    }

    std::string AminoAcidPolymer::getBaseSequence() const {
//        return std::string(residues.Select([&] (std::any aa) {
//            aa::Letter;
//        })->ToArray());
        std::string astring;
        for ( auto aa= 0; aa < (int) residues.size(); aa++ ) {
            char bb = residues[aa]->getLetter();
            astring.append(&bb, 1);
        }
        return astring;
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

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::GetSiteDeterminingFragments(AminoAcidPolymer *peptideA, AminoAcidPolymer *peptideB, FragmentTypes types) {
        // std::unordered_set<Proteomics::Fragment*> aFrags(peptideA->Fragment(types));
        //aFrags.SymmetricExceptWith(peptideB->Fragment(types));

        std::vector<Proteomics::AminoAcidPolymer::Fragment*> aFrags = peptideA->Fragment(types);
        std::vector<Proteomics::AminoAcidPolymer::Fragment*> bFrags = peptideB->Fragment(types);
        std::vector<Proteomics::AminoAcidPolymer::Fragment*> cFrags;
        // SymmetricExceptWith return an object that is either in afrags or in bfrags,
        // but not in both. There is a similar function in C++ stl, namely set_symmetric_difference,
        // it requires however for the two arrays to be pre-sorted, which I am not sure whether it
        // is given here. So I prefer to implement it manually.
        // Step 1: insert all elements of aFrags that are not in bFrags
        std::for_each(aFrags.begin(), aFrags.end(), [&] (Proteomics::AminoAcidPolymer::Fragment *a) {
                bool found = false;
                std::vector<Proteomics::AminoAcidPolymer::Fragment*>::iterator it;
                for ( it = bFrags.begin(); it != bFrags.end(); ++it) {
                    if ( a == *it ) {
                        found = true;
                        break;
                    }
                }
                if ( found == false ) {
                    cFrags.push_back( a);
                }                    
            });
        // Step 2: insert all elements of bFrags that are not in aFrags
        std::for_each(bFrags.begin(), bFrags.end(), [&] (Proteomics::AminoAcidPolymer::Fragment *b) {
                bool found = false;
                std::vector<Proteomics::AminoAcidPolymer::Fragment*>::iterator it;
                for ( it = aFrags.begin(); it != aFrags.end(); ++it) {
                    if ( b == *it ) {
                        found = true;
                        break;
                    }
                }
                if ( found == false ) {
                    cFrags.push_back( b);
                }                    
            });
        
        
        return cFrags;
    }

   std::vector<DigestionPointAndLength*> AminoAcidPolymer::GetDigestionPointsAndLengths(const std::string &sequence, std::vector<IProtease*> &proteases, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
        std::vector<int> indices = GetCleavageIndexes(sequence, proteases);
        std::vector<DigestionPointAndLength*> dpal;
        
        bool includeMethionineCut = methionineInitiator && sequence[0] == 'M';

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
//                        yield return new DigestionPointAndLength(1, newLength);
                        dpal.push_back(new DigestionPointAndLength(1, newLength));
                        if (semiDigestion) {
                            for (int j = 1; j < newLength; j++) {
                                if (j >= minLength && j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                                    yield return new DigestionPointAndLength(1, j);
                                    dpal.push_back(new DigestionPointAndLength(1, j));
                                }
                            }
                        }
                    }
                }

                if (len < minLength || len > maxLength) {
                    continue;
                }

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                yield return new DigestionPointAndLength(indices[i] + 1, len);
                dpal.push_back(new DigestionPointAndLength(indices[i] + 1, len));

                if (semiDigestion) {
                    for (int j = 1; j < len; j++) {
                        if (len - j >= minLength && len - j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                          yield return new DigestionPointAndLength();
                            dpal.push_back(new DigestionPointAndLength(indices[i] + 1 + j, len - j));
                        }
                        if (j >= minLength && j <= maxLength) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                            yield return new DigestionPointAndLength(indices[i] + 1, j);
                            dpal.push_back(new DigestionPointAndLength(indices[i] + 1, j));
                        }
                    }
                }
            }
        }
        return dpal;
   }

    std::vector<int> AminoAcidPolymer::GetCleavageIndexes(const std::string &sequence, std::vector<IProtease*> &proteases) {
        return GetCleavageIndexes(sequence, proteases, true);
    }

    std::vector<int> AminoAcidPolymer::GetCleavageIndexes(const std::string &sequence, std::vector<IProtease*> &proteases, bool includeTermini) {

        // Combine all the proteases digestion sites
        std::vector<int> locations;
#ifdef ORIG
        for (IProtease *protease : proteases.Where([&] (std::any protease) {
            return protease != nullptr;
        })) {
            locations.UnionWith(protease::GetDigestionSites(sequence));
        }
#endif
        for (IProtease *protease : proteases ) {
            if ( protease != nullptr ) {
                std::vector<int> vecs = protease->GetDigestionSites(sequence);
                for ( int v: vecs ) {
                    if ( locations.end() != std::find (locations.begin(), locations.end(), v)) {
                        locations.push_back(v);
                    }
                }   
            } 
        }
        
        if (includeTermini) {
            locations.insert(locations.begin(), -1);
            locations.push_back(sequence.length() - 1);
        }
        
        return locations;
    }

    std::vector<std::string> AminoAcidPolymer::Digest(const std::string &sequence, std::vector<IProtease*> &proteases, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
#ifdef ORIG
        return GetDigestionPointsAndLengths(sequence, proteases, maxMissedCleavages, minLength, maxLength, methionineInitiator, semiDigestion).Select([&] (std::any points) {
            sequence.substr(points::Index, points->Length);
        });
#endif
        std::vector<DigestionPointAndLength*> dpal = GetDigestionPointsAndLengths(sequence,
                                                                                  proteases,
                                                                                  maxMissedCleavages,
                                                                                  minLength,
                                                                                  maxLength,
                                                                                  methionineInitiator,
                                                                                  semiDigestion);
        std::vector<std::string> s;
        for ( DigestionPointAndLength* points: dpal ) {
            s.push_back(sequence.substr(points->getIndex(), points->getLength()));
        };
        return s;
    }

    std::vector<std::string> AminoAcidPolymer::Digest(AminoAcidPolymer *sequence, IProtease *protease) {
        return Digest(sequence, protease, 3, 1, std::numeric_limits<int>::max(), true, false);
    }

    std::vector<std::string> AminoAcidPolymer::Digest(AminoAcidPolymer *polymer, IProtease *protease, int maxMissedCleavages, int minLength, int maxLength, bool methionineInitiator, bool semiDigestion) {
#ifdef ORIG
        return Digest(polymer->getBaseSequence(), protease, maxMissedCleavages, minLength, maxLength, methionineInitiator, semiDigestion);
#endif
        return Digest(polymer, protease, maxMissedCleavages, minLength, maxLength, methionineInitiator, semiDigestion);

    }

    Residue *AminoAcidPolymer::GetResidue(int position) {
        if (position < 0 || position >= getLength()) {
            return nullptr;
        }
        return residues[position];
    }

    bool AminoAcidPolymer::Contains(char residue) {
#ifdef ORIG
        return residues.Any([&] (std::any aa) {
            aa::Letter->Equals(residue);
        });
#endif
        for ( Residue* aa: residues ) {
            if ( aa->getLetter() == residue){
                return true;
            }
        }
        return false;
    }

    bool AminoAcidPolymer::Contains(Residue *residue) {
//        return residues.Contains(residue);
        if ( residues.end() == std::find(residues.begin(), residues.end(), residue )){
            return false;
        }
             
        return true;
    }

    std::string AminoAcidPolymer::_getString ( IHasMass *mod ) {
        if ( dynamic_cast<OldSchoolModification*>(mod) != nullptr ) {
            return ((OldSchoolModification*)mod)->ToString();
        }
        else if ( dynamic_cast<Modification*>(mod) != nullptr ) {
            return ((Modification*)mod)->ToString();
        }
        else if ( dynamic_cast<ModWithOnlyMass*>(mod) != nullptr ) {
            return ((ModWithOnlyMass*)mod)->ToString();
        }
        std::string s="";
        return s;
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
            modSeqSb->append('[');
            modSeqSb->append(_getString(mod));
            modSeqSb->append("]-");
        }

        // Handle Amino Acid Residues
        for (int i = 0; i < getLength(); i++) {
            if (leucineSequence && residues[i]->getLetter() == 'I') {
                modSeqSb->append('L');
            }
            else {
                modSeqSb->append(residues[i]->getLetter());
            }

            // Handle Amino Acid Modification (1-based)
            if ((mod = _modifications[i + 1]) != nullptr && mod->getMonoisotopicMass() > 0) {
                modSeqSb->append('[');
                modSeqSb->append(_getString(mod));
                modSeqSb->append(']');
            }
        }

        // Handle C-Terminus Modification
        if ((mod = _modifications[getLength() + 1]) != nullptr && mod->getMonoisotopicMass() > 0) {
            modSeqSb->append("-[");
            modSeqSb->append(_getString(mod));
            modSeqSb->append(']');
        }

        std::string s =  modSeqSb->toString();
        delete modSeqSb;
        return s;
    }

    int AminoAcidPolymer::ResidueCount() {
        return getLength();
    }

    int AminoAcidPolymer::ResidueCount(Residue *aminoAcid) {
#ifdef ORIG
        return aminoAcid == nullptr ? 0 : residues.Count([&] (std::any aar) {
            aar->Equals(aminoAcid);
        });
#endif
        int counter=0;
        for ( Residue* aar : residues ) {
            if ( aar == aminoAcid ) {
                counter++;
            }
        }
        return counter;
    }

    int AminoAcidPolymer::ResidueCount(char residueLetter) {
#ifdef ORIG
        return residues.Count([&] (std::any aar) {
            aar::Letter->Equals(residueLetter);
        });
#endif
        int counter=0;
        for ( Residue* aar : residues ) {
            if ( aar->getLetter() == residueLetter ) {
                counter++;
            }
        }
        return counter;
    }

    int AminoAcidPolymer::ResidueCount(char residueLetter, int index, int length) {
#ifdef ORIG
        return residues.SubArray(index, length)->Count([&] (std::any aar) {
            aar::Letter->Equals(residueLetter);
        });
#endif
        int counter=0;
        for ( int i=index; i<index+length; i++ ){
            Residue* aar = residues.at(i);
            if ( aar->getLetter() == residueLetter ) {
                counter++;
            }
        }
        return counter;
    }

    int AminoAcidPolymer::ResidueCount(Residue *aminoAcid, int index, int length) {
#ifdef ORIG
        return residues.SubArray(index, length)->Count([&] (std::any aar) {
            aar->Equals(aminoAcid);
        });
#endif
        int counter=0;
        for ( int i=index; i<index+length; i++ ){
            Residue* aar = residues.at(i);
            if ( aar == aminoAcid ) {
                counter++;
            }
        }
        return counter;

    }

    int AminoAcidPolymer::ElementCountWithIsotopes(const std::string &element) {
        Element *e = PeriodicTable::GetElement(element);
        // Residues count
#ifdef ORIG
        int count = residues.Sum([&] (std::any aar) {
            aar::ThisChemicalFormula::CountWithIsotopes(element);
        });
#endif
        int count=0;
        for ( Residue * aar : residues ) {
            count += aar->getThisChemicalFormula()->CountWithIsotopes(e);
        }
        // Modifications count (if the mod is a IHasChemicalFormula)
        if (_modifications.size() > 0) {
#ifdef ORIG
            count += _modifications.Where([&] (std::any mod) {
                dynamic_cast<IHasChemicalFormula*>(mod) != nullptr;
            }).Cast<IHasChemicalFormula*>().Sum([&] (std::any mod) {
                mod::ThisChemicalFormula::CountWithIsotopes(element);
            });
#endif
            for ( IHasMass* mod: _modifications ) {
                if ( dynamic_cast<IHasChemicalFormula*>(mod) != nullptr ) {
                    count += dynamic_cast<IHasChemicalFormula*>(mod)->getThisChemicalFormula()->CountWithIsotopes(e);
                }
            }
        }

        count += ChemicalFormula::ParseFormula("H2O")->CountWithIsotopes(e);
        return count;
    }

    int AminoAcidPolymer::SpecificIsotopeCount(Isotope *isotope) {
        // Residues count
#ifdef ORIG
        int count = residues.Sum([&] (std::any aar) {
            aar::ThisChemicalFormula::CountSpecificIsotopes(isotope);
        });
#endif
        int count = 0;
        for ( Residue* aar: residues) {
            count += aar->getThisChemicalFormula()->CountSpecificIsotopes(isotope);
        }
        
        // Modifications count (if the mod is a IHasChemicalFormula)
        if (_modifications.size() > 0) {
#ifdef ORIG
            count += _modifications.Where([&] (std::any mod) {
                dynamic_cast<IHasChemicalFormula*>(mod) != nullptr;
            }).Cast<IHasChemicalFormula*>().Sum([&] (std::any mod) {
                mod::ThisChemicalFormula::CountSpecificIsotopes(isotope);
            });
#endif
            for ( IHasMass* mod: _modifications ) {
                if ( dynamic_cast<IHasChemicalFormula*>(mod) != nullptr ) {
                    count += dynamic_cast<IHasChemicalFormula*>(mod)->getThisChemicalFormula()->CountSpecificIsotopes(isotope);
                }
            }
        }
        return count;
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::GetSiteDeterminingFragments(AminoAcidPolymer *other, FragmentTypes type) {
        return GetSiteDeterminingFragments(this, other, type);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types) {
        return Fragment(types, false);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, bool calculateChemicalFormula) {
        return Fragment(types, 1, getLength() - 1, calculateChemicalFormula);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int number) {
        return Fragment(types, number, false);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int number, bool calculateChemicalFormula) {
        return Fragment(types, number, number, calculateChemicalFormula);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int minIndex, int maxIndex) {
        return Fragment(types, minIndex, maxIndex, false);
    }

    std::vector<Proteomics::AminoAcidPolymer::Fragment*> AminoAcidPolymer::Fragment(FragmentTypes types, int minIndex, int maxIndex, bool calculateChemicalFormula) {
        std::vector<Proteomics::AminoAcidPolymer::Fragment*> v;
        for (FragmentTypes type : FragmentTypesExtension::GetIndividualFragmentTypes(types)) {
            bool isChemicalFormula = calculateChemicalFormula;
            ChemicalFormula *capFormula = FragmentTypesExtension::GetIonCap(type);
            bool isCTerminal = FragmentTypesExtension::GetTerminus(type) == Terminus::C;

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
                                // C# TO C++ CONVERTER TODO TASK: C++ has no equivalent to C# pattern variables in 'is'
                                // expressions:
                                // ORIGINAL LINE: if (mod is IHasChemicalFormula modFormula)
                                if (dynamic_cast<IHasChemicalFormula*>(mod) != nullptr ) {
                                    formula->Add(dynamic_cast<IHasChemicalFormula*>(mod));
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
                            // C# TO C++ CONVERTER TODO TASK: C++ has no equivalent to C# pattern variables
                            // in 'is' expressions:
                            //ORIGINAL LINE: if (mod is IHasChemicalFormula modFormula)
                            if (dynamic_cast<IHasChemicalFormula*>(mod) != nullptr)   {
                                formula->Add(dynamic_cast<IHasChemicalFormula*>(mod));
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
                    // C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to
                    // the C# 'yield' keyword:
                    // yield return new ChemicalFormulaFragment(type, i, formula, this);
                    ChemicalFormulaFragment *cff = new ChemicalFormulaFragment(type, i, formula, this);
                    v.push_back (cff);
                }
                else {
                    // C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    // yield return new Fragment(type, i, monoMass, this);
                    Proteomics::AminoAcidPolymer::Fragment *f = new Proteomics::AminoAcidPolymer::Fragment(type, i, monoMass, this);
                    v.push_back ( f);
                }
            }

            // C# TO C++ CONVERTER TODO TASK: A 'delete formula' statement was not added since formula was
            // passed to a method or constructor. Handle memory management manually.
        }
        return v;
    }

    bool AminoAcidPolymer::ContainsModifications() {
        bool result = false;
        if (  _modifications.size() > 0 ) {
            for ( auto m :  _modifications ) {
                if  (m != nullptr) {
                    result = true;
                    break;
                }
            }
        }
        return result;
    }
    
    int AminoAcidPolymer::ModificationCount() {
        int counter=0;
        if ( !_modifications.empty() ) {
            for ( auto mod: _modifications ) {
                if ( mod != nullptr ) {
                    counter++;
                }
            }
        }
        return counter;
    }

    IHasMass *AminoAcidPolymer::GetModification(int residueNumber)  const {
        return _modifications.empty() ? nullptr : _modifications[residueNumber];
    }

    void AminoAcidPolymer::SetModification(IHasMass *modification, Terminus terminus) {
        std::bitset<32> b1((int)terminus);
        std::bitset<32> b2((int)Terminus::N);
        std::bitset<32> b3((int)Terminus::C);
//        if ((terminus & Terminus::N) == Terminus::N) {
        if ((b1 & b2) == b2) {
            setNTerminusModification(modification);
        }

//        if ((terminus & Terminus::C) == Terminus::C) {
        if ((b1 & b3) == b3) {
            setCTerminusModification(modification);
        }
    }

    int AminoAcidPolymer::SetModification(IHasMass *modification, ModificationSites sites) {
        int count = 0;
        std::bitset<32> b1((int)sites);
        std::bitset<32> b2((int)ModificationSites::NPep);
//        if ((sites & ModificationSites::NPep) == ModificationSites::NPep) {
        if ((b1 & b2) == b2) {
            setNTerminusModification(modification);
            count++;
        }

        for (int i = 0; i < getLength(); i++) {
            ModificationSites site = residues[i]->getSite();
            std::bitset<32> b3((int)site);
//            if ((sites & site) == site) {
            if ((b1 & b3) == b3) {
                ReplaceMod(i + 1, modification);
                count++;
            }
        }

        std::bitset<32> b4((int)ModificationSites::PepC);

//        if ((sites & ModificationSites::PepC) == ModificationSites::PepC) {
        if ((b1 & b4) == b4) {
            setCTerminusModification(modification);
            count++;
        }

        return count;
    }

    int AminoAcidPolymer::SetModification(IHasMass *modification, char letter) {
        int count = 0;
        for (int i = 0; i < getLength(); i++) {
            if (letter != residues[i]->getLetter()) {
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
            if (residue->getLetter() != residues[i]->getLetter()) {
                continue;
            }
            ReplaceMod(i + 1, modification);
            count++;
        }
        return count;
    }

    void AminoAcidPolymer::SetModification(IHasMass *modification, int residueNumber) {
        if (residueNumber > getLength() || residueNumber < 1) {
//            throw MzLibException(std::string::Format(CultureInfo::InvariantCulture, "Residue number not in the correct range: [{0}-{1}] you specified: {2}", 1, getLength(), residueNumber));
            throw MzLibException(StringHelper::formatSimple("Residue number not in the correct range: [{0}-{1}] you specified: {2}", 1, getLength(), residueNumber));
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
            if (mod == nullptr || oldMod->getMonoisotopicMass() != mod->getMonoisotopicMass()) {
                continue;
            }

            ReplaceMod(i, newMod);
            count++;
        }
        return count;
    }

    int AminoAcidPolymer::AddModification(IHasMass *modification, Terminus terminus) {
        IHasMass *currentMod=nullptr;
        int count = 0;

        std::bitset<32> b1((int)terminus);
        std::bitset<32> b2((int)Terminus::N);
        std::bitset<32> b3((int)Terminus::C);
//      if ((terminus & Terminus::N) == Terminus::N) {
        if ((b1 & b2) == b2) {
            currentMod= getNTerminusModification();
            if ( currentMod != nullptr ) {
                std::vector<IHasMass*> vec;
                std::vector<IHasMass*> &v = vec;

                // ModificationCollection tempVar({currentMod, modification});
                v.push_back(currentMod);
                v.push_back(modification);
                ModificationCollection tempVar(v);
                setNTerminusModification(&tempVar);
            }
            else  {
                setNTerminusModification(modification);
            }
            count++;
        }

//      if ((terminus & Terminus::C) == Terminus::C) {
        if ((b1 & b3) == b3) {
            currentMod = getCTerminusModification();
            if ( currentMod != nullptr) {
                std::vector<IHasMass*> vec;
                std::vector<IHasMass*> &v = vec;

                // ModificationCollection tempVar2({currentMod, modification});
                v.push_back(currentMod);
                v.push_back(modification);
                ModificationCollection tempVar2(v);

                setCTerminusModification(&tempVar2);
            }
            else {
                setCTerminusModification(modification);            }
            count++;
        }
        return count;
    }

    int AminoAcidPolymer::AddModification(OldSchoolModification *modification) {
        return AddModification(modification, modification->getSites());
    }

    int AminoAcidPolymer::AddModification(IHasMass *modification, ModificationSites sites) {
        if (_modifications.empty()) {
            _modifications = std::vector<IHasMass*>(getLength() + 2, nullptr);
        }

        int count = 0;
        IHasMass *currentMod=nullptr;
        
        std::bitset<32> b1((int)sites);
        std::bitset<32> b2((int)ModificationSites::NPep);
        
        // if ((sites & ModificationSites::NPep) == ModificationSites::NPep) {
        if ((b1 & b2) == b2) {
            currentMod = getNTerminusModification();
            if (currentMod != nullptr ) {
                std::vector<IHasMass*> vec;
                std::vector<IHasMass*>& v = vec;

                // ModificationCollection tempVar({currentMod, modification});
                v.push_back(currentMod);
                v.push_back(modification);
                ModificationCollection tempVar(v);
            
                setNTerminusModification(&tempVar);
            }
            else {
                setNTerminusModification(modification);
            }
            count++;
        }

        for (int i = 0; i < getLength(); i++) {
            ModificationSites site = residues[i]->getSite();
            std::bitset<32> b3((int)site);
            // if ((sites & site) == site) {
            if ((b1 & b3) == b3) {
                currentMod = _modifications[i + 1];
                if (currentMod != nullptr ) {
                    std::vector<IHasMass*> vec;
                    std::vector<IHasMass*>& v = vec;

                    // ModificationCollection tempVar2({currentMod, modification});
                    v.push_back(currentMod);
                    v.push_back(modification);
                    ModificationCollection tempVar2(v);
                    
                    ReplaceMod(i + 1, &tempVar2);
                }
                else { 
                    ReplaceMod(i + 1, modification);
               }
                count++;
            }
        }

        std::bitset<32> b4((int)ModificationSites::PepC);
        // if ((sites & ModificationSites::PepC) == ModificationSites::PepC) {
        if ((b1 & b4) == b4) {
            currentMod = getCTerminusModification();
            if (currentMod != nullptr ) {
                std::vector<IHasMass*> vec;
                std::vector<IHasMass*>& v = vec;

                // ModificationCollection tempVar3({currentMod, modification});
                v.push_back(currentMod);
                v.push_back(modification);
                ModificationCollection tempVar3(v);
                
                setCTerminusModification(&tempVar3);
            }
            else {
                setCTerminusModification(modification);
            }
            count++;
        }

        return count;
    }

    void AminoAcidPolymer::AddModification(IHasMass *modification, int location) {
        IHasMass *currentMod = GetModification(location);
        std::vector<IHasMass*> vec;
        std::vector<IHasMass*>& v = vec;

//        ModificationCollection tempVar({currentMod, modification});
        v.push_back(currentMod);
        v.push_back(modification);
        
        ModificationCollection tempVar(v);
        ReplaceMod(location, currentMod == nullptr ? modification : &tempVar);
    }

    void AminoAcidPolymer::ClearModifications(Terminus terminus) {
        std::bitset<32> b1((int)terminus);
        std::bitset<32> b2((int)Terminus::N);
        std::bitset<32> b3((int)Terminus::C);

//        if ((terminus & Terminus::N) == Terminus::N) {
        if ((b1 & b2) == b2) {
            setNTerminusModification(nullptr);
        }

//        if ((terminus & Terminus::C) == Terminus::C) {
        if ((b1 & b3) == b3) {
            setCTerminusModification(nullptr);
        }
    }

    void AminoAcidPolymer::ClearModifications(ModificationSites sites) {
        std::bitset<32> b1((int)sites);
        std::bitset<32> b2((int)ModificationSites::NPep);
        std::bitset<32> b3((int)ModificationSites::NProt);
        
//        if ((sites & ModificationSites::NPep) == ModificationSites::NPep || (sites & ModificationSites::NProt) == ModificationSites::NProt) {
        if ((b1 & b2) == b2 || (b1 & b3) == b3) {
            ReplaceMod(0, nullptr);
        }

        for (int i = 0; i < getLength(); i++) {
            int modIndex = i + 1;

            if (_modifications[modIndex] == nullptr) {
                continue;
            }

            ModificationSites curSite = residues[i]->getSite();
            std::bitset<32> b4((int)curSite);
//            if ((curSite & sites) == curSite) {
            if ((b4 & b1) == b4) {
                ReplaceMod(modIndex, nullptr);
            }
        }

        std::bitset<32> b5((int)ModificationSites::PepC);
        std::bitset<32> b6((int)ModificationSites::ProtC);
        
//        if ((sites & ModificationSites::PepC) == ModificationSites::PepC || (sites & ModificationSites::ProtC) == ModificationSites::ProtC) {
        if ((b1 & b5) == b5 || (b1 & b6) == b6) {
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
        OldSchoolModification *oMod = dynamic_cast<OldSchoolModification*>(mod);
        Modification *nMod =  dynamic_cast<Modification*>(mod);

        for (int i = 0; i <= getLength() + 1; i++) {
            if ( _modifications[i] != nullptr ) {
                if ( oMod != nullptr ) {
                    if ( !oMod->Equals(dynamic_cast<OldSchoolModification*>(_modifications[i]) )) {
                        continue;
                    }
                }
                else if ( nMod != nullptr ) {
                    if ( !nMod->Equals(dynamic_cast<Modification*>(_modifications[i]) )) {
                        continue;
                    }
                }
                else {
                    if ( mod->getMonoisotopicMass() != _modifications[i]->getMonoisotopicMass() ) {
                        continue;
                    }
                }   
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
                    throw MzLibException("Modification " + std::to_string(_modifications[i]->getMonoisotopicMass()) + " does not have a chemical formula!");
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
        return StringHelper::GetHashCode(getBaseSequence());
    }

#ifdef ORIG
    bool AminoAcidPolymer::Equals(AminoAcidPolymer *aap) {
//        AminoAcidPolymer *aap = dynamic_cast<AminoAcidPolymer*>(obj);
        return aap != nullptr && Equals(aap);
    }
#endif
    
    bool AminoAcidPolymer::Equals(AminoAcidPolymer *other) {
        if (other == nullptr || getLength() != other->getLength() ||
            !getNTerminus()->getThisChemicalFormula()->Equals(other->getNTerminus()->getThisChemicalFormula()) ||
            !getCTerminus()->getThisChemicalFormula()->Equals(other->getCTerminus()->getThisChemicalFormula())) {
            return false;
        }

        bool containsMod = ContainsModifications();

        if (containsMod != other->ContainsModifications()) {
            return false;
        }

        for (int i = 0; i <= getLength() + 1; i++) {
            //if (containsMod && !Equals(_modifications[i], other->_modifications[i])) {
            if ( containsMod                                                               &&
                 ( (_modifications[i] == nullptr  && other->_modifications[i] != nullptr ) ||
                   (_modifications[i] != nullptr  && other->_modifications[i] == nullptr ) ||
                   (_modifications[i] != nullptr  && other->_modifications[i] != nullptr  &&
                    (_modifications[i]->getMonoisotopicMass() - other->_modifications[i]->getMonoisotopicMass() > 1e-9) ))) {
                return false;
            }

            if (i == 0 || i == getLength() + 1) {
                continue; // uneven arrays, so skip these two conditions
            }

            if (!residues[i - 1]->getThisChemicalFormula()->Equals(other->residues[i - 1]->getThisChemicalFormula())) {
                return false;
            }
        }
        return true;
    }

    void AminoAcidPolymer::ReplaceTerminus(IHasChemicalFormula **terminus, IHasChemicalFormula *value) {
        if (*terminus != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() - (*terminus)->getMonoisotopicMass());
        }

        *terminus = value;

        if (value != nullptr) {
            setMonoisotopicMass(getMonoisotopicMass() + value->getMonoisotopicMass());
        }
    }

    void AminoAcidPolymer::ReplaceMod(int index, IHasMass *mod) {
        // No error checking here as all validation will occur before this method is call. This is to prevent
        // unneeded bounds checking

        if (_modifications.empty()) {
            _modifications = std::vector<IHasMass*>(getLength() + 2, nullptr);
        }

        IHasMass *oldMod = _modifications[index]; // Get the mod at the index, if present

        if ( oldMod != nullptr && mod != nullptr ) {
            if ( oldMod->getMonoisotopicMass() == mod->getMonoisotopicMass() ) {
                return; // Same modifications, no change is required
            }

            // remove the old mod mass
            setMonoisotopicMass(getMonoisotopicMass() - oldMod->getMonoisotopicMass()); 
            _modifications[index] = mod;
            // add the new mod mass        
            setMonoisotopicMass(getMonoisotopicMass() + mod->getMonoisotopicMass()); 
        }
        else {
            _modifications[index] = mod;
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
                if (letter == ']') {
                    inMod = false; // end the modification phase

                    std::string modString = modSb->toString();
                    modSb->clear();

                    IHasMass *modification2=nullptr;
                    OldSchoolChemicalFormulaModification *modification=nullptr;
                    try {
                         modification = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(modString));
                         monoMass += modification->getMonoisotopicMass();
                    }
                    catch (const MzLibException &e1) {
                        double mass;
                        // if (double::TryParse(modString, mass)) {
                        if ( 1 == sscanf(modString.c_str(), "%lf", &mass)) {
                            modification2 = new ModWithOnlyMass(mass);
                            monoMass += modification2->getMonoisotopicMass();
                        }
                        else {
                            // delete modification;
                            delete modSb;
                            throw MzLibException("Unable to correctly parse the following modification: " + modString);
                        }
                    }

                    // monoMass += modification->getMonoisotopicMass();

                    if (_modifications.empty()) {
                        _modifications = std::vector<IHasMass*>(getLength() + 2, nullptr);
                    }

                    if (cterminalMod) {
                        // _modifications[index + 1] = modification;
                        _modifications[index + 1] = modification == nullptr ? modification2 : modification;
                    }
                    else {
                        // _modifications[index] = modification;
                        _modifications[index] = modification == nullptr ? modification2 : modification;
                    }

                    cterminalMod = false;

                    // delete modification;
                    // delete modification2;

                }
                else {
                    modSb->append(letter);
                }
            }
            else {
                //char upperletter = char.ToUpper(letter); // moved to amino acid dictionary
                Residue *residue;
                if (Residue::TryGetResidue(letter, &residue)) {
                    residues[index++] = residue;
                    monoMass += residue->getMonoisotopicMass();
                }
                else {
                    switch (letter) {
                        case '[': // start of a modification
                            inMod = true;
                            break;

                        case '-': // End of an n-terminus mod or start of a c-terminus mod
                            cterminalMod = (index > 0);
                            break;

                        default:

                            delete modSb;
                            throw MzLibException("Amino Acid Letter " + std::to_string(letter) + " does not exist in the Amino Acid Dictionary. It is also not a valid character");
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

        // Array::Resize(residues, getLength());
        residues.resize(getLength());
        if (_modifications.size() > 0) {
            // Array::Resize(_modifications, getLength() + 2);
            _modifications.resize(getLength() + 2);
        }

        delete modSb;
    }

    AminoAcidPolymer::ModWithOnlyMass::ModWithOnlyMass(double mass) : mass(mass) {
    }

    double AminoAcidPolymer::ModWithOnlyMass::getMonoisotopicMass() const {
        return mass;
    }

    std::string AminoAcidPolymer::ModWithOnlyMass::ToString() {
        std::string s = std::to_string(mass);
        return s.erase ( s.find_last_not_of('0') + 1, std::string::npos );
    }
  }
}
