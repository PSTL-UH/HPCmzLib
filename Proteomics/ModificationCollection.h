#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include <string>
#include <vector>
#include <algorithm>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class IHasMass; }
namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (ModificationCollection.cs) is part of Proteomics.
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
using namespace MzLibUtil;

namespace Proteomics {
    class ModificationCollection : public ICollection<IHasMass*>, public IEquatable<ModificationCollection*>, public IHasChemicalFormula {
    private:
        double privateMonoisotopicMass = 0;

//        #region Private Fields

        const std::vector<IHasMass*> _modifications;

//        #endregion Private Fields

//        #region Public Constructors

    public:
        ModificationCollection(std::vector<IHasMass> &mods);

//        #endregion Public Constructors

//        #region Public Properties

        double getMonoisotopicMass() const override;
        void setMonoisotopicMass(double value) override;

        int getCount() const override;

        bool getIsReadOnly() const override;

        ChemicalFormula *getThisChemicalFormula() const override;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

        void Add(IHasMass *item) override;

        void Clear() override;

        bool Contains(IHasMass *item) override;

        void CopyTo(std::vector<IHasMass*> &array_Renamed, int arrayIndex) override;

        bool Remove(IHasMass *item) override;

        bool Equals(ModificationCollection *other) override;

        IEnumerator<IHasMass*> *GetEnumerator() override;

        System::Collections::IEnumerator *IEnumerable_GetEnumerator() override;

//        #endregion Public Methods
    };
}
