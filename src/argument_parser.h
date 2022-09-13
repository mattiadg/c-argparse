#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#define MAX_NAME_LENGTH 20

#define DEFAULT_POS_ARGS 5

enum errors {NULL_NAME, SPACE_INSUFFICIENT};
typedef enum {STR, INT, FLOAT} argument_types;

typedef struct {
    char* name;
    char** positional_args;
    int num_positional_args;
    int capacity_positional_args;
    char** optional_args;
    enum errors error_code;
} Parser;

Parser init_parser(const char* name);
void cleanup_parser(Parser* p);

void add_argument(Parser *p, const char* argument, argument_types t);

#endif