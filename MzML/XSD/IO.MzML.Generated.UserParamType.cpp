#include "IO.MzML.Generated.UserParamType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string UserParamType::getname() const
            {
                return this->nameField;
            }

            void UserParamType::setname(const std::string &value)
            {
                this->nameField = value;
            }

            std::string UserParamType::gettype() const
            {
                return this->typeField;
            }

            void UserParamType::settype(const std::string &value)
            {
                this->typeField = value;
            }

            std::string UserParamType::getvalue() const
            {
                return this->valueField;
            }

            void UserParamType::setvalue(const std::string &value)
            {
                this->valueField = value;
            }

            std::string UserParamType::getunitAccession() const
            {
                return this->unitAccessionField;
            }

            void UserParamType::setunitAccession(const std::string &value)
            {
                this->unitAccessionField = value;
            }

            std::string UserParamType::getunitName() const
            {
                return this->unitNameField;
            }

            void UserParamType::setunitName(const std::string &value)
            {
                this->unitNameField = value;
            }

            std::string UserParamType::getunitCvRef() const
            {
                return this->unitCvRefField;
            }

            void UserParamType::setunitCvRef(const std::string &value)
            {
                this->unitCvRefField = value;
            }
        }
    }
}
