#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { namespace ProteolyticDigestion { class Protease; } }

using namespace Proteomics::Fragmentation;

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class ProteaseDictionary final
        {
        private:
            static std::unordered_map<std::string, Protease*> privateDictionary;

            private:
                class StaticConstructor
                {
                public:
                    StaticConstructor();
                };

            private:
                static ProteaseDictionary::StaticConstructor staticConstructor;


            public:
                static std::unordered_map<std::string, Protease*> getDictionary();
                static void setDictionary(const std::unordered_map<std::string, Protease*> &value);

            static std::unordered_map<std::string, Protease*> LoadProteaseDictionary(const std::string &path);
        };
    }
}
