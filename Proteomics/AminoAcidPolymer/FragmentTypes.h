#pragma once

#include "Terminus.h"
#include <unordered_map>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (FragmentTypes.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Proteomics is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>.

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Flags] public enum FragmentTypes
    enum class FragmentTypes {
        None = 0,
        a = 1 << 0,
        adot = 1 << 1,
        b = 1 << 2,
        bdot = 1 << 3,
        c = 1 << 4,
        cdot = 1 << 5,
        x = 1 << 6,
        xdot = 1 << 7,
        y = 1 << 8,
        ydot = 1 << 9,
        z = 1 << 10,
        zdot = 1 << 11,
        Internal = 1 << 12,
        All = (1 << 12) - 1, // Handy way of setting all below the 12th bit
    };

    class FragmentTypesExtension final {

    private:
        static const std::unordered_map<FragmentTypes, ChemicalFormula*> FragmentIonCaps;

    public:
        static std::vector<FragmentTypes> GetIndividualFragmentTypes(FragmentTypes fragmentTypes);

        static Terminus GetTerminus(FragmentTypes fragmentType);

        static ChemicalFormula *GetIonCap(FragmentTypes fragmentType) ;
        static const std::vector<FragmentTypes> FragmentTypesValues; 
        static std::vector<FragmentTypes> GetValues();
        static const std::vector<std::string> FragmentTypesNames;
        static std::vector<std::string> GetNames();
        static std::string GetName( FragmentTypes fragmentType);

    };
}
