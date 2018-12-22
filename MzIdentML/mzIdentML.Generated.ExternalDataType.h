﻿#pragma once

#include "mzIdentML.Generated.IdentifiableType.h"
#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace mzIdentML { namespace Generated { class FileFormatType; } }

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
//ORIGINAL LINE: [System.Xml.Serialization.XmlIncludeAttribute(typeof(SpectraDataType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SourceFileType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SearchDatabaseType))][System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://psidev.info/psi/pi/mzIdentML/1.1.1")] public partial class ExternalDataType: IdentifiableType
        class ExternalDataType : public IdentifiableType {

        private:
            std::wstring externalFormatDocumentationField;

            FileFormatType *fileFormatField;

            std::wstring locationField;

            /// <remarks/>
        public:
            virtual ~ExternalDataType() {
                delete fileFormatField;
            }

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute(DataType = "anyURI")] public string ExternalFormatDocumentation
            std::wstring getExternalFormatDocumentation() const;
            void setExternalFormatDocumentation(const std::wstring &value);

            /// <remarks/>
            FileFormatType *getFileFormat() const;
            void setFileFormat(FileFormatType *value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType = "anyURI")] public string location
            std::wstring getlocation() const;
            void setlocation(const std::wstring &value);
        };
    }
}
