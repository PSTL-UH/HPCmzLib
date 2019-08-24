#pragma once

#include "../Proteomics/Modifications/ModLocationOnPeptideOrProtein.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "../Proteomics/Modifications/Modification.h"
//namespace Proteomics { class Modification; }

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "Generated/unimod_2.h"
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases
{
    class UnimodLoader final
    {
    private:
        static std::unordered_map<std::string, std::string> DictOfElements;

        static std::unordered_map<position_t, ModLocationOnPeptideOrProtein> positionDict;

    public:
        static std::vector<Modification*> ReadMods(const std::string &unimodLocation);
    };
}
