_Updated May 21 2022_

# Cohort - simple C test runner

Very simple test runner written in C. Ideal for calling a number of
minimal tests in a Makefile-based compilation process as for validating
a data structure implementation.

## Features

This is an unsophisticated test runner without any bells and whistles.
The user:
 * initializes the test list
 * adds tests to the test list
 * calls the test runner to run the tests in the list
 * frees (destroys) the test list at the end

One nice feature is that tests that generate a fatal signal
such as SIGBUS or SIGSEGV do _not_ end the program. Instead, they
are caught and the test runner reports the respective test as _failed_
and then continues on with the rest.

## Usage

Run `make` to run the example shown below.
**NOTE** that in the example shown 3 tests get run:
 - the first one generates a segfault
 - the second one simply return failure
 - the third one actually succeeds

This is intentional and is used to give an idea of the output.

```C
#include <stdlib.h>

#include "cohort.h"
#include "example_tests.c"

int main(int argc, char **argv){
    struct cohort *testlist = Cohort_init();

    Cohort_add(testlist, example1, "first_example");
    Cohort_add(testlist, example2, "nutty_example");
    Cohort_add(testlist, example3, "third_and_last");

    enum status status = Cohort_decimate(testlist);
    Cohort_destroy(testlist);

    exit(status);
}
```
