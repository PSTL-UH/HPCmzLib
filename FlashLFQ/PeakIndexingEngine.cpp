#include "PeakIndexingEngine.h"
#include "IndexedMassSpectralPeak.h"
#include "Ms1ScanInfo.h"
#include "SpectraFileInfo.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MzLibUtil/Tolerance.h"
#include "../Chemistry/ClassExtensions.h"
#include "../MzML/Mzml.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <typeinfo>
#include <algorithm>
#include <filesystem>

using namespace IO::MzML;

namespace FlashLFQ
{

    PeakIndexingEngine::PeakIndexingEngine() 
    {
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        //auto messageTypes = std::vector<std::type_info> { typeid(std::vector<IndexedMassSpectralPeak*>[]),
        //                                                  typeid(std::vector<IndexedMassSpectralPeak*>),
        //                                                  typeid(IndexedMassSpectralPeak)};
        // _serializer = new Serializer(messageTypes))
    }

    bool PeakIndexingEngine::IndexMassSpectralPeaks(SpectraFileInfo *fileInfo, bool silent,
                                                    std::unordered_map<SpectraFileInfo*,
                                                    std::vector<Ms1ScanInfo*>> &_ms1Scans)
    {
        if (!silent)
        {
            std::cout << "Reading spectra file" << std::endl;
        }

        std::vector<MsDataScan*> msDataScans;

        // read spectra file
        std::string fn = fileInfo->FullFilePathWithExtension;
        auto ext = fn.substr(fn.find_last_of(".") + 1);
        std::transform (ext.begin(), ext.end(), ext.begin(), ::toupper);
        if (ext == "MZML")
        {
            try
            {
                // arguments:  const std::string &filePath, FilteringParams *filterParams, int maxThreads
                msDataScans = Mzml::LoadAllStaticData(fileInfo->FullFilePathWithExtension)->GetAllScansList();
                std::sort(msDataScans.begin(), msDataScans.end(), [&] (MsDataScan *l, MsDataScan *r)  {
                        return l->getOneBasedScanNumber() < r->getOneBasedScanNumber();
                    });
            }
            catch (const std::runtime_error &e)
            {
                if (!silent)
                {
                    std::cout << "Problem opening .mzML file " << fileInfo->FullFilePathWithExtension << "; "
                              << e.what() << std::endl;
                }

                return false;
            }
            
                
            for (int i = 0; i < (int)msDataScans.size(); i++)
            {
                if (msDataScans[i]->getMsnOrder() > 1)
                {
                    msDataScans[i] = nullptr;
                }
            }
        }
        else if (ext == "RAW")
        {
            if (!silent)
            {
                std::cout << "Cannot open RAW with .NETStandard code " <<
                    fileInfo->FullFilePathWithExtension << std::endl;
            }
            return false;
        }
        else
        {
            if (!silent)
            {
                std::cout << "Unsupported file type " << ext << std::endl;
                return false;
            }
        }

        if (!silent)
        {
            std::cout << "Indexing MS1 peaks" << std::endl;
        }

#ifdef ORIG
        //if (!msDataScans.Any([&] (std::any p)
        //{
        //    return p != nullptr;
        //}))
        //{
        //    _indexedPeaks = std::vector<std::vector<IndexedMassSpectralPeak*>>(0);
        //    return false;
        //}
#endif
        bool found = false;
        for ( auto p: msDataScans ) {
            if ( p != nullptr ) {
                found = true;
                break;
            }
        }
        if ( !found ) {
            _indexedPeaks = std::vector<std::vector<IndexedMassSpectralPeak*>>(0);
            return false;
        }

#ifdef ORIG
        _indexedPeaks = std::vector<std::vector<IndexedMassSpectralPeak*>>(static_cast<int>(std::ceil(msDataScans.Where([&] (std::any p)
        {
            return p != nullptr && p::MassSpectrum::LastX != nullptr;
        }).Max([&] (std::any p)
        {
            p::MassSpectrum::LastX->Value;
        }) * BinsPerDalton)) + 1);
#endif
        double max_val =0.0;
        for ( auto p : msDataScans ) {
            if ( p != nullptr &&  p->getMassSpectrum()->getLastX().has_value() ) {
                if ( max_val < p->getMassSpectrum()->getLastX().value() ) {
                    max_val = p->getMassSpectrum()->getLastX().value();
                }
            }
        }
        
        
        _indexedPeaks = std::vector<std::vector<IndexedMassSpectralPeak*>>(static_cast<int>(std::ceil(max_val *BinsPerDalton)+1));
        int scanIndex = 0;
        std::vector<Ms1ScanInfo*> scanInfo;

        for (int i = 0; i < (int)msDataScans.size(); i++)
        {
            if (msDataScans[i] == nullptr)
            {
                continue;
            }

            auto  tempVar = new Ms1ScanInfo(msDataScans[i]->getOneBasedScanNumber(), scanIndex,
                                            msDataScans[i]->getRetentionTime());
            scanInfo.push_back(tempVar);

            for (int j = 0; j < (int)msDataScans[i]->getMassSpectrum()->getXArray().size(); j++)
            {
                int roundedMz = static_cast<int>(std::round(msDataScans[i]->getMassSpectrum()->getXArray()[j] *
                                                            BinsPerDalton * std::pow(10, 0))) / std::pow(10, 0);
                if (_indexedPeaks[roundedMz].empty())
                {
                    _indexedPeaks[roundedMz] = std::vector<IndexedMassSpectralPeak*>();
                }

                auto  tempVar2 = new IndexedMassSpectralPeak(msDataScans[i]->getMassSpectrum()->getXArray()[j],
                                                             msDataScans[i]->getMassSpectrum()->getYArray()[j],
                                                             scanIndex, msDataScans[i]->getRetentionTime());
                _indexedPeaks[roundedMz].push_back(tempVar2);
            }

            scanIndex++;
        }
        
        _ms1Scans.emplace(fileInfo, scanInfo);

        if ( _indexedPeaks.empty() )
        {
            if (!silent)
            {
                std::cout << "FlashLFQ Error: The file " << fileInfo->FilenameWithoutExtension
                          << " contained no MS1 peaks!" << std::endl;
            }

            return false;
        }

        return true;
    }

    void PeakIndexingEngine::ClearIndex()
    {
        if (!_indexedPeaks.empty())
        {
            for (int i = 0; i < (int)_indexedPeaks.size(); i++)
            {
                if (_indexedPeaks[i].empty())
                {
                    continue;
                }

                _indexedPeaks[i].clear();
                //_indexedPeaks[i].TrimExcess();
                //_indexedPeaks[i] = std::vector<IndexedMassSpectralPeak*>();
            }
        }
    }

    void PeakIndexingEngine::SerializeIndex(SpectraFileInfo *file)
    {
        std::string indexPath = file->FilenameWithoutExtension + ".ind";
        //file is created when calling ofstream with indexPath.

        //Serialize data to file
        IndexedMassSpectralPeak::Serialize(indexPath, _indexedPeaks );
    }

    void PeakIndexingEngine::DeserializeIndex(SpectraFileInfo *file)
    {
        std::string indexPath = file->FilenameWithoutExtension + ".ind";
        IndexedMassSpectralPeak::Deserialize(indexPath, _indexedPeaks);

        //Remove file at indexPath
        remove(indexPath.c_str());
    }

    IndexedMassSpectralPeak *PeakIndexingEngine::GetIndexedPeak(double theorMass, int zeroBasedScanIndex,
                                                                Tolerance *tolerance, int chargeState)
    {
        IndexedMassSpectralPeak *bestPeak = nullptr;
        int ceilingMz = static_cast<int>(std::ceil(Chemistry::ClassExtensions::ToMz(tolerance->GetMaximumValue(theorMass),
                                                                                    chargeState) * BinsPerDalton));
        int floorMz = static_cast<int>(std::floor(Chemistry::ClassExtensions::ToMz(tolerance->GetMinimumValue(theorMass),
                                                                                   chargeState) * BinsPerDalton));

        for (int j = floorMz; j <= ceilingMz; j++)
        {
            if (j < (int)_indexedPeaks.size() && !_indexedPeaks[j].empty())
            {
                std::vector<IndexedMassSpectralPeak*> bin = _indexedPeaks[j];
                int index = BinarySearchForIndexedPeak(bin, zeroBasedScanIndex);

                for (int i = index; i < (int)bin.size(); i++)
                {
                    IndexedMassSpectralPeak *peak = bin[i];

                    if (peak->ZeroBasedMs1ScanIndex > zeroBasedScanIndex)
                    {
                        break;
                    }

                    double expMass = Chemistry::ClassExtensions::ToMass(peak->Mz, chargeState);

                    if (tolerance->Within(expMass, theorMass) && peak->ZeroBasedMs1ScanIndex == zeroBasedScanIndex &&
                        (bestPeak == nullptr ||
                         std::abs(expMass - theorMass) < std::abs(Chemistry::ClassExtensions::ToMass(bestPeak->Mz,
                                                                                                     chargeState) - theorMass)))
                    {
                        bestPeak = peak;
                    }
                }
            }
        }

        return bestPeak;
    }

    int PeakIndexingEngine::BinarySearchForIndexedPeak(std::vector<IndexedMassSpectralPeak*> &indexedPeaks,
                                                       int zeroBasedScanIndex)
    {
        int m = 0;
        int l = 0;
        int r = indexedPeaks.size() - 1;

        while (l <= r)
        {
            m = l + ((r - l) / 2);

            if (r - l < 2)
            {
                break;
            }
            if (indexedPeaks[m]->ZeroBasedMs1ScanIndex < zeroBasedScanIndex)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        for (int i = m; i >= 0; i--)
        {
            if (indexedPeaks[i]->ZeroBasedMs1ScanIndex < zeroBasedScanIndex)
            {
                break;
            }

            m--;
        }

        if (m < 0)
        {
            m = 0;
        }

        return m;
    }
}
