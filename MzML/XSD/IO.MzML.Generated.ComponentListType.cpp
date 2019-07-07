#include "IO.MzML.Generated.ComponentListType.h"
#include "IO.MzML.Generated.SourceComponentType.h"
#include "IO.MzML.Generated.AnalyzerComponentType.h"
#include "IO.MzML.Generated.DetectorComponentType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SourceComponentType*> ComponentListType::getsource() const
            {
                return this->sourceField;
            }

            void ComponentListType::setsource(const std::vector<SourceComponentType*> &value)
            {
                this->sourceField = value;
            }

            std::vector<AnalyzerComponentType*> ComponentListType::getanalyzer() const
            {
                return this->analyzerField;
            }

            void ComponentListType::setanalyzer(const std::vector<AnalyzerComponentType*> &value)
            {
                this->analyzerField = value;
            }

            std::vector<DetectorComponentType*> ComponentListType::getdetector() const
            {
                return this->detectorField;
            }

            void ComponentListType::setdetector(const std::vector<DetectorComponentType*> &value)
            {
                this->detectorField = value;
            }

            std::string ComponentListType::getcount() const
            {
                return this->countField;
            }

            void ComponentListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
