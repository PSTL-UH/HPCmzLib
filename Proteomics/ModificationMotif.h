#pragma once

#include <string>
#include <cctype>
#include <any>


namespace Proteomics {
    class ModificationMotif {

    private:
//        static Regex *const ModificationMotifRegex;

        const std::string motifString;


        ModificationMotif(const std::string &motif);


        /// <summary>
        /// Only upper and lower case letters allowed, must have a single upper case letter
        /// </summary>
        /// <param name="motifString"></param>
        /// <param name="motif"></param>
        /// <returns></returns>
    public:
        static bool TryGetMotif(const std::string &motifString, ModificationMotif *&motif);

//        bool Equals(std::any o) override;
        bool Equals( ModificationMotif *&m );

//        int GetHashCode() override;
        int GetHashCode();

//        std::string ToString() override;
        std::string ToString();

    };
}
