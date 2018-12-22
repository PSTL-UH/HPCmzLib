#include "mzIdentML.Generated.MzIdentMLType.h"
#include "mzIdentML.Generated.cvType.h"
#include "mzIdentML.Generated.AnalysisSoftwareType.h"
#include "mzIdentML.Generated.ProviderType.h"
#include "mzIdentML.Generated.AbstractContactType.h"
#include "mzIdentML.Generated.SampleType.h"
#include "mzIdentML.Generated.SequenceCollectionType.h"
#include "mzIdentML.Generated.AnalysisCollectionType.h"
#include "mzIdentML.Generated.AnalysisProtocolCollectionType.h"
#include "mzIdentML.Generated.DataCollectionType.h"
#include "mzIdentML.Generated.BibliographicReferenceType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<cvType*> MzIdentMLType::getcvList() const {
            return this->cvListField;
        }

        void MzIdentMLType::setcvList(const std::vector<cvType*> &value) {
            this->cvListField = value;
        }

        std::vector<AnalysisSoftwareType*> MzIdentMLType::getAnalysisSoftwareList() const {
            return this->analysisSoftwareListField;
        }

        void MzIdentMLType::setAnalysisSoftwareList(const std::vector<AnalysisSoftwareType*> &value) {
            this->analysisSoftwareListField = value;
        }

        ProviderType *MzIdentMLType::getProvider() const {
            return this->providerField;
        }

        void MzIdentMLType::setProvider(ProviderType *value) {
            this->providerField = value;
        }

        std::vector<AbstractContactType*> MzIdentMLType::getAuditCollection() const {
            return this->auditCollectionField;
        }

        void MzIdentMLType::setAuditCollection(const std::vector<AbstractContactType*> &value) {
            this->auditCollectionField = value;
        }

        std::vector<SampleType*> MzIdentMLType::getAnalysisSampleCollection() const {
            return this->analysisSampleCollectionField;
        }

        void MzIdentMLType::setAnalysisSampleCollection(const std::vector<SampleType*> &value) {
            this->analysisSampleCollectionField = value;
        }

        SequenceCollectionType *MzIdentMLType::getSequenceCollection() const {
            return this->sequenceCollectionField;
        }

        void MzIdentMLType::setSequenceCollection(SequenceCollectionType *value) {
            this->sequenceCollectionField = value;
        }

        AnalysisCollectionType *MzIdentMLType::getAnalysisCollection() const {
            return this->analysisCollectionField;
        }

        void MzIdentMLType::setAnalysisCollection(AnalysisCollectionType *value) {
            this->analysisCollectionField = value;
        }

        AnalysisProtocolCollectionType *MzIdentMLType::getAnalysisProtocolCollection() const {
            return this->analysisProtocolCollectionField;
        }

        void MzIdentMLType::setAnalysisProtocolCollection(AnalysisProtocolCollectionType *value) {
            this->analysisProtocolCollectionField = value;
        }

        DataCollectionType *MzIdentMLType::getDataCollection() const {
            return this->dataCollectionField;
        }

        void MzIdentMLType::setDataCollection(DataCollectionType *value) {
            this->dataCollectionField = value;
        }

        std::vector<BibliographicReferenceType*> MzIdentMLType::getBibliographicReference() const {
            return this->bibliographicReferenceField;
        }

        void MzIdentMLType::setBibliographicReference(const std::vector<BibliographicReferenceType*> &value) {
            this->bibliographicReferenceField = value;
        }

        DateTime MzIdentMLType::getcreationDate() const {
            return this->creationDateField;
        }

        void MzIdentMLType::setcreationDate(DateTime value) {
            this->creationDateField = value;
        }

        bool MzIdentMLType::getcreationDateSpecified() const {
            return this->creationDateFieldSpecified;
        }

        void MzIdentMLType::setcreationDateSpecified(bool value) {
            this->creationDateFieldSpecified = value;
        }

        std::wstring MzIdentMLType::getversion() const {
            return this->versionField;
        }

        void MzIdentMLType::setversion(const std::wstring &value) {
            this->versionField = value;
        }
    }
}
