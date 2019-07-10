#pragma once

#include <unordered_map>
#include <vector>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (ClassExtensions.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.


namespace MzLibUtil {
    class ClassExtensions final {

    public:
        static std::vector<double> BoxCarSmooth(std::vector<double> &data, int points);

        template<typename T>
        static std::vector<T> SubArray(std::vector<T> &data, int index, int length);

        /// <summary>
        /// Checks if two collections are equivalent, regardless of the order of their contents
        /// </summary>
        template<typename T>
        static bool ScrambledEquals(std::vector<T> &list1, std::vector<T> &list2);

    };
}
