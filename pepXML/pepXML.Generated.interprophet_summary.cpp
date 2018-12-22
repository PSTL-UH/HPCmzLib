#include "pepXML.Generated.interprophet_summary.h"
#include "pepXML.Generated.inputFileType.h"
#include "pepXML.Generated.rocErrorDataType.h"
#include "pepXML.Generated.mixtureModelType.h"

namespace pepXML {
    namespace Generated {

        std::vector<inputFileType*> interprophet_summary::getinputfile() const {
            return this->inputfileField;
        }

        void interprophet_summary::setinputfile(const std::vector<inputFileType*> &value) {
            this->inputfileField = value;
        }

        std::vector<rocErrorDataType*> interprophet_summary::getroc_error_data() const {
            return this->roc_error_dataField;
        }

        void interprophet_summary::setroc_error_data(const std::vector<rocErrorDataType*> &value) {
            this->roc_error_dataField = value;
        }

        std::vector<mixtureModelType*> interprophet_summary::getmixturemodel() const {
            return this->mixturemodelField;
        }

        void interprophet_summary::setmixturemodel(const std::vector<mixtureModelType*> &value) {
            this->mixturemodelField = value;
        }

        std::wstring interprophet_summary::getversion() const {
            return this->versionField;
        }

        void interprophet_summary::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        std::wstring interprophet_summary::getoptions() const {
            return this->optionsField;
        }

        void interprophet_summary::setoptions(const std::wstring &value) {
            this->optionsField = value;
        }

        float interprophet_summary::getest_tot_num_correct_psm() const {
            return this->est_tot_num_correct_psmField;
        }

        void interprophet_summary::setest_tot_num_correct_psm(float value) {
            this->est_tot_num_correct_psmField = value;
        }

        bool interprophet_summary::getest_tot_num_correct_psmSpecified() const {
            return this->est_tot_num_correct_psmFieldSpecified;
        }

        void interprophet_summary::setest_tot_num_correct_psmSpecified(bool value) {
            this->est_tot_num_correct_psmFieldSpecified = value;
        }

        float interprophet_summary::getest_tot_num_correct_pep() const {
            return this->est_tot_num_correct_pepField;
        }

        void interprophet_summary::setest_tot_num_correct_pep(float value) {
            this->est_tot_num_correct_pepField = value;
        }

        bool interprophet_summary::getest_tot_num_correct_pepSpecified() const {
            return this->est_tot_num_correct_pepFieldSpecified;
        }

        void interprophet_summary::setest_tot_num_correct_pepSpecified(bool value) {
            this->est_tot_num_correct_pepFieldSpecified = value;
        }
    }
}
