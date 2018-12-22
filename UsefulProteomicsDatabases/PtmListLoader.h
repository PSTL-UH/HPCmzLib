#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }

using namespace Chemistry;
using namespace MzLibUtil;
using namespace Proteomics;

namespace UsefulProteomicsDatabases {
    class PtmListLoader final {
//        #region Private Fields

    private:
        static const std::unordered_map<std::wstring, wchar_t> aminoAcidCodes;

//        #endregion Private Fields

//        #region Public Constructors

    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static PtmListLoader::StaticConstructor staticConstructor;


//        #endregion Public Constructors

//        #region Public Methods

    public:
        static std::vector<Modification*> ReadModsFromFile(const std::wstring &ptmListLocation);

        /// <summary>
        /// Reads a list of modifications from a text file.
        /// </summary>
        /// <param name="ptmListLocation"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromFile(const std::wstring &ptmListLocation, std::unordered_map<std::wstring, int> &formalChargesDictionary);

        /// <summary>
        /// Reads a list of modifications from a string representation of a ptmlist text file.
        /// </summary>
        /// <param name="storedModifications"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromString(const std::wstring &storedModifications);

//        #endregion Public Methods

//        #region Private Methods

        /// <summary>
        /// Get a ModificationWithLocation from string representations of a modification specification. Returns null if the string representation is not recognized.
        /// </summary>
        /// <param name="specification"></param>
        /// <returns></returns>
    private:
        static std::vector<Modification*> ReadMod(std::vector<std::wstring> &specification, std::unordered_map<std::wstring, int> &formalChargesDictionary);
