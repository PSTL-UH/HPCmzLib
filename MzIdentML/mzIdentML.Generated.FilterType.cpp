#include "mzIdentML.Generated.FilterType.h"
#include "mzIdentML.Generated.ParamType.h"
#include "mzIdentML.Generated.ParamListType.h"

namespace mzIdentML {
    namespace Generated {

        ParamType *FilterType::getFilterType1() const {
            return this->filterType1Field;
        }

        void FilterType::setFilterType1(ParamType *value) {
            this->filterType1Field = value;
        }

        ParamListType *FilterType::getInclude() const {
            return this->includeField;
        }

        void FilterType::setInclude(ParamListType *value) {
            this->includeField = value;
        }

        ParamListType *FilterType::getExclude() const {
            return this->excludeField;
        }

        void FilterType::setExclude(ParamListType *value) {
            this->excludeField = value;
        }
    }
}
