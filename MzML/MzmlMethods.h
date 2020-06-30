/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
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
#include "../MassSpectrometry/MsDataFile.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO
{
    namespace MzML
    {
        class MzmlMethods final
        {
        private:
            static std::unordered_map<DissociationType, std::string> DissociationTypeAccessions;
            static std::unordered_map<DissociationType, std::string> DissociationTypeNames;
            static std::unordered_map<MZAnalyzerType, std::string> analyzerDictionary;
            static std::unordered_map<std::string, std::string> nativeIdFormatAccessions;
            static std::unordered_map<std::string, std::string> MassSpectrometerFileFormatAccessions;
            static std::unordered_map<std::string, std::string> FileChecksumAccessions;
            static std::unordered_map<bool, std::string> CentroidAccessions;
            static std::unordered_map<bool, std::string> CentroidNames;
            static std::unordered_map<Polarity, std::string> PolarityAccessions;
            static std::unordered_map<Polarity, std::string> PolarityNames;

        public:
            static void CreateAndWriteMyMzmlWithCalibratedSpectra(MsDataFile *myMsDataFile, const std::string &outputFile, bool writeIndexed);
        };
    }
}
