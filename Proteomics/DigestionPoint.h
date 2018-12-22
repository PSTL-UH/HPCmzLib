#pragma once

namespace Proteomics {
    class DigestionPointAndLength {
    private:
        int privateIndex = 0;
        int privateLength = 0;

//        #region Public Constructors

    public:
        DigestionPointAndLength(int index, int length);

//        #endregion Public Constructors

//        #region Public Properties

        int getIndex() const;
        void setIndex(int value);
        int getLength() const;
        void setLength(int value);

//        #endregion Public Properties
    };
}
