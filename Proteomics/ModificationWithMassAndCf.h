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

    public:
        ChemicalFormula *const chemicalFormula;

        virtual ~ModificationWithMassAndCf() {
            delete chemicalFormula;
        }

        ModificationWithMassAndCf(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, ChemicalFormula *chemicalFormula, std::optional<double> &mm = std::nullopt, std::unordered_map<std::string, std::vector<std::string>> &linksToOtherDbs, std::vector<std::string> &keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons);

        std::string ToString() override;

        bool Equals(std::any o) override;

        int GetHashCode() override;

    };
}
