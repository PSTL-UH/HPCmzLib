#include "IO.MzML.Generated.RunType.h"
#include "IO.MzML.Generated.SpectrumListType.h"
#include "IO.MzML.Generated.ChromatogramListType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            SpectrumListType *RunType::getspectrumList() const
            {
                return this->spectrumListField;
            }

            void RunType::setspectrumList(SpectrumListType *value)
            {
                this->spectrumListField = value;
            }

            ChromatogramListType *RunType::getchromatogramList() const
            {
                return this->chromatogramListField;
            }

            void RunType::setchromatogramList(ChromatogramListType *value)
            {
                this->chromatogramListField = value;
            }

            std::string RunType::getid() const
            {
                return this->idField;
            }

            void RunType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string RunType::getdefaultInstrumentConfigurationRef() const
            {
                return this->defaultInstrumentConfigurationRefField;
            }

            void RunType::setdefaultInstrumentConfigurationRef(const std::string &value)
            {
                this->defaultInstrumentConfigurationRefField = value;
            }

            std::string RunType::getdefaultSourceFileRef() const
            {
                return this->defaultSourceFileRefField;
            }

            void RunType::setdefaultSourceFileRef(const std::string &value)
            {
                this->defaultSourceFileRefField = value;
            }

            std::string RunType::getsampleRef() const
            {
                return this->sampleRefField;
            }

            void RunType::setsampleRef(const std::string &value)
            {
                this->sampleRefField = value;
            }

            DateTime RunType::getstartTimeStamp() const
            {
                return this->startTimeStampField;
            }

            void RunType::setstartTimeStamp(DateTime value)
            {
                this->startTimeStampField = value;
            }

            bool RunType::getstartTimeStampSpecified() const
            {
                return this->startTimeStampFieldSpecified;
            }

            void RunType::setstartTimeStampSpecified(bool value)
            {
                this->startTimeStampFieldSpecified = value;
            }
        }
    }
}
