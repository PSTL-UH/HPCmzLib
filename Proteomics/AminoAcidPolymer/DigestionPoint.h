#pragma once

namespace Proteomics {
    namespace AminoAcidPolymer    {

        class DigestionPointAndLength {
        private:
            int privateIndex = 0;
            int privateLength = 0;
            
        public:
            DigestionPointAndLength(int index, int length);
            
            int getIndex() const;
            void setIndex(int value);
            int getLength() const;
            void setLength(int value);
        };
    };
}
