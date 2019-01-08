#pragma once

#include <string>
#include <any>
#include "stringbuilder.h"


namespace Proteomics {
    class Modification {
    public:
        const std::string id;
        const std::string modificationType;
        Modification(const std::string &id, const std::string &modificationType);
//        std::wstring ToString() override;
//        bool Equals(std::any o) override;
//        int GetHashCode() override;
        std::string ToString();
        bool Equals(std::any o);
        int GetHashCode();
    };
}
