#include "mzIdentML110.Generated.SpectrumIdentificationProtocolType.h"
#include "mzIdentML110.Generated.ParamType.h"
#include "mzIdentML110.Generated.ParamListType.h"
#include "mzIdentML110.Generated.SearchModificationType.h"
#include "mzIdentML110.Generated.EnzymesType.h"
#include "mzIdentML110.Generated.MassTableType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.FilterType.h"
#include "mzIdentML110.Generated.DatabaseTranslationType.h"

namespace mzIdentML110 {
    namespace Generated {

        ParamType *SpectrumIdentificationProtocolType::getSearchType() const {
            return this->searchTypeField;
        }

        void SpectrumIdentificationProtocolType::setSearchType(ParamType *value) {
            this->searchTypeField = value;
        }

        ParamListType *SpectrumIdentificationProtocolType::getAdditionalSearchParams() const {
            return this->additionalSearchParamsField;
        }

        void SpectrumIdentificationProtocolType::setAdditionalSearchParams(ParamListType *value) {
            this->additionalSearchParamsField = value;
        }

        std::vector<SearchModificationType*> SpectrumIdentificationProtocolType::getModificationParams() const {
            return this->modificationParamsField;
        }

        void SpectrumIdentificationProtocolType::setModificationParams(const std::vector<SearchModificationType*> &value) {
            this->modificationParamsField = value;
        }

        EnzymesType *SpectrumIdentificationProtocolType::getEnzymes() const {
            return this->enzymesField;
        }

        void SpectrumIdentificationProtocolType::setEnzymes(EnzymesType *value) {
            this->enzymesField = value;
        }

        std::vector<MassTableType*> SpectrumIdentificationProtocolType::getMassTable() const {
            return this->massTableField;
        }

        void SpectrumIdentificationProtocolType::setMassTable(const std::vector<MassTableType*> &value) {
            this->massTableField = value;
        }

        std::vector<CVParamType*> SpectrumIdentificationProtocolType::getFragmentTolerance() const {
            return this->fragmentToleranceField;
        }

        void SpectrumIdentificationProtocolType::setFragmentTolerance(const std::vector<CVParamType*> &value) {
            this->fragmentToleranceField = value;
        }

        std::vector<CVParamType*> SpectrumIdentificationProtocolType::getParentTolerance() const {
            return this->parentToleranceField;
        }

        void SpectrumIdentificationProtocolType::setParentTolerance(const std::vector<CVParamType*> &value) {
            this->parentToleranceField = value;
        }

        ParamListType *SpectrumIdentificationProtocolType::getThreshold() const {
            return this->thresholdField;
        }

        void SpectrumIdentificationProtocolType::setThreshold(ParamListType *value) {
            this->thresholdField = value;
        }

        std::vector<FilterType*> SpectrumIdentificationProtocolType::getDatabaseFilters() const {
            return this->databaseFiltersField;
        }

        void SpectrumIdentificationProtocolType::setDatabaseFilters(const std::vector<FilterType*> &value) {
            this->databaseFiltersField = value;
        }

        DatabaseTranslationType *SpectrumIdentificationProtocolType::getDatabaseTranslation() const {
            return this->databaseTranslationField;
        }

        void SpectrumIdentificationProtocolType::setDatabaseTranslation(DatabaseTranslationType *value) {
            this->databaseTranslationField = value;
        }

        std::wstring SpectrumIdentificationProtocolType::getanalysisSoftware_ref() const {
            return this->analysisSoftware_refField;
        }

        void SpectrumIdentificationProtocolType::setanalysisSoftware_ref(const std::wstring &value) {
            this->analysisSoftware_refField = value;
        }
    }
}
