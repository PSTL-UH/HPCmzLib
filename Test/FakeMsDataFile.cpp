#include "FakeMsDataFile.h"

using namespace IO::MzML;
using namespace MassSpectrometry;

namespace Test {

    FakeMsDataFile::FakeMsDataFile(std::vector<IMzmlScan*> &FakeScans) : MsDataFile<IMzmlScan>(LR"(no nativeID format)", L"mzML format", L"", L"SHA-1", LR"(C:\fake.mzML)", L"") {
        this->Scans = FakeScans;
    }

    int FakeMsDataFile::GetClosestOneBasedSpectrumNumber(double retentionTime) {
        int ok = Array::BinarySearch(Scans.Select([&] (std::any b) {
            b::RetentionTime;
        })->ToArray(), retentionTime);
        if (ok < 0) {
            ok = ~ok;
        }
        return ok + 1;
    }

    IMzmlScan *FakeMsDataFile::GetOneBasedScan(int scanNumber) {
        return Scans[scanNumber - 1];
    }
}
