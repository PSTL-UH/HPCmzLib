#include "pepXML.Generated.ptmprophet_summary.h"
#include "pepXML.Generated.inputFileType.h"
#include "pepXML.Generated.mixtureModelType.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<inputFileType*> ptmprophet_summary::getinputfile() const
        {
            return this->inputfileField;
        }

        void ptmprophet_summary::setinputfile(const std::vector<inputFileType*> &value)
        {
            this->inputfileField = value;
        }

        std::vector<mixtureModelType*> ptmprophet_summary::getmixturemodel() const
        {
            return this->mixturemodelField;
        }

        void ptmprophet_summary::setmixturemodel(const std::vector<mixtureModelType*> &value)
        {
            this->mixturemodelField = value;
        }

        std::string ptmprophet_summary::getversion() const
        {
            return this->versionField;
        }

        void ptmprophet_summary::setversion(const std::string &value)
        {
            this->versionField = value;
        }

        std::string ptmprophet_summary::getoptions() const
        {
            return this->optionsField;
        }

        void ptmprophet_summary::setoptions(const std::string &value)
        {
            this->optionsField = value;
        }
    }
}
