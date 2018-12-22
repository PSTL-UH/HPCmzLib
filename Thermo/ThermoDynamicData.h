#pragma once

#include "../MassSpectrometry/IMsDynamicDataFile.h"
#include "ThermoFile.h"
#include <string>
#include <vector>
#include <optional>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class IThermoScan; } }
namespace MassSpectrometry { class SourceFile; }
namespace IO { namespace Thermo { class ThermoGlobalParams; } }

using namespace MassSpectrometry;
using namespace MSFileReaderLib;

namespace IO {
    namespace Thermo {
        class ThermoDynamicData : public ThermoFile, public IMsDynamicDataFile<IThermoScan*> {
    //        #region Private Fields

        private:
            IXRawfile5 *const _rawConnection;
            const bool trimMsMsPeaks;
            const bool trimMs1Peaks;
            const std::optional<double> minRatio;
            const std::optional<int> topNpeaks;

    //        #endregion Private Fields

    //        #region Private Constructors

            ThermoDynamicData(IXRawfile5 *_rawConnection, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks, int numSpectra, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams);

    //        #endregion Private Constructors

    //        #region Public Methods

        public:
            static ThermoDynamicData *InitiateDynamicConnection(const std::wstring &filePath, std::optional<int> &topNpeaks = std::nullopt, std::optional<double> &minRatio = std::nullopt, bool trimMs1Peaks = true, bool trimMsMsPeaks = true);

            IThermoScan *GetOneBasedScan(int oneBasedScanNumber) override;

            void ClearCachedScans() override;

            int GetClosestOneBasedSpectrumNumber(double retentionTime) override;

            ~ThermoDynamicData();

    //        #endregion Public Methods

    //        #region Protected Methods

        private:
            void Dispose(bool disposing);

    //        #endregion Protected Methods
        };
    }
}
