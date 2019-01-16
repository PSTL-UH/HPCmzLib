#pragma once

#include "../Chemistry/Interfaces/IHasMass.h"
#include "ModificationSites.h"
#include <string>
#include <cmath>
#include <any>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Modification.cs) is part of Proteomics.
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

using namespace Chemistry;

namespace Proteomics {
    /// <summary>
    /// Represents a modification with a mass and name and default amino acid sites of modification
    /// </summary>
//    class OldSchoolModification : public IHasMass, public IEquatable<OldSchoolModification*> {
    class OldSchoolModification : public IHasMass {
    private:
        std::string privateName;
        double privateMonoisotopicMass = 0;
        ModificationSites privateSites = static_cast<ModificationSites>(0);

    public:
        OldSchoolModification(const OldSchoolModification &modification);

        OldSchoolModification();

        OldSchoolModification(double monoMass);

        OldSchoolModification(double monoMass, const std::string &name);

        OldSchoolModification(double monoMass, const std::string &name, ModificationSites sites);

        /// <summary>
        /// The name of the modification
        /// </summary>
        std::string getName() const;
        void setName(const std::string &value);

        /// <summary>
        /// The monoisotopic mass of the modification, commoningly known as the delta mass
        /// </summary>
        double getMonoisotopicMass() const override;
//        void setMonoisotopicMass(double value) override;
        void setMonoisotopicMass(double value);

        /// <summary>
        /// The potentially modified sites of this modification
        /// </summary>
        ModificationSites getSites() const;
        void setSites(ModificationSites value);

        /// <summary>
        /// Displays the name of the mod and the sites it modified in a formated string
        /// </summary>
        std::string getNameAndSites() const;

//        std::string ToString() override;
        std::string ToString();

//        int GetHashCode() override;
        int GetHashCode();

//        bool Equals(std::any obj) override;
//        bool Equals(OldSchoolModification *other) override;
        bool Equals(OldSchoolModification *other);

    };
}
