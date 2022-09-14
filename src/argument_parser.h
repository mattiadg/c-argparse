#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#define MAX_NAME_LENGTH 20

#define DEFAULT_POS_ARGS 5
#define DEFAULT_OPT_ARGS 5

typedef enum {OK, NULL_NAME, INVALID_ARGUMENT, SPACE_INSUFFICIENT} errors;
typedef enum {STR, INT, FLOAT} argument_types;

typedef struct {
    char* name;
    char** positional_args;
    int num_positional_args;
    int capacity_positional_args;
    char** optional_args;
    int num_optional_args;
    int capacity_optional_args;
    errors error_code;
} Parser;

Parser init_parser(const char* name);
void cleanup_parser(Parser* p);

void add_argument(Parser *p, const char* argument, argument_types t);

#endif