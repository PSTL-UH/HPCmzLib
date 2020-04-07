#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summary.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summarySequence_search_constraint.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summaryAminoacid_modification.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summaryTerminal_modification.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML
{
    namespace Generated
    {

        msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database *msms_pipeline_analysisMsms_run_summarySearch_summary::getsearch_database() const
        {
            return this->search_databaseField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setsearch_database(msms_pipeline_analysisMsms_run_summarySearch_summarySearch_database *value)
        {
            this->search_databaseField = value;
        }

        msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint *msms_pipeline_analysisMsms_run_summarySearch_summary::getenzymatic_search_constraint() const
        {
            return this->enzymatic_search_constraintField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setenzymatic_search_constraint(msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint *value)
        {
            this->enzymatic_search_constraintField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySearch_summarySequence_search_constraint*> msms_pipeline_analysisMsms_run_summarySearch_summary::getsequence_search_constraint() const
        {
            return this->sequence_search_constraintField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setsequence_search_constraint(const std::vector<msms_pipeline_analysisMsms_run_summarySearch_summarySequence_search_constraint*> &value)
        {
            this->sequence_search_constraintField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySearch_summaryAminoacid_modification*> msms_pipeline_analysisMsms_run_summarySearch_summary::getaminoacid_modification() const
        {
            return this->aminoacid_modificationField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setaminoacid_modification(const std::vector<msms_pipeline_analysisMsms_run_summarySearch_summaryAminoacid_modification*> &value)
        {
            this->aminoacid_modificationField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySearch_summaryTerminal_modification*> msms_pipeline_analysisMsms_run_summarySearch_summary::getterminal_modification() const
        {
            return this->terminal_modificationField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setterminal_modification(const std::vector<msms_pipeline_analysisMsms_run_summarySearch_summaryTerminal_modification*> &value)
        {
            this->terminal_modificationField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summarySearch_summary::getparameter() const
        {
            return this->parameterField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setparameter(const std::vector<nameValueType*> &value)
        {
            this->parameterField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summary::getbase_name() const
        {
            return this->base_nameField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setbase_name(const std::string &value)
        {
            this->base_nameField = value;
        }

        engineType msms_pipeline_analysisMsms_run_summarySearch_summary::getsearch_engine() const
        {
            return this->search_engineField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setsearch_engine(engineType value)
        {
            this->search_engineField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summary::getsearch_engine_version() const
        {
            return this->search_engine_versionField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setsearch_engine_version(const std::string &value)
        {
            this->search_engine_versionField = value;
        }

        massType msms_pipeline_analysisMsms_run_summarySearch_summary::getprecursor_mass_type() const
        {
            return this->precursor_mass_typeField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setprecursor_mass_type(massType value)
        {
            this->precursor_mass_typeField = value;
        }

        massType msms_pipeline_analysisMsms_run_summarySearch_summary::getfragment_mass_type() const
        {
            return this->fragment_mass_typeField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setfragment_mass_type(massType value)
        {
            this->fragment_mass_typeField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summary::getout_data_type() const
        {
            return this->out_data_typeField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setout_data_type(const std::string &value)
        {
            this->out_data_typeField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summary::getout_data() const
        {
            return this->out_dataField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setout_data(const std::string &value)
        {
            this->out_dataField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySearch_summary::getsearch_id() const
        {
            return this->search_idField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summary::setsearch_id(unsigned int value)
        {
            this->search_idField = value;
        }
    }
}
