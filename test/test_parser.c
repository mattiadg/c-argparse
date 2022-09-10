#include <string.h>
#include "test_parser.h"
#include "../src/argument_parser.h"

int all_tests() {
    _verify(test_init_parser);
    return 0;
}

int test_init_parser(){
    Parser parser = init_parser("a name");
    _assert(!strncmp(parser.name, "a name", strlen("a name")));
    _assert(parser.positional_args == NULL);
    _assert(parser.optional_args == NULL);

}

int main(int argc, char** argv) {
    int r = all_tests();
    if (r == 0) {
        printf("PASSED");
    }
    return 0;
}