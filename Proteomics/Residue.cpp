#include "Residue.h"
#include "../Chemistry/ChemicalFormula.h"

using namespace Chemistry;

namespace Proteomics {

std::vector<double> Residue::ResidueMonoisotopicMass;
std::unordered_map<std::string, Residue*> Residue::ResiduesDictionary;
std::vector<Residue*> Residue::ResiduesByLetter;

    Residue::StaticConstructor::StaticConstructor() {
        std::unordered_map<std::string, Residue*> ResiduesDictionary({
            {"Alanine", new Residue("Alanine", 'A', "Ala",ChemicalFormula::ParseFormula("C3H5NO"), ModificationSites::A)}, 
            {"Asparagine", new Residue("Asparagine", 'N', "Asn",ChemicalFormula::ParseFormula("C4H6N2O2"), ModificationSites::N)}, 
            {"Cysteine", new Residue("Cysteine", 'C', "Cys",ChemicalFormula::ParseFormula("C3H5NOS"), ModificationSites::C)}, 
            {"Glutamine", new Residue("Glutamine", 'Q', "Gln",ChemicalFormula::ParseFormula("C5H8N2O2"), ModificationSites::Q)}, 
            {"Histidine", new Residue("Histidine", 'H', "His",ChemicalFormula::ParseFormula("C6H7N3O"), ModificationSites::H)}, 
            {"Leucine", new Residue("Leucine", 'L', "Leu",ChemicalFormula::ParseFormula("C6H11NO"), ModificationSites::L)}, 
            {"Methionine", new Residue("Methionine", 'M', "Met",ChemicalFormula::ParseFormula("C5H9NOS"), ModificationSites::M)}, 
            {"Proline", new Residue("Proline", 'P', "Pro",ChemicalFormula::ParseFormula("C5H7NO"), ModificationSites::P)}, 
            {"Serine", new Residue("Serine", 'S', "Ser",ChemicalFormula::ParseFormula("C3H5NO2"), ModificationSites::S)}, 
            {"Tryptophan", new Residue("Tryptophan", 'W', "Trp",ChemicalFormula::ParseFormula("C11H10N2O"), ModificationSites::W)}, 
            {"Valine", new Residue("Valine", 'V', "Val",ChemicalFormula::ParseFormula("C5H9NO"), ModificationSites::V)}
            });
        
        ResiduesByLetter = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, ResiduesDictionary["Alanine"], nullptr, ResiduesDictionary["Cysteine"], ResiduesDictionary["Aspartic Acid"], ResiduesDictionary["Glutamic Acid"], ResiduesDictionary["Phenylalanine"], ResiduesDictionary["Glycine"], ResiduesDictionary["Histidine"], ResiduesDictionary["Isoleucine"], nullptr, ResiduesDictionary["Lysine"], ResiduesDictionary["Leucine"], ResiduesDictionary["Methionine"], ResiduesDictionary["Asparagine"], nullptr, ResiduesDictionary["Proline"], ResiduesDictionary["Glutamine"], ResiduesDictionary["Arginine"], ResiduesDictionary["Serine"], ResiduesDictionary["Threonine"], ResiduesDictionary["Selenocysteine"], ResiduesDictionary["Valine"], ResiduesDictionary["Tryptophan"], nullptr, ResiduesDictionary["Tyrosine"], nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            
        ResidueMonoisotopicMass = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, ResiduesDictionary["Alanine"]->getMonoisotopicMass(), NAN, ResiduesDictionary["Cysteine"]->getMonoisotopicMass(), ResiduesDictionary["Aspartic Acid"]->getMonoisotopicMass(), ResiduesDictionary["Glutamic Acid"]->getMonoisotopicMass(), ResiduesDictionary["Phenylalanine"]->getMonoisotopicMass(), ResiduesDictionary["Glycine"]->getMonoisotopicMass(), ResiduesDictionary["Histidine"]->getMonoisotopicMass(), ResiduesDictionary["Isoleucine"]->getMonoisotopicMass(), ResiduesDictionary["Isoleucine"]->getMonoisotopicMass(), ResiduesDictionary["Lysine"]->getMonoisotopicMass(), ResiduesDictionary["Leucine"]->getMonoisotopicMass(), ResiduesDictionary["Methionine"]->getMonoisotopicMass(), ResiduesDictionary["Asparagine"]->getMonoisotopicMass(), NAN, ResiduesDictionary["Proline"]->getMonoisotopicMass(), ResiduesDictionary["Glutamine"]->getMonoisotopicMass(), ResiduesDictionary["Arginine"]->getMonoisotopicMass(), ResiduesDictionary["Serine"]->getMonoisotopicMass(), ResiduesDictionary["Threonine"]->getMonoisotopicMass(), ResiduesDictionary["Selenocysteine"]->getMonoisotopicMass(), ResiduesDictionary["Valine"]->getMonoisotopicMass(), ResiduesDictionary["Tryptophan"]->getMonoisotopicMass(), NAN, ResiduesDictionary["Tyrosine"]->getMonoisotopicMass(), NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};
    }
           
Residue::StaticConstructor Residue::staticConstructor;

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
        return symbol.length() == 1 ? ResiduesByLetter[symbol[0]] : ResiduesDictionary[symbol];
    }

    Residue *Residue::GetResidue(char letter) {
        return ResiduesByLetter[letter];
    }

    bool Residue::TryGetResidue(char letter, Residue **residue) {
        *residue = ResiduesByLetter[letter];
        return *residue != nullptr;
    }

    bool Residue::TryGetResidue(const std::string &name, Residue **residue) {
        std::unordered_map<std::string, Residue*>::const_iterator ResiduesDictionary_iterator = ResiduesDictionary.find(name);
        *residue = ResiduesDictionary_iterator->second;
        return ResiduesDictionary_iterator != ResiduesDictionary.end();
    }
}
