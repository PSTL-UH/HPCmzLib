#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <optional>
#include "exceptionhelper.h"
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MsDataScan; }
namespace MassSpectrometry { class SourceFile; }
namespace MassSpectrometry { class FilteringParams; }

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO
{
    namespace Mgf
    {
        class Mgf : public MsDataFile
        {
        private:
            std::vector<MsDataScan*> indexedScans;

            Mgf(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile);

        public:
            static Mgf *LoadAllStaticData(const std::string &filePath, FilteringParams *filterParams = nullptr);

            MsDataScan *GetOneBasedScan(int scanNumber) override;
        };
    }
}
