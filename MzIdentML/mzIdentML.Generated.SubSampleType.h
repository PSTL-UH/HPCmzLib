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


namespace mzIdentML {
    namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://psidev.info/psi/pi/mzIdentML/1.1.1")] public partial class SubSampleType
        class SubSampleType {

        private:
            std::wstring sample_refField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string sample_ref
            std::wstring getsample_ref() const;
            void setsample_ref(const std::wstring &value);
        };
    }
}
