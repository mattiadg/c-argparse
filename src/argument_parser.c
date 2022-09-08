#include <string.h>
#include "argument_parser.h"

Parser init_parser(char* name) {
    Parser p;
    strncpy(p.name, name, 100);
    p.positional_args = NULL;
    p.optional_args = NULL;
    return p;
}
