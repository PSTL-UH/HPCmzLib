#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide.h"
#include "pepXML.Generated.altProteinDataType.h"
#include "pepXML.Generated.modInfoDataType.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::vector<altProteinDataType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getalternative_protein() const {
            return this->alternative_proteinField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setalternative_protein(const std::vector<altProteinDataType*> &value) {
            this->alternative_proteinField = value;
        }

        modInfoDataType *msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getmodification_info() const {
            return this->modification_infoField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setmodification_info(modInfoDataType *value) {
            this->modification_infoField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getxlink_score() const {
            return this->xlink_scoreField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setxlink_score(const std::vector<nameValueType*> &value) {
            this->xlink_scoreField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getpeptide() const {
            return this->peptideField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setpeptide(const std::wstring &value) {
            this->peptideField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getpeptide_prev_aa() const {
            return this->peptide_prev_aaField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setpeptide_prev_aa(const std::wstring &value) {
            this->peptide_prev_aaField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getpeptide_next_aa() const {
            return this->peptide_next_aaField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setpeptide_next_aa(const std::wstring &value) {
            this->peptide_next_aaField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getprotein() const {
            return this->proteinField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setprotein(const std::wstring &value) {
            this->proteinField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getnum_tot_proteins() const {
            return this->num_tot_proteinsField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setnum_tot_proteins(unsigned int value) {
            this->num_tot_proteinsField = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getcalc_neutral_pep_mass() const {
            return this->calc_neutral_pep_massField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setcalc_neutral_pep_mass(float value) {
            this->calc_neutral_pep_massField = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getcomplement_mass() const {
            return this->complement_massField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setcomplement_mass(float value) {
            this->complement_massField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::getdesignation() const {
            return this->designationField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide::setdesignation(const std::wstring &value) {
            this->designationField = value;
        }
    }
}
