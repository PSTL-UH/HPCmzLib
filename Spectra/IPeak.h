#pragma once

namespace Spectra {
    class IPeak {

    public:
        virtual double getX() const = 0;
        virtual double getY() const = 0;

    };
}
