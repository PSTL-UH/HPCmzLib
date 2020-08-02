#pragma once
#include <algorithm>
#include <vector>

class Sort{
public:
    template <class TKEY, class TVAL>
    static void SortPairs(std::vector<TKEY> &keys,
                          std::vector<TVAL> &values, int size) {
        // return BubbleSortPairs ( keys, values, size );
        return HeapSortPairs ( keys, values, size );
    }
    
    template <class TKEY, class TVAL>
    static void BubbleSortPairs(std::vector<TKEY> &keys,
                                std::vector<TVAL> &values, int size) {
        // Sort an array of values based on the keys provided.
        TKEY tempkey;
        TVAL tempvalue;
        
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

    template <class TKEY, class TVAL>
    static void CreateHeap(std::vector<TKEY> &keys, std::vector<TVAL> &values, int size, int i) { 
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

    template <class TKEY, class TVAL>
    static void HeapSortPairs(std::vector<TKEY> &keys, std::vector<TVAL> &values, int size) {
        // Sort an array of values based on the keys provided using the Heap Sort algotithm.
        for (int i = size / 2 - 1; i >= 0; i--) 
            CreateHeap(keys, values, size, i); 

        for (int i = size-1; i >= 0; i--) 
        { 
            std::swap(keys[0], keys[i]); 
            std::swap(values[0], values[i]); 
            CreateHeap(keys, values, i, 0); 
        } 

        //The C# version seems to ensure that for equal keys the values are presented in incrementing order.
        for ( int i=0; i < size-2; i++ ) {
            if ( keys[i] == keys[i+1] &&
                 values[i] > values[i+1] ) {
                std::swap(keys[i], keys[i+1]);
                std::swap(values[i], values[i+1]);
            }
        }
    }
};
