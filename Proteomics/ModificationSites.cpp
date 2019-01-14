#include <bitset>
#include "ModificationSites.h"


namespace Proteomics {

    std::vector<ModificationSites> ModificationSiteExtensions::EnumerateActiveSites(ModificationSites sites) {
        std::vector<ModificationSites> s;
        for (auto site : GetValues()) {
            if (site == ModificationSites::None) {
                continue;
            }
            std::bitset<8> bsites((int)sites);
            std::bitset<8> bsite((int)site);
            if ((bsites & bsite) == bsite) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                yield return site;
                s.push_back(site);
            }
        }
        return s;
    }

    bool ModificationSiteExtensions::ContainsSites(ModificationSites sites, ModificationSites otherSites) {
        // By convention, if the other site is 'Any', they are always equal
        if (otherSites == ModificationSites::Any) {
            return true;
        }

        if (otherSites == ModificationSites::None) {
            return sites == ModificationSites::None;
        }

        std::bitset<8> bsites((int)sites);
        std::bitset<8> botherSites((int)otherSites);
        std::bitset<8> bNone((int)ModificationSites::None);
        
        return (~bsites & botherSites) == bNone;
    }
}
