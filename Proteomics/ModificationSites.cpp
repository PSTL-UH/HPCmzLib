#include "ModificationSites.h"


namespace Proteomics {

    std::vector<ModificationSites> ModificationSiteExtensions::EnumerateActiveSites(ModificationSites sites) {
        for (auto site : Enum::GetValues(ModificationSites::typeid)) {
            if (site == ModificationSites::None) {
                continue;
            }
            if ((sites & site) == site) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return site;
            }
        }
    }

    bool ModificationSiteExtensions::ContainsSites(ModificationSites sites, ModificationSites otherSites) {
        // By convention, if the other site is 'Any', they are always equal
        if (otherSites == ModificationSites::Any) {
            return true;
        }

        if (otherSites == ModificationSites::None) {
            return sites == ModificationSites::None;
        }

        return (~sites & otherSites) == ModificationSites::None;
    }
}
