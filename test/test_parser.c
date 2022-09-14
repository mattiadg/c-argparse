#include <stdio.h>
#include <string.h>
#include "test_parser.h"
#include "../src/argument_parser.h"

/** 
 * Test function declarations 
 */
int test_init_parser();
int test_init_parser_null_name();
int test_add_positional_argument();
int test_add_2_positional_argument();
int test_add_6_positional_argument();
int test_add_optional_argument();
int test_add_2_optional_argument();
int test_add_6_optional_argument();
int test_add_invalid_argument();

/**
 * Function definitions
 */

/**
 * @brief Registers all the test functions to call
 * 
 * @return int 0 means that it passed without errors
 */
int all_tests() {
    _verify(test_init_parser);
    _verify(test_init_parser_null_name);
    _verify(test_add_positional_argument);
    _verify(test_add_2_positional_argument);
    _verify(test_add_6_positional_argument);
    _verify(test_add_optional_argument);
    _verify(test_add_2_optional_argument);
    _verify(test_add_6_optional_argument);
    _verify(test_add_invalid_argument);
    return 0;
}

int test_init_parser(){
    Parser parser = init_parser("a name");
    _assert(!strncmp(parser.name, "a name", strlen("a name")));
    return 0;
}

int test_init_parser_null_name(){
    Parser parser = init_parser(NULL);
    _assert(parser.name == NULL);
    _assert(parser.error_code == NULL_NAME);
    return 0;
}

int test_add_positional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "argument", INT);
    _assert_str_eq(parser.positional_args[0], "argument", strlen("argument"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_2_positional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "argument", INT);
    add_argument(&parser, "another", STR);
    _assert_str_eq(parser.positional_args[0], "argument", strlen("argument"));
    _assert_str_eq(parser.positional_args[1], "another", strlen("another"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_6_positional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "a", INT);
    add_argument(&parser, "b", STR);
    add_argument(&parser, "c", STR);
    add_argument(&parser, "d", STR);
    add_argument(&parser, "e", STR);
    add_argument(&parser, "f", STR);
    _assert_str_eq(parser.positional_args[0], "a", strlen("a"));
    _assert_str_eq(parser.positional_args[1], "b", strlen("b"));
    _assert_str_eq(parser.positional_args[2], "c", strlen("c"));
    _assert_str_eq(parser.positional_args[3], "d", strlen("d"));
    _assert_str_eq(parser.positional_args[4], "e", strlen("e"));
    _assert_str_eq(parser.positional_args[5], "f", strlen("f"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_optional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "-argument", INT);
    _assert_str_eq(parser.optional_args[0], "-argument", strlen("-argument"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_2_optional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "-argument", INT);
    add_argument(&parser, "-another", STR);
    _assert_str_eq(parser.optional_args[0], "-argument", strlen("-argument"));
    _assert_str_eq(parser.optional_args[1], "-another", strlen("-another"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_6_optional_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, "-a", INT);
    add_argument(&parser, "-b", STR);
    add_argument(&parser, "-c", STR);
    add_argument(&parser, "-d", STR);
    add_argument(&parser, "-e", STR);
    add_argument(&parser, "-f", STR);
    _assert_str_eq(parser.optional_args[0], "-a", strlen("-a"));
    _assert_str_eq(parser.optional_args[1], "-b", strlen("-b"));
    _assert_str_eq(parser.optional_args[2], "-c", strlen("-c"));
    _assert_str_eq(parser.optional_args[3], "-d", strlen("-d"));
    _assert_str_eq(parser.optional_args[4], "-e", strlen("-e"));
    _assert_str_eq(parser.optional_args[5], "-f", strlen("-f"));
    cleanup_parser(&parser);
    return 0;
}

int test_add_invalid_argument(){
    Parser parser = init_parser("a name");
    add_argument(&parser, ".argument", INT);
    _assert_primitive_eq(parser.error_code, INVALID_ARGUMENT);
    cleanup_parser(&parser);
    return 0;
}

int main(int argc, char** argv) {
    int r = all_tests();
    if (r == 0) {
        printf("PASSED");
    }
    else {
        printf("failed %d tests", r);
    }
    return 0;
}