#include "IO.MzML.Generated.InstrumentConfigurationListType.h"
#include "IO.MzML.Generated.InstrumentConfigurationType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<InstrumentConfigurationType*> InstrumentConfigurationListType::getinstrumentConfiguration() const {
                return this->instrumentConfigurationField;
            }

            void InstrumentConfigurationListType::setinstrumentConfiguration(const std::vector<InstrumentConfigurationType*> &value) {
                this->instrumentConfigurationField = value;
            }

            std::wstring InstrumentConfigurationListType::getcount() const {
                return this->countField;
            }

            void InstrumentConfigurationListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
