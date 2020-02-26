#include "FakeMsDataFile.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "Search.h"

using namespace MassSpectrometry;

namespace Test
{
    std::string s0 = "";
    std::string s1 = "";
    std::string s2 = "";
    std::string s3 = "";
    std::string s4 = "";
    std::string s5 = "";
    std::string uri = "";
    Uri u(uri);
    MassSpectrometry::SourceFile tempVar(s0, s1,s2,s3,&u,s4,s5);
    FakeMsDataFile::FakeMsDataFile(std::vector<MsDataScan*> &FakeScans) : MsDataFile(FakeScans, &tempVar)
    {
        this->Scans = FakeScans;
    }

    int FakeMsDataFile::GetClosestOneBasedSpectrumNumber(double retentionTime)
    {

    #ifdef ORIG 
        int ok = Array::BinarySearch(Scans.Select([&] (std::any b)
        {
            b::RetentionTime;
        })->ToArray(), retentionTime);
    #endif
        std::vector<double> v;
        for ( auto b : Scans ) {
            v.push_back(b->getRetentionTime());
        } 

        int ok = BinarySearch(v, retentionTime);
        // if (ok < 0)
        // {
        //     ok = ~ok;
        // }
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
