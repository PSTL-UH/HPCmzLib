#pragma once

#include "../MassSpectrometry/DataScan/IMsDataScan.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class ThermoSpectrum; } }

using namespace MassSpectrometry;

namespace IO {
    namespace Thermo {
        class IThermoScan : public IMsDataScan<ThermoSpectrum*> {
        };
    }
}
