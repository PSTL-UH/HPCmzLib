#include "IO.MzML.Generated.SampleType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring SampleType::getid() const {
                return this->idField;
            }

            void SampleType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring SampleType::getname() const {
                return this->nameField;
            }

            void SampleType::setname(const std::wstring &value) {
                this->nameField = value;
            }
        }
    }
}
