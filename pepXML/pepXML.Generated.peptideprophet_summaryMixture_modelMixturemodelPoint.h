﻿#pragma once

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
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")] public partial class peptideprophet_summaryMixture_modelMixturemodelPoint
        class peptideprophet_summaryMixture_modelMixturemodelPoint {

        private:
            float valueField = 0;

            bool valueFieldSpecified = false;

            float pos_densField = 0;

            bool pos_densFieldSpecified = false;

            float neg_densField = 0;

            bool neg_densFieldSpecified = false;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float value
            float getvalue() const;
            void setvalue(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlIgnoreAttribute()] public bool valueSpecified
            bool getvalueSpecified() const;
            void setvalueSpecified(bool value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float pos_dens
            float getpos_dens() const;
            void setpos_dens(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlIgnoreAttribute()] public bool pos_densSpecified
            bool getpos_densSpecified() const;
            void setpos_densSpecified(bool value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float neg_dens
            float getneg_dens() const;
            void setneg_dens(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlIgnoreAttribute()] public bool neg_densSpecified
            bool getneg_densSpecified() const;
            void setneg_densSpecified(bool value);
        };
    }
}
