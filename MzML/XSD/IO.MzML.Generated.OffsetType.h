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


namespace IO {
    namespace MzML {
        namespace Generated {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace="http://psi.hupo.org/ms/mzml")] public partial class OffsetType
        class OffsetType {

        private:
            std::wstring idRefField;

            std::wstring spotIDField;

            double scanTimeField = 0;

            bool scanTimeFieldSpecified = false;

            long long valueField = 0;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string idRef
            std::wstring getidRef() const;
            void setidRef(const std::wstring &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string spotID
            std::wstring getspotID() const;
            void setspotID(const std::wstring &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public double scanTime
            double getscanTime() const;
            void setscanTime(double value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlIgnoreAttribute()] public bool scanTimeSpecified
            bool getscanTimeSpecified() const;
            void setscanTimeSpecified(bool value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlTextAttribute()] public long Value
            long long getValue() const;
            void setValue(long long value);
        };
        }
    }
}
