﻿#pragma once

#include "unimod_2.h"
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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://www.unimod.org/xmlns/schema/unimod_2")] public partial class xref_t
        class xref_t {

        private:
            std::wstring textField;

            xref_source_t sourceField = static_cast<xref_source_t>(0);

            std::wstring urlField;

            /// <remarks/>
        public:
            std::wstring gettext() const;
            void settext(const std::wstring &value);

            /// <remarks/>
            xref_source_t getsource() const;
            void setsource(xref_source_t value);

            /// <remarks/>
            std::wstring geturl() const;
            void seturl(const std::wstring &value);
        };
    }
}
