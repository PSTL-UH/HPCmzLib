#include "PeakIndexingEngine.h"
#include "IndexedMassSpectralPeak.h"
#include "Ms1ScanInfo.h"
#include "SpectraFileInfo.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MzLibUtil/Tolerance.h"
#include "../Chemistry/ClassExtensions.h"
#include "../MzML/Mzml.h"

//For XML serialization / deserialization
#include "../include/cereal/types/memory.hpp"
#include "../include/cereal/archives/xml.hpp"
#include <../include/cereal/types/vector.hpp>

#include <iostream>
#include <typeinfo>
#include <algorithm>

using namespace IO::MzML;
//using namespace NetSerializer;

namespace FlashLFQ
{

    PeakIndexingEngine::PeakIndexingEngine() : 
    {
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto messageTypes = std::vector<std::type_info> { typeid(std::vector<IndexedMassSpectralPeak*>[]),
                                                          typeid(std::vector<IndexedMassSpectralPeak*>),
                                                          typeid(IndexedMassSpectralPeak)};
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
        //C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
        //auto ext = Path::GetExtension(fileInfo->FullFilePathWithExtension).ToUpperInvariant();
        std::string fn = fileInfo->FullFilePathWithExtension;
        auto ext = fn.substr(fn.find_last_of(".") + 1);
        std::transform (ext.begin(), ext.end(), ext.begin(), ::toupper);
        if (ext == ".MZML")
        {
            try
            {
#ifdef ORIG
                msDataScans = Mzml::LoadAllStaticData(fileInfo->FullFilePathWithExtension)->GetAllScansList().OrderBy([&] (std::any p)
                {
                    p::OneBasedScanNumber;
                })->ToArray();
#endif
                // arguments:  const std::string &filePath, FilteringParams *filterParams, int maxThreads
                msDataScans = Mzml::LoadAllStaticData(fileInfo->FullFilePathWithExtension)->GetAllScansList();
                std::sort(msDataScans.begin(), msDataScans.end(), [&] (MsDataScan *l, MsDataScan *r)  {
                        return l->getOneBasedScanNumber() > r->getOneBasedScanNumber();
                    });
            }
#ifdef ORIG
            catch (const FileNotFoundException &e1)
            {
                if (!silent)
                {
                    std::cout << "\nCan't find .mzML file" << fileInfo->FullFilePathWithExtension << "\n" << std::endl;
                }

                return false;
            }
#endif
            catch (const std::runtime_error &e)
            {
                if (!silent)
                {
                    std::cout << "Problem opening .mzML file " << fileInfo->FullFilePathWithExtension << "; " << e.what() << std::endl;
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
        else if (ext == ".RAW")
        {
            if (!silent)
            {
                std::cout << "Cannot open RAW with .NETStandard code - are you on Linux? " << fileInfo->FullFilePathWithExtension << std::endl;
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

        int scanIndex = 0;
        std::vector<Ms1ScanInfo*> scanInfo;

        for (int i = 0; i < (int)msDataScans.size(); i++)
        {
            if (msDataScans[i] == nullptr)
            {
                continue;
            }

            Ms1ScanInfo tempVar(msDataScans[i]->getOneBasedScanNumber(), scanIndex, msDataScans[i]->getRetentionTime());
            scanInfo.push_back(&tempVar);

            for (int j = 0; j < (int)msDataScans[i]->getMassSpectrum()->getXArray().size(); j++)
            {
                int roundedMz = static_cast<int>(std::round(msDataScans[i]->getMassSpectrum()->getXArray()[j] *
                                                            BinsPerDalton * std::pow(10, 0))) / std::pow(10, 0);
                if (_indexedPeaks[roundedMz].empty())
                {
                    _indexedPeaks[roundedMz] = std::vector<IndexedMassSpectralPeak*>();
                }

                IndexedMassSpectralPeak tempVar2(msDataScans[i]->getMassSpectrum()->getXArray()[j], msDataScans[i]->getMassSpectrum()->getYArray()[j],
                                                 scanIndex, msDataScans[i]->getRetentionTime());
                _indexedPeaks[roundedMz].push_back(&tempVar2);
            }

            scanIndex++;
        }

        _ms1Scans.emplace(fileInfo, scanInfo);

        if (_indexedPeaks.empty() || _indexedPeaks.empty())
        {
            if (!silent)
            {
                std::cout << "FlashLFQ Error: The file " << fileInfo->FilenameWithoutExtension << " contained no MS1 peaks!" << std::endl;
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

        GC::Collect();
    }

    void PeakIndexingEngine::SerializeIndex(SpectraFileInfo *file)
    {
#ifdef ORIG
        std::string dir = FileSystem::getDirectoryName(file->FullFilePathWithExtension);
        std::string indexPath = FileSystem::combine(dir, file->FilenameWithoutExtension + ".ind");

        auto indexFile = File::Create(indexPath);
        _serializer->Serialize(indexFile, _indexedPeaks);
#endif

        //get directory name from SpectraFileInfo FullFilePathWithExtension.  Need to cast string to std::experimental::filesystem::path
        //in order to get path without filename.
        std::experimental::filesystem::path directory = std::experimental::filesystem::path(file->FullFilePathWithExtension);

        // combine directory string with new file name.  need to add "/" to separate directory from filename and add ".ind" extension
        std::string indexPath = directory.string() + "/" + file->FilenameWithoutExtension + ".ind";

        //file is created when calling ofstream with indexPath.

        //----------------------------------------------------------------
        //SERIALIZE DATA TO FILE

        //open ofstream of file
        std::ofstream os(indexPath);
        cereal::XMLOutputArchive archive( os );

        //Cereal only works with smart pointers, so all raw pointers in std::vector<std::vector<IndexedMassSpectralPeak*>> _indexedPeaks
        //must be converted to unique pointers with std::make_unique.  This requires traversing the vector and performing the
        //transformation for each entry.
        std::vector<std::vector<std::unique_ptr<FlashLFQ::IndexedMassSpectralPeak>>> unique_vector;

        for (int i=0; i < _indexedpeaks.size(); i++){
        std::vector<std::unique_ptr<FlashLFQ::IndexedMassSpectralPeak>> unique_vec_row;

        for (int j=0;j<_indexedpeaks[i].size();j++){

            //create unique pointer from raw pointer
            auto p = std::make_unique<FlashLFQ::IndexedMassSpectralPeak>(*_indexedpeaks[i][j]);

            //push unique pointer into vector of unique pointers
            unique_vec_row.push_back(std::move(p));
        }

        //push vector of unique pointers into vector of vectors of unique pointers
        unique_vector.push_back(std::move(unique_vec_row));
        }

        //finally serialize the vector of vectors of unique pointers to an XML file
        //this will write the info contained in _indexedpeaks to the XML file 
        //specified in the indexPath variable.
        archive(unique_vector);
        //----------------------------------------------------------------

        //calling os.close() prevents cereal from writing data to file?
        // os.close();
    }

    void PeakIndexingEngine::DeserializeIndex(SpectraFileInfo *file)
    {
#ifdef ORIG
        std::string dir = FileSystem::getDirectoryName(file->FullFilePathWithExtension);
        std::string indexPath = FileSystem::combine(dir, file->FilenameWithoutExtension + ".ind");

        auto indexFile = File::OpenRead(indexPath);
        _indexedPeaks = static_cast<std::vector<std::vector<IndexedMassSpectralPeak*>>>(_serializer->Deserialize(indexFile));
    
        File::Delete(indexPath);
#endif

        //get directory name from SpectraFileInfo FullFilePathWithExtension.  Need to cast string to std::experimental::filesystem::path
        //in order to get path without filename.
        std::experimental::filesystem::path directory = std::experimental::filesystem::path(file->FullFilePathWithExtension);

        // combine directory string with new file name.  need to add "/" to separate directory from filename and add ".ind" extension
        std::string indexPath = directory.string() + "/" + file->FilenameWithoutExtension + ".ind";

        //file is opened for reading when calling ifstream with indexPath.
        // auto indexFile = File::OpenRead(indexPath);

        //------------------------------------------------------
        //DESERIALIZE FILE INDEXFILE TO OBJECT

        //open ifstream for indexPath
        std::ifstream is(indexPath);
        cereal::XMLInputArchive archive_read(is);

        //Cereal only has functionality for smart pointers.  Must deserialize data from file to vector
        //of vecotrs of unique pointers
        std::vector<std::vector<std::unique_ptr<FlashLFQ::IndexedMassSpectralPeak>>> unique_vec;

        //deserialize xml file to unique_vec structure
        archive_read(unique_vec);

        //now must convert unique pointers to raw pointers.  This requires traversing the structure
        std::vector<std::vector<FlashLFQ::IndexedMassSpectralPeak*>> raw_vec;

        for (int i=0; i < unique_vec.size(); i++){
        std::vector<FlashLFQ::IndexedMassSpectralPeak*> raw_vec_row;

        for (int j=0;j<unique_vec[i].size();j++){
            //this sets everything but ZeroBasedMs1ScanIndex.  Im not sure why.
            // auto p = unique_vec[i][j].get();

            //because ZeroBasedMs1ScanIndex was not set with the line above, we create a new FlashLFQ::IndexedMassSpectralPeak object with
            //the information stored in the unique_vec entry.  This DOES set all values including ZeroBasedMs1ScanIndex.
            FlashLFQ::IndexedMassSpectralPeak* p = new FlashLFQ::IndexedMassSpectralPeak(unique_vec[i][j]->Mz, unique_vec[i][j]->Intensity, unique_vec[i][j]->ZeroBasedMs1ScanIndex, unique_vec[i][j]->RetentionTime);
            raw_vec_row.push_back(p);
        }

        raw_vec.push_back(raw_vec_row);
        }

        //set _indexedpeaks to equal the vector of vectors of raw pointers.
        _indexedpeaks = raw_vec;
        // return raw_vec;
        //------------------------------------------------------
        is.close()
        //Remove file at indexPath
        // File::Delete(indexPath);
        remove(indexPath.c_str());
    }

    IndexedMassSpectralPeak *PeakIndexingEngine::GetIndexedPeak(double theorMass, int zeroBasedScanIndex, Tolerance *tolerance, int chargeState)
    {
        IndexedMassSpectralPeak *bestPeak = nullptr;
        int ceilingMz = static_cast<int>(std::ceil(Chemistry::ClassExtensions::ToMz(tolerance->GetMaximumValue(theorMass), chargeState) * BinsPerDalton));
        int floorMz = static_cast<int>(std::floor(Chemistry::ClassExtensions::ToMz(tolerance->GetMinimumValue(theorMass), chargeState) * BinsPerDalton));

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

                    if (tolerance->Within(expMass, theorMass) && peak->ZeroBasedMs1ScanIndex == zeroBasedScanIndex && (bestPeak == nullptr || std::abs(expMass - theorMass) < std::abs(Chemistry::ClassExtensions::ToMass(bestPeak->Mz, chargeState) - theorMass)))
                    {
                        bestPeak = peak;
                    }
                }
            }
        }

        return bestPeak;
    }

    int PeakIndexingEngine::BinarySearchForIndexedPeak(std::vector<IndexedMassSpectralPeak*> &indexedPeaks, int zeroBasedScanIndex)
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
