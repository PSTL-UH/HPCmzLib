#pragma once

#include <string>
#include <vector>
#include <any>
#include <tuple>


namespace Proteomics {
    class DatabaseReference {
    private:
        std::wstring privateType;
        std::wstring privateId;
        std::vector<std::tuple<std::wstring, std::wstring>> privateProperties;

//        #region Public Constructors

        /// <summary>
        /// DatabaseReference constructor, which takes the type and ID strings of the reference, and a list of properties. Each property contains the "type" and "value" of the property as Item1 and Item2 of the Tuple.
        /// </summary>
        /// <param name="type"></param>
        /// <param name="id"></param>
        /// <param name="properties"></param>
    public:
        DatabaseReference(const std::wstring &type, const std::wstring &id, std::vector<std::tuple<std::wstring, std::wstring>> &properties);

//        #endregion Public Constructors

//        #region Public Properties

        /// <summary>
        /// dbRef type, e.g. "GO" for GO terms
        /// </summary>
        std::wstring getType() const;

        /// <summary>
        /// dbRef ID string
        /// </summary>
        std::wstring getId() const;

        /// <summary>
        /// Each database reference contains a list of properties. Item1 of this Tuple is the "type", and Item2 is the "value" of the property.
        /// </summary>
        std::vector<std::tuple<std::wstring, std::wstring>> getProperties() const;

//        #endregion Public Properties

//        #region Public Methods

        bool Equals(std::any obj) override;

        int GetHashCode() override;

//        #endregion Public Methods
    };
}
