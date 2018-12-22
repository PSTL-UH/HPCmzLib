#include "mzIdentML.Generated.DBSequenceType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring DBSequenceType::getSeq() const {
            return this->seqField;
        }

        void DBSequenceType::setSeq(const std::wstring &value) {
            this->seqField = value;
        }

        std::vector<CVParamType*> DBSequenceType::getcvParam() const {
            return this->cvParamField;
        }

        void DBSequenceType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> DBSequenceType::getuserParam() const {
            return this->userParamField;
        }

        void DBSequenceType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        int DBSequenceType::getlength() const {
            return this->lengthField;
        }

        void DBSequenceType::setlength(int value) {
            this->lengthField = value;
        }

        bool DBSequenceType::getlengthSpecified() const {
            return this->lengthFieldSpecified;
        }

        void DBSequenceType::setlengthSpecified(bool value) {
            this->lengthFieldSpecified = value;
        }

        std::wstring DBSequenceType::getsearchDatabase_ref() const {
            return this->searchDatabase_refField;
        }

        void DBSequenceType::setsearchDatabase_ref(const std::wstring &value) {
            this->searchDatabase_refField = value;
        }

        std::wstring DBSequenceType::getaccession() const {
            return this->accessionField;
        }

        void DBSequenceType::setaccession(const std::wstring &value) {
            this->accessionField = value;
        }
    }
}
