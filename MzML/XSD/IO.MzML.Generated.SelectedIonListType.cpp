#include "IO.MzML.Generated.SelectedIonListType.h"
#include "IO.MzML.Generated.ParamGroupType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ParamGroupType*> SelectedIonListType::getselectedIon() const
            {
                return this->selectedIonField;
            }

            void SelectedIonListType::setselectedIon(const std::vector<ParamGroupType*> &value)
            {
                this->selectedIonField = value;
            }

            std::string SelectedIonListType::getcount() const
            {
                return this->countField;
            }

            void SelectedIonListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
