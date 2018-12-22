#include "IO.MzML.Generated.RunType.h"
#include "IO.MzML.Generated.SpectrumListType.h"
#include "IO.MzML.Generated.ChromatogramListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            SpectrumListType *RunType::getspectrumList() const {
                return this->spectrumListField;
            }

            void RunType::setspectrumList(SpectrumListType *value) {
                this->spectrumListField = value;
            }

            ChromatogramListType *RunType::getchromatogramList() const {
                return this->chromatogramListField;
            }

            void RunType::setchromatogramList(ChromatogramListType *value) {
                this->chromatogramListField = value;
            }

            std::wstring RunType::getid() const {
                return this->idField;
            }

            void RunType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring RunType::getdefaultInstrumentConfigurationRef() const {
                return this->defaultInstrumentConfigurationRefField;
            }

            void RunType::setdefaultInstrumentConfigurationRef(const std::wstring &value) {
                this->defaultInstrumentConfigurationRefField = value;
            }

            std::wstring RunType::getdefaultSourceFileRef() const {
                return this->defaultSourceFileRefField;
            }

            void RunType::setdefaultSourceFileRef(const std::wstring &value) {
                this->defaultSourceFileRefField = value;
            }

            std::wstring RunType::getsampleRef() const {
                return this->sampleRefField;
            }

            void RunType::setsampleRef(const std::wstring &value) {
                this->sampleRefField = value;
            }

            DateTime RunType::getstartTimeStamp() const {
                return this->startTimeStampField;
            }

            void RunType::setstartTimeStamp(DateTime value) {
                this->startTimeStampField = value;
            }

            bool RunType::getstartTimeStampSpecified() const {
                return this->startTimeStampFieldSpecified;
            }

            void RunType::setstartTimeStampSpecified(bool value) {
                this->startTimeStampFieldSpecified = value;
            }
        }
    }
}
