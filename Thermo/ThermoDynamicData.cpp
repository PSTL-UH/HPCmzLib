#include "ThermoDynamicData.h"
#include "../MassSpectrometry/IFilteringParams.h"
#include "../MassSpectrometry/SourceFile.h"
#include "ThermoGlobalParams.h"
#include "ThermoStaticData.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MassSpectrometry/MsDataScan.h"

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;
namespace IO
{
    namespace Thermo
    {

        ThermoDynamicData::ThermoDynamicData(IXRawfile5 *_rawConnection, IFilteringParams *filterParams, int numSpectra, MassSpectrometry::SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams) : ThermoDataFile(numSpectra, sourceFile), _rawConnection(_rawConnection), filterParams(filterParams)
        {
            setThermoGlobalParams(thermoGlobalParams);
        }

        ThermoDynamicData *ThermoDynamicData::InitiateDynamicConnection(const std::string &filePath, IFilteringParams *filterParams)
        {
            if (!FileSystem::fileExists(filePath))
            {
                throw FileNotFoundException();
            }

            if (!ThermoStaticData::CheckForMsFileReader())
            {
                throw MzLibException("MsFileReader Not Installed");
            }

            MSFileReader_XRawfile tempVar();
            IXRawfile5 *_rawConnection = static_cast<IXRawfile5*>(&tempVar);
            _rawConnection->Open(filePath);
            _rawConnection->SetCurrentController(0, 1);

            int lastspectrumNumber = -1;
            _rawConnection->GetLastSpectrumNumber(lastspectrumNumber);
            int firstspectrumNumber = -1;
            _rawConnection->GetFirstSpectrumNumber(firstspectrumNumber);

            auto precursorInfoArray = std::vector<ManagedThermoHelperLayer::PrecursorInfo*>(lastspectrumNumber - firstspectrumNumber + 1);

            std::string sendCheckSum;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream stream = File.OpenRead(filePath))
            {
                FileStream stream = File::OpenRead(filePath);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (SHA1Managed sha = new SHA1Managed())
                {
                    SHA1Managed sha = SHA1Managed();
                    std::vector<unsigned char> checksum = sha.ComputeHash(stream);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    sendCheckSum = BitConverter::ToString(checksum)->Replace("-", "");
                }
            }
            MassSpectrometry::SourceFile *sourceFile = new SourceFile(R"(Thermo nativeID format)", R"(Thermo RAW format)", sendCheckSum, R"(SHA-1)", filePath, Path::GetFileNameWithoutExtension(filePath));

            auto thermoGlobalParams = ThermoStaticData::GetAllGlobalStuff(_rawConnection, precursorInfoArray, filePath);

            // if the spectra file only contains 1 scan and its MS order is 0, this indicates an errored read result
            if (thermoGlobalParams->MsOrderByScan.size() == 1 && thermoGlobalParams->MsOrderByScan[0] == 0)
            {
                delete sourceFile;
                throw MzLibException("Could not read data from file " + FileSystem::getFileName(filePath));
            }

            delete sourceFile;
            return new ThermoDynamicData(_rawConnection, filterParams, lastspectrumNumber - firstspectrumNumber + 1, sourceFile, thermoGlobalParams);
        }

        MsDataScan *ThermoDynamicData::GetOneBasedScan(int oneBasedScanNumber)
        {
            if (Scans[oneBasedScanNumber - 1] == nullptr)
            {
                Scans[oneBasedScanNumber - 1] = ThermoStaticData::GetMsDataOneBasedScanFromThermoFile(_rawConnection, oneBasedScanNumber, getThermoGlobalParams(), filterParams);
            }
            return Scans[oneBasedScanNumber - 1];
        }

        void ThermoDynamicData::ClearCachedScans()
        {
            Array::Clear(Scans, 0, Scans.size());
        }

        int ThermoDynamicData::GetClosestOneBasedSpectrumNumber(double retentionTime)
        {
            int spectrumNumber = 0;
            _rawConnection->ScanNumFromRT(retentionTime, spectrumNumber);
            return spectrumNumber;
        }

        ThermoDynamicData::~ThermoDynamicData()
        {
                delete _rawConnection;
                delete filterParams;
            this->Dispose(true);
//C# TO C++ CONVERTER WARNING: There is no garbage collector in C++:
//            GC::SuppressFinalize(this);
        }

        void ThermoDynamicData::Dispose(bool disposing)
        {
            if (disposing)
            {
                if (_rawConnection != nullptr)
                {
                    _rawConnection->Close();
                }
            }
        }
    }
}
