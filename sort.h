/*!
    \brief This is my analogue of qsort
    \param[out] void* array - pointer to a begin of array that will be sorted
    \param[in] int start - left border of the array
    \param[in] int end - right border of the array
    \param[in] unsigned int sizeBytes - size of each element of the array in bytes
    \param[in] int (*comparator) - pointer to a comare function
*/
void my_sort(void* array, int start, int end, unsigned int sizeBytes, int (*comparator)(const void*, const void*));

