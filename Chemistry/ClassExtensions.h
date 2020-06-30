/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <vector>
#include <cmath>
#include <tuple>
#include <optional>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class IHasMass; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (MassExtensions.cs) is part of Chemistry Library.
//
// Chemistry Library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chemistry Library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>.


namespace Chemistry {
    class ClassExtensions final {

        /// <summary>
        /// Calculates m/z value for a given mass assuming charge comes from losing or gaining prot
        /// </summary>
    public:
        static double ToMz(IHasMass *objectWithMass, int charge);

        /// <summary>
        /// Calculates m/z value for a given mass assuming charge comes from losing or gaining prot
        /// </summary>
        static double ToMz(double mass, int charge);

        /// <summary>
        /// Determines the original mass from an m/z value, assuming charge comes from a proton
        /// </summary>
        static double ToMass(double massToChargeRatio, int charge);

        static std::optional<double> RoundedDouble(std::optional<double> &myNumber, int places = 9);
        static double RoundedDouble(double myNumber, int places=9);

    public:
        template<typename T1, typename T2>
        class TupleList : public std::vector<std::tuple<T1, T2>>
        {
        public:
            void Add(T1 item, T2 item2)
            {
                this->Add(std::tuple<T1, T2>(item, item2));
            }
        };
    };
}
