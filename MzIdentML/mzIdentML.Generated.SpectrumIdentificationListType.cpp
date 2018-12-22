#include "mzIdentML.Generated.SpectrumIdentificationListType.h"
#include "mzIdentML.Generated.MeasureType.h"
#include "mzIdentML.Generated.SpectrumIdentificationResultType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<MeasureType*> SpectrumIdentificationListType::getFragmentationTable() const {
            return this->fragmentationTableField;
        }

        void SpectrumIdentificationListType::setFragmentationTable(const std::vector<MeasureType*> &value) {
            this->fragmentationTableField = value;
        }

        std::vector<SpectrumIdentificationResultType*> SpectrumIdentificationListType::getSpectrumIdentificationResult() const {
            return this->spectrumIdentificationResultField;
        }

        void SpectrumIdentificationListType::setSpectrumIdentificationResult(const std::vector<SpectrumIdentificationResultType*> &value) {
            this->spectrumIdentificationResultField = value;
        }

        std::vector<CVParamType*> SpectrumIdentificationListType::getcvParam() const {
            return this->cvParamField;
        }

        void SpectrumIdentificationListType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> SpectrumIdentificationListType::getuserParam() const {
            return this->userParamField;
        }

        void SpectrumIdentificationListType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        long long SpectrumIdentificationListType::getnumSequencesSearched() const {
            return this->numSequencesSearchedField;
        }

        void SpectrumIdentificationListType::setnumSequencesSearched(long long value) {
            this->numSequencesSearchedField = value;
        }

        bool SpectrumIdentificationListType::getnumSequencesSearchedSpecified() const {
            return this->numSequencesSearchedFieldSpecified;
        }

        void SpectrumIdentificationListType::setnumSequencesSearchedSpecified(bool value) {
            this->numSequencesSearchedFieldSpecified = value;
        }
    }
}
