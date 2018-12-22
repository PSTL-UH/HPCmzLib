#pragma once

#include "../Chemistry/Interfaces/IHasMass.h"
#include "FragmentTypes.h"
#include <string>
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class AminoAcidPolymer; }
namespace Chemistry { class IHasMass; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Fragment.cs) is part of Proteomics.
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
    class Fragment : public IHasMass, public IEquatable<Fragment*> {
    private:
        double privateMonoisotopicMass = 0;
        int privateNumber = 0;
        AminoAcidPolymer *privateParent;
        FragmentTypes privateFragmentType = static_cast<FragmentTypes>(0);

//        #region Public Constructors

    public:
        Fragment(FragmentTypes type, int number, double monoisotopicMass, AminoAcidPolymer *parent);

//        #endregion Public Constructors

//        #region Public Properties

        double getMonoisotopicMass() const override;
        void setMonoisotopicMass(double value) override;

        int getNumber() const;
        void setNumber(int value);

        AminoAcidPolymer *getParent() const;
        void setParent(AminoAcidPolymer *value);

        FragmentTypes getFragmentType() const;
        void setFragmentType(FragmentTypes value);

        std::vector<IHasMass*> getModifications() const;

        std::wstring getSequence() const;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

        int GetHashCode() override;

        bool Equals(Fragment *other) override;

//        #endregion Public Methods
    };
}
