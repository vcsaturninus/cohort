#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <setjmp.h>

#ifndef MOCOHORT_H
#define MOCOHORT_H

/* ****************************************************************************
    ===========================================================================
    --------------------- Cohort - simple C test runner -----------------------
    ===========================================================================

   This is a casual testing module and functionality is deliberately left basic. 
   Having a full-blown test framework that is complicated to use is often a
   deterrent from testing one's code. This module aims to be convenient and 
   extremely simple to use, without any bells and whistles. The best way to use
   this is to put the tests in a file and compile and run it when building
   the program e.g. with make by way of sanity-testing it.

   
   Features and functionality
   ---------------------------

   In a nutshell, the module offers a test runner that will iterate over a linked 
   list and execute each test registered there. A per-test as well as an overall 
   report is printed to stdout summarizing the tests that ran and which ones failed
   /passed. 

   * Each test should be in its own self-contained function. The function should return
     an e_status enum, with possible members being SUCCESS or FAILURE, and take no
     arguments.
   * Each test must be registered with the test runner list. At the end, the test runner
     gets called on the list to execute each registered test in turn.

   Usage
   -----------------------
   * Initialize a 'list' with Cohort_init().
   * Add pointers to test functions to be called to the test list using `Cohort_add()`.
   * Execute all the tests in the list with `Cohort_decimate()`.
  
   ### EXAMPLE USAGE:

   ```
        int main(void){
   
        cohort *tests = Cohort_init();
   
        Cohort_add(tests, mathtest1, "mathtest1");
        Cohort_add(tests, segfaultbane, "segbane");
        Cohort_add(tests, booltest, "booltest");
        Cohort_add(tests, segmonster, "segmonster");
        Cohort_add(tests, last_one, "last_test");
   
        Cohort_decimate(tests);
        Cohort_free(tests);  // free memory for each node in list and list itself
       }
   ```
 * All the function tests that are to be registered to be called
   should return 0 (enum status SUCCESS) on success and 1 (enum status FAILURE)
   on failure.
   ============================================================================ /
   *****************************************************************************/

/* 
 * Each test function should return an enum status */
enum status{SUCCESS, FAILURE};

/* 
 * Each test function must have this prototype:
 *  - take no arguments
 *  - return an enum status
 */
typedef enum status (*testf)();

/* 
 * Encapsulation for a test object. 
 * Each test function is associated with a struct test
 * when inserted into the testlist.
 */
struct test{
    testf testf_ptr;      // test to be executed
    char *test_name;      // the name of the test
    struct test *next;    // next test in the testlist
};

/*
 * Test list. Cohort_decimate() will iterate over this list
 * and execute each test in turn.
 */
struct cohort{
    struct test *head;
    struct test *tail;
    size_t count;
};

/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

/* 
 * Initialize testlist.
 */
struct cohort *Cohort_init(void);

/*
 * Append test to the testlist to be called by the test runner.
 */
void Cohort_add(struct cohort* testlist, enum status (*testf)(), char test_name[]);

/*
 * Return count of tests in the test list 
 */
size_t Cohort_count(struct cohort *testlist);

/* 
 * Run all tests in the testlist (cohort) and report the results.
 * Return an enum status -- either SUCCESS or FAILURE.
 */
enum status Cohort_decimate(struct cohort *testlist);

/*
 * Free the memory associated with each test in the testlist,
 * and then finally the testlist itself.
 */
void Cohort_destroy(struct cohort *testlist);

#endif
