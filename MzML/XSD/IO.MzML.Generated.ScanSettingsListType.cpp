#include "IO.MzML.Generated.ScanSettingsListType.h"
#include "IO.MzML.Generated.ScanSettingsType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ScanSettingsType*> ScanSettingsListType::getscanSettings() const {
                return this->scanSettingsField;
            }

            void ScanSettingsListType::setscanSettings(const std::vector<ScanSettingsType*> &value) {
                this->scanSettingsField = value;
            }

            std::wstring ScanSettingsListType::getcount() const {
                return this->countField;
            }

            void ScanSettingsListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
