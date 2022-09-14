#ifndef TEST_H
#define TEST_H 

#include <stdio.h>

/**
 * @brief Code for automating unit tests from 
 * https://eradman.com/posts/tdd-in-c.html
 * 
 */
#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define FAIL_EXPECTED_STR(value, expected) do { printf("\nexpected %s but found %s", expected, value); FAIL(); } while (0);
#define FAIL_EXPECTED_INT(value, expected) do { printf("\nexpected %d but found %d", expected, value); FAIL(); } while (0);
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _assert_str_eq(value, expected, N) do { if (strncmp((value), (expected), (N))) { FAIL_EXPECTED_STR(value, expected); return 1; } } while(0)
#define _assert_primitive_eq(value, expected) do { if ((value) != (expected)) { FAIL_EXPECTED_INT(value, expected); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; else printf("%s passed!\n", #test);} while(0)

#endif