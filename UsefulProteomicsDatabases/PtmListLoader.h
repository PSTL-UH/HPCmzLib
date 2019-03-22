#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include "stringhelper.h"

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

namespace UsefulProteomicsDatabases {
    class PtmListLoader final {

    private:
        static const std::unordered_map<std::string, char> aminoAcidCodes;

    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static PtmListLoader::StaticConstructor staticConstructor;

    public:
        static std::vector<Modification*> ReadModsFromFile(const std::string &ptmListLocation);

        /// <summary>
        /// Reads a list of modifications from a text file.
        /// </summary>
        /// <param name="ptmListLocation"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromFile(const std::string &ptmListLocation, std::unordered_map<std::string, int> &formalChargesDictionary);

        /// <summary>
        /// Reads a list of modifications from a string representation of a ptmlist text file.
        /// </summary>
        /// <param name="storedModifications"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromString(const std::string &storedModifications);

        /// <summary>
        /// Get a ModificationWithLocation from string representations of a modification specification. Returns null if the string representation is not recognized.
        /// </summary>
        /// <param name="specification"></param>
        /// <returns></returns>
    private:
        static std::vector<Modification*> ReadMod(std::vector<std::string> &specification, std::unordered_map<std::string, int> &formalChargesDictionary);
    }
}
