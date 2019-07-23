﻿#pragma once

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (TestAminoAcids.cs) is part of Proteomics.
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

//using namespace NUnit::Framework;
#include "../Proteomics/Proteomics.h"

using namespace Proteomics;

namespace Test {
    class TestAminoAcids final {

    public:
        static void GetResidueByCharacter();

        static void GetResidueByCharacterString();

        static void GetResidueByName();

        static void GetResidueNotInDictionary();

        static void ResidueMonoisotopicMassTest();

    };
}
