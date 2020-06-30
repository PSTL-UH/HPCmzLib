/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
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
        static std::vector<T> SubArray(std::vector<T> &data, int index, int length) {
            std::vector<T> result(length);
            std::copy(data.at(index), data.at(index+length), result.begin()) ;
            return result;
        }

        /// <summary>
        /// Checks if two collections are equivalent, regardless of the order of their contents
        /// </summary>
        template<typename T>
        static bool ScrambledEquals(std::vector<T> list1, std::vector<T> list2) {
            auto cnt = std::unordered_map<T, int>();
            for (auto s : list1) {
                if (cnt.find(s) != cnt.end()) {
                    cnt[s]++;
                }
                else {
                    cnt.emplace(s, 1);
                }
            }
            for (auto s : list2) {
                if (cnt.find(s) != cnt.end()) {
                    cnt[s]--;
                }
                else {
                    return false;
                }
            }
//        return cnt.Values->All([&] (std::any c) {
//                return (c == 0);
//        });
            for (std::pair<T, int> element : cnt)
            {
                if ( element.second != 0 ) {
                    return false;
                }
            }
            return true;        
        }       
            
        };
    }
