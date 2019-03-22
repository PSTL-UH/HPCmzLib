#include "PtmListLoader.h"
#include "../Proteomics/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace Proteomics;

namespace UsefulProteomicsDatabases {

const std::unordered_map<std::string, char> PtmListLoader::aminoAcidCodes;

    PtmListLoader::StaticConstructor::StaticConstructor() {
        aminoAcidCodes = std::unordered_map<std::string, char> {
            {"Alanine", 'A'}, {
            {"Asparagine", 'N'}, {
            {"Aspartic Acid", 'D'}, {
            {"Glutamate", 'E'}, {
            {"Glutamine", 'Q'}, {
            {"Histidine", 'H'}, {
            {"Leucine", 'L'}, {
            {"Methionine", 'M'}, {
            {"Proline", 'P'}, {
            {"Threonine", 'T'}, {
            {"Tyrosine", 'Y'}, {
            };
    }

PtmListLoader::StaticConstructor PtmListLoader::staticConstructor;

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::string &ptmListLocation) {
        return ReadModsFromFile(ptmListLocation, std::unordered_map<std::string, int>());
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::string &ptmListLocation, std::unordered_map<std::string, int> &formalChargesDictionary) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader uniprot_mods = new StreamReader(ptmListLocation))
    {
            StreamReader uniprot_mods = StreamReader(ptmListLocation);
            std::vector<std::string> modification_specification;

            while (uniprot_mods.Peek() != -1) {
                std::string line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, "//")) {
                    for (auto mod : ReadMod(modification_specification, formalChargesDictionary)) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return mod;
                    }
                    modification_specification = std::vector<std::string>();
                }
            }
    }
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromString(const std::string &storedModifications) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StringReader uniprot_mods = new StringReader(storedModifications))
    {
            StringReader uniprot_mods = StringReader(storedModifications);
            std::vector<std::string> modification_specification;

            while (uniprot_mods.Peek() != -1) {
                std::string line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, "//")) {
                    for (auto mod : ReadMod(modification_specification, std::unordered_map<std::string, int>())) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return mod;
                    }
                    modification_specification = std::vector<std::string>();
                }
            }
    }
    }

    std::vector<Modification*> PtmListLoader::ReadMod(std::vector<std::string> &specification, std::unordered_map<std::string, int> &formalChargesDictionary) {
        // UniProt-specific fields
        std::string uniprotAC = "";
        std::string uniprotFT = "";

        // Other fields
        std::string id = "";
        std::vector<std::string> motifs;
        std::string terminusLocalizationString = "";
        ChemicalFormula *correctionFormula = nullptr;
        std::optional<double> monoisotopicMass = std::nullopt;
        auto externalDatabaseLinks = std::unordered_map<std::string, std::vector<std::string>>();
        std::vector<std::string> keywords;

        // Custom fields
        std::vector<double> neutralLosses;
        std::vector<double> diagnosticIons;
        std::string modificationType = "";

        for (auto line : specification) {
            if (line.Length >= 2) {
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                switch (line.Substring(0, 2))
//ORIGINAL LINE: case "ID":
                if (line.substr(0, 2) == "ID") { // Mandatory
                        id = line.substr(5);

                }
//ORIGINAL LINE: case "AC":
                else if (line.substr(0, 2) == "AC") { // Do not use! Only present in UniProt ptmlist
                        uniprotAC = line.substr(5);

                }
//ORIGINAL LINE: case "FT":
                else if (line.substr(0, 2) == "FT") { // Optional
                        uniprotFT = line.substr(5);

                }
//ORIGINAL LINE: case "TG":
                else if (line.substr(0, 2) == "TG") { // Which amino acid(s) or motifs is the modification on
                        motifs = std::vector<std::string>(StringHelper::trimEnd(line.substr(5), ".")->Split({" or "}, StringSplitOptions::None));

                }
//ORIGINAL LINE: case "PP":
                else if (line.substr(0, 2) == "PP") { // Terminus localization
                        terminusLocalizationString = line.substr(5);

                }
//ORIGINAL LINE: case "CF":
                else if (line.substr(0, 2) == "CF") { // Correction formula
                        correctionFormula = ChemicalFormula::ParseFormula(StringHelper::replace(line.substr(5), " ", ""));

                }
//ORIGINAL LINE: case "MM":
                else if (line.substr(0, 2) == "MM") { // Monoisotopic mass difference. Might not precisely correspond to formula!
                            double thisMM;
                            if (!double::TryParse(line.substr(5), NumberStyles::Any, CultureInfo::InvariantCulture, thisMM)) {
                                throw MzLibException(line.substr(5) + " is not a valid monoisotopic mass");
                            }
                            monoisotopicMass = thisMM;

                }
//ORIGINAL LINE: case "DR":
                else if (line.substr(0, 2) == "DR") { // External database links!
                            auto splitString = StringHelper::trimEnd(line.substr(5), ".")->Split(std::vector<std::string> {"; "}, StringSplitOptions::None);
                            IList<std::string> val;
                            std::unordered_map<std::string, std::vector<std::string>>::const_iterator externalDatabaseLinks_iterator = externalDatabaseLinks.find(splitString[0]);
                            if (externalDatabaseLinks_iterator != externalDatabaseLinks.end()) {
                                val = externalDatabaseLinks_iterator->second;
                                val->Add(splitString[1]);
                            }
                            else {
                                val = externalDatabaseLinks_iterator->second;
                                externalDatabaseLinks.emplace(splitString[0], std::vector<std::vector<std::string>>(1) });
                            }

                }
//ORIGINAL LINE: case "KW":
                else if (line.substr(0, 2) == "KW") { // ; Separated keywords
                            keywords = std::vector<std::string>(StringHelper::trimEnd(line.substr(5), ".")->Split({"; "}, StringSplitOptions::None));

                    // NOW CUSTOM FIELDS:

                }
//ORIGINAL LINE: case "N":
                else if (line.substr(0, 2) == "N") { // Netural Losses. If field doesn't exist, single equal to 0
                        try {
                            neutralLosses = std::vector<double>(line.substr(5)->Split({" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                ChemicalFormula::ParseFormula(b)->getMonoisotopicMass();
                            }));
                        }
                        catch (const MzLibException &e1) {
                            neutralLosses = std::vector<double>(line.substr(5)->Split({" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                std::stod(b, CultureInfo::InvariantCulture);
                            }));
                        }

                }
//ORIGINAL LINE: case "DI":
                else if (line.substr(0, 2) == "DI") { // Masses of diagnostic ions. Might just be "DI"!!! If field doesn't exist, create an empty list!
                        try {
                            diagnosticIons = std::vector<double>(line.substr(5)->Split({" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                ChemicalFormula::ParseFormula(b)->getMonoisotopicMass();
                            }));
                        }
                        catch (const MzLibException &e2) {
                            diagnosticIons = std::vector<double>(line.substr(5)->Split({" or "}, StringSplitOptions::RemoveEmptyEntries).Select([&] (std::any b) {
                                std::stod(b, CultureInfo::InvariantCulture);
                            }));
                        }

                }
//ORIGINAL LINE: case "MT":
                else if (line.substr(0, 2) == "MT") { // Modification Type. If the field doesn't exist, set to the database name
                        modificationType = line.substr(5);

                }
//ORIGINAL LINE: case "//":
                else if (line.substr(0, 2) == "//") {
                        if (id == "") {
                            throw MzLibException("id is null");
                        }
                        if ("CROSSLNK" == uniprotFT) { // Ignore crosslinks
                            break;
                        }
                        if (uniprotAC != "") {
                            modificationType = "UniProt";
                            externalDatabaseLinks.emplace("UniProt", std::vector<std::string> {uniprotAC});
                        }
                        if (modificationType == "") {
                            throw MzLibException("modificationType of " + id + " is null");
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
                                        correctionFormula->Remove(PeriodicTable::GetElement("H"), formalChargesDictionary[dbAndAccession]);
                                    }
                                    break;
                                }
                            if (terminusLocalizationString == nullptr || motifs == nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                yield return new Modification(id, modificationType);
                            }
                            else {
                                TerminusLocalization terminusLocalization;
                                std::unordered_map<std::string, TerminusLocalization>::const_iterator ModificationWithLocation.terminusLocalizationTypeCodes_iterator = ModificationWithLocation.terminusLocalizationTypeCodes.find(terminusLocalizationString);
                                if (ModificationWithLocation::terminusLocalizationTypeCodes_iterator != ModificationWithLocation::terminusLocalizationTypeCodes.end()) {
                                terminusLocalization = ModificationWithLocation::terminusLocalizationTypeCodes_iterator->second;
                                    for (auto singleTarget : motifs) {
                                        std::string theMotif;
                                        char possibleMotifChar;
                                        std::unordered_map<std::string, char_t>::const_iterator aminoAcidCodes_iterator = aminoAcidCodes.find(singleTarget);
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
                                                idToUse += " on " + motif;
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
                                            throw MzLibException("Could not get motif from " + singleTarget);
                                        }
                                    }
                                }
                                else {
                                terminusLocalization = ModificationWithLocation::terminusLocalizationTypeCodes_iterator->second;
                                    throw MzLibException("Could not get modification site from " + terminusLocalizationString);
                                }
                            }
                            break;
                }
                                 }
                }
        }
    }
            }
