#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include <string>
#include <vector>
#include <algorithm>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Chemistry { class IHasMass; }
//namespace Chemistry { class ChemicalFormula; }

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

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {
    namespace AminoAcidPolymer    {

    
        //  class ModificationCollection : public ICollection<IHasMass*>, public IEquatable<ModificationCollection*>,
        //                                 public IHasChemicalFormula {
        class ModificationCollection : std::vector<IHasMass*>, public Chemistry::IHasChemicalFormula {
        private:
            double privateMonoisotopicMass = 0;
            
            //  const std::vector<IHasMass*> _modifications;
            std::vector<IHasMass*> _modifications;
            
        public:
            ModificationCollection(std::vector<IHasMass*> &mods);
            
            double getMonoisotopicMass() const override;
            // double getMonoisotopicMass() const;

            // void setMonoisotopicMass(double value) override;
            void setMonoisotopicMass(double value);
            
            // int getCount() const override;
            int getCount() const;
            
            // bool getIsReadOnly() const override;
            bool getIsReadOnly() const;
            
            ChemicalFormula *getThisChemicalFormula() const override;
            
            std::string ToString();

            // void Add(IHasMass *item) override;
            void Add(IHasMass *item);
            
            // void Clear() override;
            void Clear();
            
            // bool Contains(IHasMass *item) override;
            bool Contains(IHasMass *item);
            
            // void CopyTo(std::vector<IHasMass*> &array_Renamed, int arrayIndex) override;
            void CopyTo(std::vector<IHasMass*> &array_Renamed, int arrayIndex);
            
            // bool Remove(IHasMass *item) override;
            bool Remove(IHasMass *item);
            
            // bool Equals(ModificationCollection *other) override;
            bool Equals(ModificationCollection *other);
            
            // IEnumerator<IHasMass*> *GetEnumerator() override;
            std::vector<IHasMass*>::iterator GetEnumerator();

            // EG: Not implementing this method in C++ for now.
            // System::Collections::IEnumerator *IEnumerable_GetEnumerator() override;
            
        };
    }
}
