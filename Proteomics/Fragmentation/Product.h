#pragma once

#include "ProductType.h"
#include <string>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { namespace Fragmentation { class NeutralTerminusFragment; } }
#include "NeutralTerminusFragment.h"

namespace Proteomics
{
    namespace Fragmentation
    {
        class Product
        {
        public:
            const double NeutralMass;
            const ProductType productType;
            NeutralTerminusFragment *const TerminusFragment;
            const double NeutralLoss;

            /// <summary>
            /// A product is the individual neutral fragment from an MS dissociation.
            /// A fragmentation product here contains one of the two termini (N- or C-). 
            /// The ProductType describes where along the backbone the fragmentaiton occurred
            /// (e.g. b-, y-, c-, zdot-). The neutral loss mass (if any) that 
            /// occurred from a mod on the fragment is listed as a mass. Finally the neutral
            /// mass of the whole fragment is provided.
            /// </summary>
            virtual ~Product()
            {
                //delete TerminusFragment;
            }

            Product(ProductType productType, NeutralTerminusFragment *terminusFragment, double neutralLoss);

            std::string getAnnotation() const;

            /// <summary>
            /// Summarizes a Product into a string for debug purposes
            /// </summary>
            std::string ToString();

            bool Equals(Product * obj);

            int GetHashCode();
        };
    }
}
