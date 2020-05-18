#pragma once

#include <string>

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        enum class InitiatorMethionineBehavior
        {
            Undefined,
            Retain,
            Cleave,
            Variable
        };

        static std::string InitiatorMethionineBehaviorToString( InitiatorMethionineBehavior i)
        {
            std::string s;
            if ( i == InitiatorMethionineBehavior::Undefined ) {
                s = "Undefined";
            }
            else if ( i == InitiatorMethionineBehavior::Retain ) {
                s = "Retain";
            }
            else if ( i == InitiatorMethionineBehavior::Cleave  ) {
                s = "Cleave";
            }
            else if ( i == InitiatorMethionineBehavior::Variable) {
                s = "Variable";
            }
            
            return s;
        }
    }

    
}
