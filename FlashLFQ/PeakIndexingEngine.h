#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <typeinfo>
#include "exceptionhelper.h"
#include "tangible_filesystem.h"

#include "IndexedMassSpectralPeak.h"
#include "Ms1ScanInfo.h"
#include "SpectraFileInfo.h"
#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

//using namespace IO::MzML;
#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;
//using namespace NetSerializer;

#include "../MzML/Mzml.h"

namespace FlashLFQ
{
    class PeakIndexingEngine
    {
    private:
        std::vector<std::vector<IndexedMassSpectralPeak*>> _indexedPeaks;
        //XmlSerializer * _serializer;
        static constexpr int BinsPerDalton = 100;

    public:
        virtual ~PeakIndexingEngine()
        {
            //delete _serializer;
        }

        PeakIndexingEngine();

        bool IndexMassSpectralPeaks(SpectraFileInfo *fileInfo, bool silent, std::unordered_map<SpectraFileInfo*,
                                    std::vector<Ms1ScanInfo*>> &_ms1Scans);

        void ClearIndex();

        void SerializeIndex(SpectraFileInfo *file);

        void DeserializeIndex(SpectraFileInfo *file);

        IndexedMassSpectralPeak *GetIndexedPeak(double theorMass, int zeroBasedScanIndex,
                                                Tolerance *tolerance, int chargeState);

    private:
        int BinarySearchForIndexedPeak(std::vector<IndexedMassSpectralPeak*> &indexedPeaks,
                                       int zeroBasedScanIndex);
    };
}
