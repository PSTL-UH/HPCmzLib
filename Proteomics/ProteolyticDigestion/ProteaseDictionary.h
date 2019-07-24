#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { namespace ProteolyticDigestion { class Protease; } }
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
            static std::unordered_map<std::string, Protease*> privateDictionary;

            static void StaticConstructor();

            public:
                static std::unordered_map<std::string, Protease*> getDictionary();
                static void setDictionary(const std::unordered_map<std::string, Protease*> &value);

                static std::unordered_map<std::string, Protease*> LoadProteaseDictionary(const std::string &path);
        };
    }
}
