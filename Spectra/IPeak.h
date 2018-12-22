#pragma once

namespace Spectra {
    class IPeak {
//        #region Public Properties

    public:
        virtual double getX() const = 0;
        virtual double getY() const = 0;

//        #endregion Public Properties
    };
}
