#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include "functions.h"

long unsigned int get_size(FILE* stream) {
    if (stream == NULL) 
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    struct stat buf;
    fstat(stream->_fileno, &buf);

    return buf.st_size / sizeof(char);
}

unsigned int amount_of_strings(char* buffer) {
    if (buffer == NULL)
        
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    unsigned int amount = 0; 

    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            ++amount;
        }
    }

    return amount + 1;
}

void put_pointers(char* buffer, struct string* array) {
    if (buffer ==  NULL || array == NULL) 
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    array[0].beginPtr = &buffer[0];

    int arrayIndex = 1;
    int bufferIndex;  

    for (bufferIndex = 0; buffer[bufferIndex] != '\0'; ++bufferIndex) {
        if (buffer[bufferIndex] == '\n') {
            array[arrayIndex - 1].endPtr = &buffer[bufferIndex];
            array[arrayIndex - 1].length = (unsigned int)(array[arrayIndex - 1].endPtr - array[arrayIndex - 1].beginPtr) + 1;
            array[arrayIndex].beginPtr = &buffer[bufferIndex + 1];
            ++arrayIndex; 
        }
    }

    array[arrayIndex - 1].endPtr = &buffer[bufferIndex];
    array[arrayIndex - 1].length = (unsigned int)(array[arrayIndex - 1].endPtr - array[arrayIndex - 1].beginPtr) + 1;
}

char* get_buffer(const char* name) {
    if (name == NULL) {
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);
    }

    FILE* file = fopen(name, "r");

    if (!file_is_open(file)) 
        processor_of_errors(FILEWASNTOPEN, __FILE__, __PRETTY_FUNCTION__, __LINE__, name);

    long unsigned int size = get_size(file);

    char* buffer = (char*)calloc(size + 1, sizeof(char));

    if (buffer == NULL) 
        processor_of_errors(RETURNEDNULL, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    fread(buffer, sizeof(char), size, file);

    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

struct string* get_strings(char* buffer, unsigned int size) {
    if (buffer == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    struct string* strings = (string*)calloc(size, sizeof(string));

    if (strings == NULL) 
        processor_of_errors(RETURNEDNULL, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    put_pointers(buffer, strings);

    return strings;
}

struct string** get_array(struct string* strings, unsigned int size) {
    if (strings == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    struct string** arrayPtr = (struct string**)calloc(size, sizeof(struct string*));

    if (arrayPtr == NULL) 
        processor_of_errors(RETURNEDNULL, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    for (unsigned int i = 0; i < size; ++i) 
        arrayPtr[i] = &strings[i];
    
    return arrayPtr;
}

char* get_name_stdin(const char* text) {
    char* name = NULL;

    if (text == NULL) {
        scanf("%ms[\n]", &name);

    } else {
        printf("%s", text);
        scanf("%ms[\n]", &name);
    }
    
    return name;
}

int string_comparator_begin(const void* first, const void* second) {
    if (first == NULL || second == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    char* str1 = (*((string**)first))->beginPtr;
    char* str2 = (*((string**)second))->beginPtr;

    unsigned int length1 = (*((string**)first))->length;
    unsigned int length2 = (*((string**)second))->length;

    if (str1[0] == '\0' || str1[0] == '\n') {
        return -1;

    } else if (str2[0] == '\0' || str2[0] == '\n') {
        return 1;
    }

    unsigned int str1Index;
    unsigned int str2Index;

    for (str1Index = 0, str2Index = 0; str1[str1Index] != '\n' && str1[str1Index] != '\0'
                                    && str2[str2Index] != '\n' && str2[str2Index] != '\0'; 
                                    ++str1Index, ++str2Index) {

        if ((number_of_letter(str1[str1Index]) != -1) && (number_of_letter(str2[str2Index]) != -1)) {
            if (number_of_letter(str1[str1Index]) != number_of_letter(str2[str2Index])) 
                return number_of_letter(str1[str1Index]) - number_of_letter(str2[str2Index]);

        } else if ((number_of_letter(str1[str1Index]) == -1) && (number_of_letter(str2[str2Index]) == -1)) {
            --length2; 
            --length1;  

        } else if (number_of_letter(str2[str2Index]) == -1) {
            --length2;
            --str1Index;

        } else if (number_of_letter(str1[str1Index]) == -1) {
            --length1;
            --str2Index; 
        }
    }
    
    return length1 - length2; 
}

int string_comporator_end(const void* first, const void* second) {
    if (first == NULL || second == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL); 

    char* str1 = (*((string**)first))->beginPtr;
    char* str2 = (*((string**)second))->beginPtr;

    unsigned int length1 = (*((string**)first))->length;
    unsigned int length2 = (*((string**)second))->length;
    
    const unsigned int constLength1 = length1;
    const unsigned int constLength2 = length2;

    if (str1[0] == '\0' || str1[0] == '\n') {
        return -1;

    } else if (str2[0] == '\0' || str2[0] == '\n') {
        return 1;
    }

    unsigned int str1Index;
    unsigned int str2Index;
    unsigned int counter1 = 0;
    unsigned int counter2 = 0;

    bool stop = ((counter1 < constLength1) && (counter2 < constLength2));

    for (str1Index = length1 - 1, str2Index = length2 - 1; stop; --str1Index, --str2Index) {
        if ((number_of_letter(str1[str1Index]) != -1) && (number_of_letter(str2[str2Index]) != -1)) {
            if (number_of_letter(str1[str1Index]) != number_of_letter(str2[str2Index])) 
                return number_of_letter(str1[str1Index]) - number_of_letter(str2[str2Index]);

        } else if ((number_of_letter(str1[str1Index]) == -1) && (number_of_letter(str2[str2Index]) == -1)) {
            --length1;
            --length2;
        
        } else if (number_of_letter(str2[str2Index]) == -1) {
            --length2;
            ++str1Index;

        } else if (number_of_letter(str1[str1Index]) == -1) {
            --length1;
            ++str2Index;
        }

        ++counter1;
        ++counter2;
        stop = ((counter1 < constLength1) && (counter2 < constLength2));
    }

    return length1 - length2;   
}

void output(struct string** array, unsigned int size, const char* name) {
    if (array == NULL || name == NULL)
        processor_of_errors(NULLPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__, NULL);

    FILE* file = fopen(name, "w");

    if (!file_is_open(file)) 
        processor_of_errors(FILEWASNTOPEN, __FILE__, __PRETTY_FUNCTION__, __LINE__, name);

    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < array[i]->length; ++j) {
            if (array[i]->beginPtr[j] != '\0') 
                putc(array[i]->beginPtr[j], file);
            else 
                putc('\n', file);
        }
    }

    fclose(file);
}

bool file_is_open(FILE* stream) {
    if (stream == NULL) 
        return false;

    return true;   
}

int number_of_letter(const char c) {
    const char letters[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

    for (int i = 0; letters[i] != '\0'; ++i) {
        if (c == letters[i])
            return i;
    }

    return -1;
}

void processor_of_errors(errors error, const char* function, const char* name, const int line, const char* fileName) {
    switch (error) {

    case RETURNEDNULL:
        printf("In file %s function %s line %d: calloc returned NULL, programm finished\n", function, name, line);
        exit(error);
        break;

    case FILEWASNTOPEN:
        printf("In file %s function %s line %d: file %s wasn`t open, programm finished\n", function, name, line, fileName);
        break;

    case NULLPTR:
        printf("In file %s function %s line %d: NULL was given as a parameter, programm finished\n", function, name, line);
        break;

    default:
        break;
    }

    assert(0); 
}


