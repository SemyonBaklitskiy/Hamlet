#include "sort.h"
#include "functions.h"

void my_sort(void* array, int start, int end, unsigned int sizeBytes, int (*comparator)(const void*, const void*)) {
    if (array == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);
    
    if (start >= end) {
        return;
    }

    int pivot = partition(array, start, end, sizeBytes, comparator);
    my_sort(array, start, pivot - 1, sizeBytes, comparator);
    my_sort(array, pivot + 1, end, sizeBytes, comparator);
}

void swap(void* element1, void* element2, unsigned int sizeBytes) {
    if (element1 == NULL || element2 == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    char* a = (char*)element1;
    char* b = (char*)element2;

    do {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--sizeBytes > 0);
    
}

int partition(void* array, int start, int end, unsigned int sizeBytes, int (*comparator)(const void*, const void*)) {
    if (array == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

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