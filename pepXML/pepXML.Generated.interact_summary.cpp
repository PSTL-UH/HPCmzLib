#include "pepXML.Generated.interact_summary.h"
#include "pepXML.Generated.inputFileType.h"

namespace pepXML {
    namespace Generated {

        std::vector<inputFileType*> interact_summary::getinputfile() const {
            return this->inputfileField;
        }

        void interact_summary::setinputfile(const std::vector<inputFileType*> &value) {
            this->inputfileField = value;
        }

        std::wstring interact_summary::getfilename() const {
            return this->filenameField;
        }

        void interact_summary::setfilename(const std::wstring &value) {
            this->filenameField = value;
        }

        std::wstring interact_summary::getdirectory() const {
            return this->directoryField;
        }

        void interact_summary::setdirectory(const std::wstring &value) {
            this->directoryField = value;
        }
    }
}
