﻿#pragma once

#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace mzIdentML110 { namespace Generated { class AbstractParamType; } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://psidev.info/psi/pi/mzIdentML/1.1")] public partial class ParamListType
        class ParamListType {

        private:
            std::vector<AbstractParamType*> itemsField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("cvParam", typeof(CVParamType))][System.Xml.Serialization.XmlElementAttribute("userParam", typeof(UserParamType))] public AbstractParamType[] Items
            std::vector<AbstractParamType*> getItems() const;
            void setItems(const std::vector<AbstractParamType*> &value);
        };
    }
}
