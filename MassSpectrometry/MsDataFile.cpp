#include "MsDataFile.h"

using namespace MzLibUtil;

namespace MassSpectrometry {

    int MsDataFile<TScan>::ReverseComparer::Compare(double x, double y) {
        return y.CompareTo(x);
    }
}
