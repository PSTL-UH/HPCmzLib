﻿#pragma once

#include "IO.MzML.Generated.ParamGroupType.h"
#include <string>

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace IO {
    namespace MzML {
        namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace="http://psi.hupo.org/ms/mzml")] public partial class SoftwareType: ParamGroupType
        class SoftwareType : public ParamGroupType {

        private:
            std::wstring idField;

            std::wstring versionField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType="ID")] public string id
            std::wstring getid() const;
            void setid(const std::wstring &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string version
            std::wstring getversion() const;
            void setversion(const std::wstring &value);
        };
        }
    }
}
