#include "ThermoDataFile.h"
#include "ThermoGlobalParams.h"
#include "../MassSpectrometry/SourceFile.h"
#include "../MassSpectrometry/MsDataScan.h"

using namespace MassSpectrometry;
namespace IO
{
    namespace Thermo
    {

        IO::Thermo::ThermoGlobalParams *ThermoDataFile::getThermoGlobalParams() const
        {
            return privateThermoGlobalParams;
        }

        void ThermoDataFile::setThermoGlobalParams(IO::Thermo::ThermoGlobalParams *value)
        {
            privateThermoGlobalParams = value;
        }

        ThermoDataFile::ThermoDataFile(int numSpectra, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(numSpectra, sourceFile)
        {
        }

        ThermoDataFile::ThermoDataFile(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(scans, sourceFile)
        {
        }
    }
}
