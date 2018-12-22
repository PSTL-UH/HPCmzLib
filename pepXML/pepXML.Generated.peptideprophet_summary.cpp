#include "pepXML.Generated.peptideprophet_summary.h"
#include "pepXML.Generated.inputFileType.h"
#include "pepXML.Generated.rocErrorDataType.h"
#include "pepXML.Generated.peptideprophet_summaryDistribution_point.h"
#include "pepXML.Generated.peptideprophet_summaryMixture_model.h"

namespace pepXML {
    namespace Generated {

        std::vector<inputFileType*> peptideprophet_summary::getinputfile() const {
            return this->inputfileField;
        }

        void peptideprophet_summary::setinputfile(const std::vector<inputFileType*> &value) {
            this->inputfileField = value;
        }

        std::vector<rocErrorDataType*> peptideprophet_summary::getroc_error_data() const {
            return this->roc_error_dataField;
        }

        void peptideprophet_summary::setroc_error_data(const std::vector<rocErrorDataType*> &value) {
            this->roc_error_dataField = value;
        }

        std::vector<peptideprophet_summaryDistribution_point*> peptideprophet_summary::getdistribution_point() const {
            return this->distribution_pointField;
        }

        void peptideprophet_summary::setdistribution_point(const std::vector<peptideprophet_summaryDistribution_point*> &value) {
            this->distribution_pointField = value;
        }

        std::vector<peptideprophet_summaryMixture_model*> peptideprophet_summary::getmixture_model() const {
            return this->mixture_modelField;
        }

        void peptideprophet_summary::setmixture_model(const std::vector<peptideprophet_summaryMixture_model*> &value) {
            this->mixture_modelField = value;
        }

        std::wstring peptideprophet_summary::getversion() const {
            return this->versionField;
        }

        void peptideprophet_summary::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        std::wstring peptideprophet_summary::getauthor() const {
            return this->authorField;
        }

        void peptideprophet_summary::setauthor(const std::wstring &value) {
            this->authorField = value;
        }

        float peptideprophet_summary::getmin_prob() const {
            return this->min_probField;
        }

        void peptideprophet_summary::setmin_prob(float value) {
            this->min_probField = value;
        }

        std::wstring peptideprophet_summary::getoptions() const {
            return this->optionsField;
        }

        void peptideprophet_summary::setoptions(const std::wstring &value) {
            this->optionsField = value;
        }

        float peptideprophet_summary::getest_tot_num_correct() const {
            return this->est_tot_num_correctField;
        }

        void peptideprophet_summary::setest_tot_num_correct(float value) {
            this->est_tot_num_correctField = value;
        }

        bool peptideprophet_summary::getest_tot_num_correctSpecified() const {
            return this->est_tot_num_correctFieldSpecified;
        }

        void peptideprophet_summary::setest_tot_num_correctSpecified(bool value) {
            this->est_tot_num_correctFieldSpecified = value;
        }
    }
}
