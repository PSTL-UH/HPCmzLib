#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "Protease.h"

//using namespace Proteomics::Fragmentation;
//#include "../Fragmentation/FragmentationTerminus.h"

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class ProteaseDictionary final
        {
        private:

            static void StaticConstructor();
            static std::unordered_map<std::string, Protease*> privateDictionary;

        public:
            static std::unordered_map<std::string, Protease*> getDictionary();
            static void setDictionary(const std::unordered_map<std::string, Protease*> &value);
            
            static std::unordered_map<std::string, Protease*> LoadProteaseDictionary(const std::string &path);

            // Edgar: new for the C++ version.
            static void insert ( std::string name, Protease* value);

        };
    }
}
