#include "sort.h"
#include "functions.h"
#define my_assert(condition, error) processor_of_errors(condition, error, __FILE__, __PRETTY_FUNCTION__, __LINE__)

/*!
    \brief This function swaps two elements
    \param[in] void* element1 - pointer to a first element
    \param[in] void* element2 - pointer to a second element
    \param[in] unsigned int sizeBytes - size of each element in bytes
*/
static void swap(void* element1, void* element2, unsigned int sizeBytes) {
    my_assert(element1 != NULL && element2 != NULL, NULLPTR);

    char* a = (char*)element1;
    char* b = (char*)element2;

    do {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--sizeBytes > 0);
    
}

/*!
    \brief This function divides array on 2 parts
    \param[in] void* array - pointer to a begin of array
    \param[in] int start - left border of the array
    \param[in] int end - right border of the array
    \param[in] unsigned int sizeBytes - size of each element of the array in bytes
    \param[in] int (*comparator) - pointer to a comare function
*/
static int partition(void* array, int start, int end, unsigned int sizeBytes, int (*comparator)(const void*, const void*)) {
    my_assert(array != NULL, NULLPTR);

    void* pivot = array + end * sizeBytes;
    int pIndex = start;

    for (int i = start; i < end; ++i) {
        if ((comparator(array + i * sizeBytes, pivot) <= 0)) {
            swap((void*)(array + i * sizeBytes), (void*)(array + pIndex * sizeBytes), sizeBytes);
            ++pIndex;
        }
    }

    swap((void*)(array + pIndex * sizeBytes), (void*)(array + end * sizeBytes), sizeBytes);

    return pIndex;
}

void my_sort(void* array, int start, int end, unsigned int sizeBytes, int (*comparator)(const void*, const void*)) {
    my_assert(array != NULL, NULLPTR);
    
    if (start >= end) {
        return;
    }

    int pivot = partition(array, start, end, sizeBytes, comparator);
    my_sort(array, start, pivot - 1, sizeBytes, comparator);
    my_sort(array, pivot + 1, end, sizeBytes, comparator);
}


