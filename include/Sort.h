#pragma once
#include <algorithm>
#include <vector>

class Sort{
public:

    static void SortPairs(std::vector<double> &keys,
                          std::vector<double> &values, int size) {
        // return BubbleSortPairs ( keys, values, size );
        return HeapSortPairs ( keys, values, size );
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

    static void CreateHeap(std::vector<double> &keys, std::vector<double> &values, int size, int i) { 
        int largest = i;
        int left = 2*i + 1; 
        int right = 2*i + 2; 
      
        if (left < size && keys[left] > keys[largest]) {
            largest = left; 
        }
      
        if (right < size && keys[right] > keys[largest]) {
            largest = right; 
        }
      
        if (largest != i) 
        { 
            std::swap(keys[i], keys[largest]);
            std::swap(values[i], values[largest]);  
            CreateHeap(keys, values, size, largest); 
        } 
    } 

    static void HeapSortPairs(std::vector<double> &keys, std::vector<double> &values, int size) {
        // Sort an array of values based on the keys provided using the Heap Sort algotithm.
        for (int i = size / 2 - 1; i >= 0; i--) 
            CreateHeap(keys, values, size, i); 

        for (int i = size-1; i >= 0; i--) 
        { 
            std::swap(keys[0], keys[i]); 
            std::swap(values[0], values[i]); 
            CreateHeap(keys, values, i, 0); 
        } 
    }
};
