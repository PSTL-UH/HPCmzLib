#include "IO.MzML.Generated.FileDescriptionType.h"
#include "IO.MzML.Generated.ParamGroupType.h"
#include "IO.MzML.Generated.SourceFileListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            ParamGroupType *FileDescriptionType::getfileContent() const {
                return this->fileContentField;
            }

            void FileDescriptionType::setfileContent(ParamGroupType *value) {
                this->fileContentField = value;
            }

            SourceFileListType *FileDescriptionType::getsourceFileList() const {
                return this->sourceFileListField;
            }

            void FileDescriptionType::setsourceFileList(SourceFileListType *value) {
                this->sourceFileListField = value;
            }

            std::vector<ParamGroupType*> FileDescriptionType::getcontact() const {
                return this->contactField;
            }

            void FileDescriptionType::setcontact(const std::vector<ParamGroupType*> &value) {
                this->contactField = value;
            }
        }
    }
}
