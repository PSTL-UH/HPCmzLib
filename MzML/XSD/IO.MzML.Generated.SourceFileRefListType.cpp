#include "IO.MzML.Generated.SourceFileRefListType.h"
#include "IO.MzML.Generated.SourceFileRefType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SourceFileRefType*> SourceFileRefListType::getsourceFileRef() const
            {
                return this->sourceFileRefField;
            }

            void SourceFileRefListType::setsourceFileRef(const std::vector<SourceFileRefType*> &value)
            {
                this->sourceFileRefField = value;
            }

            std::string SourceFileRefListType::getcount() const
            {
                return this->countField;
            }

            void SourceFileRefListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
