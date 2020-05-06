#include "ThermoGlobalParams.h"

namespace IO
{
    namespace Thermo
    {

        ThermoGlobalParams::ThermoGlobalParams(int pnNumInstMethods, std::vector<std::string> &instrumentMethods, const std::string &pbstrInstSoftwareVersion, const std::string &pbstrInstName, const std::string &pbstrInstModel, int pnControllerType, int pnControllerNumber, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::string &filePath, std::vector<int> &msOrderByScan) : InstrumentMethods(instrumentMethods), PbstrInstModel(pbstrInstModel), PbstrInstName(pbstrInstName), PbstrInstSoftwareVersion(pbstrInstSoftwareVersion), PnControllerNumber(pnControllerNumber), PnControllerType(pnControllerType), PnNumInstMethods(pnNumInstMethods), FilePath(filePath), CouldBePrecursor(couldBePrecursor), ScanEvent(std::vector<int>(couldBePrecursor.size())), MsOrderByScan(msOrderByScan)
        {
        }

        bool ThermoGlobalParams::getMonoisotopicselectionEnabled() const
        {
            for (auto yha : InstrumentMethods)
            {
                if (Regex::IsMatch(yha, "Monoisotopic precursor selection enabled"))
                {
                    return true;
                }
            }
            return false;
        }
    }
}
