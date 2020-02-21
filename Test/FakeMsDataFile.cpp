#include "FakeMsDataFile.h"
#include "../MassSpectrometry/MsDataScan.h"

using namespace MassSpectrometry;

namespace Test
{

    FakeMsDataFile::FakeMsDataFile(std::vector<MsDataScan*> &FakeScans) : MsDataFile(FakeScans, &tempVar)
    {
        this->Scans = FakeScans;
    }

    int FakeMsDataFile::GetClosestOneBasedSpectrumNumber(double retentionTime)
    {
        int ok = Array::BinarySearch(Scans.Select([&] (std::any b)
        {
            b::RetentionTime;
        })->ToArray(), retentionTime);
        if (ok < 0)
        {
            ok = ~ok;
        }
        return ok + 1;
    }

    std::vector<MsDataScan*> FakeMsDataFile::GetMS1Scans()
    {
        throw NotImplementedException();
    }

    MsDataScan *FakeMsDataFile::GetOneBasedScan(int scanNumber)
    {
        return Scans[scanNumber - 1];
    }
}
