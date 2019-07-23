#include "FixtureSetUp.h"
#include "../UsefulProteomicsDatabases/Loaders.h"

using namespace NUnit::Framework;
using namespace UsefulProteomicsDatabases;

namespace Test
{

    void MySetUpClass::Setup()
    {
        auto elementLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "lal.dat");
        Loaders::LoadElements(elementLocation);
    }
}
