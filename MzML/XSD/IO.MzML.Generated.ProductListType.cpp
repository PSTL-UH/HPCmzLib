#include "IO.MzML.Generated.ProductListType.h"
#include "IO.MzML.Generated.ProductType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ProductType*> ProductListType::getproduct() const
            {
                return this->productField;
            }

            void ProductListType::setproduct(const std::vector<ProductType*> &value)
            {
                this->productField = value;
            }

            std::string ProductListType::getcount() const
            {
                return this->countField;
            }

            void ProductListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
