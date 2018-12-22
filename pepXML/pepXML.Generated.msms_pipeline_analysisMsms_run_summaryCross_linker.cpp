#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summaryCross_linker.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summaryCross_linker::getcross_linker_info() const {
            return this->cross_linker_infoField;
        }

        void msms_pipeline_analysisMsms_run_summaryCross_linker::setcross_linker_info(const std::vector<nameValueType*> &value) {
            this->cross_linker_infoField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summaryCross_linker::getidentifier() const {
            return this->identifierField;
        }

        void msms_pipeline_analysisMsms_run_summaryCross_linker::setidentifier(const std::wstring &value) {
            this->identifierField = value;
        }

        float msms_pipeline_analysisMsms_run_summaryCross_linker::getmass() const {
            return this->massField;
        }

        void msms_pipeline_analysisMsms_run_summaryCross_linker::setmass(float value) {
            this->massField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summaryCross_linker::getlink_sites() const {
            return this->link_sitesField;
        }

        void msms_pipeline_analysisMsms_run_summaryCross_linker::setlink_sites(const std::wstring &value) {
            this->link_sitesField = value;
        }

        msms_pipeline_analysisMsms_run_summaryCross_linkerIsotope_labeled msms_pipeline_analysisMsms_run_summaryCross_linker::getisotope_labeled() const {
            return this->isotope_labeledField;
        }

        void msms_pipeline_analysisMsms_run_summaryCross_linker::setisotope_labeled(msms_pipeline_analysisMsms_run_summaryCross_linkerIsotope_labeled value) {
            this->isotope_labeledField = value;
        }
    }
}
