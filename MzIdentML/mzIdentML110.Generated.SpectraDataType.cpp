#include "mzIdentML110.Generated.SpectraDataType.h"
#include "mzIdentML110.Generated.SpectrumIDFormatType.h"

namespace mzIdentML110 {
    namespace Generated {

        SpectrumIDFormatType *SpectraDataType::getSpectrumIDFormat() const {
            return this->spectrumIDFormatField;
        }

        void SpectraDataType::setSpectrumIDFormat(SpectrumIDFormatType *value) {
            this->spectrumIDFormatField = value;
        }
    }
}
