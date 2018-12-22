#include "pepXML.Generated.msms_pipeline_analysisDataset_derivation.h"
#include "pepXML.Generated.msms_pipeline_analysisDataset_derivationData_filter.h"

namespace pepXML {
    namespace Generated {

        std::vector<msms_pipeline_analysisDataset_derivationData_filter*> msms_pipeline_analysisDataset_derivation::getdata_filter() const {
            return this->data_filterField;
        }

        void msms_pipeline_analysisDataset_derivation::setdata_filter(const std::vector<msms_pipeline_analysisDataset_derivationData_filter*> &value) {
            this->data_filterField = value;
        }

        std::wstring msms_pipeline_analysisDataset_derivation::getgeneration_no() const {
            return this->generation_noField;
        }

        void msms_pipeline_analysisDataset_derivation::setgeneration_no(const std::wstring &value) {
            this->generation_noField = value;
        }
    }
}
