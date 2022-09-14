#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "argument_parser.h"

/**
 * Auxiliary types
 */

/**
 * @brief Pointers to the fields needed to define a dynamic array. 
 * Used for dynamic polymorphism of the arrays in the parser struct.
 * 
 */
struct dynamic_string_array {
    char ***arr;
    int *num;
    int *capacity;
};

/**
 * Private methods declarations
 */

void maybe_increase_capacity(char ***vec, int* num, int* capacity);
void _add_argument(char ***vec, int* num, const char* argument, errors *error_var);
struct dynamic_string_array choose_argument_kind(Parser *p, const char* argument);
bool is_valid_string(const char* str);

/**
 * Public methods
 */

/**
 * @brief Create a new argument parser instance by providing the name of the parser
 * 
 * @param name used for visualization purposes
 * @return Parser 
 */
Parser init_parser(const char* name) {
    Parser p;
    if (name == NULL) {
        p.name = NULL;
        p.error_code = NULL_NAME;
        return p;
    }
    p.name = malloc(strlen(name) * sizeof *name);
    strncpy(p.name, name, strlen(name));
    p.positional_args = calloc(DEFAULT_POS_ARGS, sizeof(p.positional_args));
    p.num_positional_args = 0;
    p.capacity_positional_args = DEFAULT_POS_ARGS;
    p.optional_args = calloc(DEFAULT_OPT_ARGS, sizeof(p.optional_args));
    p.num_optional_args = 0;
    p.capacity_optional_args = DEFAULT_OPT_ARGS;
    p.error_code = OK;
    return p;
}

/**
 * @brief destructor for Parser
 * 
 * @param p 
 */
void cleanup_parser(Parser* p) {
    if (p->name != NULL) {
        free(p->name);
    }
    if (p->positional_args != NULL) {
        for (int i = 0; i < p->num_positional_args; i++){
            if (p->positional_args[i] != NULL) {
                free(p->positional_args[i]);
            }
        }
        free(p->positional_args);
    }
    if (p->optional_args != NULL) {
        for (int i = 0; i < p->num_optional_args; i++){
            if (p->optional_args[i] != NULL) {
                free(p->optional_args[i]);
            }
        }
        free(p->optional_args);
    }
}

/**
 * @brief Add an argument to the argument parser
 * 
 * @param p 
 * @param argument argument name. Starts with "-" if optional argument, or with alphabetic characters if positional.
 * @param t 
 */
void add_argument(Parser *p, const char* argument, argument_types t) {
    struct dynamic_string_array s = choose_argument_kind(p, argument);
    
    if (p->error_code == INVALID_ARGUMENT) {
        return;
    }
    
    maybe_increase_capacity(s.arr, s.num, s.capacity);
    _add_argument(s.arr, s.num, argument, &p->error_code);
    (*(s.num))++;
}

// Private functions
struct dynamic_string_array choose_argument_kind(Parser* p, const char* argument) {
    struct dynamic_string_array s;
    if (!is_valid_string(argument)) {
        p->error_code = INVALID_ARGUMENT;
        return s;
    }

    if (argument[0] == '-') {
        s.arr = &p->optional_args;
        s.num = &p->num_optional_args;
        s.capacity = &p->capacity_optional_args;
    } 
    else {
        s.arr = &p->positional_args;
        s.num = &p->num_positional_args;
        s.capacity = &p->capacity_positional_args;
    }
    return s;
}

bool is_valid_string(const char* str) {
    int l = strlen(str);
    for(int i = 0; i < l; i++) {
        char c = str[i];
        if (!(isalpha(c) || c == '-' || c == '_')) {
            return false;
        }
    }
    return true;
}

void maybe_increase_capacity(char ***vec, int* num, int* capacity) {
    if (*num >= *capacity) {
        *vec = realloc(*vec, 2*(*capacity)*sizeof(*vec));
        *capacity *= 2;
    }
}

void _add_argument(char ***vec, int* num, const char* argument, errors *error_var) {
    int i = *num;
    int src_len = strlen(argument);
    (*vec)[i] = calloc(src_len, sizeof((*vec)[i]));
    if ((*vec)[i] == NULL) {
        *error_var = SPACE_INSUFFICIENT;
        return;
    }
    strncpy((*vec)[i], argument, src_len);
}