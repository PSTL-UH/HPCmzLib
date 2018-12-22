#pragma once

#include "IPeak.h"

namespace Spectra {
    class Peak : public IPeak {
    private:
        double privateX = 0;
        double privateY = 0;

//        #region Public Constructors

    public:
        Peak(double x, double y);

//        #endregion Public Constructors

//        #region Public Properties

        double getX() const override;
        void setX(double value) override;
        double getY() const override;
        void setY(double value) override;

//        #endregion Public Properties
    };
}
