#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#define MAX_NAME_LENGTH 20 

typedef struct {
    char* name;
    char** positional_args;
    char** optional_args;
} Parser;

Parser init_parser(char* name);

#endif