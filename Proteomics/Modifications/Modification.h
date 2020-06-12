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

#include "ModificationMotif.h"
#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../../MassSpectrometry/MassSpectrometry.h"
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
        std::string getOriginalId() const;
        std::string getAccession() const;
        std::string getModificationType() const;
        std::string getFeatureType() const;
        ModificationMotif *getTarget() const;
        void setTarget(ModificationMotif *value);
        std::string getLocationRestriction() const;
        Chemistry::ChemicalFormula *getChemicalFormula() const;

    private:
        std::optional<double> monoisotopicMass;

    public:
        std::optional<double> getMonoisotopicMass() const;
        std::unordered_map<std::string, std::vector<std::string>> getDatabaseReference() const;
        std::unordered_map<std::string, std::vector<std::string>> getTaxonomicRange() const;
        std::vector<std::string> getKeywords() const;
        std::unordered_map<DissociationType, std::vector<double>> getNeutralLosses() const;
        std::unordered_map<DissociationType, std::vector<double>> getDiagnosticIons() const;
        std::string getFileOrigin() const;

    private:
        void setIdWithMotif(const std::string &value);
        void setOriginalId(const std::string &value);
        void setAccession(const std::string &value);
        void setModificationType(const std::string &value);
        void setFeatureType(const std::string &value);
        void setLocationRestriction(const std::string &value);
        void setChemicalFormula(Chemistry::ChemicalFormula *value);
        void setMonoisotopicMass(const std::optional<double> &value);
        void setDatabaseReference(const std::unordered_map<std::string, std::vector<std::string>> &value);

        void setTaxonomicRange(const std::unordered_map<std::string, std::vector<std::string>> &value);
        void setKeywords(const std::vector<std::string> &value);
        void setNeutralLosses(const std::unordered_map<DissociationType, std::vector<double>> &value);
        void setDiagnosticIons(const std::unordered_map<DissociationType, std::vector<double>> &value);
        void setFileOrigin(const std::string &value);

    protected:
        static constexpr double tolForEquality = 1e-9;

    public:
        bool getValidModification() const;

        Modification(const std::string &_originalId = "",
                     const std::string &_accession = "",
                     const std::string &_modificationType = "",
                     const std::string &_featureType = "",
                     ModificationMotif *_target = nullptr,
                     const std::string &_locationRestriction = "Unassigned.",
                     Chemistry::ChemicalFormula *_chemicalFormula = nullptr,
                     std::optional<double> _monoisotopicMass = std::nullopt,
                     std::unordered_map<std::string, std::vector<std::string>> _databaseReference = std::unordered_map<std::string, std::vector<std::string>>(),
                     std::unordered_map<std::string,std::vector<std::string>> _taxonomicRange = std::unordered_map<std::string, std::vector<std::string>>(),
                     std::vector<std::string> _keywords = std::vector<std::string>(),
                     std::unordered_map<DissociationType,std::vector<double>> _neutralLosses = std::unordered_map<DissociationType, std::vector<double>>(),
                     std::unordered_map<DissociationType, std::vector<double>> _diagnosticIons = std::unordered_map<DissociationType, std::vector<double>>(), const std::string &_fileOrigin = "");

        static std::string ModLocationOnPeptideOrProtein(const std::string &_locationRestriction);

        //bool Equals(std::any o) override;
        bool Equals (Modification* o);

        int GetHashCode();

        std::string ToString();

        std::string ModificationErrorsToString(); //reports errors in required fields.
    };
}
