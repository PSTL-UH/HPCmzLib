#include <bitset>
#include "ModificationSites.h"


namespace Proteomics {
    namespace AminoAcidPolymer    {
        static  const std::vector<ModificationSites> ModificationSitesValues = {   ModificationSites::None,
                                                                                   ModificationSites::A,
                                                                                   ModificationSites::R,
                                                                                   ModificationSites::N,
                                                                                   ModificationSites::D,
                                                                                   ModificationSites::C,
                                                                                   ModificationSites::E,
                                                                                   ModificationSites::Q,
                                                                                   ModificationSites::G,
                                                                                   ModificationSites::H,
                                                                                   ModificationSites::I,
                                                                                   ModificationSites::L,
                                                                                   ModificationSites::K,
                                                                                   ModificationSites::M,
                                                                                   ModificationSites::F,
                                                                                   ModificationSites::P,
                                                                                   ModificationSites::S,
                                                                                   ModificationSites::T,
                                                                                   ModificationSites::U,
                                                                                   ModificationSites::W,
                                                                                   ModificationSites::Y,
                                                                                   ModificationSites::V,
                                                                                   ModificationSites::NPep,
                                                                                   ModificationSites::PepC,
                                                                                   ModificationSites::NProt,
                                                                                   ModificationSites::ProtC,
                                                                                   ModificationSites::All,
                                                                                   ModificationSites::NTerminus,
                                                                                   ModificationSites::TerminusC,
                                                                                   ModificationSites::Any};
        
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
                    // yield return site;
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
        
        std::vector<ModificationSites> GetValues() {
            return ModificationSiteExtensions::ModificationSitesValues;
        }
        
    }
}
