#pragma once

#include "../Proteomics/Modifications/ModLocationOnPeptideOrProtein.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>

#include "../Proteomics/Modifications/Modification.h"
#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "unimod_2/unimod_2.h"
using namespace xmlns::schema::unimod_2;

namespace UsefulProteomicsDatabases
{
    class UnimodLoader final
    {
    private:
        static std::unordered_map<std::string, std::string> DictOfElements;

#ifdef ORIG
        //EDGAR: seems to be unused, but causes compilation problems. Deactivating for now.
        static std::unordered_map<position_t, ModLocationOnPeptideOrProtein> positionDict;
#endif

    public:
        static std::vector<Modification*> ReadMods(const std::string &unimodLocation);
    };
}
