#include "ThermoDynamicData.h"
#include "IThermoScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "ThermoGlobalParams.h"

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
namespace IO {
    namespace Thermo {

        ThermoDynamicData::ThermoDynamicData(IXRawfile5 *_rawConnection, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks, int numSpectra, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams) : ThermoFile(_rawConnection, numSpectra, couldBePrecursor, sourceFile, thermoGlobalParams), _rawConnection(_rawConnection), trimMsMsPeaks(trimMsMsPeaks), trimMs1Peaks(trimMs1Peaks), minRatio(minRatio), topNpeaks(topNpeaks) {
        }

        ThermoDynamicData *ThermoDynamicData::InitiateDynamicConnection(const std::wstring &filePath, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks) {
            MSFileReader_XRawfile tempVar();
            IXRawfile5 *_rawConnection = static_cast<IXRawfile5*>(&tempVar);
            _rawConnection->Open(filePath);
            _rawConnection->SetCurrentController(0, 1);

            int lastspectrumNumber = -1;
            _rawConnection->GetLastSpectrumNumber(lastspectrumNumber);
            int firstspectrumNumber = -1;
            _rawConnection->GetFirstSpectrumNumber(firstspectrumNumber);

            auto precursorInfoArray = std::vector<ManagedThermoHelperLayer::PrecursorInfo*>(lastspectrumNumber - firstspectrumNumber + 1);

            std::wstring sendCheckSum;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream stream = File.OpenRead(filePath))
            {
                FileStream stream = File::OpenRead(filePath);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (SHA1Managed sha = new SHA1Managed())
                {
                    SHA1Managed sha = SHA1Managed();
                    std::vector<unsigned char> checksum = sha.ComputeHash(stream);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    sendCheckSum = BitConverter::ToString(checksum)->Replace(L"-", L"");
                }
            }
            SourceFile *sourceFile = new SourceFile(LR"(Thermo nativeID format)", LR"(Thermo RAW format)", sendCheckSum, LR"(SHA-1)", filePath, Path::GetFileNameWithoutExtension(filePath));

            auto thermoGlobalParams = GetAllGlobalStuff(_rawConnection, precursorInfoArray, filePath);

            delete sourceFile;
            return new ThermoDynamicData(_rawConnection, topNpeaks, minRatio, trimMs1Peaks, trimMsMsPeaks, lastspectrumNumber - firstspectrumNumber + 1, precursorInfoArray, sourceFile, thermoGlobalParams);
        }

        IThermoScan *ThermoDynamicData::GetOneBasedScan(int oneBasedScanNumber) {
            if (Scans[oneBasedScanNumber - 1] == nullptr) {
                Scans[oneBasedScanNumber - 1] = GetMsDataOneBasedScanFromThermoFile(oneBasedScanNumber, _rawConnection, getThermoGlobalParams(), topNpeaks, minRatio, trimMs1Peaks, trimMsMsPeaks);
            }
            return Scans[oneBasedScanNumber - 1];
        }

        void ThermoDynamicData::ClearCachedScans() {
            Array::Clear(Scans, 0, Scans->Length);
        }

        int ThermoDynamicData::GetClosestOneBasedSpectrumNumber(double retentionTime) {
            int spectrumNumber = 0;
            _rawConnection->ScanNumFromRT(retentionTime, spectrumNumber);
            return spectrumNumber;
        }

        ThermoDynamicData::~ThermoDynamicData() {
                delete _rawConnection;
            this->Dispose(true);
//C# TO C++ CONVERTER WARNING: There is no garbage collector in native C++:
//            GC::SuppressFinalize(this);
        }

        void ThermoDynamicData::Dispose(bool disposing) {
            if (disposing) {
                if (_rawConnection != nullptr) {
                    _rawConnection->Close();
                }
            }
        }
    }
}
