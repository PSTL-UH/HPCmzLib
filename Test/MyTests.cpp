#include "MyTests.h"
#include "../Proteomics/OldSchoolModification.h"
#include "../Proteomics/ModificationCollection.h"

using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void MyTests::ModificationCollectionTest() {
        OldSchoolModification *mod1 = new OldSchoolModification(10, L"mass 10 modification");
        OldSchoolModification *mod2 = new OldSchoolModification(100, L"mass 100 modification");
        OldSchoolModification *mod3 = new OldSchoolModification(1000, L"mass 1000 modification");
        ModificationCollection *a = new ModificationCollection({mod1, mod2, mod3, mod1});
        ModificationCollection *b = new ModificationCollection({mod1, mod3, mod1, mod2});
        Assert::IsTrue(a->Equals(b));
        ModificationCollection *c = new ModificationCollection({mod1});
        Assert::IsFalse(c->Equals(b));

        delete c;
//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
        delete a;
//C# TO C++ CONVERTER TODO TASK: A 'delete mod3' statement was not added since mod3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mod2' statement was not added since mod2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mod1' statement was not added since mod1 was passed to a method or constructor. Handle memory management manually.
    }
}
