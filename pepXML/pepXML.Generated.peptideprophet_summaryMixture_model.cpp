#include "pepXML.Generated.peptideprophet_summaryMixture_model.h"

namespace pepXML {
    namespace Generated {

        std::vector<std::any> peptideprophet_summaryMixture_model::getItems() const {
            return this->itemsField;
        }

        void peptideprophet_summaryMixture_model::setItems(const std::vector<std::any> &value) {
            this->itemsField = value;
        }

        std::wstring peptideprophet_summaryMixture_model::getprecursor_ion_charge() const {
            return this->precursor_ion_chargeField;
        }

        void peptideprophet_summaryMixture_model::setprecursor_ion_charge(const std::wstring &value) {
            this->precursor_ion_chargeField = value;
        }

        std::wstring peptideprophet_summaryMixture_model::getcomments() const {
            return this->commentsField;
        }

        void peptideprophet_summaryMixture_model::setcomments(const std::wstring &value) {
            this->commentsField = value;
        }

        float peptideprophet_summaryMixture_model::getprior_probability() const {
            return this->prior_probabilityField;
        }

        void peptideprophet_summaryMixture_model::setprior_probability(float value) {
            this->prior_probabilityField = value;
        }

        float peptideprophet_summaryMixture_model::getest_tot_correct() const {
            return this->est_tot_correctField;
        }

        void peptideprophet_summaryMixture_model::setest_tot_correct(float value) {
            this->est_tot_correctField = value;
        }

        std::wstring peptideprophet_summaryMixture_model::gettot_num_spectra() const {
            return this->tot_num_spectraField;
        }

        void peptideprophet_summaryMixture_model::settot_num_spectra(const std::wstring &value) {
            this->tot_num_spectraField = value;
        }

        std::wstring peptideprophet_summaryMixture_model::getnum_iterations() const {
            return this->num_iterationsField;
        }

        void peptideprophet_summaryMixture_model::setnum_iterations(const std::wstring &value) {
            this->num_iterationsField = value;
        }
    }
}
