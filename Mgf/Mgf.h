#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <optional>
#include "exceptionhelper.h"
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
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
