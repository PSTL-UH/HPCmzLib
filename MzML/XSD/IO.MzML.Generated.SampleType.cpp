#include "IO.MzML.Generated.SampleType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string SampleType::getid() const
            {
                return this->idField;
            }

            void SampleType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string SampleType::getname() const
            {
                return this->nameField;
            }

            void SampleType::setname(const std::string &value)
            {
                this->nameField = value;
            }
        }
    }
}
