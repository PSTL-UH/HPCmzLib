#include "IO.MzML.Generated.ScanSettingsListType.h"
#include "IO.MzML.Generated.ScanSettingsType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ScanSettingsType*> ScanSettingsListType::getscanSettings() const
            {
                return this->scanSettingsField;
            }

            void ScanSettingsListType::setscanSettings(const std::vector<ScanSettingsType*> &value)
            {
                this->scanSettingsField = value;
            }

            std::string ScanSettingsListType::getcount() const
            {
                return this->countField;
            }

            void ScanSettingsListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
