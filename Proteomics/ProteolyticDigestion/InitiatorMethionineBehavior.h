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

        static InitiatorMethionineBehavior InitiatorMethionineBehaviorFromString ( std::string s )
        {
            InitiatorMethionineBehavior i;
            if ( s == "Undefined" ) {
                i = InitiatorMethionineBehavior::Undefined;
            }
            else if ( s == "Retain" ) {
                i = InitiatorMethionineBehavior::Retain;
            }
            else if ( s == "Cleave" ) {
                i = InitiatorMethionineBehavior::Cleave;
            }
            else if ( s == "Variable" ) {
                i = InitiatorMethionineBehavior::Variable;
            }
            return i;
        }
    }

    
}
