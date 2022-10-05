#include <stdio.h>

/// enum type errors
enum errors {
    FILEWASNTOPEN = -1, ///< parameter FILEWASNOPEN = -1
    RETURNEDNULL = 1, ///< parameter RETURNEDNULL = 1
    NULLPTR = 2 ///<parameter NULLPTR = 2
};

/*!
    \brief This structure contains all information about string
*/
struct string {
    char* beginPtr;
    char* endPtr;
    unsigned int length;
};

/*!
    \brief This function handles the errors and stop the programm if necessary
    \param[in] errors error - type of error
    \param[in] const char* function - name of file where error happened
    \param[in] const char* name - name of function where error happened
    \param[in] const int line - line where error happened
    \param[in] const char* fileName - name of file with error 
*/
void processor_of_errors(errors error, const char* function, const char* name, const int line, const char* fileName);

/*!
    \brief This function calculates size of file 
    \param[in] FILE* stream - pointer to the stream of data
    \return long unsigned int number - size of file
*/
long unsigned int get_size(FILE* stream);

/*!
    \brief This function calculates number of lines (strings) in file
    \param[in] char* buffer - array of chars (buffer)
    \return unsigned int number - number of lines (strings)
*/
unsigned int amount_of_strings(char* buffer);

/*!
    \brief This function reads data from file and saves it to buffer
    \param[in] const char* name = name of input file
    \return char* pointer - pointer to begin of array with data  
*/
char* get_buffer(const char* name);

/*!
    \brief This function creates array of struct string and fills in the fields for each element
    \param[in] char* buffer - array of chars (buffer of data)
    \param[in] unsigned int size - size of array of struct string 
    \return struct string* pointer - pointer to begin of struct string array
*/
struct string* get_strings(char* buffer, unsigned int size);

/*!
    \brief This function creates array of pointers of struct string
    \param[in] struct string* strings - array of struct strings
    \param[in] unsigned int size - size of array
    \return struct string** - array of pointers of each elements in array of struct string* strings
*/
struct string** get_array(struct string* strings, unsigned int size);

/*!
    \brief This function reads name of file from stdinput and writes text (as given parameter) to stdoutput
    \param[in] const char* text - text
    \return char* value - name of read file
*/
char* get_name_stdin(const char* text);

/*!
    \brief This function compares two elements (two strings from begin) and returnes 1 if first > second, -1 if first < second and 0 if first == second
    \param[in] const void* first - pointer to a first element
    \param[in] const void second - pointer to a second element
    \return int value - result of compare

*/
int string_comparator_begin(const void* first, const void* second);

/*!
    \brief This functions compares two elements (two strings from end) and returnes 1 if first > second, -1 if first < second and 0 if first == second
    \param[in] const void* first - pointer to a first element
    \param[in] const void second - pointer to a second element
    \return int value - result of compare
*/
int string_comporator_end(const void* first, const void* second);

/*!
    \brief This function outputs sorted data to output file
    \param[in] struct string** - sorted array of pointers
    \param[in] unsigned int size - size of array
    \param[in] const char* name - name of output file
*/
void output(struct string** array, unsigned int size, const char* name);

