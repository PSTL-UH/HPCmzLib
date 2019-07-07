#include "IO.MzML.Generated.SampleListType.h"
#include "IO.MzML.Generated.SampleType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SampleType*> SampleListType::getsample() const
            {
                return this->sampleField;
            }

            void SampleListType::setsample(const std::vector<SampleType*> &value)
            {
                this->sampleField = value;
            }

            std::string SampleListType::getcount() const
            {
                return this->countField;
            }

            void SampleListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
