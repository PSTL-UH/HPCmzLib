#include "mzIdentML.Generated.DataCollectionType.h"
#include "mzIdentML.Generated.InputsType.h"
#include "mzIdentML.Generated.AnalysisDataType.h"

namespace mzIdentML {
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
