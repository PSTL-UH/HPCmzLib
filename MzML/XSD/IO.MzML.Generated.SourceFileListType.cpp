#include "IO.MzML.Generated.SourceFileListType.h"
#include "IO.MzML.Generated.SourceFileType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SourceFileType*> SourceFileListType::getsourceFile() const
            {
                return this->sourceFileField;
            }

            void SourceFileListType::setsourceFile(const std::vector<SourceFileType*> &value)
            {
                this->sourceFileField = value;
            }

            std::string SourceFileListType::getcount() const
            {
                return this->countField;
            }

            void SourceFileListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
