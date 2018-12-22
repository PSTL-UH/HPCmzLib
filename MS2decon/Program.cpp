#include "Program.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/IMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScan.h"
#include "../MassSpectrometry/MzSpectra/IMzPeak.h"
#include "../MassSpectrometry/MzSpectra/IMzSpectrum.h"
#include "../MassSpectrometry/DataScan/IMsDataScanWithPrecursor.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/DeconvolutionFeatureWithMassesAndScans.h"

using namespace Fclp;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace UsefulProteomicsDatabases;

namespace MS2decon {

    void Program::Main(std::vector<std::wstring> &args) {
        Loaders::LoadElements(L"elements.dat");

        auto p = new FluentCommandLineParser<ApplicationArguments*>();

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
//ORIGINAL LINE: using (StreamWriter output = new StreamWriter("TangibleTempVerbatimOpenTagMS2DeconvolutionOutput-TangibleTempVerbatimCloseTag" + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss", CultureInfo.InvariantCulture) + ".tsv"))
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            {
                StreamWriter output = StreamWriter(LR"(MS2DeconvolutionOutput-)" + DateTime::Now.ToString(L"yyyy-MM-dd-HH-mm-ss", CultureInfo::InvariantCulture) + L".tsv");
                output.WriteLine(L"Mass\tNumPeaks\tNumScans\tMinScan\tMaxScan\tAverageElutionTime\tIntensity\tObservedCharges\tMostIntenseCharge\tMostIntenseMz\tNumPeaksInMostIntenseEnvelope");

                for (auto ok : myMsDataFile->OfType<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>()) {
                    if ((!p->Object.MinScan.HasValue || ok->OneBasedScanNumber >= p->Object.MinScan) && (!p->Object.MaxScan.HasValue || ok->OneBasedScanNumber <= p->Object.MaxScan)) {
                        MzRange tempVar(0, std::numeric_limits<double>::infinity());
                        auto hmm = ok->MassSpectrum.Deconvolute(&tempVar, p->Object.MaxAssumedChargeState, p->Object.DeconvolutionTolerancePpm, p->Object.IntensityRatioLimit).ToList();

                        std::vector<DeconvolutionFeatureWithMassesAndScans*> currentListOfGroups;

                        for (auto isotopicEnvelope : hmm) {
                            DeconvolutionFeatureWithMassesAndScans *matchingGroup = nullptr;
                            auto mass = isotopicEnvelope.monoisotopicMass;
                            for (auto possibleGroup : currentListOfGroups) {
                                auto possibleGroupMass = possibleGroup->getMass();
                                if (std::abs(mass - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass + 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass + 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass + 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass - 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass - 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm || std::abs(mass - 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= p->Object.AggregationTolerancePpm) {
                                    matchingGroup = possibleGroup;
                                    matchingGroup->AddEnvelope(isotopicEnvelope, ok->OneBasedScanNumber, ok->RetentionTime);
                                    break;
                                }
                            }

                            if (matchingGroup == nullptr) {
                                auto newGroupScans = new DeconvolutionFeatureWithMassesAndScans();
                                newGroupScans->AddEnvelope(isotopicEnvelope, ok->OneBasedScanNumber, ok->RetentionTime);
                                currentListOfGroups.push_back(newGroupScans);

//C# TO C++ CONVERTER TODO TASK: A 'delete newGroupScans' statement was not added since newGroupScans was passed to a method or constructor. Handle memory management manually.
                            }
                        }
                        for (auto ook : currentListOfGroups) {
                            output.WriteLine(ook->OneLineString());
                        }
                    }
                }
            }
        }
        else {
            std::wcout << L"BAD PARAMETERS" << std::endl;
            std::wcout << result->ErrorText << std::endl;
        }

        delete p;
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
        sb->appendLine(L"FilePath: " + getFilePath());
        sb->appendLine(L"MinScan: " + getMinScan());
        sb->appendLine(L"MaxScan: " + getMaxScan());
        sb->appendLine(L"MaxAssumedChargeState: " + std::to_wstring(getMaxAssumedChargeState()));
        sb->appendLine(L"DeconvolutionTolerancePpm: " + std::to_wstring(getDeconvolutionTolerancePpm()));
        sb->appendLine(L"IntensityRatioLimit: " + std::to_wstring(getIntensityRatioLimit()));
        sb->appendLine(L"AggregationTolerancePpm: " + std::to_wstring(getAggregationTolerancePpm()));

        delete sb;
        return sb->toString();
    }
}
