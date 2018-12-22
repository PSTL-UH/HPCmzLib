#include "mzIdentML.Generated.SpectraDataType.h"
#include "mzIdentML.Generated.SpectrumIDFormatType.h"

namespace mzIdentML {
    namespace Generated {

        SpectrumIDFormatType *SpectraDataType::getSpectrumIDFormat() const {
            return this->spectrumIDFormatField;
        }

        void SpectraDataType::setSpectrumIDFormat(SpectrumIDFormatType *value) {
            this->spectrumIDFormatField = value;
        }
    }
}
