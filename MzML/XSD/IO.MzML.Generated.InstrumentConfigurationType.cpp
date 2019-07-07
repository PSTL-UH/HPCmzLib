#include "IO.MzML.Generated.InstrumentConfigurationType.h"
#include "IO.MzML.Generated.ComponentListType.h"
#include "IO.MzML.Generated.SoftwareRefType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            ComponentListType *InstrumentConfigurationType::getcomponentList() const
            {
                return this->componentListField;
            }

            void InstrumentConfigurationType::setcomponentList(ComponentListType *value)
            {
                this->componentListField = value;
            }

            SoftwareRefType *InstrumentConfigurationType::getsoftwareRef() const
            {
                return this->softwareRefField;
            }

            void InstrumentConfigurationType::setsoftwareRef(SoftwareRefType *value)
            {
                this->softwareRefField = value;
            }

            std::string InstrumentConfigurationType::getid() const
            {
                return this->idField;
            }

            void InstrumentConfigurationType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string InstrumentConfigurationType::getscanSettingsRef() const
            {
                return this->scanSettingsRefField;
            }

            void InstrumentConfigurationType::setscanSettingsRef(const std::string &value)
            {
                this->scanSettingsRefField = value;
            }
        }
    }
}
