#include "mzIdentML110.Generated.SpectrumIdentificationResultType.h"
#include "mzIdentML110.Generated.SpectrumIdentificationItemType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<SpectrumIdentificationItemType*> SpectrumIdentificationResultType::getSpectrumIdentificationItem() const {
            return this->spectrumIdentificationItemField;
        }

        void SpectrumIdentificationResultType::setSpectrumIdentificationItem(const std::vector<SpectrumIdentificationItemType*> &value) {
            this->spectrumIdentificationItemField = value;
        }

        std::vector<CVParamType*> SpectrumIdentificationResultType::getcvParam() const {
            return this->cvParamField;
        }

        void SpectrumIdentificationResultType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> SpectrumIdentificationResultType::getuserParam() const {
            return this->userParamField;
        }

        void SpectrumIdentificationResultType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        std::wstring SpectrumIdentificationResultType::getspectrumID() const {
            return this->spectrumIDField;
        }

        void SpectrumIdentificationResultType::setspectrumID(const std::wstring &value) {
            this->spectrumIDField = value;
        }

        std::wstring SpectrumIdentificationResultType::getspectraData_ref() const {
            return this->spectraData_refField;
        }

        void SpectrumIdentificationResultType::setspectraData_ref(const std::wstring &value) {
            this->spectraData_refField = value;
        }
    }
}
