#include "mzIdentML.Generated.SpectrumIdentificationItemType.h"
#include "mzIdentML.Generated.PeptideEvidenceRefType.h"
#include "mzIdentML.Generated.IonTypeType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<PeptideEvidenceRefType*> SpectrumIdentificationItemType::getPeptideEvidenceRef() const {
            return this->peptideEvidenceRefField;
        }

        void SpectrumIdentificationItemType::setPeptideEvidenceRef(const std::vector<PeptideEvidenceRefType*> &value) {
            this->peptideEvidenceRefField = value;
        }

        std::vector<IonTypeType*> SpectrumIdentificationItemType::getFragmentation() const {
            return this->fragmentationField;
        }

        void SpectrumIdentificationItemType::setFragmentation(const std::vector<IonTypeType*> &value) {
            this->fragmentationField = value;
        }

        std::vector<CVParamType*> SpectrumIdentificationItemType::getcvParam() const {
            return this->cvParamField;
        }

        void SpectrumIdentificationItemType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> SpectrumIdentificationItemType::getuserParam() const {
            return this->userParamField;
        }

        void SpectrumIdentificationItemType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        int SpectrumIdentificationItemType::getchargeState() const {
            return this->chargeStateField;
        }

        void SpectrumIdentificationItemType::setchargeState(int value) {
            this->chargeStateField = value;
        }

        double SpectrumIdentificationItemType::getexperimentalMassToCharge() const {
            return this->experimentalMassToChargeField;
        }

        void SpectrumIdentificationItemType::setexperimentalMassToCharge(double value) {
            this->experimentalMassToChargeField = value;
        }

        double SpectrumIdentificationItemType::getcalculatedMassToCharge() const {
            return this->calculatedMassToChargeField;
        }

        void SpectrumIdentificationItemType::setcalculatedMassToCharge(double value) {
            this->calculatedMassToChargeField = value;
        }

        bool SpectrumIdentificationItemType::getcalculatedMassToChargeSpecified() const {
            return this->calculatedMassToChargeFieldSpecified;
        }

        void SpectrumIdentificationItemType::setcalculatedMassToChargeSpecified(bool value) {
            this->calculatedMassToChargeFieldSpecified = value;
        }

        float SpectrumIdentificationItemType::getcalculatedPI() const {
            return this->calculatedPIField;
        }

        void SpectrumIdentificationItemType::setcalculatedPI(float value) {
            this->calculatedPIField = value;
        }

        bool SpectrumIdentificationItemType::getcalculatedPISpecified() const {
            return this->calculatedPIFieldSpecified;
        }

        void SpectrumIdentificationItemType::setcalculatedPISpecified(bool value) {
            this->calculatedPIFieldSpecified = value;
        }

        std::wstring SpectrumIdentificationItemType::getpeptide_ref() const {
            return this->peptide_refField;
        }

        void SpectrumIdentificationItemType::setpeptide_ref(const std::wstring &value) {
            this->peptide_refField = value;
        }

        int SpectrumIdentificationItemType::getrank() const {
            return this->rankField;
        }

        void SpectrumIdentificationItemType::setrank(int value) {
            this->rankField = value;
        }

        bool SpectrumIdentificationItemType::getpassThreshold() const {
            return this->passThresholdField;
        }

        void SpectrumIdentificationItemType::setpassThreshold(bool value) {
            this->passThresholdField = value;
        }

        std::wstring SpectrumIdentificationItemType::getmassTable_ref() const {
            return this->massTable_refField;
        }

        void SpectrumIdentificationItemType::setmassTable_ref(const std::wstring &value) {
            this->massTable_refField = value;
        }

        std::wstring SpectrumIdentificationItemType::getsample_ref() const {
            return this->sample_refField;
        }

        void SpectrumIdentificationItemType::setsample_ref(const std::wstring &value) {
            this->sample_refField = value;
        }
    }
}
