#include "MzmlSpectrum.h"
#include "MzmlPeak.h"

using namespace MassSpectrometry;
namespace IO {
    namespace MzML {

        MzmlMzSpectrum::MzmlMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : MzSpectrum<MzmlPeak>(mz, intensities, shouldCopy) {
        }

        MzmlPeak *MzmlMzSpectrum::GeneratePeak(int index) {
            return new MzmlPeak(getXArray()[index], getYArray()[index]);
        }
    }
}
