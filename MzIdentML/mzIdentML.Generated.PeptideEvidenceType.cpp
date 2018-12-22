#include "mzIdentML.Generated.PeptideEvidenceType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        PeptideEvidenceType::PeptideEvidenceType() {
            this->isDecoyField = false;
        }

        std::vector<CVParamType*> PeptideEvidenceType::getcvParam() const {
            return this->cvParamField;
        }

        void PeptideEvidenceType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> PeptideEvidenceType::getuserParam() const {
            return this->userParamField;
        }

        void PeptideEvidenceType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        std::wstring PeptideEvidenceType::getdBSequence_ref() const {
            return this->dBSequence_refField;
        }

        void PeptideEvidenceType::setdBSequence_ref(const std::wstring &value) {
            this->dBSequence_refField = value;
        }

        std::wstring PeptideEvidenceType::getpeptide_ref() const {
            return this->peptide_refField;
        }

        void PeptideEvidenceType::setpeptide_ref(const std::wstring &value) {
            this->peptide_refField = value;
        }

        int PeptideEvidenceType::getstart() const {
            return this->startField;
        }

        void PeptideEvidenceType::setstart(int value) {
            this->startField = value;
        }

        bool PeptideEvidenceType::getstartSpecified() const {
            return this->startFieldSpecified;
        }

        void PeptideEvidenceType::setstartSpecified(bool value) {
            this->startFieldSpecified = value;
        }

        int PeptideEvidenceType::getend() const {
            return this->endField;
        }

        void PeptideEvidenceType::setend(int value) {
            this->endField = value;
        }

        bool PeptideEvidenceType::getendSpecified() const {
            return this->endFieldSpecified;
        }

        void PeptideEvidenceType::setendSpecified(bool value) {
            this->endFieldSpecified = value;
        }

        std::wstring PeptideEvidenceType::getpre() const {
            return this->preField;
        }

        void PeptideEvidenceType::setpre(const std::wstring &value) {
            this->preField = value;
        }

        std::wstring PeptideEvidenceType::getpost() const {
            return this->postField;
        }

        void PeptideEvidenceType::setpost(const std::wstring &value) {
            this->postField = value;
        }

        std::wstring PeptideEvidenceType::gettranslationTable_ref() const {
            return this->translationTable_refField;
        }

        void PeptideEvidenceType::settranslationTable_ref(const std::wstring &value) {
            this->translationTable_refField = value;
        }

        int PeptideEvidenceType::getframe() const {
            return this->frameField;
        }

        void PeptideEvidenceType::setframe(int value) {
            this->frameField = value;
        }

        bool PeptideEvidenceType::getframeSpecified() const {
            return this->frameFieldSpecified;
        }

        void PeptideEvidenceType::setframeSpecified(bool value) {
            this->frameFieldSpecified = value;
        }

        bool PeptideEvidenceType::getisDecoy() const {
            return this->isDecoyField;
        }

        void PeptideEvidenceType::setisDecoy(bool value) {
            this->isDecoyField = value;
        }
    }
}
