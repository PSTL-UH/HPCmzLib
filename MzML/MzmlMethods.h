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
    //        #region Internal Fields

        public:
            static XmlSerializer *const indexedSerializer;
            static XmlSerializer *const mzmlSerializer;

    //        #endregion Internal Fields

    //        #region Private Fields

        private:
            static const std::unordered_map<DissociationType, std::wstring> DissociationTypeAccessions;

            static const std::unordered_map<DissociationType, std::wstring> DissociationTypeNames;

            static const std::unordered_map<MZAnalyzerType, std::wstring> analyzerDictionary;

            static const std::unordered_map<std::wstring, std::wstring> nativeIdFormatAccessions;

            static const std::unordered_map<std::wstring, std::wstring> MassSpectrometerFileFormatAccessions;

            static const std::unordered_map<std::wstring, std::wstring> FileChecksumAccessions;

            static const std::unordered_map<bool, std::wstring> CentroidAccessions;

            static const std::unordered_map<bool, std::wstring> CentroidNames;

            static const std::unordered_map<Polarity, std::wstring> PolarityAccessions;

            static const std::unordered_map<Polarity, std::wstring> PolarityNames;

    //        #endregion Private Fields

    //        #region Public Methods

        public:
            static void CreateAndWriteMyMzmlWithCalibratedSpectra(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *myMsDataFile, const std::wstring &outputFile, bool writeIndexed);

    //        #endregion Public Methods
        };
    }
}
