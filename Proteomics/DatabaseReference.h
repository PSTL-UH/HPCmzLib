#pragma once

#include <string>
#include <vector>
#include <any>
#include <tuple>


namespace Proteomics {
    class DatabaseReference {
    private:
        std::string privateType;
        std::string privateId;
        std::vector<std::tuple<std::string, std::string>> privateProperties;


        /// <summary>
        /// DatabaseReference constructor, which takes the type and ID strings of the reference, and a list of properties. Each property contains the "type" and "value" of the property as Item1 and Item2 of the Tuple.
        /// </summary>
        /// <param name="type"></param>
        /// <param name="id"></param>
        /// <param name="properties"></param>
    public:
        DatabaseReference(const std::string &type, const std::string &id, std::vector<std::tuple<std::string, std::string>> &properties);

        /// <summary>
        /// dbRef type, e.g. "GO" for GO terms
        /// </summary>
        std::string getType() const;

        /// <summary>
        /// dbRef ID string
        /// </summary>
        std::string getId() const;

        /// <summary>
        /// Each database reference contains a list of properties. Item1 of this Tuple is the "type", and Item2 is the "value" of the property.
        /// </summary>
        std::vector<std::tuple<std::string, std::string>> getProperties() const;

//        bool Equals(std::any obj) override;
        bool Equals(DatabaseReference *);

//        int GetHashCode() override;
        int GetHashCode();

    };
}
