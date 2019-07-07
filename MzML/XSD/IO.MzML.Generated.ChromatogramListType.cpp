#include "IO.MzML.Generated.ChromatogramListType.h"
#include "IO.MzML.Generated.ChromatogramType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ChromatogramType*> ChromatogramListType::getchromatogram() const
            {
                return this->chromatogramField;
            }

            void ChromatogramListType::setchromatogram(const std::vector<ChromatogramType*> &value)
            {
                this->chromatogramField = value;
            }

            std::string ChromatogramListType::getcount() const
            {
                return this->countField;
            }

            void ChromatogramListType::setcount(const std::string &value)
            {
                this->countField = value;
            }

            std::string ChromatogramListType::getdefaultDataProcessingRef() const
            {
                return this->defaultDataProcessingRefField;
            }

            void ChromatogramListType::setdefaultDataProcessingRef(const std::string &value)
            {
                this->defaultDataProcessingRefField = value;
            }
        }
    }
}
