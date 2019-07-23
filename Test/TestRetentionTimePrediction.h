#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>
#include <any>
#include "stringhelper.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
using namespace Proteomics::RetentionTimePrediction;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
    /*
     * Original author: Brendan MacLean <brendanx .at. u.washington.edu>,
     *                  MacCoss Lab, Department of Genome Sciences, UW
     *
     * Copyright 2009 University of Washington - Seattle, WA
     *
     * Licensed under the Apache License, Version 2.0 (the "License");
     * you may not use this file except in compliance with the License.
     * You may obtain a copy of the License at
     *
     *     http://www.apache.org/licenses/LICENSE-2.0
     *
     * Unless required by applicable law or agreed to in writing, software
     * distributed under the License is distributed on an "AS IS" BASIS,
     * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
     * See the License for the specific language governing permissions and
     * limitations under the License.
     */

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestRetentionTimePrediction
    class TestRetentionTimePrediction final
    {
    private:
        static Stopwatch *privateStopwatch;

        const std::vector<std::vector<std::any>> _peptides300A;
        const std::vector<std::vector<std::any>> _peptides100A;
        const std::vector<std::vector<std::any>> _peptidesCZE;

    public:
        TestRetentionTimePrediction();

    private:
        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setuppp()
        static void Setuppp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

        /// <summary>
        ///A test for ScoreSequence with 300A column
        ///</summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void SSRCalc3_300A_Test()
        void SSRCalc3_300A_Test();

        /// <summary>
        ///A test for ScoreSequence with 100A column
        ///</summary>
        // Problems with the results from the article
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void SSRCalc3_100A_Test()
        void SSRCalc3_100A_Test();

        /// <summary>
        ///A test for CZE retention time prediction
        ///</summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void CZE_RetentionTime_Test()
        void CZE_RetentionTime_Test();
    };
}
