#pragma once

#include <iostream>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "../Mgf/Mgf.h"
using namespace IO::Mgf;

namespace Test
{
    class TestMgf final
    {
    public:
        static void TestLoadMgf();
    };
}
