#include "IO.MzML.Generated.ScanSettingsType.h"
#include "IO.MzML.Generated.SourceFileRefListType.h"
#include "IO.MzML.Generated.TargetListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            SourceFileRefListType *ScanSettingsType::getsourceFileRefList() const {
                return this->sourceFileRefListField;
            }

            void ScanSettingsType::setsourceFileRefList(SourceFileRefListType *value) {
                this->sourceFileRefListField = value;
            }

            TargetListType *ScanSettingsType::gettargetList() const {
                return this->targetListField;
            }

            void ScanSettingsType::settargetList(TargetListType *value) {
                this->targetListField = value;
            }

            std::wstring ScanSettingsType::getid() const {
                return this->idField;
            }

            void ScanSettingsType::setid(const std::wstring &value) {
                this->idField = value;
            }
        }
    }
}
