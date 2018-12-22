#include "IO.MzML.Generated.SpectrumListType.h"
#include "IO.MzML.Generated.SpectrumType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<SpectrumType*> SpectrumListType::getspectrum() const {
                return this->spectrumField;
            }

            void SpectrumListType::setspectrum(const std::vector<SpectrumType*> &value) {
                this->spectrumField = value;
            }

            std::wstring SpectrumListType::getcount() const {
                return this->countField;
            }

            void SpectrumListType::setcount(const std::wstring &value) {
                this->countField = value;
            }

            std::wstring SpectrumListType::getdefaultDataProcessingRef() const {
                return this->defaultDataProcessingRefField;
            }

            void SpectrumListType::setdefaultDataProcessingRef(const std::wstring &value) {
                this->defaultDataProcessingRefField = value;
            }
        }
    }
}
