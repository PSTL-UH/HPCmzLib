#include "Program.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/IMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScan.h"
#include "../MassSpectrometry/MzSpectra/IMzPeak.h"
#include "../MassSpectrometry/MzSpectra/IMzSpectrum.h"

using namespace Fclp;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace UsefulProteomicsDatabases;

namespace ConsoleApp1 {

    void Program::Main(std::vector<std::wstring> &args) {
        Loaders::LoadElements(L"elements.dat");

        DoFileDecon(args);
    }

    void Program::DoFileDecon(std::vector<std::wstring> &args) {
        auto p = new FluentCommandLineParser<ApplicationArguments*>();

        p->Setup([&] (std::any arg) {
            arg::AggregationTolerancePpm;
        }).As(L"AggregationTolerancePpm");

        p->Setup([&] (std::any arg) {
            arg::DeconvolutionTolerancePpm;
        }).As(L"DeconvolutionTolerancePpm");

        p->Setup([&] (std::any arg) {
            arg::MinScan;
        }).As(L"MinScan");

        p->Setup([&] (std::any arg) {
            arg::MaxScan;
        }).As(L"MaxScan");

        p->Setup([&] (std::any arg) {
            arg::MaxAssumedChargeState;
        }).As(L"MaxAssumedChargeState");

        p->Setup([&] (std::any arg) {
            arg::IntensityRatioLimit;
        }).As(L"IntensityRatioLimit");

        p->Setup([&] (std::any arg) {
            arg::FilePath;
        }).As(L"FilePath").Required();

        auto result = p->Parse(args);

        std::wcout << L"Running deconvolution using the following parameters:" << std::endl;
        std::wcout << p->Object << std::endl;

        if (result->HasErrors == false) {
            IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
            if (Path::GetExtension(p->Object.FilePath).Equals(L".mzML", StringComparison::OrdinalIgnoreCase)) {
                myMsDataFile = Mzml::LoadAllStaticData(p->Object.FilePath);
            }
            else {
                myMsDataFile = ThermoStaticData::LoadAllStaticData(p->Object.FilePath);
            }

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter output = new StreamWriter("TangibleTempVerbatimOpenTagDeconvolutionOutput-TangibleTempVerbatimCloseTag" + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss", CultureInfo.InvariantCulture) + ".tsv"))
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            {
                StreamWriter output = StreamWriter(LR"(DeconvolutionOutput-)" + DateTime::Now.ToString(L"yyyy-MM-dd-HH-mm-ss", CultureInfo::InvariantCulture) + L".tsv");
                output.WriteLine(L"Mass\tNumPeaks\tNumScans\tMinScan\tMaxScan\tAverageElutionTime\tIntensity\tObservedCharges\tMostIntenseCharge\tMostIntenseMz\tNumPeaksInMostIntenseEnvelope");
                for (auto nice : myMsDataFile->Deconvolute(p->Object.MinScan, p->Object.MaxScan, p->Object.MaxAssumedChargeState, p->Object.DeconvolutionTolerancePpm, p->Object.IntensityRatioLimit, p->Object.AggregationTolerancePpm, [&] (std::any b) {
                delete p;
                    return b->MsnOrder == 1;
                }).OrderByDescending([&] (std::any b) {
                    b::TotalIntensity;
                })) {
                }
                }
        }

            delete p;
    }
}

std::optional<int> ApplicationArguments::getMinScan() const {
    return privateMinScan;
}

void ApplicationArguments::setMinScan(const std::optional<int> &value) {
    privateMinScan = value;
}

std::optional<int> ApplicationArguments::getMaxScan() const {
    return privateMaxScan;
}

void ApplicationArguments::setMaxScan(const std::optional<int> &value) {
    privateMaxScan = value;
}

int ApplicationArguments::getMaxAssumedChargeState() const {
    return privateMaxAssumedChargeState;
}

void ApplicationArguments::setMaxAssumedChargeState(int value) {
    privateMaxAssumedChargeState = value;
}

double ApplicationArguments::getDeconvolutionTolerancePpm() const {
    return privateDeconvolutionTolerancePpm;
}

void ApplicationArguments::setDeconvolutionTolerancePpm(double value) {
    privateDeconvolutionTolerancePpm = value;
}

double ApplicationArguments::getIntensityRatioLimit() const {
    return privateIntensityRatioLimit;
}

void ApplicationArguments::setIntensityRatioLimit(double value) {
    privateIntensityRatioLimit = value;
}

double ApplicationArguments::getAggregationTolerancePpm() const {
    return privateAggregationTolerancePpm;
}

void ApplicationArguments::setAggregationTolerancePpm(double value) {
    privateAggregationTolerancePpm = value;
}

std::wstring ApplicationArguments::getFilePath() const {
    return privateFilePath;
}

void ApplicationArguments::setFilePath(const std::wstring &value) {
    privateFilePath = value;
}

std::wstring ApplicationArguments::ToString() {
    StringBuilder *sb = new StringBuilder();
    sb->appendLine(L"FilePath: " + FilePath);
    sb->appendLine(L"MinScan: " + MinScan);
    sb->appendLine(L"MaxScan: " + MaxScan);
    sb->appendLine(L"MaxAssumedChargeState: " + MaxAssumedChargeState);
    sb->appendLine(L"DeconvolutionTolerancePpm: " + DeconvolutionTolerancePpm);
    sb->appendLine(L"IntensityRatioLimit: " + IntensityRatioLimit);
    sb->appendLine(L"AggregationTolerancePpm: " + AggregationTolerancePpm);

    delete sb;
    return sb->toString();
}
