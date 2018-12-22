#include "mzIdentML110.Generated.ProteinDetectionType.h"
#include "mzIdentML110.Generated.InputSpectrumIdentificationsType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<InputSpectrumIdentificationsType*> ProteinDetectionType::getInputSpectrumIdentifications() const {
            return this->inputSpectrumIdentificationsField;
        }

        void ProteinDetectionType::setInputSpectrumIdentifications(const std::vector<InputSpectrumIdentificationsType*> &value) {
            this->inputSpectrumIdentificationsField = value;
        }

        std::wstring ProteinDetectionType::getproteinDetectionList_ref() const {
            return this->proteinDetectionList_refField;
        }

        void ProteinDetectionType::setproteinDetectionList_ref(const std::wstring &value) {
            this->proteinDetectionList_refField = value;
        }

        std::wstring ProteinDetectionType::getproteinDetectionProtocol_ref() const {
            return this->proteinDetectionProtocol_refField;
        }

        void ProteinDetectionType::setproteinDetectionProtocol_ref(const std::wstring &value) {
            this->proteinDetectionProtocol_refField = value;
        }
    }
}
