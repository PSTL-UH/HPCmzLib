#include "ThermoFile.h"
#include "IThermoScan.h"
#include "ThermoGlobalParams.h"
#include "../MassSpectrometry/SourceFile.h"
#include "../MzLibUtil/MzLibException.h"
#include "ThermoSpectrum.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "ThermoScanWithPrecursor.h"
#include "ThermoScan.h"

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;
namespace IO {
    namespace Thermo {

Regex *const ThermoFile::PolarityRegex = new Regex(LR"(\+ )", RegexOptions::Compiled);
Regex *const ThermoFile::mFindParentIonOnlyNonMsx = new Regex(LR"([Mm][Ss]\d*[^\[\r\n]* (?<ParentMZ>[0-9.]+)@?[A-Za-z]*\d*\.?\d*(\[[^\]\r\n]\])?)", RegexOptions::IgnoreCase | RegexOptions::Compiled);
Regex *const ThermoFile::mFindParentIonOnlyMsx = new Regex(LR"([Mm][Ss]\d* (?<ParentMZ>[0-9.]+)@?[A-Za-z]*\d*\.?\d*[^\[\r\n]*(\[[^\]\r\n]+\])?)", RegexOptions::IgnoreCase | RegexOptions::Compiled);

        ThermoFile::ThermoFile(std::vector<IThermoScan*> &scans, IO::Thermo::ThermoGlobalParams *thermoGlobalParams, MassSpectrometry::SourceFile *sourceFile) : MsDataFile<IThermoScan>(scans, sourceFile) {
            this->ThermoGlobalParams = thermoGlobalParams;
        }

        ThermoFile::ThermoFile(IXRawfile5 *_rawConnection, int numSpectra, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, MassSpectrometry::SourceFile *sourceFile, IO::Thermo::ThermoGlobalParams *thermoGlobalParams) : MsDataFile<IThermoScan>(numSpectra, sourceFile) {
            this->ThermoGlobalParams = thermoGlobalParams;
        }

        IO::Thermo::ThermoGlobalParams *ThermoFile::getThermoGlobalParams() const {
            return privateThermoGlobalParams;
        }

        IO::Thermo::ThermoGlobalParams *ThermoFile::GetAllGlobalStuff(IXRawfile5 *_rawConnection, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::wstring &filePath) {
            int pnNumInstMethods = 0;
            _rawConnection->GetNumInstMethods(pnNumInstMethods);

            std::vector<std::wstring> instrumentMethods(pnNumInstMethods);
            for (int nInstMethodItem = 0; nInstMethodItem < pnNumInstMethods; nInstMethodItem++) {
                std::wstring pbstrInstMethod = L"";
                _rawConnection->GetInstMethod(nInstMethodItem, pbstrInstMethod);
                instrumentMethods[nInstMethodItem] = pbstrInstMethod;
            }

            std::wstring pbstrInstSoftwareVersion = L"";
            _rawConnection->GetInstSoftwareVersion(pbstrInstSoftwareVersion);

            std::wstring pbstrInstName = L"";
            _rawConnection->GetInstName(pbstrInstName);

            std::wstring pbstrInstModel = L"";
            _rawConnection->GetInstModel(pbstrInstModel);

            int pnControllerNumber = 0;
            int pnControllerType = 0;
            _rawConnection->GetCurrentController(pnControllerType, pnControllerNumber);

            std::vector<int> msOrderByScan(couldBePrecursor.size());
            for (int i = 0; i < couldBePrecursor.size(); i++) {
                _rawConnection->GetMSOrderForScanNum((i + 1), msOrderByScan[i]);
            }

            return new ThermoGlobalParams(pnNumInstMethods, instrumentMethods, pbstrInstSoftwareVersion, pbstrInstName, pbstrInstModel, pnControllerType, pnControllerNumber, couldBePrecursor, filePath, msOrderByScan);
        }

        IThermoScan *ThermoFile::GetMsDataOneBasedScanFromThermoFile(int nScanNumber, IXRawfile5 *theConnection, IO::Thermo::ThermoGlobalParams *globalParams, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks) {
            int pnNumPackets = 0;
            double pdLowMass = 0;
            double pdHighMass = 0;
            double pdTIC = 0;
            double pdBasePeakMass = 0;
            double pdBasePeakIntensity = 0;
            int pnNumChannels = 0;
            int pbUniformTime = 0;
            double pdFrequency = 0;
            double pdStartTime = 0;
            theConnection->GetScanHeaderInfoForScanNum(nScanNumber, pnNumPackets, pdStartTime, pdLowMass, pdHighMass, pdTIC, pdBasePeakMass, pdBasePeakIntensity, pnNumChannels, pbUniformTime, pdFrequency);

            std::optional<double> ms2isolationWidthFromTrailerExtra = std::nullopt;
            std::optional<double> injectionTimeFromTrailerExtra = std::nullopt;
            std::optional<double> precursorMonoisotopicMZfromTrailierExtra = std::nullopt;
            std::optional<int> chargeStatefromTrailierExtra = std::nullopt;

            std::any pvarValues = nullptr;
            std::any pvarLables = nullptr;
            int pnArraySize = 0;
            theConnection->GetTrailerExtraForScanNum(nScanNumber, pvarLables, pvarValues, pnArraySize);

            std::vector<std::wstring> labels = std::any_cast<std::vector<std::wstring>>(pvarLables);
            std::vector<std::wstring> values = std::any_cast<std::vector<std::wstring>>(pvarValues);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'GetLowerBound' for vectors in native C++:
            for (int i = labels.GetLowerBound(0); i <= labels.size() - 1; i++) {
                if (labels[i].StartsWith(L"MS2 Isolation Width", StringComparison::Ordinal)) {
                    ms2isolationWidthFromTrailerExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith(L"Ion Injection Time (ms)", StringComparison::Ordinal)) {
                    injectionTimeFromTrailerExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith(L"Monoisotopic M/Z", StringComparison::Ordinal)) {
                    precursorMonoisotopicMZfromTrailierExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith(L"Charge State", StringComparison::Ordinal)) {
                    chargeStatefromTrailierExtra = std::stoi(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<int>>(nullptr): std::make_optional(std::stoi(values[i], CultureInfo::InvariantCulture));
                }
            }

            std::wstring pbstrFilter = L"";
            theConnection->GetFilterForScanNum(nScanNumber, pbstrFilter);

            int pnMSOrder = 0;
            theConnection->GetMSOrderForScanNum(nScanNumber, pnMSOrder);

            int pnMassAnalyzerType = 0;
            theConnection->GetMassAnalyzerTypeForScanNum(nScanNumber, pnMassAnalyzerType);

            std::any pvarNoisePacket = nullptr;
            theConnection->GetNoiseData(pvarNoisePacket, nScanNumber);
            std::vector<std::vector<double>> noiseData = dynamic_cast<std::vector<std::vector<double>>>(pvarNoisePacket);

            std::vector<std::vector<double>> data;
            try {
                std::any pvarFlags = nullptr;
                std::any pvarLabels = nullptr;
                theConnection->GetLabelData(pvarLabels, pvarFlags, nScanNumber);
                data = dynamic_cast<std::vector<std::vector<double>>>(pvarLabels);
                if (data.empty() || data.empty()) {
                    throw MzLibException(L"For spectrum number " + std::to_wstring(nScanNumber) + L" the data is null!");
                }
            }
            catch (const MzLibException &e1) {
                // Warning: the masses reported by GetMassListFromScanNum when centroiding are not properly calibrated and thus could be off by 0.3 m/z or more

                double pdCentroidPeakWidth = 0;
                std::any pvarnMassList = nullptr;
                std::any pvarPeakFlags = nullptr;
                theConnection->GetMassListFromScanNum(nScanNumber, nullptr, 0, 0, 0, 1, pdCentroidPeakWidth, pvarnMassList, pvarPeakFlags, pnArraySize);
                data = std::any_cast<std::vector<std::vector<double>>>(pvarnMassList);
            }

            ThermoSpectrum *thermoSpectrum;
            if ((minRatio || topNpeaks) && ((trimMs1Peaks && pnMSOrder == 1) || (trimMsMsPeaks && pnMSOrder > 1))) {
                auto count = (data.size() == 0 ? 0 : data[0].size());

                auto mzArray = std::vector<double>(count);
                auto intensityArray = std::vector<double>(count);
                Buffer::BlockCopy(data, 0, mzArray, 0, sizeof(double) * count);
                Buffer::BlockCopy(data, sizeof(double) * count, intensityArray, 0, sizeof(double) * count);

                IComparer<double> *c = new ReverseComparer();
                Array::Sort(intensityArray, mzArray, c);

                int numPeaks = intensityArray.size();
                if (minRatio) {
                    double minIntensity = minRatio.value() * intensityArray[0];
                    numPeaks = std::min(intensityArray.Count([&] (std::any b) {
//C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c was passed to a method or constructor. Handle memory management manually.
                        return b >= minIntensity;
                    }), numPeaks);
                }

                if (topNpeaks) {
                    numPeaks = std::min(topNpeaks.value(), numPeaks);
                }

                Array::Resize(intensityArray, numPeaks);
                Array::Resize(mzArray, numPeaks);

                Array::Sort(mzArray, intensityArray);
                thermoSpectrum = new ThermoSpectrum(mzArray, intensityArray, false);

//C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c was passed to a method or constructor. Handle memory management manually.
            }
            else {
                thermoSpectrum = new ThermoSpectrum(data);
            }
            MZAnalyzerType mzAnalyzerType;
            switch (static_cast<ThermoMzAnalyzer>(pnMassAnalyzerType)) {
                case ThermoMzAnalyzer::FTMS:
                    mzAnalyzerType = MZAnalyzerType::Orbitrap;
                    break;

                default:
                    mzAnalyzerType = MZAnalyzerType::Unknown;
                    break;
            }
            std::wstring nativeId = L"controllerType=0 controllerNumber=1 scan=" + std::to_wstring(nScanNumber);

            if (pnMSOrder > 1) {
                int pnActivationType = 0;
                theConnection->GetActivationTypeForScanNum(nScanNumber, pnMSOrder, pnActivationType);

                // INITIALIZE globalParams.couldBePrecursor[nScanNumber - 1] (for dynamic connections that don't have it initialized yet)
                if (globalParams->couldBePrecursor[nScanNumber - 1]->Equals(default(ManagedThermoHelperLayer::PrecursorInfo))) {
                    auto ok = new ManagedThermoHelperLayer::HelperClass();
                    globalParams->couldBePrecursor[nScanNumber - 1] = ok->GetSingleScanPrecursorInfo(nScanNumber, globalParams->filePath);

                    delete ok;
                }

                auto precursorInfo = globalParams->couldBePrecursor[nScanNumber - 1];

                // THIS METHOD IS BUGGY!!! DO NOT USE
                //theConnection.FindPrecursorMassInFullScan(nScanNumber, ref pnMasterScan, ref pdFoundMass, ref pdHeaderMass, ref pnChargeState);

                int oneBasedPrecursorScanNumber;
                if (precursorInfo->nScanNumber > 0) {
                    oneBasedPrecursorScanNumber = precursorInfo->nScanNumber;
                }
                else {
                    oneBasedPrecursorScanNumber = nScanNumber - 1;
                    // Use info from ScanEvent! Loop back until scan event is equal to 1
                    while (true) {
                        if (globalParams->scanEvent[oneBasedPrecursorScanNumber - 1] == 0) {
                            std::any pvarValuesHere = nullptr;
                            std::any pvarLablesHere = nullptr;
                            int pnArraySizeHere = 0;
                            theConnection->GetTrailerExtraForScanNum(oneBasedPrecursorScanNumber, pvarLablesHere, pvarValuesHere, pnArraySizeHere);
                            std::vector<std::wstring> labelsHere = std::any_cast<std::vector<std::wstring>>(pvarLablesHere);
                            std::vector<std::wstring> valuesHere = std::any_cast<std::vector<std::wstring>>(pvarValuesHere);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'GetLowerBound' for vectors in native C++:
                            for (int i = labelsHere.GetLowerBound(0); i <= labelsHere.size() - 1; i++) {
                                if (labelsHere[i].StartsWith(L"Scan Event", StringComparison::Ordinal)) {
                                    globalParams->scanEvent[oneBasedPrecursorScanNumber - 1] = std::stoi(valuesHere[i], CultureInfo::InvariantCulture);
                                }
                            }
                        }
                        if (globalParams->scanEvent[oneBasedPrecursorScanNumber - 1] == 1) {
                            break;
                        }
                        oneBasedPrecursorScanNumber--;
                    }
                }

                std::optional<int> selectedIonGuessChargeStateGuess = std::nullopt;
                if (precursorInfo->nChargeState > 0) {
                    selectedIonGuessChargeStateGuess = precursorInfo->nChargeState;
                }
                else if (chargeStatefromTrailierExtra) {
                    selectedIonGuessChargeStateGuess = chargeStatefromTrailierExtra;
                }

                std::optional<double> selectedIonGuessMonoisotopicMz = std::nullopt;
                if (precursorMonoisotopicMZfromTrailierExtra && precursorMonoisotopicMZfromTrailierExtra.value() > 0) {
                    selectedIonGuessMonoisotopicMz = precursorMonoisotopicMZfromTrailierExtra;
                }
                if (precursorInfo->dMonoIsoMass > 0 && !selectedIonGuessMonoisotopicMz) {
                    selectedIonGuessMonoisotopicMz = precursorInfo->dMonoIsoMass;
                }

                Regex *matcher;
                if (StringHelper::toLower(pbstrFilter).find(L"msx") != std::wstring::npos) {
                    matcher = mFindParentIonOnlyMsx;
                }
                else {
                    matcher = mFindParentIonOnlyNonMsx;
                }
                double selectedIonGuessMZ = std::stod(matcher->Match(pbstrFilter)->Groups[L"ParentMZ"]->Value);

                delete thermoSpectrum;
                MzRange tempVar(pdLowMass, pdHighMass);
                return new ThermoScanWithPrecursor(nScanNumber, thermoSpectrum, pnMSOrder, PolarityRegex->IsMatch(pbstrFilter) ? Polarity::Positive: Polarity::Negative, pdStartTime, &tempVar, pbstrFilter, mzAnalyzerType, pdTIC, selectedIonGuessMZ, selectedIonGuessChargeStateGuess, ms2isolationWidthFromTrailerExtra, static_cast<DissociationType>(pnActivationType), std::make_optional(oneBasedPrecursorScanNumber), selectedIonGuessMonoisotopicMz, injectionTimeFromTrailerExtra, noiseData, nativeId);
            }
            else {
//C# TO C++ CONVERTER TODO TASK: A 'delete thermoSpectrum' statement was not added since thermoSpectrum was passed to a method or constructor. Handle memory management manually.
                MzRange tempVar2(pdLowMass, pdHighMass);
                return new ThermoScan(nScanNumber, thermoSpectrum, 1, PolarityRegex->IsMatch(pbstrFilter) ? Polarity::Positive : Polarity::Negative, pdStartTime, &tempVar2, pbstrFilter, mzAnalyzerType, pdTIC, injectionTimeFromTrailerExtra, noiseData, nativeId);
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete thermoSpectrum' statement was not added since thermoSpectrum was passed to a method or constructor. Handle memory management manually.
        }
    }
}
