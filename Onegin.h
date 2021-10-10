#pragma once

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctype.h>


struct String { // String
    char* start = NULL;
    int length = 0;
};

 struct Text {
     struct String* strings;
     size_t file_size = NULL;
     int n_strings = 0;
     char* file_name;
     char* buffer = NULL;
 };
//const int MAXSTRINGS = 10000;
const int MAXLINE = 1000;

enum errors {FILE_NOT_OPEN = -1, WRONG_FILE_READING = -2};


int text_init(struct Text* text);
/**
 * Counts bytes in it.
 *
 * Do not forget to close file and free the buffer!

 * @param [out] k_bytes Pointer to count of bytes in file
 * @param [in] pointer_to_file Pointer to pointer to file.
 */
//int get_file_size(size_t* k_bytes, FILE* point_to_file);
int get_file_size(struct Text* text);

/**
 * Reads strings from the file and puts them in the "buffer".
 */
int read_from_file(char* buffer, size_t k_bytes, FILE* point_to_file);

int count_strings(struct Text* text);

/**
 * Separates "buffer" to different strings.
 */
int serarate_to_strings(struct Text* text);

/**
 * Counts string length, writes pointer to each string.
 */
int my_getline2(char* filestream);

/**
 * Sorts file (sorted by the beginning of strings(alphabetically)).
 */
int sort_file(struct Text* text);
/**
 * Prints strings of the sorted file.
 */
int print_sort_file(const char** index, int n_strings);

/**
 * Checks if symbol is appropriate.
 */
int is_write_symbol(char sym);

/**
 * Sorts file (sorted by the end of strings(alphabetically)).
 */
int reverse_sort_file(struct Text* text);

/**
 * Writes in new file first sorted file(sorted by the beginning of strings(alphabetically).
 */
int write_new_file(struct Text* text, const char* name);

/**
 * Writes in new file(already created, just add new information in it) second sorted file(sorted by the end of strings(alphabetically) and
 * the original file text. // params, returns
 */
int add_to_new_file(struct Text* text, const char* name);

int comparator(const void* str1, const void* str2);
