﻿#pragma once

#include "IPeak.h"

namespace Spectra {
    class Peak : public virtual IPeak {
    private:
        double privateX = 0;
        double privateY = 0;

    public:
        Peak();
        Peak(double x, double y);

        double getX() const override;
        void setX(double value);
        double getY() const override;
        void setY(double value);

    };
}
