#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationWithLocation; }
namespace UsefulProteomicsDatabases { namespace Generated { class obo; } }

// Copyright 2016 Stefan Solntsev
//
// This file (Loaders.cs) is part of UsefulProteomicsDatabases.
//
// UsefulProteomicsDatabases is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// UsefulProteomicsDatabases is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with UsefulProteomicsDatabases. If not, see <http://www.gnu.org/licenses/>.

using namespace Proteomics;
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases {
    class Loaders final {

    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static Loaders::StaticConstructor staticConstructor;


    public:
        static void UpdateUniprot(const std::string &uniprotLocation);

        static void UpdateUnimod(const std::string &unimodLocation);

        static void UpdatePsiMod(const std::string &psimodLocation);

        static void UpdateElements(const std::string &elementLocation);

        static std::unordered_map<std::string, int> GetFormalChargesDictionary(obo *psiModDeserialized);

        static std::vector<ModificationWithLocation*> LoadUnimod(const std::string &unimodLocation);

        static Generated::obo *LoadPsiMod(const std::string &psimodLocation);

        static std::vector<ModificationWithLocation*> LoadUniprot(const std::string &uniprotLocation, std::unordered_map<std::string, int> &formalChargesDictionary);

    private:
        static bool FilesAreEqual_Hash(const std::string &first, const std::string &second);

        static void DownloadPsiMod(const std::string &psimodLocation);

        static void DownloadUnimod(const std::string &unimodLocation);

        static void DownloadElements(const std::string &elementLocation);

        static void DownloadUniprot(const std::string &uniprotLocation);

    };
}
