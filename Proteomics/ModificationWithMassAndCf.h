#pragma once

#include "ModificationWithMass.h"
#include "TerminusLocalization.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <any>
#include <optional>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class ChemicalFormula; }
namespace Proteomics { class ModificationMotif; }

using namespace Chemistry;

namespace Proteomics {
    class ModificationWithMassAndCf : public ModificationWithMass {
//        #region Public Fields

    public:
        ChemicalFormula *const chemicalFormula;

//        #endregion Public Fields

//        #region Public Constructors

        virtual ~ModificationWithMassAndCf() {
            delete chemicalFormula;
        }

        ModificationWithMassAndCf(const std::wstring &id, const std::wstring &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, ChemicalFormula *chemicalFormula, std::optional<double> &mm = std::nullopt, std::unordered_map<std::wstring, std::vector<std::wstring>> &linksToOtherDbs, std::vector<std::wstring> &keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons);

//        #endregion Public Constructors

//        #region Public Methods

        std::wstring ToString() override;

        bool Equals(std::any o) override;

        int GetHashCode() override;

//        #endregion Public Methods
    };
}
