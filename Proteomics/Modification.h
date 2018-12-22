#pragma once

#include <string>
#include <any>
#include "stringbuilder.h"


namespace Proteomics {
    class Modification {
    public:
        const std::wstring id;
        const std::wstring modificationType;
        Modification(const std::wstring &id, const std::wstring &modificationType);
//        std::wstring ToString() override;
//        bool Equals(std::any o) override;
//        int GetHashCode() override;
        std::wstring ToString();
        bool Equals(std::any o);
        int GetHashCode();
    };
}
