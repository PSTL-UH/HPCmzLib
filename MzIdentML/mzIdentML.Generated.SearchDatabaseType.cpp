#include "mzIdentML.Generated.SearchDatabaseType.h"
#include "mzIdentML.Generated.ParamType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        ParamType *SearchDatabaseType::getDatabaseName() const {
            return this->databaseNameField;
        }

        void SearchDatabaseType::setDatabaseName(ParamType *value) {
            this->databaseNameField = value;
        }

        std::vector<CVParamType*> SearchDatabaseType::getcvParam() const {
            return this->cvParamField;
        }

        void SearchDatabaseType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::wstring SearchDatabaseType::getversion() const {
            return this->versionField;
        }

        void SearchDatabaseType::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        DateTime SearchDatabaseType::getreleaseDate() const {
            return this->releaseDateField;
        }

        void SearchDatabaseType::setreleaseDate(DateTime value) {
            this->releaseDateField = value;
        }

        bool SearchDatabaseType::getreleaseDateSpecified() const {
            return this->releaseDateFieldSpecified;
        }

        void SearchDatabaseType::setreleaseDateSpecified(bool value) {
            this->releaseDateFieldSpecified = value;
        }

        long long SearchDatabaseType::getnumDatabaseSequences() const {
            return this->numDatabaseSequencesField;
        }

        void SearchDatabaseType::setnumDatabaseSequences(long long value) {
            this->numDatabaseSequencesField = value;
        }

        bool SearchDatabaseType::getnumDatabaseSequencesSpecified() const {
            return this->numDatabaseSequencesFieldSpecified;
        }

        void SearchDatabaseType::setnumDatabaseSequencesSpecified(bool value) {
            this->numDatabaseSequencesFieldSpecified = value;
        }

        long long SearchDatabaseType::getnumResidues() const {
            return this->numResiduesField;
        }

        void SearchDatabaseType::setnumResidues(long long value) {
            this->numResiduesField = value;
        }

        bool SearchDatabaseType::getnumResiduesSpecified() const {
            return this->numResiduesFieldSpecified;
        }

        void SearchDatabaseType::setnumResiduesSpecified(bool value) {
            this->numResiduesFieldSpecified = value;
        }
    }
}
