﻿#pragma once

#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace mzIdentML110 { namespace Generated { class RoleType; } }

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


// 
// This source code was auto-generated by xsd, Version=4.7.2046.0.
// 

namespace mzIdentML110 {
    namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://psidev.info/psi/pi/mzIdentML/1.1")] public partial class ContactRoleType
        class ContactRoleType {

        private:
            RoleType *roleField;

            std::wstring contact_refField;

            /// <remarks/>
        public:
            virtual ~ContactRoleType() {
                delete roleField;
            }

            RoleType *getRole() const;
            void setRole(RoleType *value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string contact_ref
            std::wstring getcontact_ref() const;
            void setcontact_ref(const std::wstring &value);
        };
    }
}
