#pragma once

#include "../../MassSpectrometry/Enums/DissociationType.h"
#include "../Protein/DatabaseReference.h"
#include "ModLocationOnPeptideOrProtein.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <any>
#include <optional>
#include "stringhelper.h"
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationMotif; }
namespace Chemistry { class ChemicalFormula; }

using namespace Chemistry;
using namespace MassSpectrometry;

namespace Proteomics
{
    class Modification
    {
    private:
        std::string privateIdWithMotif;
        std::string privateOriginalId;
        std::string privateAccession;
        std::string privateModificationType;
        std::string privateFeatureType;
        ModificationMotif *privateTarget;
        std::string privateLocationRestriction;
        Chemistry::ChemicalFormula *privateChemicalFormula;
        std::unordered_map<std::string, std::vector<std::string>> privateDatabaseReference;
        std::unordered_map<std::string, std::vector<std::string>> privateTaxonomicRange;
        std::vector<std::string> privateKeywords;
        std::unordered_map<DissociationType, std::vector<double>> privateNeutralLosses;
        std::unordered_map<DissociationType, std::vector<double>> privateDiagnosticIons;
        std::string privateFileOrigin;

    public:
        std::string getIdWithMotif() const;
        void setIdWithMotif(const std::string &value);
        std::string getOriginalId() const;
        void setOriginalId(const std::string &value);
        std::string getAccession() const;
        void setAccession(const std::string &value);
        std::string getModificationType() const;
        void setModificationType(const std::string &value);
        std::string getFeatureType() const;
        void setFeatureType(const std::string &value);
        ModificationMotif *getTarget() const;
        void setTarget(ModificationMotif *value);
        std::string getLocationRestriction() const;
        void setLocationRestriction(const std::string &value);
        Chemistry::ChemicalFormula *getChemicalFormula() const;
        void setChemicalFormula(Chemistry::ChemicalFormula *value);
    private:
        std::optional<double> monoisotopicMass;

    public:
        std::optional<double> getMonoisotopicMass() const;
        private:
        void setMonoisotopicMass(const std::optional<double> &value);

        std::unordered_map<std::string, std::vector<std::string>> getDatabaseReference() const;
        void setDatabaseReference(const std::unordered_map<std::string, std::vector<std::string>> &value);
        std::unordered_map<std::string, std::vector<std::string>> getTaxonomicRange() const;
        void setTaxonomicRange(const std::unordered_map<std::string, std::vector<std::string>> &value);
        std::vector<std::string> getKeywords() const;
        void setKeywords(const std::vector<std::string> &value);
        std::unordered_map<DissociationType, std::vector<double>> getNeutralLosses() const;
        void setNeutralLosses(const std::unordered_map<DissociationType, std::vector<double>> &value);
        std::unordered_map<DissociationType, std::vector<double>> getDiagnosticIons() const;
        void setDiagnosticIons(const std::unordered_map<DissociationType, std::vector<double>> &value);
        std::string getFileOrigin() const;
        void setFileOrigin(const std::string &value);
    protected:
        static constexpr double tolForEquality = 1e-9;

    public:
        bool getValidModification() const;

        Modification(const std::string &_originalId = "", const std::string &_accession = "", const std::string &_modificationType = "", const std::string &_featureType = "", ModificationMotif *_target = nullptr, const std::string &_locationRestriction = "Unassigned.", Chemistry::ChemicalFormula *_chemicalFormula = nullptr, std::optional<double> &_monoisotopicMass = std::nullopt, std::unordered_map<std::string, std::vector<std::string>> &_databaseReference = std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>> &_taxonomicRange = std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string> &_keywords = std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>> &_neutralLosses = std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>> &_diagnosticIons = std::unordered_map<DissociationType, std::vector<double>>(), const std::string &_fileOrigin = "");

        static std::string ModLocationOnPeptideOrProtein(const std::string &_locationRestriction);

        bool Equals(std::any o) override;

        int GetHashCode() override;

        std::string ToString() override;

        std::string ModificationErrorsToString(); //reports errors in required fields.
    };
}
