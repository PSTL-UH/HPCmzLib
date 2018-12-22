#pragma once

#include "Modification.h"
#include "TerminusLocalization.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationMotif; }


namespace Proteomics {
    class ModificationWithLocation : public Modification {
//        #region Public Fields

    public:
        static const std::unordered_map<std::wstring, TerminusLocalization> terminusLocalizationTypeCodes;
        const std::unordered_map<std::wstring, std::vector<std::wstring>> linksToOtherDbs;
        const std::vector<std::wstring> keywords;
        const TerminusLocalization terminusLocalization;
        ModificationMotif *const motif;

//        #endregion Public Fields

//        #region Public Constructors

        virtual ~ModificationWithLocation() {
            delete motif;
        }

    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static ModificationWithLocation::StaticConstructor staticConstructor;


    public:
        ModificationWithLocation(const std::wstring &id, const std::wstring &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, std::unordered_map<std::wstring, std::vector<std::wstring>> &linksToOtherDbs = nullptr, std::vector<std::wstring> &keywords);

//        #endregion Public Constructors

//        #region Public Methods

        std::wstring ToString() override;

        bool Equals(std::any o) override;

        int GetHashCode() override;

//        #endregion Public Methods
    };
}
