#include "UsefulProteomicsDatabases.Generated.specificity_t.h"
#include "UsefulProteomicsDatabases.Generated.NeutralLoss_t.h"
#include "UsefulProteomicsDatabases.Generated.PepNeutralLoss_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        specificity_t::specificity_t() {
            this->hiddenField = false;
            this->spec_groupField = L"1";
        }

        std::vector<NeutralLoss_t*> specificity_t::getNeutralLoss() const {
            return this->neutralLossField;
        }

        void specificity_t::setNeutralLoss(const std::vector<NeutralLoss_t*> &value) {
            this->neutralLossField = value;
        }

        std::vector<PepNeutralLoss_t*> specificity_t::getPepNeutralLoss() const {
            return this->pepNeutralLossField;
        }

        void specificity_t::setPepNeutralLoss(const std::vector<PepNeutralLoss_t*> &value) {
            this->pepNeutralLossField = value;
        }

        std::wstring specificity_t::getmisc_notes() const {
            return this->misc_notesField;
        }

        void specificity_t::setmisc_notes(const std::wstring &value) {
            this->misc_notesField = value;
        }

        bool specificity_t::gethidden() const {
            return this->hiddenField;
        }

        void specificity_t::sethidden(bool value) {
            this->hiddenField = value;
        }

        std::wstring specificity_t::getsite() const {
            return this->siteField;
        }

        void specificity_t::setsite(const std::wstring &value) {
            this->siteField = value;
        }

        position_t specificity_t::getposition() const {
            return this->positionField;
        }

        void specificity_t::setposition(position_t value) {
            this->positionField = value;
        }

        classification_t specificity_t::getclassification() const {
            return this->classificationField;
        }

        void specificity_t::setclassification(classification_t value) {
            this->classificationField = value;
        }

        std::wstring specificity_t::getspec_group() const {
            return this->spec_groupField;
        }

        void specificity_t::setspec_group(const std::wstring &value) {
            this->spec_groupField = value;
        }
    }
}
