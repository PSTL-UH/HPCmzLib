#include "IO.MzML.Generated.ParamGroupType.h"
#include "IO.MzML.Generated.ReferenceableParamGroupRefType.h"
#include "IO.MzML.Generated.CVParamType.h"
#include "IO.MzML.Generated.UserParamType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ReferenceableParamGroupRefType*> ParamGroupType::getreferenceableParamGroupRef() const
            {
                return this->referenceableParamGroupRefField;
            }

            void ParamGroupType::setreferenceableParamGroupRef(const std::vector<ReferenceableParamGroupRefType*> &value)
            {
                this->referenceableParamGroupRefField = value;
            }

            std::vector<CVParamType*> ParamGroupType::getcvParam() const
            {
                return this->cvParamField;
            }

            void ParamGroupType::setcvParam(const std::vector<CVParamType*> &value)
            {
                this->cvParamField = value;
            }

            std::vector<UserParamType*> ParamGroupType::getuserParam() const
            {
                return this->userParamField;
            }

            void ParamGroupType::setuserParam(const std::vector<UserParamType*> &value)
            {
                this->userParamField = value;
            }
        }
    }
}
