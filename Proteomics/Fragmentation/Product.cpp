#include "Product.h"
#include "NeutralTerminusFragment.h"
#include "DissociationTypeCollection.h"
#include "stringhelper.h"


namespace Proteomics
{
    namespace Fragmentation
    {

        Product::Product(ProductType productType, NeutralTerminusFragment *terminusFragment, double neutralLoss) : NeutralMass(DissociationTypeCollection::ProductTypeSpecificFragmentNeutralMass(terminusFragment->NeutralMass, productType) - neutralLoss), productType(productType), TerminusFragment(terminusFragment), NeutralLoss(neutralLoss)
        {
        }

        std::string Product::getAnnotation() const
        {
            StringBuilder *sb = new StringBuilder();

            sb->append(static_cast<int>(productType));

            // for "normal" fragments this is just the fragment number (e.g., the 3 in the b3 ion)
            // for diagnostic ions, it's the m/z assuming z=1
            // (e.g., a diagnostic ion with neutral mass 100 Da will be reported as the D101 fragment)
            sb->append(TerminusFragment->FragmentNumber);

            if (NeutralLoss != 0)
            {
                sb->append("-");
                sb->append(std::to_string(NeutralLoss));
            }

            std::string s = sb->toString();
            delete sb;
            return s;
        }

        std::string Product::ToString()
        {
            ProductType pT = productType;
            std::ostringstream out;
            out.precision(11);
            out << TerminusFragment->FragmentNumber << ";";
            out << NeutralMass << "-" << NeutralLoss;
                                                                               
            return ProductTypeToString(pT) + out.str();

        }

        bool Product::Equals(Product *other)
        {

            return this->productType == other->productType              &&
                this->TerminusFragment->Equals(other->TerminusFragment) &&
                this->NeutralLoss == other->NeutralLoss;
        }

        int Product::GetHashCode()
        {
            return StringHelper::GetHashCode(std::to_string(NeutralMass));
        }
    }
}
