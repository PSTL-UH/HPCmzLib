#include "IO.MzML.Generated.ScanType.h"
#include "IO.MzML.Generated.ScanWindowListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            ScanWindowListType *ScanType::getscanWindowList() const {
                return this->scanWindowListField;
            }

            void ScanType::setscanWindowList(ScanWindowListType *value) {
                this->scanWindowListField = value;
            }

            std::wstring ScanType::getspectrumRef() const {
                return this->spectrumRefField;
            }

            void ScanType::setspectrumRef(const std::wstring &value) {
                this->spectrumRefField = value;
            }

            std::wstring ScanType::getsourceFileRef() const {
                return this->sourceFileRefField;
            }

            void ScanType::setsourceFileRef(const std::wstring &value) {
                this->sourceFileRefField = value;
            }

            std::wstring ScanType::getexternalSpectrumID() const {
                return this->externalSpectrumIDField;
            }

            void ScanType::setexternalSpectrumID(const std::wstring &value) {
                this->externalSpectrumIDField = value;
            }

            std::wstring ScanType::getinstrumentConfigurationRef() const {
                return this->instrumentConfigurationRefField;
            }

            void ScanType::setinstrumentConfigurationRef(const std::wstring &value) {
                this->instrumentConfigurationRefField = value;
            }
        }
    }
}
