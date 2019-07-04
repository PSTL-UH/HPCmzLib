#pragma once

#include "../MassSpectrometry/DataScan/IMsDataScan.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class MzmlMzSpectrum; } }

using namespace MassSpectrometry;

namespace IO {
    namespace MzML {
        class IMzmlScan : public IMsDataScan<MzmlMzSpectrum*> {
        };
    }
}
