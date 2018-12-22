#include "IO.MzML.Generated.ScanListType.h"
#include "IO.MzML.Generated.ScanType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ScanType*> ScanListType::getscan() const {
                return this->scanField;
            }

            void ScanListType::setscan(const std::vector<ScanType*> &value) {
                this->scanField = value;
            }

            std::wstring ScanListType::getcount() const {
                return this->countField;
            }

            void ScanListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
