#include "IO.MzML.Generated.ProductListType.h"
#include "IO.MzML.Generated.ProductType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ProductType*> ProductListType::getproduct() const {
                return this->productField;
            }

            void ProductListType::setproduct(const std::vector<ProductType*> &value) {
                this->productField = value;
            }

            std::wstring ProductListType::getcount() const {
                return this->countField;
            }

            void ProductListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
