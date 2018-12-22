#include "ClassExtensions.h"
#include "Interfaces/IHasMass.h"
#include "Constants.h"


namespace Chemistry {

    double ClassExtensions::ToMz(IHasMass *objectWithMass, int charge) {
        return ToMz(objectWithMass->getMonoisotopicMass(), charge);
    }

    double ClassExtensions::ToMz(double mass, int charge) {
        return mass / std::abs(charge) + Math::Sign(charge) * Constants::protonMass;
    }

    double ClassExtensions::ToMass(double massToChargeRatio, int charge) {
        return std::abs(charge) * massToChargeRatio - charge * Constants::protonMass;
    }
}
