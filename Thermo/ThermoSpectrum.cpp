#include "ThermoSpectrum.h"
#include "../MassSpectrometry/MzSpectra/MzPeak.h"

using namespace MassSpectrometry;
namespace IO {
    namespace Thermo {

        ThermoSpectrum::ThermoSpectrum(std::vector<double> &mz, std::vector<double> &intensity, bool shouldCopy) : MzSpectrum<MzPeak>(mz, intensity, shouldCopy) {
        }

        ThermoSpectrum::ThermoSpectrum(const ThermoSpectrum &thermoSpectrum) : ThermoSpectrum(thermoSpectrum->getXArray(), thermoSpectrum->getYArray(), true) {
        }

        ThermoSpectrum::ThermoSpectrum(std::vector<std::vector<double>> &peakData) : MzSpectrum<MzPeak>(peakData) {
        }

        MzPeak *ThermoSpectrum::GeneratePeak(int index) {
            return new MzPeak(getXArray()[index], getYArray()[index]);
        }
    }
}
