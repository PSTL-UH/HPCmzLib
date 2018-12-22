#include "Residue.h"
#include "../Chemistry/ChemicalFormula.h"

using namespace Chemistry;

namespace Proteomics {

std::vector<double> const Residue::ResidueMonoisotopicMass;
const std::unordered_map<std::wstring, Residue*> Residue::ResiduesDictionary;
std::vector<Residue*> const Residue::ResiduesByLetter;

    Residue::StaticConstructor::StaticConstructor() {
        ResiduesDictionary = std::unordered_map<std::wstring, Residue*> {
            {L"Alanine", new Residue(L"Alanine", L'A', L"Ala",ChemicalFormula::ParseFormula(L"C3H5NO"), ModificationSites::A)}, {
            {L"Asparagine", new Residue(L"Asparagine", L'N', L"Asn",ChemicalFormula::ParseFormula(L"C4H6N2O2"), ModificationSites::N)}, {
            {L"Cysteine", new Residue(L"Cysteine", L'C', L"Cys",ChemicalFormula::ParseFormula(L"C3H5NOS"), ModificationSites::C)}, {
            {L"Glutamine", new Residue(L"Glutamine", L'Q', L"Gln",ChemicalFormula::ParseFormula(L"C5H8N2O2"), ModificationSites::Q)}, {
            {L"Histidine", new Residue(L"Histidine", L'H', L"His",ChemicalFormula::ParseFormula(L"C6H7N3O"), ModificationSites::H)}, {
            {L"Leucine", new Residue(L"Leucine", L'L', L"Leu",ChemicalFormula::ParseFormula(L"C6H11NO"), ModificationSites::L)}, {
            {L"Methionine", new Residue(L"Methionine", L'M', L"Met",ChemicalFormula::ParseFormula(L"C5H9NOS"), ModificationSites::M)}, {
            {L"Proline", new Residue(L"Proline", L'P', L"Pro",ChemicalFormula::ParseFormula(L"C5H7NO"), ModificationSites::P)}, {
            {L"Serine", new Residue(L"Serine", L'S', L"Ser",ChemicalFormula::ParseFormula(L"C3H5NO2"), ModificationSites::S)}, {
            {L"Tryptophan", new Residue(L"Tryptophan", L'W', L"Trp",ChemicalFormula::ParseFormula(L"C11H10N2O"), ModificationSites::W)}, {
            {L"Valine", new Residue(L"Valine", L'V', L"Val",ChemicalFormula::ParseFormula(L"C5H9NO"), ModificationSites::V)}
            };
        
        ResiduesByLetter = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, ResiduesDictionary[L"Alanine"], nullptr, ResiduesDictionary[L"Cysteine"], ResiduesDictionary[L"Aspartic Acid"], ResiduesDictionary[L"Glutamic Acid"], ResiduesDictionary[L"Phenylalanine"], ResiduesDictionary[L"Glycine"], ResiduesDictionary[L"Histidine"], ResiduesDictionary[L"Isoleucine"], nullptr, ResiduesDictionary[L"Lysine"], ResiduesDictionary[L"Leucine"], ResiduesDictionary[L"Methionine"], ResiduesDictionary[L"Asparagine"], nullptr, ResiduesDictionary[L"Proline"], ResiduesDictionary[L"Glutamine"], ResiduesDictionary[L"Arginine"], ResiduesDictionary[L"Serine"], ResiduesDictionary[L"Threonine"], ResiduesDictionary[L"Selenocysteine"], ResiduesDictionary[L"Valine"], ResiduesDictionary[L"Tryptophan"], nullptr, ResiduesDictionary[L"Tyrosine"], nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        ResidueMonoisotopicMass = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, ResiduesDictionary[L"Alanine"]->getMonoisotopicMass(), NAN, ResiduesDictionary[L"Cysteine"]->getMonoisotopicMass(), ResiduesDictionary[L"Aspartic Acid"]->getMonoisotopicMass(), ResiduesDictionary[L"Glutamic Acid"]->getMonoisotopicMass(), ResiduesDictionary[L"Phenylalanine"]->getMonoisotopicMass(), ResiduesDictionary[L"Glycine"]->getMonoisotopicMass(), ResiduesDictionary[L"Histidine"]->getMonoisotopicMass(), ResiduesDictionary[L"Isoleucine"]->getMonoisotopicMass(), ResiduesDictionary[L"Isoleucine"]->getMonoisotopicMass(), ResiduesDictionary[L"Lysine"]->getMonoisotopicMass(), ResiduesDictionary[L"Leucine"]->getMonoisotopicMass(), ResiduesDictionary[L"Methionine"]->getMonoisotopicMass(), ResiduesDictionary[L"Asparagine"]->getMonoisotopicMass(), NAN, ResiduesDictionary[L"Proline"]->getMonoisotopicMass(), ResiduesDictionary[L"Glutamine"]->getMonoisotopicMass(), ResiduesDictionary[L"Arginine"]->getMonoisotopicMass(), ResiduesDictionary[L"Serine"]->getMonoisotopicMass(), ResiduesDictionary[L"Threonine"]->getMonoisotopicMass(), ResiduesDictionary[L"Selenocysteine"]->getMonoisotopicMass(), ResiduesDictionary[L"Valine"]->getMonoisotopicMass(), ResiduesDictionary[L"Tryptophan"]->getMonoisotopicMass(), NAN, ResiduesDictionary[L"Tyrosine"]->getMonoisotopicMass(), NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};
    }

Residue::StaticConstructor Residue::staticConstructor;

    Residue::Residue(const std::wstring &name, wchar_t oneLetterAbbreviation, const std::wstring &threeLetterAbbreviation, ChemicalFormula *chemicalFormula, ModificationSites site) {
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

    wchar_t Residue::getLetter() const {
        return privateLetter;
    }

    void Residue::setLetter(wchar_t value) {
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

    std::wstring Residue::getName() const {
        return privateName;
    }

    void Residue::setName(const std::wstring &value) {
        privateName = value;
    }

    std::wstring Residue::getSymbol() const {
        return privateSymbol;
    }

    void Residue::setSymbol(const std::wstring &value) {
        privateSymbol = value;
    }

    Residue *Residue::GetResidue(const std::wstring &symbol) {
        return symbol.length() == 1 ? ResiduesByLetter[symbol[0]] : ResiduesDictionary[symbol];
    }

    Residue *Residue::GetResidue(wchar_t letter) {
        return ResiduesByLetter[letter];
    }

    bool Residue::TryGetResidue(wchar_t letter, Residue *&residue) {
        residue = ResiduesByLetter[letter];
        return residue != nullptr;
    }

    bool Residue::TryGetResidue(const std::wstring &name, Residue *&residue) {
        std::unordered_map<std::wstring, Residue*>::const_iterator ResiduesDictionary_iterator = ResiduesDictionary.find(name);
        return ResiduesDictionary_iterator != ResiduesDictionary.end();
        residue = ResiduesDictionary_iterator->second;
    }
}
