#pragma once

#include "OldSchoolModification.h"
#include "ModificationSites.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class OldSchoolModification; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Isotopologue.cs) is part of Proteomics.
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

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {
    class ModificationWithMultiplePossibilitiesCollection : public OldSchoolModification, public std::vector<OldSchoolModification*> {

    private:
//        SortedList<double, OldSchoolModification*> *const _modifications;
        std::map<double, OldSchoolModification*> *const _modifications;

    public:
        virtual ~ModificationWithMultiplePossibilitiesCollection() {
            delete _modifications;
        }

        ModificationWithMultiplePossibilitiesCollection(const std::string &name, ModificationSites sites);

        int getCount() const;

        OldSchoolModification *operator [](int index);

        void AddModification(OldSchoolModification *modification);

        bool Contains(OldSchoolModification *modification);


//        IEnumerator<OldSchoolModification*> *GetEnumerator() override;
//
//        System::Collections::IEnumerator *IEnumerable_GetEnumerator() override;

    };
}
