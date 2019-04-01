#include "MsDataFile.h"

using namespace MzLibUtil;

namespace MassSpectrometry {

    template<typename TScan>
    int MsDataFile<TScan>::ReverseComparer::Compare(double x, double y) {
        if ( x == y ) {
            return 0;
        }
        else if ( x < y ) {
            return -1;
        }
        return 1;
    }
}
