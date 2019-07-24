#include "../Chemistry/ChemicalFormula.h"
#include "Residue.h"
#include <iostream>


using namespace Chemistry;

namespace Proteomics {
    namespace AminoAcidPolymer  {

        std::vector<double> Residue::ResidueMonoisotopicMass;
        std::unordered_map<std::string, Residue*> Residue::ResiduesDictionary;
        std::vector<Residue*> Residue::ResiduesByLetter;

        void Residue::StaticConstructor() {

            ResiduesDictionary = {
                {"Alanine", new Residue("Alanine", 'A', "Ala",ChemicalFormula::ParseFormula("C3H5NO"), ModificationSites::A)},
                {"Arginine",  new Residue("Arginine",  'R', "Arg",ChemicalFormula::ParseFormula("C6H12N4O"), ModificationSites::R)},
                {"Asparagine", new Residue("Asparagine", 'N', "Asn",ChemicalFormula::ParseFormula("C4H6N2O2"), ModificationSites::N)},
                {"Aspartic Acid",  new Residue("Aspartic Acid", 'D', "Asp",ChemicalFormula::ParseFormula("C4H5NO3"),  ModificationSites::D)},
                {"Cysteine", new Residue("Cysteine", 'C', "Cys",ChemicalFormula::ParseFormula("C3H5NOS"), ModificationSites::C)}, 
                {"Glutamic Acid",  new Residue("Glutamic Acid", 'E', "Glu",ChemicalFormula::ParseFormula("C5H7NO3"),  ModificationSites::E)},
                {"Glutamine", new Residue("Glutamine", 'Q', "Gln",ChemicalFormula::ParseFormula("C5H8N2O2"), ModificationSites::Q)}, 
                {"Glycine", new Residue("Glycine", 'G', "Gly", ChemicalFormula::ParseFormula("C2H3NO"),  ModificationSites::G)},
                {"Histidine", new Residue("Histidine", 'H', "His",ChemicalFormula::ParseFormula("C6H7N3O"), ModificationSites::H)}, 
                {"Isoleucine",     new Residue("Isoleucine", 'I', "Ile",ChemicalFormula::ParseFormula("C6H11NO"),  ModificationSites::I)},
                {"Leucine", new Residue("Leucine", 'L', "Leu",ChemicalFormula::ParseFormula("C6H11NO"), ModificationSites::L)}, 
                {"Lysine",         new Residue("Lysine", 'K', "Lys",ChemicalFormula::ParseFormula("C6H12N2O"),  ModificationSites::K)},
                {"Methionine", new Residue("Methionine", 'M', "Met",ChemicalFormula::ParseFormula("C5H9NOS"), ModificationSites::M)}, 
                {"Phenylalanine",  new Residue("Phenylalanine", 'F', "Phe",ChemicalFormula::ParseFormula("C9H9NO"),  ModificationSites::F)},
                {"Proline", new Residue("Proline", 'P', "Pro",ChemicalFormula::ParseFormula("C5H7NO"), ModificationSites::P)}, 
                {"Selenocysteine", new Residue("Selenocysteine", 'U', "Sec",ChemicalFormula::ParseFormula("C3H5NOSe"),  ModificationSites::U)},
                {"Serine", new Residue("Serine", 'S', "Ser",ChemicalFormula::ParseFormula("C3H5NO2"), ModificationSites::S)}, 
                {"Threonine",      new Residue("Threonine", 'T', "Thr",ChemicalFormula::ParseFormula("C4H7NO2"),  ModificationSites::T)},
                {"Tryptophan", new Residue("Tryptophan", 'W', "Trp",ChemicalFormula::ParseFormula("C11H10N2O"), ModificationSites::W)}, 
                {"Tyrosine",       new Residue("Tyrosine", 'Y', "Try",ChemicalFormula::ParseFormula("C9H9NO2"),  ModificationSites::Y)},
                {"Valine", new Residue("Valine", 'V', "Val",ChemicalFormula::ParseFormula("C5H9NO"), ModificationSites::V)}
            };
        
            ResiduesByLetter = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, ResiduesDictionary["Alanine"], nullptr, ResiduesDictionary["Cysteine"], ResiduesDictionary["Aspartic Acid"], ResiduesDictionary["Glutamic Acid"], ResiduesDictionary["Phenylalanine"], ResiduesDictionary["Glycine"], ResiduesDictionary["Histidine"], ResiduesDictionary["Isoleucine"], nullptr, ResiduesDictionary["Lysine"], ResiduesDictionary["Leucine"], ResiduesDictionary["Methionine"], ResiduesDictionary["Asparagine"], nullptr, ResiduesDictionary["Proline"], ResiduesDictionary["Glutamine"], ResiduesDictionary["Arginine"], ResiduesDictionary["Serine"], ResiduesDictionary["Threonine"], ResiduesDictionary["Selenocysteine"], ResiduesDictionary["Valine"], ResiduesDictionary["Tryptophan"], nullptr, ResiduesDictionary["Tyrosine"], nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            
            
            ResidueMonoisotopicMass = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Alanine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Cysteine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Aspartic Acid"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Glutamic Acid"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Phenylalanine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Glycine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Histidine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Isoleucine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Isoleucine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Lysine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Leucine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Methionine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Asparagine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Proline"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Glutamine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Arginine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Serine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Threonine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Selenocysteine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Valine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Tryptophan"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(ResiduesDictionary["Tyrosine"]->getMonoisotopicMass());
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
            ResidueMonoisotopicMass.push_back(NAN);
        };
        

        Residue::Residue(const std::string &name, char oneLetterAbbreviation, const std::string &threeLetterAbbreviation, ChemicalFormula *chemicalFormula, ModificationSites site) {
            setName(name);
            setLetter(oneLetterAbbreviation);
            setSymbol(threeLetterAbbreviation);
            setThisChemicalFormula(chemicalFormula);
            setMonoisotopicMass(getThisChemicalFormula()->getMonoisotopicMass());
            setSite(site);
        }
        
        ChemicalFormula *Residue::getThisChemicalFormula() const {
            return privateThisChemicalFormula;
        }
        
        void Residue::setThisChemicalFormula(ChemicalFormula *value) {
            privateThisChemicalFormula = value;
        }
        
        char Residue::getLetter() const {
            return privateLetter;
        }
        
        void Residue::setLetter(char value) {
            privateLetter = value;
        }
        
        ModificationSites Residue::getSite() const {
            return privateSite;
        }
        
        void Residue::setSite(ModificationSites value) {
            privateSite = value;
        }
        
        double Residue::getMonoisotopicMass() const {
            return privateMonoisotopicMass;
        }
        
        void Residue::setMonoisotopicMass(double value) {
            privateMonoisotopicMass = value;
        }
        
        std::string Residue::getName() const {
            return privateName;
        }
        
        void Residue::setName(const std::string &value) {
            privateName = value;
        }
        
        std::string Residue::getSymbol() const {
            return privateSymbol;
        }
        
        void Residue::setSymbol(const std::string &value) {
            privateSymbol = value;
        }
        
        Residue *Residue::GetResidue(const std::string &symbol) {
            if ( ResiduesByLetter.size() == 0 ) {
                Residue::StaticConstructor() ;
            }

            if ( symbol.length() == 1 )
                return ResiduesByLetter[symbol[0]];
            else {
                return ResiduesDictionary[symbol];
            }
        }
        
        Residue *Residue::GetResidue(char letter) {
            if ( ResiduesByLetter.size() == 0 ) {
                Residue::StaticConstructor() ;
            }
            return ResiduesByLetter[letter];
        }
        
        bool Residue::TryGetResidue(char letter, Residue **residue) {
            if ( ResiduesByLetter.size() == 0 ) {
                Residue::StaticConstructor() ;
            }
            *residue = ResiduesByLetter[letter];
            return *residue != nullptr;
        }
        
        bool Residue::TryGetResidue(const std::string &name, Residue **residue) {
            if ( ResiduesDictionary.size() == 0 ) {
                Residue::StaticConstructor() ;
            }

            std::unordered_map<std::string, Residue*>::const_iterator s = ResiduesDictionary.find(name);
            if ( s != ResiduesDictionary.end() ){
                *residue = ResiduesDictionary[name];
                return true;
            }
            return false;
        }
    }
}
