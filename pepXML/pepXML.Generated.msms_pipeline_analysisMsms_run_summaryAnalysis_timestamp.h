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


namespace pepXML {
    namespace Generated {
        /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

        /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

            /// <remarks/>

        /// <remarks/>

            /// <remarks/>

            /// <remarks/>

        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")] public partial class msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp
        class msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp {

        private:
            System::Xml::XmlElement *anyField;

            DateTime timeField;

            std::wstring analysisField;

            unsigned int idField = 0;

            /// <remarks/>
        public:
            virtual ~msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp() {
                delete anyField;
            }

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAnyElementAttribute()] public System.Xml.XmlElement Any
            System::Xml::XmlElement *getAny() const;
            void setAny(System::Xml::XmlElement *value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public System.DateTime time
            DateTime gettime() const;
            void settime(DateTime value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string analysis
            std::wstring getanalysis() const;
            void setanalysis(const std::wstring &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public uint id
            unsigned int getid() const;
            void setid(unsigned int value);
        };
    }
}
