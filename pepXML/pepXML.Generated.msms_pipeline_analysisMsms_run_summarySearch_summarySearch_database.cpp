#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database.h"

namespace pepXML {
    namespace Generated {

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getlocal_path() const {
            return this->local_pathField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setlocal_path(const std::wstring &value) {
            this->local_pathField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getURL() const {
            return this->uRLField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setURL(const std::wstring &value) {
            this->uRLField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getdatabase_name() const {
            return this->database_nameField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setdatabase_name(const std::wstring &value) {
            this->database_nameField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getorig_database_url() const {
            return this->orig_database_urlField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setorig_database_url(const std::wstring &value) {
            this->orig_database_urlField = value;
        }

        DateTime msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getdatabase_release_date() const {
            return this->database_release_dateField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setdatabase_release_date(DateTime value) {
            this->database_release_dateField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getdatabase_release_dateSpecified() const {
            return this->database_release_dateFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setdatabase_release_dateSpecified(bool value) {
            this->database_release_dateFieldSpecified = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getdatabase_release_identifier() const {
            return this->database_release_identifierField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setdatabase_release_identifier(const std::wstring &value) {
            this->database_release_identifierField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getsize_in_db_entries() const {
            return this->size_in_db_entriesField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setsize_in_db_entries(const std::wstring &value) {
            this->size_in_db_entriesField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::getsize_of_residues() const {
            return this->size_of_residuesField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::setsize_of_residues(const std::wstring &value) {
            this->size_of_residuesField = value;
        }

        msms_pipeline_analysisMsms_run_summarySearch_summarySearch_databaseType msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::gettype() const {
            return this->typeField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database::settype(msms_pipeline_analysisMsms_run_summarySearch_summarySearch_databaseType value) {
            this->typeField = value;
        }
    }
}
