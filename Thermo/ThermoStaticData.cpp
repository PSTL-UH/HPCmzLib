#include "ThermoStaticData.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "ThermoGlobalParams.h"
#include "../MassSpectrometry/IFilteringParams.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;
namespace IO
{
    namespace Thermo
    {

Regex *const ThermoStaticData::PolarityRegex = new Regex(R"(\+ )", RegexOptions::Compiled);
Regex *const ThermoStaticData::mFindParentIonOnlyNonMsx = new Regex(R"([Mm][Ss]\d*[^\[\r\n]* (?<ParentMZ>[0-9.]+)@?[A-Za-z]*\d*\.?\d*(\[[^\]\r\n]\])?)", RegexOptions::IgnoreCase | RegexOptions::Compiled);
Regex *const ThermoStaticData::mFindParentIonOnlyMsx = new Regex(R"([Mm][Ss]\d* (?<ParentMZ>[0-9.]+)@?[A-Za-z]*\d*\.?\d*[^\[\r\n]*(\[[^\]\r\n]+\])?)", RegexOptions::IgnoreCase | RegexOptions::Compiled);

        ThermoStaticData::ThermoStaticData(std::vector<MsDataScan*> &scans, IO::Thermo::ThermoGlobalParams *thermoGlobalParams, MassSpectrometry::SourceFile *sourceFile) : ThermoDataFile(scans, sourceFile)
        {
            this->setThermoGlobalParams(thermoGlobalParams);
        }

        ThermoStaticData *ThermoStaticData::LoadAllStaticData(const std::string &filePath, IFilteringParams *filterParams)
        {
            if (!FileSystem::fileExists(filePath))
            {
                throw FileNotFoundException();
            }

            if (CheckForMsFileReader() == false)
            {
                throw MzLibException("MsFileReader Not Installed");
            }

            auto ok = new ManagedThermoHelperLayer::HelperClass();
            MSFileReader_XRawfile tempVar();
            IXRawfile5 *theConnection = static_cast<IXRawfile5*>(&tempVar);
            theConnection->Open(filePath);
            int pbSMData = 0;
            theConnection->IsThereMSData(pbSMData);
            if (pbSMData == 0)
            {
                delete ok;
                throw MzLibException("Could not read data from file " + FileSystem::getFileName(filePath));
            }

            theConnection->SetCurrentController(0, 1);

            auto precursorInfosArray = ok->GetAllPrecursorInfos(filePath);
            for (int i = 0; i < precursorInfosArray->Length; i++)
            {
                if (precursorInfosArray[i]->nScanNumber == 0)
                {
                    precursorInfosArray[i]->nScanNumber = -1;
                }
            }

            int pnFirstSpectrum = 0;
            theConnection->GetFirstSpectrumNumber(pnFirstSpectrum);
            int pnLastSpectrum = 0;
            theConnection->GetLastSpectrumNumber(pnLastSpectrum);

            IO::Thermo::ThermoGlobalParams *p = GetAllGlobalStuff(theConnection, precursorInfosArray, filePath);

            std::vector<MsDataScan*> scans(pnLastSpectrum - pnFirstSpectrum + 1);
            for (int nScanNumber = pnFirstSpectrum; nScanNumber <= pnLastSpectrum; nScanNumber++)
            {
                scans[nScanNumber - pnFirstSpectrum] = GetMsDataOneBasedScanFromThermoFile(theConnection, nScanNumber, p, filterParams);
            }

            theConnection->Close();

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

            delete sourceFile;
            delete ok;
            return new ThermoStaticData(scans, p, sourceFile);
        }

        MsDataScan *ThermoStaticData::GetMsDataOneBasedScanFromThermoFile(IXRawfile5 *theConnection, int nScanNumber, IO::Thermo::ThermoGlobalParams *globalParams, IFilteringParams *filterParams)
        {
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

            std::optional<double> ms2isolationWidthFromTrailerExtra;
            std::optional<double> injectionTimeFromTrailerExtra;
            std::optional<double> precursorMonoisotopicMZfromTrailierExtra;
            std::optional<int> chargeStatefromTrailierExtra;
            std::optional<int> masterScanfromTrailierExtra;

            std::any pvarValues;
            std::any pvarLables;
            int pnArraySize = 0;
            theConnection->GetTrailerExtraForScanNum(nScanNumber, pvarLables, pvarValues, pnArraySize);

            std::vector<std::string> labels = std::any_cast<std::vector<std::string>>(pvarLables);
            std::vector<std::string> values = std::any_cast<std::vector<std::string>>(pvarValues);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'GetLowerBound' for vectors in C++:
            for (int i = labels.GetLowerBound(0); i <= labels.size() - 1; i++)
            {
                if (labels[i].StartsWith("MS2 Isolation Width", StringComparison::Ordinal))
                {
                    ms2isolationWidthFromTrailerExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith("Ion Injection Time (ms)", StringComparison::Ordinal))
                {
                    injectionTimeFromTrailerExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith("Monoisotopic M/Z", StringComparison::Ordinal))
                {
                    precursorMonoisotopicMZfromTrailierExtra = std::stod(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<double>>(nullptr): std::make_optional(std::stod(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith("Charge State", StringComparison::Ordinal))
                {
                    chargeStatefromTrailierExtra = std::stoi(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<int>>(nullptr): std::make_optional(std::stoi(values[i], CultureInfo::InvariantCulture));
                }
                if (labels[i].StartsWith("Master Scan Number", StringComparison::Ordinal))
                {
                    masterScanfromTrailierExtra = std::stoi(values[i], CultureInfo::InvariantCulture) == 0 ? static_cast<std::optional<int>>(nullptr): std::make_optional(std::stoi(values[i], CultureInfo::InvariantCulture));
                }
            }

            std::string pbstrFilter = "";
            theConnection->GetFilterForScanNum(nScanNumber, pbstrFilter);

            int pnMSOrder = 0;
            theConnection->GetMSOrderForScanNum(nScanNumber, pnMSOrder);

            int pnMassAnalyzerType = 0;
            theConnection->GetMassAnalyzerTypeForScanNum(nScanNumber, pnMassAnalyzerType);

            std::any pvarNoisePacket;
            try //if there is no noise data
            {
                theConnection->GetNoiseData(pvarNoisePacket, nScanNumber);
            }
            catch (...)
            {
                //pvarNoisePAcket is already null
            }
            std::vector<std::vector<double>> noiseData = dynamic_cast<std::vector<std::vector<double>>>(pvarNoisePacket);

            std::vector<std::vector<double>> data;
            try
            {
                std::any pvarFlags;
                std::any pvarLabels;
                theConnection->GetLabelData(pvarLabels, pvarFlags, nScanNumber);
                data = dynamic_cast<std::vector<std::vector<double>>>(pvarLabels);
                if (data.empty() || data.empty())
                {
                    throw MzLibException("For spectrum number " + std::to_string(nScanNumber) + " the data is null!");
                }
            }
            catch (const MzLibException &e1)
            {
                // Warning: the masses reported by GetMassListFromScanNum when centroiding are not properly calibrated and thus could be off by 0.3 m/z or more

                double pdCentroidPeakWidth = 0;
                std::any pvarnMassList;
                std::any pvarPeakFlags;
                theConnection->GetMassListFromScanNum(nScanNumber, nullptr, 0, 0, 0, 1, pdCentroidPeakWidth, pvarnMassList, pvarPeakFlags, pnArraySize);
                data = std::any_cast<std::vector<std::vector<double>>>(pvarnMassList);
            }

            MzSpectrum *thermoSpectrum;
            if (filterParams != nullptr && (data.size() == 0 ? 0 : data[0].size()) > 0 && (filterParams->getMinimumAllowedIntensityRatioToBasePeakM() || filterParams->getNumberOfPeaksToKeepPerWindow()) && ((filterParams->getApplyTrimmingToMs1() && pnMSOrder == 1) || (filterParams->getApplyTrimmingToMsMs() && pnMSOrder > 1)))
            {
                auto count = (data.size() == 0 ? 0 : data[0].size());

                auto mzArray = std::vector<double>(count);
                auto intensityArray = std::vector<double>(count);
                Buffer::BlockCopy(data, 0, mzArray, 0, sizeof(double) * count);
                Buffer::BlockCopy(data, sizeof(double) * count, intensityArray, 0, sizeof(double) * count);
                if (!filterParams->getNumberOfWindows())
                {
                    int numPeaks = TopNpeakHelper(intensityArray, mzArray, filterParams);
                    //the following arrays are modified after TopN helper
                    Array::Resize(intensityArray, numPeaks);
                    Array::Resize(mzArray, numPeaks);
                }
                //Array reference passed by value, array calues will be modified after calling
                else
                {
                    WindowModeHelper(intensityArray, mzArray, filterParams, pdLowMass, pdHighMass);
                }
                Array::Sort(mzArray, intensityArray);
                thermoSpectrum = new MzSpectrum(mzArray, intensityArray, false);
            }
            else
            {
                thermoSpectrum = new MzSpectrum(data);
            }
            MZAnalyzerType mzAnalyzerType;
            if (static_cast<ThermoMzAnalyzer>(pnMassAnalyzerType) == ThermoMzAnalyzer::FTMS)
            {
                mzAnalyzerType = MZAnalyzerType::Orbitrap;
            }
            else
            {
                mzAnalyzerType = MZAnalyzerType::Unknown;
            }
            std::string nativeId = "controllerType=0 controllerNumber=1 scan=" + std::to_string(nScanNumber);

            if (pnMSOrder > 1)
            {
                int pnActivationType = 0;
                theConnection->GetActivationTypeForScanNum(nScanNumber, pnMSOrder, pnActivationType);

                // INITIALIZE globalParams.couldBePrecursor[nScanNumber - 1] (for dynamic connections that don't have it initialized yet)
                if (globalParams->CouldBePrecursor[nScanNumber - 1]->Equals(nullptr))
                {
                    auto ok = new ManagedThermoHelperLayer::HelperClass();
                    globalParams->CouldBePrecursor[nScanNumber - 1] = ok->GetSingleScanPrecursorInfo(nScanNumber, globalParams->FilePath);

                    delete ok;
                }

                auto precursorInfo = globalParams->CouldBePrecursor[nScanNumber - 1];

                // THIS METHOD IS BUGGY!!! DO NOT USE
                //theConnection.FindPrecursorMassInFullScan(nScanNumber, ref pnMasterScan, ref pdFoundMass, ref pdHeaderMass, ref pnChargeState);

                int oneBasedPrecursorScanNumber = -1;
                if (precursorInfo->nScanNumber > 0)
                {
                    oneBasedPrecursorScanNumber = precursorInfo->nScanNumber;
                }
//C# TO C++ CONVERTER TODO TASK: Comparisons involving nullable type instances will need to be rewritten since comparison rules are different between C++ optional and System.Nullable:
                else if (masterScanfromTrailierExtra && masterScanfromTrailierExtra > 0)
                {
                    oneBasedPrecursorScanNumber = masterScanfromTrailierExtra.value();
                }
                else
                {
                    // we weren't able to get the precursor scan number, so we'll have to guess;
                    // loop back to find precursor scan
                    // (assumed to be the first scan before this scan with an MS order of this scan's MS order - 1)
                    // e.g., if this is an MS2 scan, find the first MS1 scan before this and assume that's the precursor scan
                    int scanOrder = globalParams->MsOrderByScan[nScanNumber - 1];
                    int precursorScanOrder = scanOrder - 1;

                    for (int i = nScanNumber - 1; i >= 0; i--)
                    {
                        int msOrder = globalParams->MsOrderByScan[i];

                        if (msOrder == precursorScanOrder)
                        {
                            oneBasedPrecursorScanNumber = i + 1;
                            break;
                        }
                    }
                }
                if (oneBasedPrecursorScanNumber == -1)
                {
                    delete thermoSpectrum;
                    throw MzLibException("Could not find precursor info for scan #" + std::to_string(nScanNumber));
                }

                std::optional<int> selectedIonGuessChargeStateGuess;
                if (precursorInfo->nChargeState > 0)
                {
                    selectedIonGuessChargeStateGuess = precursorInfo->nChargeState;
                }
                else if (chargeStatefromTrailierExtra)
                {
                    selectedIonGuessChargeStateGuess = chargeStatefromTrailierExtra;
                }

                std::optional<double> selectedIonGuessMonoisotopicMz;
                if (precursorMonoisotopicMZfromTrailierExtra && precursorMonoisotopicMZfromTrailierExtra.value() > 0)
                {
                    selectedIonGuessMonoisotopicMz = precursorMonoisotopicMZfromTrailierExtra;
                }
                if (precursorInfo->dMonoIsoMass > 0 && !selectedIonGuessMonoisotopicMz)
                {
                    selectedIonGuessMonoisotopicMz = precursorInfo->dMonoIsoMass;
                }

                Regex *matcher;
                if (StringHelper::toLower(pbstrFilter).find("msx") != std::string::npos)
                {
                    matcher = mFindParentIonOnlyMsx;
                }
                else
                {
                    matcher = mFindParentIonOnlyNonMsx;
                }
                double selectedIonGuessMZ = std::stod(matcher->Match(pbstrFilter).Groups["ParentMZ"]->Value);

                //   int? selectedIonChargeStateGuess, double? selectedIonIntensity, double? isolationMZ, double? isolationWidth, DissociationType dissociationType, int? oneBasedPrecursorScanNumber, double? selectedIonMonoisotopicGuessMz, double? injectionTime, double[,] noiseData, string nativeId)
                // double TotalIonCurrent, double selectedIonMZ, int? selectedIonChargeStateGuess, double? selectedIonIntensity, double? isolationMZ, double? isolationWidth, DissociationType dissociationType, int? oneBasedPrecursorScanNumber, double? selectedIonMonoisotopicGuessMz, double? injectionTime, double[,] noiseData, string nativeId)

                delete thermoSpectrum;
                MzRange tempVar(pdLowMass, pdHighMass);
                return new MsDataScan(thermoSpectrum, nScanNumber, pnMSOrder, true, PolarityRegex->IsMatch(pbstrFilter) ? Polarity::Positive: Polarity::Negative, pdStartTime, &tempVar, pbstrFilter, mzAnalyzerType, pdTIC, injectionTimeFromTrailerExtra, noiseData, nativeId, std::make_optional(selectedIonGuessMZ), selectedIonGuessChargeStateGuess, std::nullopt, std::make_optional(selectedIonGuessMZ), ms2isolationWidthFromTrailerExtra, std::make_optional(static_cast<DissociationType>(pnActivationType)), std::make_optional(oneBasedPrecursorScanNumber), selectedIonGuessMonoisotopicMz);
            }
            else
            {
//C# TO C++ CONVERTER TODO TASK: A 'delete thermoSpectrum' statement was not added since thermoSpectrum was passed to a method or constructor. Handle memory management manually.
                MzRange tempVar2(pdLowMass, pdHighMass);
                return new MsDataScan(thermoSpectrum, nScanNumber, 1, true, PolarityRegex->IsMatch(pbstrFilter) ? Polarity::Positive : Polarity::Negative, pdStartTime, &tempVar2, pbstrFilter, mzAnalyzerType, pdTIC, injectionTimeFromTrailerExtra, noiseData, nativeId);
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete thermoSpectrum' statement was not added since thermoSpectrum was passed to a method or constructor. Handle memory management manually.
        }

        IO::Thermo::ThermoGlobalParams *ThermoStaticData::GetAllGlobalStuff(IXRawfile5 *_rawConnection, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::string &filePath)
        {
            int pnNumInstMethods = 0;
            _rawConnection->GetNumInstMethods(pnNumInstMethods);

            std::vector<std::string> instrumentMethods(pnNumInstMethods);
            for (int nInstMethodItem = 0; nInstMethodItem < pnNumInstMethods; nInstMethodItem++)
            {
                std::string pbstrInstMethod = "";
                _rawConnection->GetInstMethod(nInstMethodItem, pbstrInstMethod);
                instrumentMethods[nInstMethodItem] = pbstrInstMethod;
            }

            std::string pbstrInstSoftwareVersion = "";
            _rawConnection->GetInstSoftwareVersion(pbstrInstSoftwareVersion);

            std::string pbstrInstName = "";
            _rawConnection->GetInstName(pbstrInstName);

            std::string pbstrInstModel = "";
            _rawConnection->GetInstModel(pbstrInstModel);

            int pnControllerNumber = 0;
            int pnControllerType = 0;
            _rawConnection->GetCurrentController(pnControllerType, pnControllerNumber);

            std::vector<int> msOrderByScan(couldBePrecursor.size());
            for (int i = 0; i < couldBePrecursor.size(); i++)
            {
                _rawConnection->GetMSOrderForScanNum((i + 1), msOrderByScan[i]);
            }

            return new ThermoGlobalParams(pnNumInstMethods, instrumentMethods, pbstrInstSoftwareVersion, pbstrInstName, pbstrInstModel, pnControllerType, pnControllerNumber, couldBePrecursor, filePath, msOrderByScan);
        }

        bool ThermoStaticData::CheckForMsFileReader()
        {
            const std::string THERMO_READER_CLSID = "{1d23188d-53fe-4c25-b032-dc70acdbdc02}";
            //Check if Thermo File Reader Exists
            try
            {
                auto thermoReader = std::type_info::GetTypeFromCLSID(Guid::Parse(THERMO_READER_CLSID));
                Activator::CreateInstance(thermoReader);
            }
            catch (const COMException &e1)
            {
                return false;
            }
            return true;
        }
    }
}
