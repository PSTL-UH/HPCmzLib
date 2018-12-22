#include "IO.MzML.Generated.InstrumentConfigurationType.h"
#include "IO.MzML.Generated.ComponentListType.h"
#include "IO.MzML.Generated.SoftwareRefType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            ComponentListType *InstrumentConfigurationType::getcomponentList() const {
                return this->componentListField;
            }

            void InstrumentConfigurationType::setcomponentList(ComponentListType *value) {
                this->componentListField = value;
            }

            SoftwareRefType *InstrumentConfigurationType::getsoftwareRef() const {
                return this->softwareRefField;
            }

            void InstrumentConfigurationType::setsoftwareRef(SoftwareRefType *value) {
                this->softwareRefField = value;
            }

            std::wstring InstrumentConfigurationType::getid() const {
                return this->idField;
            }

            void InstrumentConfigurationType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring InstrumentConfigurationType::getscanSettingsRef() const {
                return this->scanSettingsRefField;
            }

            void InstrumentConfigurationType::setscanSettingsRef(const std::wstring &value) {
                this->scanSettingsRefField = value;
            }
        }
    }
}
