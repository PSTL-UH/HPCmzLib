#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_query.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result.h"

namespace pepXML {
    namespace Generated {

        std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result*> msms_pipeline_analysisMsms_run_summarySpectrum_query::getsearch_result() const {
            return this->search_resultField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setsearch_result(const std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result*> &value) {
            this->search_resultField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_query::getspectrum() const {
            return this->spectrumField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setspectrum(const std::wstring &value) {
            this->spectrumField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_query::getspectrumNativeID() const {
            return this->spectrumNativeIDField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setspectrumNativeID(const std::wstring &value) {
            this->spectrumNativeIDField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_query::getstart_scan() const {
            return this->start_scanField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setstart_scan(unsigned int value) {
            this->start_scanField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_query::getend_scan() const {
            return this->end_scanField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setend_scan(unsigned int value) {
            this->end_scanField = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_query::getretention_time_sec() const {
            return this->retention_time_secField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setretention_time_sec(float value) {
            this->retention_time_secField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_query::getretention_time_secSpecified() const {
            return this->retention_time_secFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setretention_time_secSpecified(bool value) {
            this->retention_time_secFieldSpecified = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_query::getcollision_energy() const {
            return this->collision_energyField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setcollision_energy(float value) {
            this->collision_energyField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_query::getcollision_energySpecified() const {
            return this->collision_energyFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setcollision_energySpecified(bool value) {
            this->collision_energyFieldSpecified = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_query::getcompensation_voltage() const {
            return this->compensation_voltageField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setcompensation_voltage(float value) {
            this->compensation_voltageField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_query::getcompensation_voltageSpecified() const {
            return this->compensation_voltageFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setcompensation_voltageSpecified(bool value) {
            this->compensation_voltageFieldSpecified = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_query::getprecursor_intensity() const {
            return this->precursor_intensityField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setprecursor_intensity(float value) {
            this->precursor_intensityField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_query::getprecursor_intensitySpecified() const {
            return this->precursor_intensityFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setprecursor_intensitySpecified(bool value) {
            this->precursor_intensityFieldSpecified = value;
        }

        activationMethodType msms_pipeline_analysisMsms_run_summarySpectrum_query::getactivation_method() const {
            return this->activation_methodField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setactivation_method(activationMethodType value) {
            this->activation_methodField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySpectrum_query::getactivation_methodSpecified() const {
            return this->activation_methodFieldSpecified;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setactivation_methodSpecified(bool value) {
            this->activation_methodFieldSpecified = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_query::getprecursor_neutral_mass() const {
            return this->precursor_neutral_massField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setprecursor_neutral_mass(float value) {
            this->precursor_neutral_massField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_query::getassumed_charge() const {
            return this->assumed_chargeField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setassumed_charge(const std::wstring &value) {
            this->assumed_chargeField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_query::getsearch_specification() const {
            return this->search_specificationField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setsearch_specification(const std::wstring &value) {
            this->search_specificationField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_query::getindex() const {
            return this->indexField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_query::setindex(unsigned int value) {
            this->indexField = value;
        }
    }
}
