﻿#pragma once

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


// 
// This source code was auto-generated by xsd, Version=4.6.1055.0.
// 

namespace UsefulProteomicsDatabases {
    namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true)] public partial class oboHeaderSubsetdef
        class oboHeaderSubsetdef {

        private:
            std::wstring idField;

            std::wstring nameField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified)] public string id
            std::wstring getid() const;
            void setid(const std::wstring &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified)] public string name
            std::wstring getname() const;
            void setname(const std::wstring &value);
        };
    }
}
