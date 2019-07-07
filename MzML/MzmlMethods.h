#pragma once

#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <cctype>
#include <optional>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MsDataFile; }

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO
{
    namespace MzML
    {
        class MzmlMethods final
        {
        public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
            static XmlSerializer *const indexedSerializer;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
            static XmlSerializer *const mzmlSerializer;

        private:
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<DissociationType, string> DissociationTypeAccessions = new Dictionary<DissociationType, string> { {DissociationType.CID, "MS:1000133"}, {DissociationType.ISCID, "MS:1001880"}, {DissociationType.HCD, "MS:1000422" }, {DissociationType.ETD, "MS:1000598"}, {DissociationType.IRMPD, "MS:1000435"}, {DissociationType.PQD, "MS:1000599"}, {DissociationType.Unknown, "MS:1000044"} };
            static std::unordered_map<DissociationType, std::string> DissociationTypeAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<DissociationType, string> DissociationTypeNames = new Dictionary<DissociationType, string> { {DissociationType.CID, "collision-induced dissociation"}, {DissociationType.ISCID, "in-source collision-induced dissociation"}, {DissociationType.HCD, "beam-type collision-induced dissociation"}, {DissociationType.ETD, "electron transfer dissociation"}, {DissociationType.IRMPD, "photodissociation"}, {DissociationType.PQD, "pulsed q dissociation"}, {DissociationType.Unknown, "dissociation method"} };
            static std::unordered_map<DissociationType, std::string> DissociationTypeNames;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<MZAnalyzerType, string> analyzerDictionary = new Dictionary<MZAnalyzerType, string> { {MZAnalyzerType.Unknown, "MS:1000443"}, {MZAnalyzerType.Quadrupole, "MS:1000081"}, {MZAnalyzerType.IonTrap2D, "MS:1000291"}, {MZAnalyzerType.IonTrap3D,"MS:1000082"}, {MZAnalyzerType.Orbitrap,"MS:1000484"}, {MZAnalyzerType.TOF,"MS:1000084"}, {MZAnalyzerType.FTICR,"MS:1000079"}, {MZAnalyzerType.Sector,"MS:1000080"} };
            static std::unordered_map<MZAnalyzerType, std::string> analyzerDictionary;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, string> nativeIdFormatAccessions = new Dictionary<string, string> { {"scan number only nativeID format", "MS:1000776"}, {"Thermo nativeID format", "MS:1000768"}, {"no nativeID format", "MS:1000824" }};
            static std::unordered_map<std::string, std::string> nativeIdFormatAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, string> MassSpectrometerFileFormatAccessions = new Dictionary<string, string> { {"Thermo RAW format", "MS:1000563"}, {"mzML format", "MS:1000584"}};
            static std::unordered_map<std::string, std::string> MassSpectrometerFileFormatAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<string, string> FileChecksumAccessions = new Dictionary<string, string> { {"MD5", "MS:1000568"}, {"SHA-1", "MS:1000569"}};
            static std::unordered_map<std::string, std::string> FileChecksumAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<bool, string> CentroidAccessions = new Dictionary<bool, string> { {true, "MS:1000127"}, {false, "MS:1000128"} };
            static std::unordered_map<bool, std::string> CentroidAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<bool, string> CentroidNames = new Dictionary<bool, string> { {true, "centroid spectrum"}, {false, "profile spectrum"} };
            static std::unordered_map<bool, std::string> CentroidNames;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<Polarity, string> PolarityAccessions = new Dictionary<Polarity, string> { {Polarity.Negative, "MS:1000129"}, {Polarity.Positive, "MS:1000130"} };
            static std::unordered_map<Polarity, std::string> PolarityAccessions;

//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<Polarity, string> PolarityNames = new Dictionary<Polarity, string> { {Polarity.Negative, "negative scan"}, {Polarity.Positive, "positive scan"} };
            static std::unordered_map<Polarity, std::string> PolarityNames;

        public:
            static void CreateAndWriteMyMzmlWithCalibratedSpectra(MsDataFile *myMsDataFile, const std::string &outputFile, bool writeIndexed);
        };
    }
}
