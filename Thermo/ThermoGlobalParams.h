#pragma once

#include <string>
#include <vector>


namespace IO
{
    namespace Thermo
    {
        class ThermoGlobalParams
        {
        public:
            const std::vector<std::string> InstrumentMethods;
            const std::string PbstrInstModel;
            const std::string PbstrInstName;
            const std::string PbstrInstSoftwareVersion;
            const int PnControllerNumber;
            const int PnControllerType;
            const int PnNumInstMethods;
            const std::string FilePath;

            const std::vector<ManagedThermoHelperLayer::PrecursorInfo*> CouldBePrecursor;
            const std::vector<int> ScanEvent;
            const std::vector<int> MsOrderByScan;

            ThermoGlobalParams(int pnNumInstMethods, std::vector<std::string> &instrumentMethods, const std::string &pbstrInstSoftwareVersion, const std::string &pbstrInstName, const std::string &pbstrInstModel, int pnControllerType, int pnControllerNumber, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::string &filePath, std::vector<int> &msOrderByScan);

            bool getMonoisotopicselectionEnabled() const;
        };
    }
}
