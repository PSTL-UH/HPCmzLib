#include "IO.MzML.Generated.mzMLType.h"
#include "IO.MzML.Generated.CVListType.h"
#include "IO.MzML.Generated.FileDescriptionType.h"
#include "IO.MzML.Generated.ReferenceableParamGroupListType.h"
#include "IO.MzML.Generated.SampleListType.h"
#include "IO.MzML.Generated.SoftwareListType.h"
#include "IO.MzML.Generated.ScanSettingsListType.h"
#include "IO.MzML.Generated.InstrumentConfigurationListType.h"
#include "IO.MzML.Generated.DataProcessingListType.h"
#include "IO.MzML.Generated.RunType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            CVListType *mzMLType::getcvList() const {
                return this->cvListField;
            }

            void mzMLType::setcvList(CVListType *value) {
                this->cvListField = value;
            }

            FileDescriptionType *mzMLType::getfileDescription() const {
                return this->fileDescriptionField;
            }

            void mzMLType::setfileDescription(FileDescriptionType *value) {
                this->fileDescriptionField = value;
            }

            ReferenceableParamGroupListType *mzMLType::getreferenceableParamGroupList() const {
                return this->referenceableParamGroupListField;
            }

            void mzMLType::setreferenceableParamGroupList(ReferenceableParamGroupListType *value) {
                this->referenceableParamGroupListField = value;
            }

            SampleListType *mzMLType::getsampleList() const {
                return this->sampleListField;
            }

            void mzMLType::setsampleList(SampleListType *value) {
                this->sampleListField = value;
            }

            SoftwareListType *mzMLType::getsoftwareList() const {
                return this->softwareListField;
            }

            void mzMLType::setsoftwareList(SoftwareListType *value) {
                this->softwareListField = value;
            }

            ScanSettingsListType *mzMLType::getscanSettingsList() const {
                return this->scanSettingsListField;
            }

            void mzMLType::setscanSettingsList(ScanSettingsListType *value) {
                this->scanSettingsListField = value;
            }

            InstrumentConfigurationListType *mzMLType::getinstrumentConfigurationList() const {
                return this->instrumentConfigurationListField;
            }

            void mzMLType::setinstrumentConfigurationList(InstrumentConfigurationListType *value) {
                this->instrumentConfigurationListField = value;
            }

            DataProcessingListType *mzMLType::getdataProcessingList() const {
                return this->dataProcessingListField;
            }

            void mzMLType::setdataProcessingList(DataProcessingListType *value) {
                this->dataProcessingListField = value;
            }

            RunType *mzMLType::getrun() const {
                return this->runField;
            }

            void mzMLType::setrun(RunType *value) {
                this->runField = value;
            }

            std::wstring mzMLType::getaccession() const {
                return this->accessionField;
            }

            void mzMLType::setaccession(const std::wstring &value) {
                this->accessionField = value;
            }

            std::wstring mzMLType::getversion() const {
                return this->versionField;
            }

            void mzMLType::setversion(const std::wstring &value) {
                this->versionField = value;
            }

            std::wstring mzMLType::getid() const {
                return this->idField;
            }

            void mzMLType::setid(const std::wstring &value) {
                this->idField = value;
            }
        }
    }
}
