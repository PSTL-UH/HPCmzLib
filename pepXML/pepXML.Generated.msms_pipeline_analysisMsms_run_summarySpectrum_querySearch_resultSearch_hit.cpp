#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit.h"
#include "pepXML.Generated.altProteinDataType.h"
#include "pepXML.Generated.modInfoDataType.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink.h"
#include "pepXML.Generated.nameValueType.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result.h"

namespace pepXML {
    namespace Generated {

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit() {
            this->is_rejectedField = msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitIs_rejected::Item0;
        }

        std::vector<altProteinDataType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getalternative_protein() const {
            return this->alternative_proteinField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setalternative_protein(const std::vector<altProteinDataType*> &value) {
            this->alternative_proteinField = value;
        }

        modInfoDataType *msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getmodification_info() const {
            return this->modification_infoField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setmodification_info(modInfoDataType *value) {
            this->modification_infoField = value;
        }

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink *msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getxlink() const {
            return this->xlinkField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setxlink(msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink *value) {
            this->xlinkField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getsearch_score() const {
            return this->search_scoreField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setsearch_score(const std::vector<nameValueType*> &value) {
            this->search_scoreField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getanalysis_result() const {
            return this->analysis_resultField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setanalysis_result(const std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result*> &value) {
            this->analysis_resultField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getparameter() const {
            return this->parameterField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setparameter(const std::vector<nameValueType*> &value) {
            this->parameterField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::gethit_rank() const {
            return this->hit_rankField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::sethit_rank(unsigned int value) {
            this->hit_rankField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getpeptide() const {
            return this->peptideField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setpeptide(const std::wstring &value) {
            this->peptideField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getpeptide_prev_aa() const {
            return this->peptide_prev_aaField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setpeptide_prev_aa(const std::wstring &value) {
            this->peptide_prev_aaField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getpeptide_next_aa() const {
            return this->peptide_next_aaField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setpeptide_next_aa(const std::wstring &value) {
            this->peptide_next_aaField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getprotein() const {
            return this->proteinField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setprotein(const std::wstring &value) {
            this->proteinField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getnum_tot_proteins() const {
            return this->num_tot_proteinsField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setnum_tot_proteins(unsigned int value) {
            this->num_tot_proteinsField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getnum_matched_ions() const {
            return this->num_matched_ionsField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setnum_matched_ions(const std::wstring &value) {
            this->num_matched_ionsField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::gettot_num_ions() const {
            return this->tot_num_ionsField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::settot_num_ions(const std::wstring &value) {
            this->tot_num_ionsField = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getcalc_neutral_pep_mass() const {
            return this->calc_neutral_pep_massField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setcalc_neutral_pep_mass(float value) {
            this->calc_neutral_pep_massField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getmassdiff() const {
            return this->massdiffField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setmassdiff(const std::wstring &value) {
            this->massdiffField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getnum_tol_term() const {
            return this->num_tol_termField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setnum_tol_term(const std::wstring &value) {
            this->num_tol_termField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getnum_missed_cleavages() const {
            return this->num_missed_cleavagesField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setnum_missed_cleavages(const std::wstring &value) {
            this->num_missed_cleavagesField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getnum_matched_peptides() const {
            return this->num_matched_peptidesField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setnum_matched_peptides(const std::wstring &value) {
            this->num_matched_peptidesField = value;
        }

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink_type msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getxlink_type() const {
            return this->xlink_typeField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setxlink_type(msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink_type value) {
            this->xlink_typeField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getxlink_typeSpecified() const {
            return this->xlink_typeFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setxlink_typeSpecified(bool value) {
            this->xlink_typeFieldSpecified = value;
        }

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitIs_rejected msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getis_rejected() const {
            return this->is_rejectedField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setis_rejected(msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitIs_rejected value) {
            this->is_rejectedField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getprotein_descr() const {
            return this->protein_descrField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setprotein_descr(const std::wstring &value) {
            this->protein_descrField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getcalc_pI() const {
            return this->calc_pIField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setcalc_pI(const std::wstring &value) {
            this->calc_pIField = value;
        }

        double msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getprotein_mw() const {
            return this->protein_mwField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setprotein_mw(double value) {
            this->protein_mwField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::getprotein_mwSpecified() const {
            return this->protein_mwFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit::setprotein_mwSpecified(bool value) {
            this->protein_mwFieldSpecified = value;
        }
    }
}
