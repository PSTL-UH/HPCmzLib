#pragma once

#include "PeriodicTableLoader.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "tangible_filesystem.h"

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

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "Generated/UsefulProteomicsDatabases.Generated.obo.h"
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases
{
    class Loaders final
    {
    private:
        // Edgar: removing in the C++ version for now.
        //class StaticConstructor
        // {
        //public:
        //    StaticConstructor();
        //};

    private:
        //static Loaders::StaticConstructor staticConstructor;

        static bool FilesAreEqual_Hash(const std::string &first, const std::string &second);

#ifdef ORIG
        static void DownloadPsiMod(std::string psimodLocation);
        static void DownloadUnimod(std::string unimodLocation);
        static void DownloadElements(std::string elementLocation);
        static void DownloadUniprot(std::string uniprotLocation);
#endif
        
    public:
        static void UpdateUniprot(const std::string &uniprotLocation);

        static void UpdateUnimod(const std::string &unimodLocation);

        static void UpdatePsiMod(const std::string &psimodLocation);

        static void UpdateElements(const std::string &elementLocation);

        static std::unordered_map<std::string, int> GetFormalChargesDictionary(obo *psiModDeserialized);

        static void LoadElements(std::string elementLocation);

        static std::vector<Modification*> LoadUnimod(const std::string &unimodLocation);

        static Generated::obo* LoadPsiMod(const std::string &psimodLocation);
        
        static std::vector<Modification*> LoadUniprot(const std::string &uniprotLocation, std::unordered_map<std::string, int> formalChargesDictionary);
    };

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //public static IEnumerable<Modification> LoadUnimod(string unimodLocation);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //public static Generated.obo LoadPsiMod(string psimodLocation);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //public static IEnumerable<Modification> LoadUniprot(string uniprotLocation, Dictionary<string, int> formalChargesDictionary);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //private static bool FilesAreEqual_Hash(string first, string second);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //private static void DownloadPsiMod(string psimodLocation);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //private static void DownloadUnimod(string unimodLocation);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //private static void DownloadElements(string elementLocation);

    //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
    //private static void DownloadUniprot(string uniprotLocation);
}
