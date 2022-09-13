#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "argument_parser.h"

Parser init_parser(const char* name) {
    Parser p;
    if (name == NULL) {
        p.name = NULL;
        p.error_code = NULL_NAME;
        return p;
    }
    p.name = malloc(strlen(name) * sizeof *name);
    strncpy(p.name, name, strlen(name));
    p.positional_args = calloc(DEFAULT_POS_ARGS, sizeof p.positional_args);
    p.num_positional_args = 0;
    p.capacity_positional_args = DEFAULT_POS_ARGS;
    p.optional_args = calloc(DEFAULT_POS_ARGS, sizeof p.optional_args);
    p.num_optional_args = 0;
    p.capacity_optional_args = DEFAULT_OPT_ARGS;
    return p;
}

void maybe_increase_capacity(char ***vec, int* num, int* capacity);
void _add_argument(char ***vec, int* num, const char* argument, errors *error_var);

void add_argument(Parser *p, const char* argument, argument_types t) {
    maybe_increase_capacity(&p->positional_args, &p->num_positional_args, &p->capacity_positional_args);
    _add_argument(&p->positional_args, &p->num_positional_args, argument, &p->error_code);
    p->num_positional_args++;
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
    (*vec)[i] = calloc(src_len, sizeof *vec[i]);
    if ((*vec)[i] == NULL) {
        *error_var = SPACE_INSUFFICIENT;
        return;
    }
    strncpy((*vec)[i], argument, src_len);
}

void cleanup_parser(Parser* p) {
    if (p->name != NULL) {
        free(p->name);
    }
    if (p->positional_args != NULL) {
        free(p->positional_args[0]);
        free(p->positional_args);
    }
}