#include "ThermoStaticData.h"
#include "IThermoScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "ThermoGlobalParams.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;
namespace IO {
    namespace Thermo {

        ThermoStaticData::ThermoStaticData(std::vector<IThermoScan*> &scans, IO::Thermo::ThermoGlobalParams *p, MassSpectrometry::SourceFile *sourceFile) : ThermoFile(scans, p, sourceFile) {
        }

        ThermoStaticData *ThermoStaticData::LoadAllStaticData(const std::wstring &filePath, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks) {
            auto ok = new ManagedThermoHelperLayer::HelperClass();
            MSFileReader_XRawfile tempVar();
            IXRawfile5 *theConnection = static_cast<IXRawfile5*>(&tempVar);
            theConnection->Open(filePath);
            int pbSMData = 0;
            theConnection->IsThereMSData(pbSMData);
            if (pbSMData == 0) {
                delete ok;
                throw MzLibException(L"File not found");
            }

            theConnection->SetCurrentController(0, 1);

            auto precursorInfosArray = ok->GetAllPrecursorInfos(filePath);
            for (int i = 0; i < precursorInfosArray->Length; i++) {
                if (precursorInfosArray[i]->nScanNumber == 0) {
                    precursorInfosArray[i]->nScanNumber = -1;
                }
            }

            int pnFirstSpectrum = 0;
            theConnection->GetFirstSpectrumNumber(pnFirstSpectrum);
            int pnLastSpectrum = 0;
            theConnection->GetLastSpectrumNumber(pnLastSpectrum);

            IO::Thermo::ThermoGlobalParams *p = GetAllGlobalStuff(theConnection, precursorInfosArray, filePath);

            std::vector<IThermoScan*> scans(pnLastSpectrum - pnFirstSpectrum + 1);
            for (int nScanNumber = pnFirstSpectrum; nScanNumber <= pnLastSpectrum; nScanNumber++) {
                scans[nScanNumber - pnFirstSpectrum] = GetMsDataOneBasedScanFromThermoFile(nScanNumber, theConnection, p, topNpeaks, minRatio, trimMs1Peaks, trimMsMsPeaks);
            }

            theConnection->Close();

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
            MassSpectrometry::SourceFile *sourceFile = new SourceFile(LR"(Thermo nativeID format)", LR"(Thermo RAW format)", sendCheckSum, LR"(SHA-1)", filePath, Path::GetFileNameWithoutExtension(filePath));

            delete sourceFile;
            delete ok;
            return new ThermoStaticData(scans, p, sourceFile);
        }

        IThermoScan *ThermoStaticData::GetOneBasedScan(int oneBasedScanNumber) {
            return Scans[oneBasedScanNumber - 1];
        }
    }
}
