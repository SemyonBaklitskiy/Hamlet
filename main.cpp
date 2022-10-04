#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

#ifdef MYSORT
    #include "sort.h"
#endif

int main() {
    char* name = get_name_stdin("Enter name of input file (or enter D to use default file (Hamlet.txt)): ");

    char* buffer = NULL;

    if (name[0] == 'D') {
        buffer = get_buffer("Hamlet.txt");

    }   else {
        buffer = get_buffer(name);
    }

    free(name);

    unsigned int size = amount_of_strings(buffer);
    string* strings = get_strings(buffer, size);
    string** arrayPtr = get_array(strings, size);

#ifndef MYSORT

    char* name1 = get_name_stdin("Enter name of output file1 (sort from begin): ");
    qsort(arrayPtr, size, sizeof(string*), string_comparator_begin);
    output(arrayPtr, size, name1);

    char* name2 = get_name_stdin("Enter name of output file2 (sort from end): ");
    qsort(arrayPtr, size, sizeof(string*), string_comporator_end);
    output(arrayPtr, size, name2);

#else

    char* name1 = get_name_stdin("Enter name of output file1 (sort from begin): ");
    my_sort(arrayPtr, 0, size - 1, sizeof(string*), string_comparator_begin);
    output(arrayPtr, size, name1);

    char* name2 = get_name_stdin("Enter name of output file2 (sort from end): ");
    my_sort(arrayPtr, 0, size - 1, sizeof(string*), string_comporator_end);
    output(arrayPtr, size, name2);
    
#endif
    
    free(arrayPtr);
    free(strings);
    free(buffer);
    free(name1);
    free(name2);

    return 0;
}