#include "PtmListLoader.h"
#include "../Proteomics/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace Proteomics;

namespace UsefulProteomicsDatabases {

const std::unordered_map<std::wstring, wchar_t> PtmListLoader::aminoAcidCodes;

    PtmListLoader::StaticConstructor::StaticConstructor() {
        aminoAcidCodes = std::unordered_map<std::wstring, wchar_t> {
            {L"Alanine", L'A'}, {
            {L"Asparagine", L'N'}, {
            {L"Aspartic Acid", L'D'}, {
            {L"Glutamate", L'E'}, {
            {L"Glutamine", L'Q'}, {
            {L"Histidine", L'H'}, {
            {L"Leucine", L'L'}, {
            {L"Methionine", L'M'}, {
            {L"Proline", L'P'}, {
            {L"Threonine", L'T'}, {
            {L"Tyrosine", L'Y'}, {
            };
    }

PtmListLoader::StaticConstructor PtmListLoader::staticConstructor;

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::wstring &ptmListLocation) {
        return ReadModsFromFile(ptmListLocation, std::unordered_map<std::wstring, int>());
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::wstring &ptmListLocation, std::unordered_map<std::wstring, int> &formalChargesDictionary) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader uniprot_mods = new StreamReader(ptmListLocation))
    {
            StreamReader uniprot_mods = StreamReader(ptmListLocation);
            std::vector<std::wstring> modification_specification;

            while (uniprot_mods.Peek() != -1) {
                std::wstring line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, L"//")) {
                    for (auto mod : ReadMod(modification_specification, formalChargesDictionary)) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return mod;
                    }
                    modification_specification = std::vector<std::wstring>();
                }
            }
    }
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromString(const std::wstring &storedModifications) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StringReader uniprot_mods = new StringReader(storedModifications))
    {
            StringReader uniprot_mods = StringReader(storedModifications);
            std::vector<std::wstring> modification_specification;

            while (uniprot_mods.Peek() != -1) {
                std::wstring line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, L"//")) {
                    for (auto mod : ReadMod(modification_specification, std::unordered_map<std::wstring, int>())) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return mod;
                    }
                    modification_specification = std::vector<std::wstring>();
                }
            }
    }
    }

    std::vector<Modification*> PtmListLoader::ReadMod(std::vector<std::wstring> &specification, std::unordered_map<std::wstring, int> &formalChargesDictionary) {
        // UniProt-specific fields
        std::wstring uniprotAC = L"";
        std::wstring uniprotFT = L"";

        // Other fields
        std::wstring id = L"";
        std::vector<std::wstring> motifs;
        std::wstring terminusLocalizationString = L"";
        ChemicalFormula *correctionFormula = nullptr;
        std::optional<double> monoisotopicMass = std::nullopt;
        auto externalDatabaseLinks = std::unordered_map<std::wstring, std::vector<std::wstring>>();
        std::vector<std::wstring> keywords;

        // Custom fields
        std::vector<double> neutralLosses;
        std::vector<double> diagnosticIons;
        std::wstring modificationType = L"";

        for (auto line : specification) {
            if (line.Length >= 2) {
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                switch (line.Substring(0, 2))
//ORIGINAL LINE: case "ID":
                if (line.substr(0, 2) == L"ID") { // Mandatory
                        id = line.substr(5);

                }
//ORIGINAL LINE: case "AC":
                else if (line.substr(0, 2) == L"AC") { // Do not use! Only present in UniProt ptmlist
                        uniprotAC = line.substr(5);

                }
//ORIGINAL LINE: case "FT":
                else if (line.substr(0, 2) == L"FT") { // Optional
                        uniprotFT = line.substr(5);

                }
//ORIGINAL LINE: case "TG":
                else if (line.substr(0, 2) == L"TG") { // Which amino acid(s) or motifs is the modification on
                        motifs = std::vector<std::wstring>(StringHelper::trimEnd(line.substr(5), L".")->Split({L" or "}, StringSplitOptions::None));

                }
//ORIGINAL LINE: case "PP":
                else if (line.substr(0, 2) == L"PP") { // Terminus localization
                        terminusLocalizationString = line.substr(5);

                }
//ORIGINAL LINE: case "CF":
                else if (line.substr(0, 2) == L"CF") { // Correction formula
                        correctionFormula = ChemicalFormula::ParseFormula(StringHelper::replace(line.substr(5), L" ", L""));

                }
//ORIGINAL LINE: case "MM":
                else if (line.substr(0, 2) == L"MM") { // Monoisotopic mass difference. Might not precisely correspond to formula!
                            double thisMM;
                            if (!double::TryParse(line.substr(5), NumberStyles::Any, CultureInfo::InvariantCulture, thisMM)) {
                                throw MzLibException(line.substr(5) + L" is not a valid monoisotopic mass");
                            }
                            monoisotopicMass = thisMM;

                }
//ORIGINAL LINE: case "DR":
                else if (line.substr(0, 2) == L"DR") { // External database links!
                            auto splitString = StringHelper::trimEnd(line.substr(5), L".")->Split(std::vector<std::wstring> {L"; "}, StringSplitOptions::None);
                            IList<std::wstring> val;
                            std::unordered_map<std::wstring, std::vector<std::wstring>>::const_iterator externalDatabaseLinks_iterator = externalDatabaseLinks.find(splitString[0]);
                            if (externalDatabaseLinks_iterator != externalDatabaseLinks.end()) {
                                val = externalDatabaseLinks_iterator->second;
                                val->Add(splitString[1]);
                            }
                            else {
                                val = externalDatabaseLinks_iterator->second;
                                externalDatabaseLinks.emplace(splitString[0], std::vector<std::vector<std::wstring>>(1) });
                            }

                }
//ORIGINAL LINE: case "KW":
                else if (line.substr(0, 2) == L"KW") { // ; Separated keywords
                            keywords = std::vector<std::wstring>(StringHelper::trimEnd(line.substr(5), L".")->Split({L"; "}, StringSplitOptions::None));

                    // NOW CUSTOM FIELDS:

                }
//ORIGINAL LINE: case "NL":
                else if (line.substr(0, 2) == L"NL") { // Netural Losses. If field doesn't exist, single equal to 0
                        try {
                            neutralLosses = std::vector<double>(line.substr(5)->Split({L" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                ChemicalFormula::ParseFormula(b)->getMonoisotopicMass();
                            }));
                        }
                        catch (const MzLibException &e1) {
                            neutralLosses = std::vector<double>(line.substr(5)->Split({L" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                std::stod(b, CultureInfo::InvariantCulture);
                            }));
                        }

                }
//ORIGINAL LINE: case "DI":
                else if (line.substr(0, 2) == L"DI") { // Masses of diagnostic ions. Might just be "DI"!!! If field doesn't exist, create an empty list!
                        try {
                            diagnosticIons = std::vector<double>(line.substr(5)->Split({L" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                ChemicalFormula::ParseFormula(b)->getMonoisotopicMass();
                            }));
                        }
                        catch (const MzLibException &e2) {
                            diagnosticIons = std::vector<double>(line.substr(5)->Split({L" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                std::stod(b, CultureInfo::InvariantCulture);
                            }));
                        }

                }
//ORIGINAL LINE: case "MT":
                else if (line.substr(0, 2) == L"MT") { // Modification Type. If the field doesn't exist, set to the database name
                        modificationType = line.substr(5);

                }
//ORIGINAL LINE: case "//":
                else if (line.substr(0, 2) == L"//") {
                        if (id == L"") {
                            throw MzLibException(L"id is null");
                        }
                        if (L"CROSSLNK" == uniprotFT) { // Ignore crosslinks
                            break;
                        }
                        if (uniprotAC != L"") {
                            modificationType = L"UniProt";
                            externalDatabaseLinks.emplace(L"UniProt", std::vector<std::wstring> {uniprotAC});
                        }
                        if (modificationType == L"") {
                            throw MzLibException(L"modificationType of " + id + L" is null");
                        }
                        if (!monoisotopicMass && correctionFormula != nullptr) {
                            monoisotopicMass = std::make_optional(correctionFormula->getMonoisotopicMass());
                        }

                        for (auto dbAndAccession : externalDatabaseLinks.SelectMany([&] (std::any b) {
                            b->Value->Select([&] (std::any c) {
                                return b::Key + ";
                            };
                        }" + c)))
                                if (formalChargesDictionary.ContainsKey(dbAndAccession)) {
                                    if (monoisotopicMass.HasValue) {
                                        monoisotopicMass -= formalChargesDictionary[dbAndAccession] * Constants::protonMass;
                                    }
                                    if (correctionFormula != nullptr) {
                                        correctionFormula->Remove(PeriodicTable::GetElement(L"H"), formalChargesDictionary[dbAndAccession]);
                                    }
                                    break;
                                }
                            if (terminusLocalizationString == nullptr || motifs == nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                yield return new Modification(id, modificationType);
                            }
                            else {
                                TerminusLocalization terminusLocalization;
                                std::unordered_map<std::wstring, TerminusLocalization>::const_iterator ModificationWithLocation.terminusLocalizationTypeCodes_iterator = ModificationWithLocation.terminusLocalizationTypeCodes.find(terminusLocalizationString);
                                if (ModificationWithLocation::terminusLocalizationTypeCodes_iterator != ModificationWithLocation::terminusLocalizationTypeCodes.end()) {
                                terminusLocalization = ModificationWithLocation::terminusLocalizationTypeCodes_iterator->second;
                                    for (auto singleTarget : motifs) {
                                        std::wstring theMotif;
                                        char possibleMotifChar;
                                        std::unordered_map<std::wstring, wchar_t>::const_iterator aminoAcidCodes_iterator = aminoAcidCodes.find(singleTarget);
                                        if (aminoAcidCodes_iterator != aminoAcidCodes.end()) {
                                            possibleMotifChar = aminoAcidCodes_iterator->second;
                                            theMotif = possibleMotifChar.ToString();
                                        }
                                        else {
                                            possibleMotifChar = aminoAcidCodes_iterator->second;
                                            theMotif = singleTarget;
                                        }
                                        ModificationMotif motif;
                                        if (ModificationMotif::TryGetMotif(theMotif, motif)) {
                                            auto idToUse = id;
                                            // Augment id if mulitple motifs!
                                            // Add id to keywords
                                            if (motifs.Count != 1) {
                                                if (keywords == nullptr) {
                                                    keywords = {id};
                                                }
                                                else {
                                                    keywords.Add(id);
                                                }
                                                idToUse += L" on " + motif;
                                            }
    
                                            // Add the modification!
    
                                            if (!monoisotopicMass.HasValue) {
                                                // Return modification
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                                yield return new ModificationWithLocation(idToUse, modificationType, motif, terminusLocalization, externalDatabaseLinks, keywords);
                                            }
                                            else {
                                                if (correctionFormula == nullptr) {
                                                    // Return modification with mass
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                                    yield return new ModificationWithMass(idToUse, modificationType, motif, terminusLocalization, monoisotopicMass.Value, externalDatabaseLinks, keywords, neutralLosses, diagnosticIons);
                                                }
                                                else {
                                                    // Return modification with complete information!
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                                    yield return new ModificationWithMassAndCf(idToUse, modificationType, motif, terminusLocalization, correctionFormula, std::make_optional(monoisotopicMass.Value), externalDatabaseLinks, keywords, neutralLosses, diagnosticIons);
                                                }
                                            }
                                        }
                                        else {
                                            throw MzLibException(L"Could not get motif from " + singleTarget);
                                        }
                                    }
                                }
                                else {
                                terminusLocalization = ModificationWithLocation::terminusLocalizationTypeCodes_iterator->second;
                                    throw MzLibException(L"Could not get modification site from " + terminusLocalizationString);
                                }
                            }
                            break;
                }}}}}}
