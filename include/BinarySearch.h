#include <vector>

#define ACCURACY 1e-9

template <typename T>
int binarySearch(std::vector<T>& array, T element)
{
    int left = 0, right = array.size() - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        // If element being searched for is the middle value, return its index
        if (std::abs(array[middle] - element) <= ACCURACY) 
            return middle;

        // if element being searched for is less than the middle element,
        // restrict search space to values smaller than the middle value
        else if (element < array[middle])
            right = middle - 1;

        // if element being searched for is greater than the mid element, 
        // restrict search space to values greater than the middle element
        else
            left = middle + 1;
    }

    // If element not present in array, the bitwise complement of the next highest index is returned.  
    // If the element is larger than the largest element in the array, the bitwise complement of the highest index + 1 is returned
    // If the element is smaller than the smallest element in the array, the bitwise complement of the lowest index is returned
    return ~left;
} 