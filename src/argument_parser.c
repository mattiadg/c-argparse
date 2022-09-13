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
    p.positional_args = NULL;
    p.num_positional_args = 0;
    p.capacity_positional_args = DEFAULT_POS_ARGS;
    p.optional_args = NULL;
    return p;
}

void add_argument(Parser *p, const char* argument, argument_types t) {
    if (p->positional_args == NULL) {
        p->positional_args = calloc(DEFAULT_POS_ARGS, sizeof p->positional_args);
    }
    if (p->num_positional_args >= p->capacity_positional_args) {
        p->positional_args = realloc(p->positional_args, 2*p->capacity_positional_args*sizeof(p->positional_args));
        p->capacity_positional_args *= 2;
    }
    int i = p->num_positional_args;
    p->positional_args[i] = calloc((strlen(argument)), sizeof *p->positional_args);
    if (p->positional_args[i] == NULL) {
        p->error_code = SPACE_INSUFFICIENT;
        return;
    }
    strncpy(p->positional_args[i], argument, strlen(argument));
    p->num_positional_args++;
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