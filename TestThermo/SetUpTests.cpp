#include "SetUpTests.h"
#include "../UsefulProteomicsDatabases/Loaders.h"

using namespace NUnit::Framework;
using namespace UsefulProteomicsDatabases;

namespace TestThermo {

    void MySetUpClass::Setup() {
        auto elementLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"lal.dat");
        Loaders::LoadElements(elementLocation);
    }
}
