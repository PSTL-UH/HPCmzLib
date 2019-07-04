#pragma once

#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <optional>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { template<typename TScan>class IMsDataFile; }
namespace MassSpectrometry { template<typename TSpectrum>class IMsDataScan; }
namespace MassSpectrometry { class IMzPeak; }
namespace MassSpectrometry { template<typename TPeak>class IMzSpectrum; }

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO {
    namespace MzML {
        class MzmlMethods final {

        public:
            static XmlSerializer *const indexedSerializer;
            static XmlSerializer *const mzmlSerializer;

        private:
            static const std::unordered_map<DissociationType, std::string> DissociationTypeAccessions;

            static const std::unordered_map<DissociationType, std::string> DissociationTypeNames;

            static const std::unordered_map<MZAnalyzerType, std::string> analyzerDictionary;

            static const std::unordered_map<std::string, std::string> nativeIdFormatAccessions;

            static const std::unordered_map<std::string, std::string> MassSpectrometerFileFormatAccessions;

            static const std::unordered_map<std::string, std::string> FileChecksumAccessions;

            static const std::unordered_map<bool, std::string> CentroidAccessions;

            static const std::unordered_map<bool, std::string> CentroidNames;

            static const std::unordered_map<Polarity, std::string> PolarityAccessions;

            static const std::unordered_map<Polarity, std::string> PolarityNames;


        public:
            static void CreateAndWriteMyMzmlWithCalibratedSpectra(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *myMsDataFile, const std::string &outputFile, bool writeIndexed);

        };
    }
}
