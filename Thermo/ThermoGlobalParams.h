#pragma once

#include <string>
#include <vector>


namespace IO {
    namespace Thermo {
        class ThermoGlobalParams {
    //        #region Public Fields

        public:
            std::vector<std::wstring> const instrumentMethods;
            const std::wstring pbstrInstModel;
            const std::wstring pbstrInstName;
            const std::wstring pbstrInstSoftwareVersion;
            const int pnControllerNumber;
            const int pnControllerType;
            const int pnNumInstMethods;
            const std::wstring filePath;

            std::vector<ManagedThermoHelperLayer::PrecursorInfo*> const couldBePrecursor;
            std::vector<int> const scanEvent;
            std::vector<int> const msOrderByScan;

    //        #endregion Public Fields

    //        #region Public Constructors

            ThermoGlobalParams(int pnNumInstMethods, std::vector<std::wstring> &instrumentMethods, const std::wstring &pbstrInstSoftwareVersion, const std::wstring &pbstrInstName, const std::wstring &pbstrInstModel, int pnControllerType, int pnControllerNumber, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::wstring &filePath, std::vector<int> &msOrderByScan);

    //        #endregion Public Constructors

    //        #region Public Properties

            bool getMonoisotopicselectionEnabled() const;

    //        #endregion Public Properties
        };
    }
}
