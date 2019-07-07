#include "IO.MzML.Generated.ScanType.h"
#include "IO.MzML.Generated.ScanWindowListType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            ScanWindowListType *ScanType::getscanWindowList() const
            {
                return this->scanWindowListField;
            }

            void ScanType::setscanWindowList(ScanWindowListType *value)
            {
                this->scanWindowListField = value;
            }

            std::string ScanType::getspectrumRef() const
            {
                return this->spectrumRefField;
            }

            void ScanType::setspectrumRef(const std::string &value)
            {
                this->spectrumRefField = value;
            }

            std::string ScanType::getsourceFileRef() const
            {
                return this->sourceFileRefField;
            }

            void ScanType::setsourceFileRef(const std::string &value)
            {
                this->sourceFileRefField = value;
            }

            std::string ScanType::getexternalSpectrumID() const
            {
                return this->externalSpectrumIDField;
            }

            void ScanType::setexternalSpectrumID(const std::string &value)
            {
                this->externalSpectrumIDField = value;
            }

            std::string ScanType::getinstrumentConfigurationRef() const
            {
                return this->instrumentConfigurationRefField;
            }

            void ScanType::setinstrumentConfigurationRef(const std::string &value)
            {
                this->instrumentConfigurationRefField = value;
            }
        }
    }
}
