#include "ClassExtensions.h"
#include "Interfaces/IHasMass.h"
#include "Constants.h"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace Chemistry {

    double ClassExtensions::ToMz(IHasMass *objectWithMass, int charge) {
        return ToMz(objectWithMass->getMonoisotopicMass(), charge);
    }

    double ClassExtensions::ToMz(double mass, int charge) {
        return mass / std::abs(charge) + sign(charge) * Constants::protonMass;
    }

    double ClassExtensions::ToMass(double massToChargeRatio, int charge) {
        return std::abs(charge) * massToChargeRatio - charge * Constants::protonMass;
    }
}
