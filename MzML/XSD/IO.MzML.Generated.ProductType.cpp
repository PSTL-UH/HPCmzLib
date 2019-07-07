#include "IO.MzML.Generated.ProductType.h"
#include "IO.MzML.Generated.ParamGroupType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            ParamGroupType *ProductType::getisolationWindow() const
            {
                return this->isolationWindowField;
            }

            void ProductType::setisolationWindow(ParamGroupType *value)
            {
                this->isolationWindowField = value;
            }
        }
    }
}
