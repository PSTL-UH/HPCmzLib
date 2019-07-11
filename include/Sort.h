#pragma once

#include <vector>

class Sort{
public:

    static void SortPairs(std::vector<double> &keys,
                          std::vector<double> &values, int size) {
        return BubbleSortPairs ( keys, values, size );
    }

    static void BubbleSortPairs(std::vector<double> &keys,
                                std::vector<double> &values, int size) {
        // Sort an array of values based on the keys provided.
        double tempkey, tempvalue;
        
        for ( int i=0; i< (size-1); i++ ) {
            for (int j=0; j <(size-1); j++ ) {
                if ( keys[j] > keys[j+1] ) {
                    tempkey     = keys[j+1];
                    tempvalue   = values[j+1];
                    keys[j+1]   = keys[j];
                    values[j+1] = values[j];
                    keys[j]     = tempkey;
                    values[j]   = tempvalue;
                }
            }
        }
    }  
};
