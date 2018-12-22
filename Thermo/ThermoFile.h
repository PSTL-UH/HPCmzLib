#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include <string>
#include <vector>
#include <any>
#include <optional>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class IThermoScan; } }
namespace IO { namespace Thermo { class ThermoGlobalParams; } }
namespace MassSpectrometry { class SourceFile; }

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;

namespace IO {
    namespace Thermo {
        class ThermoFile : public MsDataFile<IThermoScan*> {
        private:
            IO::Thermo::ThermoGlobalParams *privateThermoGlobalParams;

    //        #region Private Fields

            static Regex *const PolarityRegex;
            static Regex *const mFindParentIonOnlyNonMsx;
            static Regex *const mFindParentIonOnlyMsx;

    //        #endregion Private Fields

    //        #region Protected Constructors

        protected:
            ThermoFile(std::vector<IThermoScan*> &scans, IO::Thermo::ThermoGlobalParams *thermoGlobalParams, MassSpectrometry::SourceFile *sourceFile);

            ThermoFile(IXRawfile5 *_rawConnection, int numSpectra, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, MassSpectrometry::SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams);

    //        #endregion Protected Constructors

    //        #region Private Enums

        private:
            enum class ThermoMzAnalyzer {
                None = -1,
                ITMS = 0,
                TQMS = 1,
                SQMS = 2,
                TOFMS = 3,
                FTMS = 4,
                Sector = 5
            };

    //        #endregion Private Enums

    //        #region Public Properties

            public:
                IO::Thermo::ThermoGlobalParams *getThermoGlobalParams() const;

    //        #endregion Public Properties

    //        #region Public Methods

            static IO::Thermo::ThermoGlobalParams *GetAllGlobalStuff(IXRawfile5 *_rawConnection, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::wstring &filePath);

    //        #endregion Public Methods

    //        #region Protected Methods

        protected:
            static IThermoScan *GetMsDataOneBasedScanFromThermoFile(int nScanNumber, IXRawfile5 *theConnection, IO::Thermo::ThermoGlobalParams *globalParams, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks);

    //        #endregion Protected Methods
        };
    }
}
