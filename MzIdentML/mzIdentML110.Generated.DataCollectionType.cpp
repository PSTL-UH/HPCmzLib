#include "mzIdentML110.Generated.DataCollectionType.h"
#include "mzIdentML110.Generated.InputsType.h"
#include "mzIdentML110.Generated.AnalysisDataType.h"

namespace mzIdentML110 {
    namespace Generated {

        InputsType *DataCollectionType::getInputs() const {
            return this->inputsField;
        }

        void DataCollectionType::setInputs(InputsType *value) {
            this->inputsField = value;
        }

        AnalysisDataType *DataCollectionType::getAnalysisData() const {
            return this->analysisDataField;
        }

        void DataCollectionType::setAnalysisData(AnalysisDataType *value) {
            this->analysisDataField = value;
        }
    }
}
