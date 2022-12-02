#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strings.h"

dynstr make_str(const char* str_content, size_t capacity) {
    if (capacity <= 0) {
        dynstr empty = { .str = "", .capacity = 0, .len = 0};
        return empty;
    }

    char* s = calloc(capacity, sizeof(str_content));
    strncpy(s, str_content, capacity);
    dynstr str = { .str = s, .capacity = capacity, .len = strlen(s)};
    return str;
}

char *safe_strncat(dynstr* dest, const char* src, size_t n) {
    if (dest->len + n > dest->capacity) {
        dest->str = realloc(dest->str, dest->len + n);
    }

    strncat(dest->str, src, n);
    return dest->str;
}

char *str_concat(const char* dest, const char* src) {
    int len_dest = strlen(dest);
    int len_src = strlen(src);

    char* new_str = calloc(len_dest + len_src + 1, sizeof('a'));
    strncpy(new_str, dest, len_dest + 1);

    if (dest != NULL) {
        strncat(new_str, src, len_src);
    }
    return new_str;    
}