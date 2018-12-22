#pragma once

#include <string>
#include <cctype>
#include <any>


namespace Proteomics {
    class ModificationMotif {
//        #region Private Fields

    private:
        static Regex *const ModificationMotifRegex;

        const std::wstring motifString;

//        #endregion Private Fields

//        #region Private Constructors

        ModificationMotif(const std::wstring &motif);

//        #endregion Private Constructors

//        #region Public Methods

        /// <summary>
        /// Only upper and lower case letters allowed, must have a single upper case letter
        /// </summary>
        /// <param name="motifString"></param>
        /// <param name="motif"></param>
        /// <returns></returns>
    public:
        static bool TryGetMotif(const std::wstring &motifString, ModificationMotif *&motif);

        bool Equals(std::any o) override;

        int GetHashCode() override;

        std::wstring ToString() override;

//        #endregion Public Methods
    };
}
