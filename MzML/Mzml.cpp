#include "Mzml.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "../MassSpectrometry/FilteringParams.h"
#include "MzmlMethods.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MassSpectrometry/IFilteringParams.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"

#include <iostream>
#include <fstream>
#include "../include/stringhelper.h"
#include "../include/Sort.h"
#include "../include/BitConverter.h"
#include "../include/hasEnding.h"

#include <cmath>

#include "zlib.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace xercesc_3_1;

#include <stdio.h>

void print_chars (char * c_ptr, int len )
{
    while ( len > 0 )
    {
        printf ( " %2.2x", (0xff&(int)*c_ptr++));
        len--;
    }
    printf ( "\n" );
}

namespace IO
{
    namespace MzML
    {

const std::string Mzml::_zlibCompression = "MS:1000574";
const std::string Mzml::_64bit = "MS:1000523";
const std::string Mzml::_32bit = "MS:1000521";
const std::string Mzml::_filterString = "MS:1000512";
const std::string Mzml::_centroidSpectrum = "MS:1000127";
const std::string Mzml::_profileSpectrum = "MS:1000128";
const std::string Mzml::_peakIntensity = "MS:1000042";
const std::string Mzml::_totalIonCurrent = "MS:1000285";
const std::string Mzml::_scanWindowLowerLimit = "MS:1000501";
const std::string Mzml::_scanWindowUpperLimit = "MS:1000500";
const std::string Mzml::_msnOrderAccession = "MS:1000511";
const std::string Mzml::_precursorCharge = "MS:1000041";
const std::string Mzml::_selectedIonMz = "MS:1000744";
const std::string Mzml::_isolationWindowTargetMZ = "MS:1000827";
const std::string Mzml::_isolationWindowLowerOffset = "MS:1000828";
const std::string Mzml::_isolationWindowUpperOffset = "MS:1000829";
const std::string Mzml::_oneBasedScanNumber = "MS:1000797";
const std::string Mzml::_retentionTime = "MS:1000016";
const std::string Mzml::_ionInjectionTime = "MS:1000927";
const std::string Mzml::_mzArray = "MS:1000514";
const std::string Mzml::_intensityArray = "MS:1000515";
// Regex *const Mzml::MZAnalyzerTypeRegex = new Regex(R"(^[a-zA-Z]*)", RegexOptions::Compiled);
std::unordered_map<std::string, Polarity> Mzml::polarityDictionary =
{
    {"MS:1000129",Polarity::Negative},
    {"MS:1000130",Polarity::Positive}
};
std::unordered_map<std::string, MZAnalyzerType> Mzml::analyzerDictionary =
{
    {"MS:1000443", MZAnalyzerType::Unknown},
    {"MS:1000081",MZAnalyzerType::Quadrupole},
    {"MS:1000291",MZAnalyzerType::IonTrap2D},
    {"MS:1000082",MZAnalyzerType::IonTrap3D},
    {"MS:1000484",MZAnalyzerType::Orbitrap},
    {"MS:1000084",MZAnalyzerType::TOF},
    {"MS:1000079",MZAnalyzerType::FTICR},
    {"MS:1000080",MZAnalyzerType::Sector}
};
std::unordered_map<std::string, DissociationType> Mzml::dissociationDictionary =
{
    {"MS:1000133",DissociationType::CID},
    {"MS:1001880",DissociationType::ISCID},
    {"MS:1000422",DissociationType::HCD},
    {"MS:1000598",DissociationType::ETD},
    {"MS:1000435",DissociationType::IRMPD},
    {"MS:1000599",DissociationType::PQD},
    {"MS:1000044",DissociationType::Unknown}
};

        Mzml::Mzml(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(scans, sourceFile)
        {
        }

        Mzml *Mzml::LoadAllStaticData(const std::string &filePath, FilteringParams *filterParams, int maxThreads)
        {
            if (!std::experimental::filesystem::exists(filePath))
            {
                std::cout << "ERROR:  File "  << filePath <<  " not found" << std::endl;
            }

            ms::mzml::mzMLType *_mzMLConnection;
            std::unique_ptr<ms::mzml::mzMLType> _mzML_object;
            std::unique_ptr<ms::mzml::indexedmzML> _indexedmzMLConnection_object;

            try{
                std::ifstream fs = std::ifstream(filePath);
                _indexedmzMLConnection_object = ms::mzml::indexedmzML_ (fs, xml_schema::flags::dont_validate);
                fs.close();
                _mzMLConnection = &_indexedmzMLConnection_object.get()->mzML();
            }
            catch (const xml_schema::exception& e){
                std::ifstream fs = std::ifstream(filePath);
                _mzML_object = ms::mzml::mzML (fs, xml_schema::flags::dont_validate);
                fs.close();
                _mzMLConnection = _mzML_object.get();
            }

            MassSpectrometry::SourceFile *sourceFile;

            if (_mzMLConnection->fileDescription().sourceFileList() != nullptr && 
                !_mzMLConnection->fileDescription().sourceFileList().get().sourceFile().empty() &&
                !_mzMLConnection->fileDescription().sourceFileList()->sourceFile()[0].cvParam().empty())
             {
                auto simpler = _mzMLConnection->fileDescription().sourceFileList()->sourceFile()[0];
                std::string nativeIdFormat = "";
                std::string fileFormat = "";
                std::string checkSum = "";
                std::string checkSumType = "";
                for (auto cv : simpler.cvParam())
                {
                    if (cv.accession() == R"(MS:1000563)")
                    {
                        fileFormat = "Thermo RAW format";
                    }
                    if (cv.accession() == R"(MS:1000584)")
                    {
                        fileFormat = "mzML format";
                    }
                    if (cv.accession() == R"(MS:1000768)")
                    {
                        nativeIdFormat = "Thermo nativeID format";
                    }
                    if (cv.accession() == R"(MS:1000776)")
                    {
                        nativeIdFormat = "scan number only nativeID format";
                    }
                    if (cv.accession() == R"(MS:1000824)")
                    {
                        nativeIdFormat = "no nativeID format";
                    }
                    if (cv.accession() == R"(MS:1000568)")
                    {
                        checkSum = cv.value().get();
                        checkSumType = "MD5";
                    }
                    if (cv.accession() == R"(MS:1000569)")
                    {
                        checkSum = cv.value().get();
                        checkSumType = "SHA-1";
                    }
                }

                Uri tempVar(simpler.location());
                sourceFile = new SourceFile(nativeIdFormat, fileFormat, checkSum, checkSumType, &tempVar, simpler.id(), simpler.name());
            }
            else
            {
                std::string sendCheckSum;
                {
                    std::ifstream stream = std::ifstream(filePath);
                    {
                        //Original computed hashstring from file stream
                        sendCheckSum = "1111100000";                   
                    }
                }

                std::experimental::filesystem::path fp = filePath;
                sourceFile = new SourceFile(R"(no nativeID format)", R"(mzML format)", sendCheckSum, R"(No checksum type)", std::experimental::filesystem::absolute(fp), fp.stem());
            }

            auto numSpecta = _mzMLConnection->run().spectrumList().get().spectrum().size();
            std::vector<MsDataScan*> scans(numSpecta);

            for ( long unsigned int i = 0; i < numSpecta; i++)  {
                scans[i] = GetMsDataOneBasedScanFromConnection(_mzMLConnection, i + 1, filterParams);
            }

            //Mzml sometimes have scan numbers specified, but usually not.
            //In the event that they do, the iterator above unintentionally assigned them to an incorrect index.
            //Check to make sure that the scans are in order and that there are no duplicate scans
            std::unordered_set<int> checkForDuplicateScans;
            bool ordered = true;
            int previousScanNumber = -1;
            for (auto scan : scans)
            {
                //check if no duplicates
                std::unordered_set<int>::const_iterator dup_iterator = checkForDuplicateScans.find(scan->getOneBasedScanNumber());

                //for all scans, if scan not in checkForDuplicateScans set, it is inserted
                if (dup_iterator == checkForDuplicateScans.end()) {
                    checkForDuplicateScans.insert(scan->getOneBasedScanNumber());
                }
                //if scan is in checkForDuplicateScans set, throw exception
                else{
                    throw MzLibException("Scan number " + std::to_string(scan->getOneBasedScanNumber()) + " appeared multiple times in " + filePath);
                    // std::cout << "TODO fix exception Mzml.cpp line 274:  Scan number " << std::to_string(scan->getOneBasedScanNumber()) << " appeared multiple times in " << filePath << std::endl;   
                }

                //check if scans are in order
                if (previousScanNumber > scan->getOneBasedScanNumber())
                {
                    ordered = false;
                }
                previousScanNumber = scan->getOneBasedScanNumber();
            }

            if (!ordered) //reassign indexes if not ordered
            {
                std::vector<MsDataScan*> indexedScans(checkForDuplicateScans.size());
                for (auto scan : scans)
                {
                    indexedScans[scan->getOneBasedScanNumber() - 1] = scan;
                }
                scans = indexedScans;
            }

            //make reference pervious ms1 scan
            // we weren't able to get the precursor scan number, so we'll have to guess;
            // loop back to find precursor scan
            // (assumed to be the first scan before this scan with an MS order of this scan's MS order - 1)
            // e.g., if this is an MS2 scan, find the first MS1 scan before this and assume that's the precursor scan
            for (long unsigned int i = 0; i < scans.size(); i++)
            {
                if (scans[i]->getMsnOrder() > 1 && !scans[i]->getOneBasedPrecursorScanNumber())
                {
                    for (int j = i; j >= 0; j--)
                    {
                        if (scans[i]->getMsnOrder() - scans[j]->getMsnOrder() == 1)
                        {
                            scans[i]->setOneBasedPrecursorScanNumber(scans[j]->getOneBasedScanNumber());
                            break;
                        }
                    }
                }
            }
            return new Mzml(scans, sourceFile);
        }

        MsDataScan *Mzml::GetMsDataOneBasedScanFromConnection(ms::mzml::mzMLType *_mzMLConnection, int oneBasedIndex, IFilteringParams *filterParams)
        {
            // Read in the instrument configuration types from connection (in mzml it's at the start)
            std::vector<ms::mzml::InstrumentConfigurationType> configs;
            for (long unsigned int i = 0; i < _mzMLConnection->instrumentConfigurationList().instrumentConfiguration().size(); i++)
            {
                configs.push_back(_mzMLConnection->instrumentConfigurationList().instrumentConfiguration()[i]);
            }

            auto defaultInstrumentConfig = _mzMLConnection->run().defaultInstrumentConfigurationRef();
            // May be null!
            auto scanSpecificInsturmentConfig = _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].instrumentConfigurationRef();

            MZAnalyzerType analyzer = static_cast<MassSpectrometry::MZAnalyzerType>(0);
            // use default
            if (scanSpecificInsturmentConfig == nullptr || *scanSpecificInsturmentConfig == *defaultInstrumentConfig)
            {
                if (configs[0].componentList() == nullptr)
                {
                    analyzer = static_cast<MassSpectrometry::MZAnalyzerType>(0);
                }
                else
                {
                    MZAnalyzerType returnVal;
                    std::unordered_map<std::string, MZAnalyzerType>::const_iterator analyzerDictionary_iterator = analyzerDictionary.find(configs[0].componentList()->analyzer()[0].cvParam()[0].accession());
                    if (analyzerDictionary_iterator != analyzerDictionary.end())
                    {
                    returnVal = analyzerDictionary_iterator->second;
                        analyzer = returnVal;
                    }
                else
                {
                    returnVal = analyzerDictionary_iterator->second;
                }
                }
            }
            // use scan-specific
            else
            {
                for (long unsigned int i = 0; i < _mzMLConnection->instrumentConfigurationList().instrumentConfiguration().size(); i++)
                {
                    if (configs[i].id() == *scanSpecificInsturmentConfig)
                    {
                        MZAnalyzerType returnVal;
                        std::unordered_map<std::string, MZAnalyzerType>::const_iterator analyzerDictionary_iterator = analyzerDictionary.find(configs[i].componentList()->analyzer()[0].cvParam()[0].accession());
                        returnVal = analyzerDictionary_iterator->second;
                        analyzer = returnVal;
                    }
                }
            }

            std::string nativeId = _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].id();

            std::optional<int> msOrder;
            std::optional<bool> isCentroid;
            Polarity polarity = Polarity::Unknown;
            double tic = NAN;

            for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].cvParam())
            {
                if (cv.accession() == _msnOrderAccession)
                {
                    msOrder = std::make_optional(std::stoi(cv.value().get()));
                }
                if (cv.accession() == _centroidSpectrum)
                {
                    isCentroid = std::make_optional(true);
                }
                if (cv.accession() == _profileSpectrum)
                {
                    throw MzLibException("Reading profile mode mzmls not supported");
                }
                if (cv.accession() == _totalIonCurrent)
                {
                    tic = std::stod(cv.value().get());
                }
                if (polarity == Polarity::Unknown)
                {
                    std::unordered_map<std::string, Polarity>::const_iterator polarityDictionary_iterator = polarityDictionary.find(cv.accession());
                    if (polarityDictionary_iterator != polarityDictionary.end())
                        polarity = polarityDictionary_iterator->second;
                    else
                        polarity = Polarity::Unknown;
                }
            }

            if (!msOrder || !isCentroid)
            {
                throw MzLibException("!msOrder.HasValue || !isCentroid.HasValue");
            }

            std::vector<double> masses(0);
            std::vector<double> intensities(0);

            for (ms::mzml::BinaryDataArrayType binaryData : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].binaryDataArrayList().get().binaryDataArray())
            {
                bool compressed = false;
                bool mzArray = false;
                bool intensityArray = false;
                bool is32bit = true;
                for (auto cv : binaryData.cvParam())
                {
                    compressed |= cv.accession() == _zlibCompression;
                    is32bit &= cv.accession() != _64bit;
                    is32bit |= cv.accession() == _32bit;
                    mzArray |= cv.accession() == _mzArray;
                    intensityArray |= cv.accession() == _intensityArray;
                }

                //get binaryData as char array
                char *binary_data = binaryData.binary().data();
                long binsize = binaryData.binary().size();

                std::vector<double> data = ConvertBase64ToDoubles(binary_data, binsize, compressed, is32bit);
                if (mzArray)
                {
                    masses = data;
                }

                if (intensityArray)
                {
                    intensities = data;
                }
            }

            double high = NAN;
            double low = NAN;

            auto aScanWindowList = _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].scanWindowList();

            if (aScanWindowList != nullptr)
            {
                for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam())
                {
                    if (cv.accession() == _scanWindowLowerLimit)
                    {
                        low = std::stod(cv.value().get());
                    }
                    else if (cv.accession() == _scanWindowUpperLimit)
                    {
                        high = std::stod(cv.value().get());
                    }
                }
            }

            if (filterParams != nullptr && intensities.size() > 0 && (filterParams->getMinimumAllowedIntensityRatioToBasePeakM() || filterParams->getNumberOfPeaksToKeepPerWindow()) && ((filterParams->getApplyTrimmingToMs1() && msOrder.value() == 1) || (filterParams->getApplyTrimmingToMsMs() && msOrder.value() > 1)))
            {

                if (!filterParams->getNumberOfWindows())
                {
                    int numPeaks = TopNpeakHelper(intensities, masses, filterParams);
                    intensities.resize(numPeaks);
                    masses.resize(numPeaks);
                }
                else
                {
                    WindowModeHelper(intensities, masses, filterParams, low, high);
                }
            }

            //Sort items in array based on keys in first array
            Sort::SortPairs(masses, intensities, masses.size());

            auto mzmlMzSpectrum = new MzSpectrum(masses, intensities, false);

            double rtInMinutes = NAN;
            std::string scanFilter = "";
            std::optional<double> injectionTime;
            int oneBasedScanNumber = oneBasedIndex;

            if (!_mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].cvParam().empty())
            {
                for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].cvParam())
                {
                    if (cv.accession() == _retentionTime)
                    {
                        rtInMinutes = std::stod(cv.value().get());
                        if (cv.unitName().get() == "second")
                        {
                            rtInMinutes /= 60;
                        }
                    }
                    if (cv.accession() == _filterString)
                    {
                        scanFilter = cv.value().get();
                    }
                    if (cv.accession() == _ionInjectionTime)
                    {
                        injectionTime = std::make_optional(std::stod(cv.value().get()));
                    }
                    if (cv.accession() == _oneBasedScanNumber) //get the real one based spectrum number (if available), the other assumes they are in order. This is present in .mgf->.mzml conversions from MSConvert
                    {
                        oneBasedScanNumber = std::stoi(cv.value().get());
                    }
                }
            }

            if (msOrder.value() == 1)
            {
                MzRange tempVar(low, high);
                return new MsDataScan(mzmlMzSpectrum, oneBasedScanNumber, msOrder.value(), isCentroid.value(), polarity, rtInMinutes, &tempVar, scanFilter, analyzer, tic, injectionTime, std::vector<std::vector<double>>(), nativeId);
            }

            double selectedIonMz = NAN;
            std::optional<int> selectedIonCharge;
            std::optional<double> selectedIonIntensity;

            for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam())
            {
                if (cv.accession() == _selectedIonMz)
                {
                    selectedIonMz = std::stod(cv.value().get());
                }
                if (cv.accession() == _precursorCharge)
                {
                    selectedIonCharge = std::make_optional(std::stoi(cv.value().get()));
                }
                if (cv.accession() == _peakIntensity)
                {
                    selectedIonIntensity = std::make_optional(std::stod(cv.value().get()));
                }
            }

            std::optional<double> isolationMz;
            double lowIsolation = NAN;
            double highIsolation = NAN;
            if (_mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].isolationWindow() != nullptr)
            {
                for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].isolationWindow()->cvParam())
                {
                    if (cv.accession() == _isolationWindowTargetMZ)
                    {
                        isolationMz = std::make_optional(std::stod(cv.value().get()));
                    }
                    if (cv.accession() == _isolationWindowLowerOffset)
                    {
                        lowIsolation = std::stod(cv.value().get());
                    }
                    if (cv.accession() == _isolationWindowUpperOffset)
                    {
                        highIsolation = std::stod(cv.value().get());
                    }
                }
            }

            DissociationType dissociationType = DissociationType::Unknown;
            if (!_mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].activation().cvParam().empty())
            {
                for (ms::mzml::CVParamType cv : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].activation().cvParam())
                {
                    std::unordered_map<std::string, DissociationType>::const_iterator dissociationDictionary_iterator = dissociationDictionary.find(cv.accession());
                    if (dissociationDictionary_iterator != dissociationDictionary.end()){
                        dissociationType = dissociationDictionary_iterator->second;
                    }
                }
            }
            std::optional<double> monoisotopicMz;
            if (!_mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].userParam().empty())
            {
                for (auto userParam : _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].scanList()->scan()[0].userParam())
                {

                    std::string fullstring = userParam.name();
                    std::string ending = "Monoisotopic M/Z:";
                    if (hasEnding(fullstring, ending))
                    {
                        monoisotopicMz = std::make_optional(std::stod(userParam.value().get()));
                    }
                }
            }

            std::optional<int> precursorScanNumber;
            if (_mzMLConnection->run().spectrumList().get().spectrum()[oneBasedIndex - 1].precursorList()->precursor()[0].spectrumRef() == nullptr)
            {
                precursorScanNumber = std::nullopt;
            }
            else
            {
                precursorScanNumber = std::make_optional(GetOneBasedPrecursorScanNumber(_mzMLConnection, oneBasedIndex));
            }

            MzRange tempVar2(low, high);
            return new MsDataScan(mzmlMzSpectrum, oneBasedIndex, msOrder.value(), isCentroid.value(), polarity, rtInMinutes, &tempVar2, scanFilter, analyzer, tic, injectionTime, std::vector<std::vector<double>>(), nativeId, std::make_optional(selectedIonMz), selectedIonCharge, selectedIonIntensity, isolationMz, std::make_optional(lowIsolation + highIsolation), std::make_optional(dissociationType), precursorScanNumber, monoisotopicMz);
        }

        std::vector<double> Mzml::ConvertBase64ToDoubles(char* bytes, long bytes_size, bool zlibCompressed, bool is32bit)
        {
            unsigned char *out_stream = NULL;
            if (zlibCompressed){
                unsigned char *unsigned_bytes = (unsigned char*)bytes;
                out_stream = (unsigned char*)malloc(bytes_size);
                if (out_stream == nullptr)
                    std::cout << "Error allocating out_stream" << std::endl;

                int CHUNK = 16384;
                long max_size = bytes_size;

                int ret;
                unsigned have;
                z_stream strm;

                unsigned char out[CHUNK];

                //set avail_in to bytes_size
                strm.avail_in = CHUNK;

                //reset bytes_size to 0
                bytes_size = 0;

                //set avail_nextin to bytes ptr
                strm.next_in = unsigned_bytes;

                /* allocate inflate state */
                strm.zalloc = Z_NULL;
                strm.zfree = Z_NULL;
                strm.opaque = Z_NULL;
                strm.avail_in = 0;
                strm.next_in = Z_NULL;
                ret = inflateInit(&strm);
                if (ret != Z_OK){
                    std::cout << "Error initializing inflate" << std::endl;
                }

                /* run inflate() on input until output buffer not full */
                do {
                    strm.avail_out = CHUNK;
                    strm.next_out = out;
                    ret = inflate(&strm, Z_NO_FLUSH);
                    assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
                    switch (ret) {
                    case Z_NEED_DICT:
                        ret = Z_DATA_ERROR;     /* and fall through */
                    case Z_DATA_ERROR:
                    case Z_MEM_ERROR:
                        (void)inflateEnd(&strm);
                        std::cout << "Z memory error" << std::endl;
                    }

                    have = CHUNK - strm.avail_out;

                    if ((bytes_size + have) > max_size){
                        out_stream = (unsigned char*)realloc(out_stream, max_size + have);
                        max_size += have;
                        if (out_stream == nullptr)
                            std::cout << "Error reallocating out_stream" << std::endl;
                    }

                    memcpy(out_stream + bytes_size, out, have);

                    bytes_size += have;
                } while (strm.avail_out == 0);
                (void)inflateEnd(&strm);
                //cast unsigned char *out_stream to char*, and set
                //bytes pointer to beginning of out_stream
                bytes = (char *)out_stream;
            }

            int size = is32bit ? sizeof(float) : sizeof(double);

            int length = bytes_size / size;
            std::vector<double> convertedArray(length);

            for (int i = 0; i < length; i++)
            {
                if (is32bit)
                {
                    BitConverter bc;
                    convertedArray[i] = bc.toSingle(bytes, i*size);
                }
                else
                {
                    BitConverter bc;
                    convertedArray[i] = bc.toDouble(bytes, i*size);
                }
            }
            free(out_stream);
            return convertedArray;
        }

        int Mzml::GetOneBasedPrecursorScanNumber(ms::mzml::mzMLType *_mzMLConnection, int oneBasedSpectrumNumber)
        {
            std::string precursorID = _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedSpectrumNumber - 1].precursorList()->precursor()[0].spectrumRef().get();
            do
            {
                oneBasedSpectrumNumber--;
            } while (precursorID != _mzMLConnection->run().spectrumList().get().spectrum()[oneBasedSpectrumNumber - 1].id());
            return oneBasedSpectrumNumber;
        }
    }
}
