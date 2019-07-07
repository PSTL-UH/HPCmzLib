#include "MsDataScan.h"
#include "MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"
#include "MzSpectra/IsotopicEnvelope.h"
#include "MzSpectra/MzPeak.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;

namespace MassSpectrometry
{

    MsDataScan::MsDataScan(MzSpectrum *massSpectrum, int oneBasedScanNumber, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::string &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, std::optional<double> &injectionTime, std::vector<std::vector<double>> &noiseData, const std::string &nativeId, std::optional<double> &selectedIonMz, std::optional<int> &selectedIonChargeStateGuess, std::optional<double> &selectedIonIntensity, std::optional<double> &isolationMZ, std::optional<double> &isolationWidth, std::optional<MassSpectrometry::DissociationType> &dissociationType, std::optional<int> &oneBasedPrecursorScanNumber, std::optional<double> &selectedIonMonoisotopicGuessMz)
    {
        OneBasedScanNumber = oneBasedScanNumber;
        MsnOrder = msnOrder;
        IsCentroid = isCentroid;
        Polarity = polarity;
        RetentionTime = retentionTime;
        ScanWindowRange = scanWindowRange;
        ScanFilter = scanFilter;
        MzAnalyzer = mzAnalyzer;
        TotalIonCurrent = totalIonCurrent;
        InjectionTime = injectionTime;
        NoiseData = noiseData;
        setMassSpectrum(massSpectrum);
        NativeId = nativeId;
        setOneBasedPrecursorScanNumber(oneBasedPrecursorScanNumber);
        setIsolationMz(isolationMZ);
        IsolationWidth = isolationWidth;
        DissociationType = dissociationType;
        setSelectedIonMZ(selectedIonMz);
        setSelectedIonIntensity(selectedIonIntensity);
        SelectedIonChargeStateGuess = selectedIonChargeStateGuess;
        setSelectedIonMonoisotopicGuessMz(selectedIonMonoisotopicGuessMz);
    }

    MzSpectrum *MsDataScan::getMassSpectrum() const
    {
        return privateMassSpectrum;
    }

    void MsDataScan::setMassSpectrum(MzSpectrum *value)
    {
        privateMassSpectrum = value;
    }

    int MsDataScan::getOneBasedScanNumber() const
    {
        return privateOneBasedScanNumber;
    }

    int MsDataScan::getMsnOrder() const
    {
        return privateMsnOrder;
    }

    double MsDataScan::getRetentionTime() const
    {
        return privateRetentionTime;
    }

    MassSpectrometry::Polarity MsDataScan::getPolarity() const
    {
        return privatePolarity;
    }

    MZAnalyzerType MsDataScan::getMzAnalyzer() const
    {
        return privateMzAnalyzer;
    }

    MzRange *MsDataScan::getScanWindowRange() const
    {
        return privateScanWindowRange;
    }

    std::string MsDataScan::getScanFilter() const
    {
        return privateScanFilter;
    }

    std::string MsDataScan::getNativeId() const
    {
        return privateNativeId;
    }

    bool MsDataScan::getIsCentroid() const
    {
        return privateIsCentroid;
    }

    double MsDataScan::getTotalIonCurrent() const
    {
        return privateTotalIonCurrent;
    }

    std::optional<double> MsDataScan::getInjectionTime() const
    {
        return privateInjectionTime;
    }

    std::vector<std::vector<double>> MsDataScan::getNoiseData() const
    {
        return privateNoiseData;
    }

    std::optional<double> MsDataScan::getIsolationMz() const
    {
        return privateIsolationMz;
    }

    void MsDataScan::setIsolationMz(const std::optional<double> &value)
    {
        privateIsolationMz = value;
    }

    std::optional<int> MsDataScan::getSelectedIonChargeStateGuess() const
    {
        return privateSelectedIonChargeStateGuess;
    }

    std::optional<double> MsDataScan::getSelectedIonIntensity() const
    {
        return privateSelectedIonIntensity;
    }

    void MsDataScan::setSelectedIonIntensity(const std::optional<double> &value)
    {
        privateSelectedIonIntensity = value;
    }

    std::optional<double> MsDataScan::getSelectedIonMZ() const
    {
        return privateSelectedIonMZ;
    }

    void MsDataScan::setSelectedIonMZ(const std::optional<double> &value)
    {
        privateSelectedIonMZ = value;
    }

    std::optional<MassSpectrometry::DissociationType> MsDataScan::getDissociationType() const
    {
        return privateDissociationType;
    }

    std::optional<double> MsDataScan::getIsolationWidth() const
    {
        return privateIsolationWidth;
    }

    std::optional<int> MsDataScan::getOneBasedPrecursorScanNumber() const
    {
        return privateOneBasedPrecursorScanNumber;
    }

    void MsDataScan::setOneBasedPrecursorScanNumber(const std::optional<int> &value)
    {
        privateOneBasedPrecursorScanNumber = value;
    }

    std::optional<double> MsDataScan::getSelectedIonMonoisotopicGuessIntensity() const
    {
        return privateSelectedIonMonoisotopicGuessIntensity;
    }

    void MsDataScan::setSelectedIonMonoisotopicGuessIntensity(const std::optional<double> &value)
    {
        privateSelectedIonMonoisotopicGuessIntensity = value;
    }

    std::optional<double> MsDataScan::getSelectedIonMonoisotopicGuessMz() const
    {
        return privateSelectedIonMonoisotopicGuessMz;
    }

    void MsDataScan::setSelectedIonMonoisotopicGuessMz(const std::optional<double> &value)
    {
        privateSelectedIonMonoisotopicGuessMz = value;
    }

    MzRange *MsDataScan::getIsolationRange() const
    {
        if (isolationRange != nullptr)
        {
            return isolationRange;
        }
        if (getIsolationWidth() && getIsolationMz())
        {
            isolationRange = new MzRange(getIsolationMz().value() - getIsolationWidth().value() / 2, getIsolationMz().value() + getIsolationWidth().value() / 2);
        }
        return isolationRange;
    }

    std::string MsDataScan::ToString()
    {
        return StringHelper::formatSimple("Scan #{0}", getOneBasedScanNumber());
    }

    std::vector<unsigned char> MsDataScan::Get64BitNoiseDataMass()
    {
        return MzSpectrum::Get64Bitarray(GetNoiseDataMass(getNoiseData()));
    }

    std::vector<unsigned char> MsDataScan::Get64BitNoiseDataNoise()
    {
        return MzSpectrum::Get64Bitarray(GetNoiseDataNoise(getNoiseData()));
    }

    std::vector<unsigned char> MsDataScan::Get64BitNoiseDataBaseline()
    {
        return MzSpectrum::Get64Bitarray(GetNoiseDataBaseline(getNoiseData()));
    }

    std::vector<IsotopicEnvelope*> MsDataScan::GetIsolatedMassesAndCharges(MzSpectrum *precursorSpectrum, int minAssumedChargeState, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio)
    {
        if (getIsolationRange() == nullptr)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield break;
        }
        for (auto haha : precursorSpectrum->Deconvolute(new MzRange(getIsolationRange()->Minimum - 8.5, getIsolationRange()->Maximum + 8.5), minAssumedChargeState, maxAssumedChargeState, deconvolutionTolerancePpm, intensityRatio).Where([&] (std::any b)
        {
            b::peaks::Any([&] (std::any cc)
            {
                isolationRange->Contains(cc::mz);
            });
        }))
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return haha;
        }
    }

    void MsDataScan::TransformMzs(std::function<double(MzPeak*)> convertorForSpectrum, std::function<double(MzPeak*)> convertorForPrecursor)
    {
        getMassSpectrum()->ReplaceXbyApplyingFunction(convertorForSpectrum);
        MzPeak tempVar(getSelectedIonMZ().value(), getSelectedIonIntensity().value());
        setSelectedIonMZ(convertorForPrecursor(&tempVar));
        if (getSelectedIonMonoisotopicGuessMz())
        {
            MzPeak tempVar2(getSelectedIonMonoisotopicGuessMz().value(), getSelectedIonMonoisotopicGuessIntensity().value());
            setSelectedIonMonoisotopicGuessMz(convertorForPrecursor(&tempVar2));
        }
        if (getIsolationMz())
        {
            MzPeak tempVar3(getIsolationMz().value(), getSelectedIonIntensity().value());
            setIsolationMz(convertorForPrecursor(&tempVar3));
        }

        // Will need to recompute this...
        isolationRange = nullptr;
    }

    void MsDataScan::RefineSelectedMzAndIntensity(MzSpectrum *precursorSpectrum)
    {
        if (!getIsolationMz())
        {
            throw MzLibException("Could not define precursor ion because the isolation m/z window is undefined in the spectra file");
        }
        if (precursorSpectrum->getSize() == 0)
        {
            throw MzLibException("Could not define precursor ion because the precursor scan contains no peaks");
        }
        auto thePeak = precursorSpectrum->GetClosestPeakIndex(getIsolationMz().value());
        setSelectedIonIntensity(std::make_optional(precursorSpectrum->getYArray()[thePeak.value()]));
        setSelectedIonMZ(std::make_optional(precursorSpectrum->getXArray()[thePeak.value()]));
    }

    void MsDataScan::ComputeSelectedPeakIntensity(MzSpectrum *precursorSpectrum)
    {
        if (precursorSpectrum->getSize() == 0)
        {
            throw MzLibException("Could not compute selected peak intensity because the precursor scan contains no peaks");
        }
        auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMZ().value());
        setSelectedIonIntensity(std::make_optional(precursorSpectrum->getYArray()[thePeak.value()]));
        setSelectedIonMZ(std::make_optional(precursorSpectrum->getXArray()[thePeak.value()]));
    }

    void MsDataScan::ComputeMonoisotopicPeakIntensity(MzSpectrum *precursorSpectrum)
    {
        if (precursorSpectrum->getSize() == 0)
        {
            throw MzLibException("Could not compute monoisotopic peak intensity because the precursor scan contains no peaks");
        }
        auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMonoisotopicGuessMz().value());
        setSelectedIonMonoisotopicGuessIntensity(std::make_optional(precursorSpectrum->getYArray()[thePeak.value()]));
        setSelectedIonMonoisotopicGuessMz(std::make_optional(precursorSpectrum->getXArray()[thePeak.value()]));
    }

    void MsDataScan::setOneBasedPrecursorScanNumber(int value)
    {
        this->setOneBasedPrecursorScanNumber(std::make_optional(value));
    }

    std::vector<double> MsDataScan::GetNoiseDataMass(std::vector<std::vector<double>> &noiseData)
    {
        for (int i = 0; i < noiseData.size() / 3; i++)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return noiseData[0][i];
        }
    }

    std::vector<double> MsDataScan::GetNoiseDataNoise(std::vector<std::vector<double>> &noiseData)
    {
        for (int i = 0; i < noiseData.size() / 3; i++)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return noiseData[1][i];
        }
    }

    std::vector<double> MsDataScan::GetNoiseDataBaseline(std::vector<std::vector<double>> &noiseData)
    {
        for (int i = 0; i < noiseData.size() / 3; i++)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return noiseData[2][i];
        }
    }
}
