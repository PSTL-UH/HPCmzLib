#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class ThermoGlobalParams; } }
namespace MassSpectrometry { class SourceFile; }
namespace MassSpectrometry { class MsDataScan; }

using namespace MassSpectrometry;

namespace IO
{
    namespace Thermo
    {
        //This file exists to deal with the configuration differences of netStandard and Net Framework, of which Thermo is only available for Net framework
        class ThermoDataFile : public MsDataFile
        {
        private:
            IO::Thermo::ThermoGlobalParams *privateThermoGlobalParams;

            public:
                IO::Thermo::ThermoGlobalParams *getThermoGlobalParams() const;
                void setThermoGlobalParams(IO::Thermo::ThermoGlobalParams *value);

            ThermoDataFile(int numSpectra, MassSpectrometry::SourceFile *sourceFile);

            ThermoDataFile(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile);
        };
    }
}
