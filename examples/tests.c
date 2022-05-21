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
