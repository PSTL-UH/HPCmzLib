#include "IO.MzML.Generated.SpectrumListType.h"
#include "IO.MzML.Generated.SpectrumType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SpectrumType*> SpectrumListType::getspectrum() const
            {
                return this->spectrumField;
            }

            void SpectrumListType::setspectrum(const std::vector<SpectrumType*> &value)
            {
                this->spectrumField = value;
            }

            std::string SpectrumListType::getcount() const
            {
                return this->countField;
            }

            void SpectrumListType::setcount(const std::string &value)
            {
                this->countField = value;
            }

            std::string SpectrumListType::getdefaultDataProcessingRef() const
            {
                return this->defaultDataProcessingRefField;
            }

            void SpectrumListType::setdefaultDataProcessingRef(const std::string &value)
            {
                this->defaultDataProcessingRefField = value;
            }
        }
    }
}
