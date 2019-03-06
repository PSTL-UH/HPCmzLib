#pragma once

#include <string>

// Copyright 2016 Stefan Solntsev
//
// This file (PeriodicTable.cs) is part of UsefulProteomicsDatabases.
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

using namespace Chemistry;

namespace UsefulProteomicsDatabases {
    /// <summary>
    /// The Periodic Table of Elements.
    /// </summary>
    class PeriodicTableLoader final {

    public:
        static void Load(const std::string &elementLocation);

    };
}
