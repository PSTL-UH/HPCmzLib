#pragma once

#include "ModificationWithLocation.h"
#include "TerminusLocalization.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationMotif; }


namespace Proteomics {
    class ModificationWithMass : public ModificationWithLocation {
//        #region Public Fields

    public:
        const double monoisotopicMass;
        const std::vector<double> diagnosticIons;
        const std::vector<double> neutralLosses;

//        #endregion Public Fields

//        #region Protected Fields

    protected:
        static constexpr double tolForEquality = 1e-9;

//        #endregion Protected Fields

//        #region Public Constructors

    public:
        ModificationWithMass(const std::wstring &id, const std::wstring &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, double monoisotopicMass, std::unordered_map<std::wstring, std::vector<std::wstring>> &externalDatabaseReferences = nullptr, std::vector<std::wstring> &keywords = nullptr, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons = nullptr);

//        #endregion Public Constructors

//        #region Public Methods

        std::wstring ToString() override;

        bool Equals(std::any o) override;

        int GetHashCode() override;

//        #endregion Public Methods

//        #region Private Methods

    private:
        bool ApproxSequenceEqual(std::vector<double> &a, std::vector<double> &b, double tolForEquality);

//        #endregion Private Methods
    };
}
