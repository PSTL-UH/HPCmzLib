#include "IO.MzML.Generated.OffsetType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring OffsetType::getidRef() const {
                return this->idRefField;
            }

            void OffsetType::setidRef(const std::wstring &value) {
                this->idRefField = value;
            }

            std::wstring OffsetType::getspotID() const {
                return this->spotIDField;
            }

            void OffsetType::setspotID(const std::wstring &value) {
                this->spotIDField = value;
            }

            double OffsetType::getscanTime() const {
                return this->scanTimeField;
            }

            void OffsetType::setscanTime(double value) {
                this->scanTimeField = value;
            }

            bool OffsetType::getscanTimeSpecified() const {
                return this->scanTimeFieldSpecified;
            }

            void OffsetType::setscanTimeSpecified(bool value) {
                this->scanTimeFieldSpecified = value;
            }

            long long OffsetType::getValue() const {
                return this->valueField;
            }

            void OffsetType::setValue(long long value) {
                this->valueField = value;
            }
        }
    }
}
