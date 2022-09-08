#ifndef ARGUMENT_PARSER_H

typedef struct {
    char* name;
    char** positional_args;
    char** optional_args;
} Parser;

Parser init_parser(char* name);

#endif