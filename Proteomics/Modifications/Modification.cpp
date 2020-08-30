#include "Modification.h"
#include "ModificationMotif.h"
#include "../../Chemistry/ChemicalFormula.h"
#include "../../Chemistry/ClassExtensions.h"
#include "stringhelper.h"
#include <iostream>

using namespace Chemistry;
using namespace MassSpectrometry;

namespace Proteomics
{

    std::string Modification::getIdWithMotif() const
    {
        return privateIdWithMotif;
    }

    void Modification::setIdWithMotif(const std::string &value)
    {
        privateIdWithMotif = value;
    }

    std::string Modification::getOriginalId() const
    {
        return privateOriginalId;
    }

    void Modification::setOriginalId(const std::string &value)
    {
        privateOriginalId = value;
    }

    std::string Modification::getAccession() const
    {
        return privateAccession;
    }

    void Modification::setAccession(const std::string &value)
    {
        privateAccession = value;
    }

    std::string Modification::getModificationType() const
    {
        return privateModificationType;
    }

    void Modification::setModificationType(const std::string &value)
    {
        privateModificationType = value;
    }

    std::string Modification::getFeatureType() const
    {
        return privateFeatureType;
    }

    void Modification::setFeatureType(const std::string &value)
    {
        privateFeatureType = value;
    }

    ModificationMotif *Modification::getTarget() const
    {
        return privateTarget;
    }

    void Modification::setTarget(ModificationMotif *value)
    {
        privateTarget = value;
    }

    std::string Modification::getLocationRestriction() const
    {
        return privateLocationRestriction;
    }

    void Modification::setLocationRestriction(const std::string &value)
    {
        privateLocationRestriction = value;
    }

    Chemistry::ChemicalFormula *Modification::getChemicalFormula() const
    {
        return privateChemicalFormula;
    }

    void Modification::setChemicalFormula(Chemistry::ChemicalFormula *value)
    {
        privateChemicalFormula = value;
    }

    std::optional<double> Modification::getMonoisotopicMass() const
    {
        std::optional<double> d = monoisotopicMass;
        return Chemistry::ClassExtensions::RoundedDouble(d);
    }

    void Modification::setMonoisotopicMass(const std::optional<double> &value)
    {
        monoisotopicMass = value;
    }

    std::unordered_map<std::string, std::vector<std::string>> Modification::getDatabaseReference() const
    {
        return privateDatabaseReference;
    }

    void Modification::setDatabaseReference(const std::unordered_map<std::string, std::vector<std::string>> &value)
    {
        privateDatabaseReference = value;
    }

    std::unordered_map<std::string, std::vector<std::string>> Modification::getTaxonomicRange() const
    {
        return privateTaxonomicRange;
    }

    void Modification::setTaxonomicRange(const std::unordered_map<std::string, std::vector<std::string>> &value)
    {
        privateTaxonomicRange = value;
    }

    std::vector<std::string> Modification::getKeywords() const
    {
        return privateKeywords;
    }

    void Modification::setKeywords(const std::vector<std::string> &value)
    {
        privateKeywords = value;
    }

    std::unordered_map<DissociationType, std::vector<double>> Modification::getNeutralLosses() const
    {
        return privateNeutralLosses;
    }

    void Modification::setNeutralLosses(const std::unordered_map<DissociationType, std::vector<double>> &value)
    {
        privateNeutralLosses = value;
    }

    std::unordered_map<DissociationType, std::vector<double>> Modification::getDiagnosticIons() const
    {
        return privateDiagnosticIons;
    }

    void Modification::setDiagnosticIons(const std::unordered_map<DissociationType, std::vector<double>> &value)
    {
        privateDiagnosticIons = value;
    }

    std::string Modification::getFileOrigin() const
    {
        return privateFileOrigin;
    }

    void Modification::setFileOrigin(const std::string &value)
    {
        privateFileOrigin = value;
    }

    bool Modification::getValidModification() const
    {
        auto found = privateModificationType.find(':');
        return this->privateIdWithMotif != ""                 &&
            (this->privateChemicalFormula != nullptr      ||
             this->getMonoisotopicMass().has_value()     ) &&
            this->privateTarget != nullptr                    &&
            this->privateLocationRestriction != "Unassigned." &&
            this->privateModificationType != ""               &&
            this->privateFeatureType != "CROSSLINK"           &&
            found == std::string::npos;
        
    }

    Modification::Modification(const std::string &_originalId,
                               const std::string &_accession,
                               const std::string &_modificationType,
                               const std::string &_featureType,
                               ModificationMotif *_target,
                               const std::string &_locationRestriction,
                               Chemistry::ChemicalFormula *_chemicalFormula,
                               std::optional<double> _monoisotopicMass,
                               std::unordered_map<std::string, std::vector<std::string>> _databaseReference,
                               std::unordered_map<std::string, std::vector<std::string>> _taxonomicRange,
                               std::vector<std::string> _keywords,
                               std::unordered_map<DissociationType, std::vector<double>> _neutralLosses,
                               std::unordered_map<DissociationType, std::vector<double>> _diagnosticIons,
                               const std::string &_fileOrigin)
    {
        if (_originalId != "")
        {
            if (_originalId.find(" on ") != std::string::npos)
            {
                privateIdWithMotif = _originalId;
#ifdef ORIG
                this->setOriginalId(_originalId.Split({" on "}, StringSplitOptions::None)[0]);
#endif
                auto pos = _originalId.find(" on "); 
                privateOriginalId = _originalId.substr(0, pos);
            }
            else if (_originalId.find(" of ") != std::string::npos)
            {
                privateIdWithMotif = StringHelper::replace(_originalId, " of ", " on ");
#ifdef ORIG
                this->setOriginalId(_originalId.Split({" of ", " on "}, StringSplitOptions::None)[0]);
#endif
                auto pos1 = _originalId.find(" on ");                    
                auto pos2 = _originalId.find(" of ");
                auto pos = pos1 < pos2 ? pos1 : pos2;
                privateOriginalId = _originalId.substr(0, pos);
            }
            else if (_target != nullptr)
            {
                privateIdWithMotif = _originalId + " on " + _target->ToString();
                privateOriginalId = _originalId ;
            }
            else
            {
                privateOriginalId = _originalId;
            }
        }

        privateAccession = _accession;
        privateModificationType = _modificationType;
        privateFeatureType = _featureType;
        privateTarget = _target;
        privateLocationRestriction = ModLocationOnPeptideOrProtein(_locationRestriction);
        privateChemicalFormula = _chemicalFormula;
        monoisotopicMass = _monoisotopicMass ;
        privateDatabaseReference = _databaseReference;
        privateTaxonomicRange = _taxonomicRange;
        privateKeywords = _keywords;
        privateNeutralLosses = _neutralLosses;
        privateDiagnosticIons = _diagnosticIons;
        privateFileOrigin = _fileOrigin;

        if (!getMonoisotopicMass().has_value() && privateChemicalFormula != nullptr)
        {
            monoisotopicMass = std::make_optional(privateChemicalFormula->getMonoisotopicMass());
        }
    }

    std::string Modification::ModLocationOnPeptideOrProtein(const std::string &_locationRestriction)
    {
        //C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
        //        switch (_locationRestriction)
        if (_locationRestriction == "N-terminal.") {
            return _locationRestriction;
        }
        else if (_locationRestriction == "C-terminal.") {
            return _locationRestriction;            
        }
        else if (_locationRestriction == "Peptide N-terminal.")  {
            return _locationRestriction;            
        }
        else if (_locationRestriction == "Peptide C-terminal.")  {
                return _locationRestriction;
        }
        else if (_locationRestriction == "Anywhere.")  {
                return _locationRestriction;
        }
        else  {
                return "Unassigned.";
        }
    }

    bool Modification::Equals(Modification *m)
    {
        return privateIdWithMotif == m->getIdWithMotif()             &&
            privateOriginalId == m->getOriginalId()                  &&
            privateModificationType == m->getModificationType()      &&
            ( (getMonoisotopicMass() == m->getMonoisotopicMass()) ||
              (getMonoisotopicMass().has_value()                 &&
              m->getMonoisotopicMass().has_value()              &&
              std::abs(static_cast<double>(m->getMonoisotopicMass().value()) - static_cast<double>(getMonoisotopicMass().value()) ) < tolForEquality));
    }

    int Modification::GetHashCode()
    {
        std::string tempVar = privateIdWithMotif;
        std::string tempVar2 = privateOriginalId;
        std::string id = (tempVar != "") ? tempVar : (tempVar2 != "") ? tempVar2 : "";
        std::string tempVar3 = privateModificationType;
        std::string mt = (tempVar3 != "") ? tempVar3 : "";
        return StringHelper::GetHashCode(id) ^ StringHelper::GetHashCode(mt);
    }

    std::string Modification::ToString()
    {
        StringBuilder *sb = new StringBuilder();
        if (privateIdWithMotif != "")
        {
            sb->appendLine("ID   " + privateIdWithMotif);
        }
        if (privateAccession != "")
        {
            sb->appendLine("AC   " + privateAccession);
        }
        if (privateModificationType != "")
        {
            sb->appendLine("MT   " + privateModificationType);
        }
        if (privateFeatureType != "")
        {
            sb->appendLine("FT   " + privateFeatureType);
        }
        if (privateTarget != nullptr)
        {
            sb->appendLine("TG   " + privateTarget->ToString());
        } // at this stage, each mod has only one target though many may have the same Id
        if (privateLocationRestriction != "")
        {
            sb->appendLine("PP   " + privateLocationRestriction);
        }
        if (privateChemicalFormula != nullptr)
        {
            sb->appendLine("CF   " + privateChemicalFormula->getFormula());
        }
        if (getMonoisotopicMass().has_value())
        {
            sb->appendLine("MM   " + std::to_string(getMonoisotopicMass().value()));
        }
        if (!privateDatabaseReference.empty())
        {
#ifdef ORIG
            std::vector<std::string> myKeys(getDatabaseReference().Keys);
#endif
            std::vector<std::string> myKeys;
            for ( auto gD: privateDatabaseReference ) {
                myKeys.push_back(std::get<0>(gD));
            }
            
            std::sort(myKeys.begin(), myKeys.end());
            for (auto myKey : myKeys)
            {
                std::vector<std::string> myValues(privateDatabaseReference[myKey]);
                std::sort(myValues.begin(), myValues.end());
                for (auto myValue : myValues)
                {
                    sb->appendLine("DR   " + myKey + "; " + myValue);
                }
            }
        }
        if (!privateTaxonomicRange.empty())
        {
#ifdef ORIG
            std::vector<std::string> myKeys(getTaxonomicRange().Keys);
#endif
            std::vector<std::string> myKeys;
            for ( auto gT: privateTaxonomicRange ) {
                myKeys.push_back(std::get<0>(gT));
            }
            
            std::sort(myKeys.begin(), myKeys.end());
            for (auto myKey : myKeys)
            {
                std::vector<std::string> myValues(privateTaxonomicRange[myKey]);
                std::sort(myValues.begin(), myValues.end());
                for (auto myValue : myValues)
                {
                    sb->appendLine("TR   " + myKey + "; " + myValue);
                }
            }
        }
        if (!privateNeutralLosses.empty())
        {
#ifdef ORIG
            std::vector<DissociationType> allDissociationTypes = getNeutralLosses().Keys->ToList();
#endif
            std::vector<DissociationType> allDissociationTypes;
            for ( auto nL : privateNeutralLosses ) {
                allDissociationTypes.push_back( std::get<0>(nL));
            }
            std::sort(allDissociationTypes.begin(), allDissociationTypes.end());
            
            for (auto dissociationType : allDissociationTypes)
            {
                StringBuilder *myLine = new StringBuilder();
                myLine->append("NL   ");
                
                std::vector<double> myValues(privateNeutralLosses[dissociationType]);
                std::sort(myValues.begin(), myValues.end());
                for (int i = 0; i < (int)myValues.size(); i++)
                {
                    std::optional<double> d =std::make_optional( myValues[i]);
                    myLine->append(std::to_string(static_cast<int>(dissociationType)) + ":" + std::to_string(Chemistry::ClassExtensions::RoundedDouble(d).value()));
                    if (i < (int) myValues.size() - 1)
                    {
                        myLine->append(" or ");
                    }
                }
                
                sb->appendLine(myLine->toString());
                
                delete myLine;
            }
        }
        if (!privateDiagnosticIons.empty())
        {
#ifdef ORIG
            std::vector<DissociationType> allDissociationTypes = getDiagnosticIons().Keys->ToList();
#endif
            std::vector<DissociationType> allDissociationTypes;
            for ( auto nD: privateDiagnosticIons ) {
                allDissociationTypes.push_back(std::get<0>(nD));
            }
            std::sort(allDissociationTypes.begin(), allDissociationTypes.end());
            
            for (auto dissociationType : allDissociationTypes)
            {
                StringBuilder *myLine = new StringBuilder();
                myLine->append("DI   ");
                
                std::vector<double> myValues(privateDiagnosticIons[dissociationType]);
                std::sort(myValues.begin(), myValues.end());
                for (int i = 0; i < (int)myValues.size(); i++)
                {
                    std::optional<double> d =std::make_optional( myValues[i]);
                    myLine->append(std::to_string(static_cast<int>(dissociationType)) + ":" + std::to_string(Chemistry::ClassExtensions::RoundedDouble(d).value()));
                    if (i < (int)myValues.size() - 1)
                    {
                        myLine->append(" or ");
                    }
                }
                
                sb->appendLine(myLine->toString());
                
                delete myLine;
            }
        }

        if (!privateKeywords.empty())
        {
#ifdef ORIG
//                sb->appendLine("KW   " + std::string::Join(" or ", this->getKeywords().ToList()->OrderBy([&] (std::any b)
//                {
//                    return b;
//                })));
#endif
            StringBuilder *myLine = new StringBuilder();
            myLine->append("KW   ");
            std::string del = " or ";
            myLine->append(StringHelper::join(getKeywords(), del));
            sb->appendLine(myLine->toString() );
        }

        std::string s = sb->toString();
        delete sb;
        return s;
    }

    std::string Modification::ModificationErrorsToString()
    {
        StringBuilder *sb = new StringBuilder();

        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        sb->append(ToString());

        if (getIdWithMotif() == "")
        {
            sb->appendLine("#Required field ID missing or malformed. Current value = " + getIdWithMotif());
        }

        if (getModificationType() == "")
        {
            sb->appendLine("#Required field MT missing or malformed. Current value = " + getModificationType());
        }

        if (getLocationRestriction() == "")
        {
            sb->appendLine("#Required field PP missing or malformed. Current value = " + getLocationRestriction() + ".");
        }

        if (getChemicalFormula() == nullptr && !getMonoisotopicMass())
        {
            sb->appendLine("#Required fields CF and MM are both missing or malformed. One of those two fields must be provided.");
        }

        if (getModificationType() != "" && getModificationType().find(':') != std::string::npos)
        {
            sb->appendLine("#Modification type cannot contain ':'!");
        }

        sb->append("#This modification can be found in file " + getFileOrigin());

        std::string s = sb->toString();
        delete sb;
        return s;
    }
}
