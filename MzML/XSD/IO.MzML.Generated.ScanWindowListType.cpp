#include "IO.MzML.Generated.ScanWindowListType.h"
#include "IO.MzML.Generated.ParamGroupType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ParamGroupType*> ScanWindowListType::getscanWindow() const {
                return this->scanWindowField;
            }

            void ScanWindowListType::setscanWindow(const std::vector<ParamGroupType*> &value) {
                this->scanWindowField = value;
            }

            int ScanWindowListType::getcount() const {
                return this->countField;
            }

            void ScanWindowListType::setcount(int value) {
                this->countField = value;
            }
        }
    }
}
