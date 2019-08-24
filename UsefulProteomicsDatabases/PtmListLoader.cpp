#include "PtmListLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

std::unordered_map<std::string, char> PtmListLoader::AminoAcidCodes;

    PtmListLoader::StaticConstructor::StaticConstructor()
    {
        AminoAcidCodes = std::unordered_map<std::string, char>
        {
            {"Alanine", 'A'},
            {"Arginine", 'R'},
            {"Asparagine", 'N'},
            {"Aspartate", 'D'},
            {"Aspartic Acid", 'D'},
            {"Cysteine", 'C'},
            {"Glutamate", 'E'},
            {"Glutamic Acid", 'E'},
            {"Glutamine", 'Q'},
            {"Glycine", 'G'},
            {"Histidine", 'H'},
            {"Isoleucine", 'I'},
            {"Leucine", 'L'},
            {"Lysine", 'K'},
            {"Methionine", 'M'},
            {"Phenylalanine", 'F'},
            {"Proline", 'P'},
            {"Pyrrolysine", 'O'},
            {"Selenocysteine", 'U'},
            {"Serine", 'S'},
            {"Threonine", 'T'},
            {"Tryptophan", 'W'},
            {"Tyrosine", 'Y'},
            {"Valine", 'V'}
        };
    }

PtmListLoader::StaticConstructor PtmListLoader::staticConstructor;

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::string &ptmListLocation, std::vector<(Modification, std::string)*> &filteredModificationsWithWarnings)
    {
        return ReadModsFromFile(ptmListLocation, std::unordered_map<std::string, int>(), filteredModificationsWithWarnings).OrderBy([&] (std::any b)
        {
            b::IdWithMotif;
        });
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::string &ptmListLocation, std::unordered_map<std::string, int> &formalChargesDictionary, std::vector<(Modification, std::string)*> &filteredModificationsWithWarnings)
    {
        std::vector<Modification*> acceptedModifications;
        filteredModificationsWithWarnings = std::vector<(Modification filteredMod, std::string warningString)*>();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader uniprot_mods = new StreamReader(ptmListLocation))
        {
            StreamReader uniprot_mods = StreamReader(ptmListLocation);
            std::vector<std::string> modification_specification;

            //This block will read one complete modification entry at a time until the EOF is reached.
            while (uniprot_mods.Peek() != -1) //The Peek method returns an integer value in order to determine whether the end of the file, or another error has occurred.
            {
                std::string line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, "//"))
                {
                    for (auto mod : ReadMod(ptmListLocation, modification_specification, formalChargesDictionary))
                    {
                        // Filter out the modifications that don't meet validation
                        if (mod->getValidModification())
                        {
                            acceptedModifications.push_back(mod);
                        }
                        else
                        {
                            filteredModificationsWithWarnings.push_back((mod, mod->ModificationErrorsToString()));
                        }
                    }
                    modification_specification = std::vector<std::string>();
                }
            }
        }
        return acceptedModifications;
    }

    std::vector<Modification*> PtmListLoader::ReadModsFromString(const std::string &storedModifications, std::vector<(Modification, std::string)*> &filteredModificationsWithWarnings)
    {
        std::vector<Modification*> acceptedModifications;
        filteredModificationsWithWarnings = std::vector<(Modification filteredMod, std::string warningString)*>();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StringReader uniprot_mods = new StringReader(storedModifications))
        {
            StringReader uniprot_mods = StringReader(storedModifications);
            std::vector<std::string> modification_specification;

            while (uniprot_mods.Peek() != -1)
            {
                std::string line = uniprot_mods.ReadLine();
                modification_specification.push_back(line);
                if (StringHelper::startsWith(line, "//"))
                {
                    for (auto mod : ReadMod("", modification_specification, std::unordered_map<std::string, int>()))
                    {
                        // Filter out the modifications that don't meet validation
                        if (mod->getValidModification())
                        {
                            acceptedModifications.push_back(mod);
                        }
                        else
                        {
                            filteredModificationsWithWarnings.push_back((mod, mod->ModificationErrorsToString()));
                        }
                    }
                    modification_specification = std::vector<std::string>();
                }
            }
        }
        return acceptedModifications;
    }

    std::vector<Modification*> PtmListLoader::ReadMod(const std::string &ptmListLocation, std::vector<std::string> &specification, std::unordered_map<std::string, int> &formalChargesDictionary)
    {
        std::string _id = "";
        std::string _accession = "";
        std::string _modificationType = "";
        std::string _featureType = "";
        std::vector<ModificationMotif*> _target;
        std::string _locationRestriction = ""; //constructor will convert this to enum type
        ChemicalFormula *_chemicalFormula = nullptr;
        std::optional<double> _monoisotopicMass;
        std::unordered_map<std::string, std::vector<std::string>> _databaseReference;
        std::unordered_map<std::string, std::vector<std::string>> _taxonomicRange;
        std::vector<std::string> _keywords;
        std::unordered_map<DissociationType, std::vector<double>> _neutralLosses;
        std::unordered_map<DissociationType, std::vector<double>> _diagnosticIons;
        std::string _fileOrigin = ptmListLocation;

        for (auto line : specification)
        {
            if (line.Length >= 2)
            {
                std::string modKey = line.substr(0, 2);
                std::string modValue = "";
                if (line.Length > 5)
                {
                    try
                    {
                        modValue = line.Split('#')[0].Trim()->substr(5); //removes commented text
                    }
                    catch (...)
                    {
                        //do nothing leave as null
                    }
                }

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                switch (modKey)
//ORIGINAL LINE: case "ID":
                if (modKey == "ID") // Mandatory
                {
                        _id = modValue;

                }
//ORIGINAL LINE: case "AC":
                else if (modKey == "AC") // Do not use! Only present in UniProt ptmlist
                {
                        _accession = modValue;
                        _modificationType = "UniProt";

                }
//ORIGINAL LINE: case "FT":
                else if (modKey == "FT") // Optional
                {
                        _featureType = modValue;

                }
//ORIGINAL LINE: case "TG":
                else if (modKey == "TG") // Which amino acid(s) or motifs is the modification on
                {
                        std::vector<std::string> possibleMotifs = StringHelper::trimEnd(modValue, ".")->Split({" or "}, StringSplitOptions::None);
                        std::vector<ModificationMotif*> acceptableMotifs;
                        for (auto singleTarget : possibleMotifs)
                        {
                            std::string theMotif;
                            char possibleMotifChar;
                            std::unordered_map<std::string, char>::const_iterator AminoAcidCodes_iterator = AminoAcidCodes.find(singleTarget);
                            if (AminoAcidCodes_iterator != AminoAcidCodes.end())
                            {
                                possibleMotifChar = AminoAcidCodes_iterator->second;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                                theMotif = possibleMotifChar.ToString();
                            }
                            else
                            {
                                possibleMotifChar = AminoAcidCodes_iterator->second;
                                theMotif = singleTarget;
                            }
                            ModificationMotif motif;
                            if (ModificationMotif::TryGetMotif(theMotif, motif))
                            {
                                acceptableMotifs.push_back(motif);
                            }
                        }
                        _target = acceptableMotifs.ToList();

                }
//ORIGINAL LINE: case "PP":
                else if (modKey == "PP") // Terminus localization
                {
                        _locationRestriction = modValue;

                }
//ORIGINAL LINE: case "CF":
                else if (modKey == "CF") // Correction formula
                {
                        _chemicalFormula = ChemicalFormula::ParseFormula(StringHelper::replace(modValue, " ", ""));

                }
//ORIGINAL LINE: case "MM":
                else if (modKey == "MM") // Monoisotopic mass difference. Might not precisely correspond to formula!
                {
                        double thisMM;
                        if (!double::TryParse(modValue, NumberStyles::Any, CultureInfo::InvariantCulture, thisMM))
                        {
                            throw MzLibException(line.substr(5) + " is not a valid monoisotopic mass");
                        }
                        _monoisotopicMass = thisMM;

                }
//ORIGINAL LINE: case "DR":
                else if (modKey == "DR") // External database links!
                {
                        auto splitStringDR = StringHelper::trimEnd(modValue, ".")->Split(std::vector<std::string> {"; "}, StringSplitOptions::None);
                        try
                        {
                            IList<std::string> val;
                            std::unordered_map<std::string, std::vector<std::string>>::const_iterator _databaseReference_iterator = _databaseReference.find(splitStringDR[0]);
                            val = _databaseReference_iterator->second;
                            val->Add(splitStringDR[1]);
                        }
                        catch (...)
                        {
                            if (_databaseReference.empty())
                            {
                                _databaseReference = std::unordered_map<std::string, std::vector<std::string>>();
                                _databaseReference.emplace(splitStringDR[0], std::vector<std::vector<std::string>>(1) });
                            }
                            else
                            {
                                _databaseReference.emplace(splitStringDR[0], std::vector<std::vector<std::string>>(1) });
                            }
                        }

                }
//ORIGINAL LINE: case "TR":
                else if (modKey == "TR") // External database links!
                {
                        auto splitStringTR = StringHelper::trimEnd(modValue, ".")->Split(std::vector<std::string> {"; "}, StringSplitOptions::None);
                        try
                        {
                            IList<std::string> val;
                            std::unordered_map<std::string, std::vector<std::string>>::const_iterator _taxonomicRange_iterator = _taxonomicRange.find(splitStringTR[0]);
                            val = _taxonomicRange_iterator->second;
                            val->Add(splitStringTR[1]);
                        }
                        catch (...)
                        {
                            if (_taxonomicRange.empty())
                            {
                                _taxonomicRange = std::unordered_map<std::string, std::vector<std::string>>();
                                _taxonomicRange.emplace(splitStringTR[0], std::vector<std::vector<std::string>>(1) });
                            }
                            else
                            {
                                _taxonomicRange.emplace(splitStringTR[0], std::vector<std::vector<std::string>>(1) });
                            }
                        }

                }
//ORIGINAL LINE: case "KW":
                else if (modKey == "KW") // ; Separated keywords
                {
                        _keywords = std::vector<std::string>(StringHelper::trimEnd(modValue, ".")->Split({"; "}, StringSplitOptions::None));

                    // NOW CUSTOM FIELDS:

                }
//ORIGINAL LINE: case "NL":
                else if (modKey == "NL") // Netural Losses. when field doesn't exist, single equal to 0. these must all be on one line;
                {
                        if (UsefulProteomicsDatabases::PtmListLoader::IsNullOrEmpty(_neutralLosses))
                        {
                            _neutralLosses = std::unordered_map<DissociationType, std::vector<double>>();
                        }
                        _neutralLosses = DiagnosticIonsAndNeutralLosses(modValue, _neutralLosses);

                }
//ORIGINAL LINE: case "DI":
                else if (modKey == "DI") // Masses of diagnostic ions. Might just be "DI"!!! If field doesn't exist, create an empty list!
                {
                        if (UsefulProteomicsDatabases::PtmListLoader::IsNullOrEmpty(_diagnosticIons))
                        {
                            _diagnosticIons = std::unordered_map<DissociationType, std::vector<double>>();
                        }
                        _diagnosticIons = DiagnosticIonsAndNeutralLosses(modValue, _diagnosticIons);

                }
//ORIGINAL LINE: case "MT":
                else if (modKey == "MT") // Modification Type. If the field doesn't exist, set to the database name
                {
                        _modificationType = modValue;

                }
//ORIGINAL LINE: case "//":
                else if (modKey == "//")
                {
                        if (_target.empty() || _target.empty()) //This happens for FT=CROSSLINK modifications. We ignore these for now.
                        {
                            _target = {nullptr};
                        }
                        for (auto motif : _target)
                        {
                            bool useChemFormulaForMM = !_monoisotopicMass && _chemicalFormula != nullptr;
                            bool adjustWithFormalCharge = _monoisotopicMass && !_databaseReference.empty();
                            if (useChemFormulaForMM)
                            {
                                _monoisotopicMass = std::make_optional(_chemicalFormula->getMonoisotopicMass());
                            }
                            if (adjustWithFormalCharge)
                            {
                                _monoisotopicMass = std::make_optional(AdjustMonoIsotopicMassForFormalCharge(_monoisotopicMass, _chemicalFormula, _databaseReference, formalChargesDictionary));
                            }
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            yield return new Modification(_id, _accession, _modificationType, _featureType, motif, _locationRestriction, _chemicalFormula, _monoisotopicMass, _databaseReference, _taxonomicRange, _keywords, _neutralLosses, _diagnosticIons, _fileOrigin);
                        }

                }
                else
                {
                }
            }
        }
    }

    double PtmListLoader::AdjustMonoIsotopicMassForFormalCharge(std::optional<double> &_monoisotopicMass, ChemicalFormula *_chemicalFormula, std::unordered_map<std::string, std::vector<std::string>> &_databaseReference, std::unordered_map<std::string, int> &formalChargesDictionary)
    {
//C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
        for (auto dbAndAccession : _databaseReference.SelectMany(b =>
        {
//C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
            b->Value->Select(c =>
            {
                return b::Key + ";
            };

            case "CID":
                return DissociationType::CID;

            case "MPD":
                return DissociationType::IRMPD;

            case "ECD":
                return DissociationType::ECD;

            case "PQD":
                return DissociationType::PQD;

            case "ETD":
                return DissociationType::ETD;

            case "HCD":
                return DissociationType::HCD;

            case "EThcD":
                return DissociationType::EThcD;

            case "Custom":
                return DissociationType::Custom;

            default:
                return nullptr;
        }
    }

    std::unordered_map<DissociationType, std::vector<double>> PtmListLoader::DiagnosticIonsAndNeutralLosses(const std::string &oneEntry, std::unordered_map<DissociationType, std::vector<double>> &dAndNDictionary)
    {
        try
        {
            std::vector<std::string> nlOrDiEntries = oneEntry.Split({" or "}, StringSplitOptions::None);
            for (auto nlOrDiEntry : nlOrDiEntries)
            {
                std::vector<std::string> entryKeyValue = nlOrDiEntry.Split({":"}, StringSplitOptions::RemoveEmptyEntries);
                if (entryKeyValue.size() == 1) // assume there is no dissociation type listed and only formula or mass are supplied
                {
                    double mm;
                    try
                    {
                        mm = ChemicalFormula::ParseFormula(entryKeyValue[0])->getMonoisotopicMass(); // turn chemical formula into monoisotopic mass
                    }
                    catch (...)
                    {
                        mm = std::stod(entryKeyValue[0], CultureInfo::InvariantCulture);
                    }

                    List<double> val;
                    std::unordered_map<DissociationType, std::vector<double>>::const_iterator dAndNDictionary_iterator = dAndNDictionary.find(DissociationType::AnyActivationType); // check the dictionary to see if AnyActivationType is already listed in the keys,
                    val = dAndNDictionary_iterator->second;
                    if (val != nullptr)
                    {
                        dAndNDictionary[DissociationType::AnyActivationType].push_back(mm);
                    }
                    else
                    {
                        dAndNDictionary.emplace(DissociationType::AnyActivationType, std::vector<double> {mm});
                    }
                }
                else if (entryKeyValue.size() == 2) // an entry with two values is assumed to have a dissociation type and a neutral loss formula or mass
                {
                    std::optional<DissociationType> dt = ModDissociationType(entryKeyValue[0]);
                    if (dt)
                    {
                        //try // see if dictionary already contains key AnyActivationType
                        //{
                        double mm;
                        try
                        {
                            mm = ChemicalFormula::ParseFormula(entryKeyValue[1])->getMonoisotopicMass(); // turn chemical formula into monoisotopic mass
                        }
                        catch (...)
                        {
                            mm = std::stod(entryKeyValue[1], CultureInfo::InvariantCulture);
                        }

                        List<double> val;
                        std::unordered_map<DissociationType, std::vector<double>>::const_iterator dAndNDictionary_iterator = dAndNDictionary.find(static_cast<DissociationType>(dt)); // check the dictionary to see if AnyActivationType is already listed in the keys,
                        val = dAndNDictionary_iterator->second;
                        if (val != nullptr)
                        {
                            dAndNDictionary[static_cast<DissociationType>(dt)].push_back(mm);
                        }
                        else
                        {
                            dAndNDictionary.emplace(static_cast<DissociationType>(dt), std::vector<double> {mm});
                        }
                    }
                    else
                    {
                        throw MzLibException("neutral loss or diagnostic ion entry dissociation type is not parsable");
                    }
                }
                else
                {
                    throw MzLibException("your neutral loss or diagnostic ion is junk");
                }
            }
        }
        catch (...)
        {
            dAndNDictionary = std::unordered_map<DissociationType, std::vector<double>>(); // must have run into some junk
        }

        return dAndNDictionary;
    }
}
