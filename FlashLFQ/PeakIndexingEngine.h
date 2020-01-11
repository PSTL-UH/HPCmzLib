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

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class IndexedMassSpectralPeak; }
namespace FlashLFQ { class Ms1ScanInfo; }
namespace FlashLFQ { class SpectraFileInfo; }

//namespace MzLibUtil { class Tolerance; }

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

//using namespace IO::MzML;
#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;
//using namespace NetSerializer;

namespace FlashLFQ
{
    class PeakIndexingEngine
    {
    private:
        std::vector<std::vector<IndexedMassSpectralPeak*>> _indexedPeaks;
        Serializer *const _serializer;
        static constexpr int BinsPerDalton = 100;

    public:
        virtual ~PeakIndexingEngine()
        {
            //delete _serializer;
        }

        PeakIndexingEngine();

        bool IndexMassSpectralPeaks(SpectraFileInfo *fileInfo, bool silent, std::unordered_map<SpectraFileInfo*, std::vector<Ms1ScanInfo*>> &_ms1Scans);

        void ClearIndex();

        void SerializeIndex(SpectraFileInfo *file);

        void DeserializeIndex(SpectraFileInfo *file);

        IndexedMassSpectralPeak *GetIndexedPeak(double theorMass, int zeroBasedScanIndex, Tolerance *tolerance, int chargeState);

    private:
        int BinarySearchForIndexedPeak(std::vector<IndexedMassSpectralPeak*> &indexedPeaks, int zeroBasedScanIndex);
    };
}
