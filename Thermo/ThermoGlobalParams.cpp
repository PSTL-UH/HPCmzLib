#include "ThermoGlobalParams.h"

namespace IO {
    namespace Thermo {

        ThermoGlobalParams::ThermoGlobalParams(int pnNumInstMethods, std::vector<std::wstring> &instrumentMethods, const std::wstring &pbstrInstSoftwareVersion, const std::wstring &pbstrInstName, const std::wstring &pbstrInstModel, int pnControllerType, int pnControllerNumber, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::wstring &filePath, std::vector<int> &msOrderByScan) : instrumentMethods(instrumentMethods), pbstrInstModel(pbstrInstModel), pbstrInstName(pbstrInstName), pbstrInstSoftwareVersion(pbstrInstSoftwareVersion), pnControllerNumber(pnControllerNumber), pnControllerType(pnControllerType), pnNumInstMethods(pnNumInstMethods), filePath(filePath), couldBePrecursor(couldBePrecursor), scanEvent(std::vector<int>(couldBePrecursor.size())), msOrderByScan(msOrderByScan) {
        }

        bool ThermoGlobalParams::getMonoisotopicselectionEnabled() const {
            for (auto yha : instrumentMethods) {
                if (Regex::IsMatch(yha, L"Monoisotopic precursor selection enabled")) {
                    return true;
                }
            }
            return false;
        }
    }
}
