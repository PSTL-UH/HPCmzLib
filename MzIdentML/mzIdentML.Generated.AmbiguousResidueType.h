﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace mzIdentML { namespace Generated { class CVParamType; } }
namespace mzIdentML { namespace Generated { class UserParamType; } }

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace mzIdentML {
    namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://psidev.info/psi/pi/mzIdentML/1.1.1")] public partial class AmbiguousResidueType
        class AmbiguousResidueType {

        private:
            std::vector<CVParamType*> cvParamField;

            std::vector<UserParamType*> userParamField;

            std::wstring codeField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("cvParam")] public CVParamType[] cvParam
            std::vector<CVParamType*> getcvParam() const;
            void setcvParam(const std::vector<CVParamType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("userParam")] public UserParamType[] userParam
            std::vector<UserParamType*> getuserParam() const;
            void setuserParam(const std::vector<UserParamType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string code
            std::wstring getcode() const;
            void setcode(const std::wstring &value);
        };
    }
}
