#pragma once

#include "../Proteomics/TerminusLocalization.h"
#include <string>
#include <unordered_map>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationWithLocation; }

using namespace Chemistry;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases {
    class UnimodLoader final {
//        #region Private Fields

    private:
        static const std::unordered_map<std::wstring, std::wstring> DictOfElements;

        static const std::unordered_map<position_t, TerminusLocalization> positionDict;

//        #endregion Private Fields

//        #region Internal Methods

    public:
        static std::vector<ModificationWithLocation*> ReadMods(const std::wstring &unimodLocation);

//        #endregion Internal Methods
    };
}
