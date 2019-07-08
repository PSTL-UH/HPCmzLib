#include "DigestionPoint.h"

namespace Proteomics {
    namespace AminoAcidPolymer    {

        DigestionPointAndLength::DigestionPointAndLength(int index, int length) {
            setIndex(index);
            setLength(length);
        }
        
        int DigestionPointAndLength::getIndex() const {
            return privateIndex;
        }
        
        void DigestionPointAndLength::setIndex(int value) {
            privateIndex = value;
        }
        
        int DigestionPointAndLength::getLength() const {
            return privateLength;
        }
        
        void DigestionPointAndLength::setLength(int value) {
            privateLength = value;
        }
    }
}
