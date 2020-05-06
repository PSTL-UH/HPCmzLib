#pragma once

#include "ThermoDataFile.h"
#include <string>
#include <vector>
#include "exceptionhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class IFilteringParams; }
namespace MassSpectrometry { class SourceFile; }
namespace IO { namespace Thermo { class ThermoGlobalParams; } }
namespace MassSpectrometry { class MsDataScan; }

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;

namespace IO
{
    namespace Thermo
    {
        class ThermoDynamicData : public ThermoDataFile, public IDisposable
        {
        private:
            IXRawfile5 *const _rawConnection;
            IFilteringParams *const filterParams;

            ThermoDynamicData(IXRawfile5 *_rawConnection, IFilteringParams *filterParams, int numSpectra, MassSpectrometry::SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams);

        public:
            static ThermoDynamicData *InitiateDynamicConnection(const std::string &filePath, IFilteringParams *filterParams = nullptr);

            MsDataScan *GetOneBasedScan(int oneBasedScanNumber) override;

            virtual void ClearCachedScans();

            int GetClosestOneBasedSpectrumNumber(double retentionTime) override;

            ~ThermoDynamicData();

        private:
            void Dispose(bool disposing);
        };
    }
}
