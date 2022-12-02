#ifndef STRINGS_H
#define STRINGS_H

typedef struct dynstr {
    char* str;
    size_t capacity;
    size_t len;
} dynstr;

/**
 * @brief Allocates space for a new dynamic string
 * 
 * @param str string content to initialize the new string
 * @param len initial array capacity
 * @return char* pointer to the allocated space in the heap of size len
 */
dynstr make_str(const char* str, size_t capacity);

/**
 * @brief Safely concatenates two strings preventing buffer overflow
 * 
 * @param dest first string to concatenate and output of concatenation
 * @param src string to be concatenated
 * @param n maximum number of characters to concatenate
 * @return char* 
 */
char *safe_strncat(dynstr* dest, const char* src, size_t n);
char *str_concat(const char* dest, const char* src);

#endif