#include "Peak.h"

namespace Spectra {

    Peak::Peak() {
        setX((double)0);
        setY((double)0);
    }

    Peak::Peak(double x, double y) {
        setX(x);
        setY(y);
    }

    double Peak::getX() const {
        return privateX;
    }

    void Peak::setX(double value) {
        privateX = value;
    }

    double Peak::getY() const {
        return privateY;
    }

    void Peak::setY(double value) {
        privateY = value;
    }
}
