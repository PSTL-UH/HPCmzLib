#include "PtmListLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include "stringhelper.h"

#include <fstream>
#include <iostream>

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

    std::unordered_map<std::string, char>   PtmListLoader::AminoAcidCodes =  {
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

    
    std::vector<Modification*> PtmListLoader::ReadModsFromFile(const std::string &ptmListLocation,
           std::vector<std::tuple<Modification*, std::string>> &filteredModificationsWithWarnings)
    {
#ifdef ORIG
        return ReadModsFromFile(ptmListLocation, std::unordered_map<std::string, int>(),
                                filteredModificationsWithWarnings).OrderBy([&] (std::any b )     {
                                        b::IdWithMotif;
                                    });
#endif
        std::unordered_map<std::string, int> formalChargesDict;
        std::vector<Modification*> ret = ReadModsFromFile(ptmListLocation, formalChargesDict,
                                                          filteredModificationsWithWarnings);
        std::sort(ret.begin(), ret.end(), [&] (auto *l, auto r ) {
                return l->getIdWithMotif() < r->getIdWithMotif();
            });
        return ret;
    }
    
    std::vector<Modification*> PtmListLoader::ReadModsFromFile(
        const std::string &ptmListLocation,
        std::unordered_map<std::string, int> &formalChargesDictionary,
        std::vector<std::tuple<Modification *, std::string>> &filteredModificationsWithWarnings)
    {
        std::vector<Modification*> acceptedModifications;
        //filteredModificationsWithWarnings = std::vector<(Modification filteredMod, std::string warningString)*>();
        //if ( AminoAcidCodes.size() == 0 ) {
        //    InitAminoAcidCodes();
        // }

        //StreamReader uniprot_mods = StreamReader(ptmListLocation);
        std::ifstream uniprot_mods(ptmListLocation);
        std::vector<std::string> modification_specification;
        
        //This block will read one complete modification entry at a time until the EOF is reached.
        //The Peek method returns an integer value in order to determine whether
        //the end of the file, or another error has occurred.

        // C++ version the peek method returns a character
        while (uniprot_mods.peek() != EOF) 
        {
            //std::string line = uniprot_mods.ReadLine();
            std::string line;
            getline(uniprot_mods, line);
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
                        filteredModificationsWithWarnings.push_back(std::make_tuple(mod, mod->ModificationErrorsToString()));
                    }
                }
                //modification_specification = std::vector<std::string>();
                modification_specification.clear();
            }
        }
        return acceptedModifications;
    }
    
    std::vector<Modification*> PtmListLoader::ReadModsFromString(const std::string &storedModifications,
                                          std::vector<std::tuple<Modification *, std::string>> &filteredModificationsWithWarnings)
    {
        std::vector<Modification*> acceptedModifications;
        //filteredModificationsWithWarnings = std::vector<(Modification filteredMod, std::string warningString)*>();
        //if ( AminoAcidCodes.size() == 0 ) {
        //    InitAminoAcidCodes();
        //}
        
        //StringReader uniprot_mods = StringReader(storedModifications);
        std::stringstream uniprot_mods(storedModifications);
        std::vector<std::string> modification_specification;
        
        while (uniprot_mods.peek() != EOF)
        {
            //std::string line = uniprot_mods.ReadLine();
            std::string line;
            getline(uniprot_mods, line );
            modification_specification.push_back(line);
            if (StringHelper::startsWith(line, "//"))
            {
                std::unordered_map<std::string, int> tmpmap;
                for (auto mod : ReadMod("", modification_specification, tmpmap))
                {
                    // Filter out the modifications that don't meet validation
                    if (mod->getValidModification())
                    {
                        acceptedModifications.push_back(mod);
                    }
                    else
                    {
                        filteredModificationsWithWarnings.push_back(std::make_tuple(mod, mod->ModificationErrorsToString()) );
                    }
                }
                //modification_specification = std::vector<std::string>();
                modification_specification.clear();
            }
        }
        
        return acceptedModifications;
    }
    
    std::vector<Modification*> PtmListLoader::ReadMod(const std::string &ptmListLocation,
                                                      std::vector<std::string> &specification,
                                                      std::unordered_map<std::string, int> &formalChargesDictionary)
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

        std::vector<Modification *> retvec;
        
        for (auto l : specification)
        {
            std::string line = StringHelper::stripUnicode(l);
            if (line.length() >= 2)
            {
                std::string modKey = line.substr(0, 2);
                std::string modValue = "";
                if (line.length() > 5)
                {
                    //modValue = line.Split('#')[0].Trim()->substr(5); //removes commented text
                    char del = '#';
                    modValue = StringHelper::trim(StringHelper::split(line, del)[0]).substr(5); //removes commented text
                }
                
                if (modKey == "ID") // Mandatory
                {
                    _id = modValue;
                    
                }
                else if (modKey == "AC") // Do not use! Only present in UniProt ptmlist
                {
                    _accession = modValue;
                    _modificationType = "UniProt";
                    
                }
                else if (modKey == "FT") // Optional
                {
                    _featureType = modValue;
                    
                }
                else if (modKey == "TG") // Which amino acid(s) or motifs is the modification on
                {
                    //std::vector<std::string> possibleMotifs = StringHelper::trimEnd(modValue, ".")->Split({" or "});
                    std::string del = " or ";
                    std::vector<std::string> possibleMotifs = StringHelper::split(StringHelper::trimEnd(modValue, "."), del);
                    
                    std::vector<ModificationMotif*> acceptableMotifs;
                    for (auto singleTarget : possibleMotifs)
                    {
                        std::string theMotif;
                        char possibleMotifChar;
                        std::unordered_map<std::string, char>::const_iterator AminoAcidCodes_iterator = AminoAcidCodes.find(singleTarget);
                        if (AminoAcidCodes_iterator != AminoAcidCodes.end())
                        {
                            possibleMotifChar = AminoAcidCodes_iterator->second;
                            theMotif = possibleMotifChar;
                        }
                        else
                        {
                            theMotif = singleTarget;
                        }
                        ModificationMotif *motif;
                        if (ModificationMotif::TryGetMotif(theMotif, &motif))
                        {
                            acceptableMotifs.push_back(motif);
                        }
                    }
                    _target = acceptableMotifs;//.ToList();
                    
                }
                else if (modKey == "PP") // Terminus localization
                {
                    _locationRestriction = modValue;
                    
                }
                else if (modKey == "CF") // Correction formula
                {
                    _chemicalFormula = ChemicalFormula::ParseFormula(StringHelper::replace(modValue, " ", ""));
                    
                }
                else if (modKey == "MM") // Monoisotopic mass difference. Might not precisely correspond to formula!
                {
                    double thisMM;
                    //if (!double::TryParse(modValue, NumberStyles::Any, CultureInfo::InvariantCulture, thisMM))
                    try                        
                    {
                        thisMM = std::stod(modValue);
                    }
                    catch (...)
                    {
                        throw MzLibException(line.substr(5) + " is not a valid monoisotopic mass");
                    }
                    _monoisotopicMass = thisMM;
                    
                }
                else if (modKey == "DR") // External database links!
                {
                    //auto splitStringDR = StringHelper::trimEnd(modValue, ".")->Split(std::vector<std::string> {"; "});
                    std::string del = "; ";
                    auto splitStringDR = StringHelper::split(StringHelper::trimEnd(modValue, "."), del );
                    std::vector<std::string> val;
                    std::unordered_map<std::string, std::vector<std::string>>::const_iterator _databaseReference_iterator =
                        _databaseReference.find(splitStringDR[0]);

                    if ( _databaseReference_iterator !=  _databaseReference.end() ) {
                        val = _databaseReference_iterator->second;
                        val.push_back(splitStringDR[1]);
                    }
                    else 
                    {
                        val.push_back(splitStringDR[1]);
                        if (_databaseReference.empty())
                        {
                            //_databaseReference = std::unordered_map<std::string, std::vector<std::string>>();
                            _databaseReference.clear();
                            _databaseReference.emplace(splitStringDR[0], val );
                        }
                        else
                        {
                            _databaseReference.emplace(splitStringDR[0], val );
                        }
                    }
                }
                else if (modKey == "TR") // External database links!
                {
                    //auto splitStringTR = StringHelper::trimEnd(modValue, ".")->Split(std::vector<std::string> {"; "});
                    std::string del = "; ";
                    auto splitStringTR = StringHelper::split(StringHelper::trimEnd(modValue, "."), del );
                    std::vector<std::string> val;
                    std::unordered_map<std::string, std::vector<std::string>>::const_iterator _taxonomicRange_iterator =
                        _taxonomicRange.find(splitStringTR[0]);
                    if ( _taxonomicRange_iterator !=  _taxonomicRange.end() ) {
                        val = _taxonomicRange_iterator->second;
                        val.push_back(splitStringTR[1]);
                    }
                    else
                    {
                        val.push_back(splitStringTR[1]);
                        _taxonomicRange.emplace(splitStringTR[0], val );                        
                    }
                }
                else if (modKey == "KW") // ; Separated keywords
                {
                    std::string del = "; ";
                    _keywords = StringHelper::split(StringHelper::trimEnd(modValue, "."), del);
                    
                    // NOW CUSTOM FIELDS:
                    
                }
                else if (modKey == "NL") // Netural Losses. when field doesn't exist, single equal to 0. these must all be on one line;
                {
                    if (UsefulProteomicsDatabases::PtmListLoader::IsNullOrEmpty(_neutralLosses))
                    {
                        //_neutralLosses = std::unordered_map<DissociationType, std::vector<double>>();
                        _neutralLosses.clear();
                    }
                    _neutralLosses = DiagnosticIonsAndNeutralLosses(modValue, _neutralLosses);
                    
                }
                else if (modKey == "DI") // Masses of diagnostic ions. Might just be "DI"!!! If field doesn't exist, create an empty list!
                {
                    if (UsefulProteomicsDatabases::PtmListLoader::IsNullOrEmpty(_diagnosticIons))
                    {
                        //_diagnosticIons = std::unordered_map<DissociationType, std::vector<double>>();
                        _diagnosticIons.clear();
                    }
                    _diagnosticIons = DiagnosticIonsAndNeutralLosses(modValue, _diagnosticIons);
                    
                }
                else if (modKey == "MT") // Modification Type. If the field doesn't exist, set to the database name
                {
                    _modificationType = modValue;
                    
                }
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
                            _monoisotopicMass = std::make_optional(AdjustMonoIsotopicMassForFormalCharge(_monoisotopicMass,
                                                                                                         _chemicalFormula,
                                                                                                         _databaseReference,
                                                                                                         formalChargesDictionary));
                        }
#ifdef ORIG
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return new Modification(_id, _accession, _modificationType, _featureType, motif,
                                                      _locationRestriction, _chemicalFormula, _monoisotopicMass,
                                                      _databaseReference, _taxonomicRange, _keywords, _neutralLosses,
                                                      _diagnosticIons, _fileOrigin);
#endif
                        Modification *mod = new Modification(_id, _accession, _modificationType, _featureType,
                                                             motif, _locationRestriction, _chemicalFormula,
                                                             _monoisotopicMass,  _databaseReference,
                                                             _taxonomicRange, _keywords, _neutralLosses,
                                                             _diagnosticIons, _fileOrigin);
                        retvec.push_back(mod);
                    }                    
                }
            }
        }
        return retvec;
    }
        
    
    double PtmListLoader::AdjustMonoIsotopicMassForFormalCharge(std::optional<double> &_monoisotopicMass,
                                                                       ChemicalFormula *_chemicalFormula,
                           std::unordered_map<std::string, std::vector<std::string>> &_databaseReference,
                                           std::unordered_map<std::string, int> &formalChargesDictionary)
    {
        //C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
        //foreach (var dbAndAccession in _databaseReference.SelectMany(b => b.Value.Select(c => b.Key + "; " + c)))

        std::vector<std::string> tmpvec;
        for ( auto b : _databaseReference ) {
            for ( auto c: std::get<1>(b) ) {
                std::string s = std::get<0>(b) + ";" + c;
                tmpvec.push_back(s);
            }
        }
        
        for ( auto dbAndAccession : tmpvec )
        {
            if (formalChargesDictionary.find(dbAndAccession) !=  formalChargesDictionary.end() )
            {
                if (_monoisotopicMass.has_value())
                {
                    _monoisotopicMass = std::make_optional(_monoisotopicMass.value() -
                                                         formalChargesDictionary[dbAndAccession] * Constants::protonMass);
                }
                if (_chemicalFormula != nullptr)
                {
                    _chemicalFormula->Remove(PeriodicTable::GetElement("H"), formalChargesDictionary[dbAndAccession]);
                }
                break;
            }
        }
        return _monoisotopicMass.value();
    }

    DissociationType  PtmListLoader::ModDissociationType(std::string modType)
    {
        if (modType ==  "CID")
            return DissociationType::CID;
        
        else if (modType ==  "MPD")
            return DissociationType::IRMPD;
        
        else if (modType ==  "ECD")
            return DissociationType::ECD;
        
        else if (modType ==  "PQD")
            return DissociationType::PQD;
        
        else if (modType ==  "ETD")
            return DissociationType::ETD;
                
        else if (modType ==  "HCD")
            return DissociationType::HCD;
        
        else if (modType ==  "EThcD")
            return DissociationType::EThcD;
        
        else if (modType ==  "Custom") 
            return DissociationType::Custom;
        
        return DissociationType::Unknown;
    }
    
    std::unordered_map<DissociationType, std::vector<double>> PtmListLoader::DiagnosticIonsAndNeutralLosses(const std::string &oneEntry,
                                                                                                    std::unordered_map<DissociationType,
                                                                                                  std::vector<double>> &dAndNDictionary)
    {
        try
        {
            //std::vector<std::string> nlOrDiEntries = StringHelper::split(oneEntry.Split({" or "} );
            std::string del = " or ";
            std::vector<std::string> nlOrDiEntries = StringHelper::split(oneEntry, del);
            for (auto nlOrDiEntry : nlOrDiEntries)
            {
                //std::vector<std::string> entryKeyValue = nlOrDiEntry.Split({":"}, StringSplitOptions::RemoveEmptyEntries);
                std::string del2 = ":";
                std::vector<std::string> entryKeyValue = StringHelper::split(nlOrDiEntry, del2);
                if (entryKeyValue.size() == 1) 
                {
                    // assume there is no dissociation type listed and only formula or mass are supplied
                    double mm;
                    try
                    {
                        // turn chemical formula into monoisotopic mass
                        mm = ChemicalFormula::ParseFormula(entryKeyValue[0])->getMonoisotopicMass(); 
                    }
                    catch (...)
                    {
                        mm = std::stod(entryKeyValue[0] );
                    }
                    
                    std::vector<double> val;
                    // check the dictionary to see if AnyActivationType is already listed in the keys,
                    std::unordered_map<DissociationType, std::vector<double>>::const_iterator dAndNDictionary_iterator =
                        dAndNDictionary.find(DissociationType::AnyActivationType); 
                    if ( dAndNDictionary_iterator != dAndNDictionary.end() ) {
                        val = dAndNDictionary_iterator->second;
                        dAndNDictionary[DissociationType::AnyActivationType].push_back(mm);
                    }
                    else
                    {
                        dAndNDictionary.emplace(DissociationType::AnyActivationType, std::vector<double> {mm});
                    }
                }
                else if (entryKeyValue.size() == 2) 
                {
                    // an entry with two values is assumed to have a dissociation type and a neutral loss formula or mass
                    
                    std::optional<DissociationType> dt = ModDissociationType(entryKeyValue[0]);
                    if (dt.has_value())
                    {
                        //try // see if dictionary already contains key AnyActivationType
                        //{
                        double mm;
                        try
                        {
                            // turn chemical formula into monoisotopic mass
                            mm = ChemicalFormula::ParseFormula(entryKeyValue[1])->getMonoisotopicMass(); 
                        }
                        catch (...)
                        {
                            mm = std::stod(entryKeyValue[1]);
                        }
                        
                        std::vector<double> val;
                        // check the dictionary to see if AnyActivationType is already listed in the keys,
                        std::unordered_map<DissociationType, std::vector<double>>::const_iterator dAndNDictionary_iterator =
                            dAndNDictionary.find(static_cast<DissociationType>(dt.value())); 
                        if (  dAndNDictionary_iterator !=  dAndNDictionary.end() ) {
                            //val = dAndNDictionary_iterator->second;
                            dAndNDictionary[static_cast<DissociationType>(dt.value())].push_back(mm);
                        }
                        else
                        {
                            dAndNDictionary.emplace(static_cast<DissociationType>(dt.value()), std::vector<double> {mm});
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
