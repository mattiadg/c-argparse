#ifndef TEST_H
#define TEST_H 

#include <stdio.h>

/**
 * @brief Code for automating unit tests from 
 * https://eradman.com/posts/tdd-in-c.html
 * 
 */
#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

#endif