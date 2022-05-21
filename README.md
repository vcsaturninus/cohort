_updated Nov 23 2021_

Overview
==========================

This is a library that can be included and used in other projects; 
The way to use it is dead-simple and is shown in detail in the header file (clogger.h).

It provides a test runner, a signal handler able to catch SUGBUS, SIGSEGV etc, 
and some structs to wrap each test object in.
```
    EXAMPLE:

    Total number of tests: 5
	  test 1 of 1 passed.  | mathtest1                      |
	! test 2 of 2 !FAILED! | segbane                        |		[* caught deadly signal *]
	  test 3 of 3 passed.  | booltest                       |
	! test 4 of 4 !FAILED! | segmonster                     |		[* caught deadly signal *]
	  test 5 of 5 passed.  | last_test                      |

	| DONE --> Passed: 3 of 5

```

Memory leaks 
------------------

This is not meant to be running on a target machine with
resource constraints, obviously. It's also not meant to be running 
complicated tests that run for very long. Therefore the initial idea
was for this tool to compeltely disregard memory leaks. I've made a
complete uturn on this however. On the contrary, by making sure this
tool does free all memory in the linked list at the very end, one can
easily run `Valgrind`  on a `tests` program that contains
data-structure tests being run through `cohort` and find that way if
the data structure itself leaks. 
If cohort has no leaks then it's the data structure leaking. This is a
really great way of checking that a data structure **DOES NOT LEAK**,
which should always be the case as a particular data structure might
be part of libraries that run for a long time. Memory leaks there are
unacceptable. 

Valgrind's output should look like this:
```
    ==384599== 
    ==384599== HEAP SUMMARY:
    ==384599==     in use at exit: 0 bytes in 0 blocks
    ==384599==   total heap usage: 31 allocs, 31 frees, 1,456 bytes allocated
    ==384599== 
    ==384599== All heap blocks were freed -- no leaks are possible
    ==384599== 
    ==384599== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Contrast this with the following run, which shows significant leakage
even for a very short-lived program:
```
    └─$ valgrind ./tests 
    ==1368367== Memcheck, a memory error detector
    ==1368367== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==1368367== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==1368367== Command: ./tests
    ==1368367== 
    Total number of tests: 3
          test 1 of 1 passed.  | enqueue_one                    | 
          test 2 of 2 passed.  | is_counter_updated             | 
          test 3 of 3 passed.  | dequeue_tests                  | 

        | DONE --> Passed: 3 of 3

    ==1368367== 
    ==1368367== HEAP SUMMARY:
    ==1368367==     in use at exit: 280 bytes in 14 blocks
    ==1368367==   total heap usage: 19 allocs, 5 frees, 1,368 bytes allocated
    ==1368367== 
    ==1368367== LEAK SUMMARY:
    ==1368367==    definitely lost: 96 bytes in 4 blocks
    ==1368367==    indirectly lost: 160 bytes in 9 blocks
    ==1368367==      possibly lost: 0 bytes in 0 blocks
    ==1368367==    still reachable: 24 bytes in 1 blocks
    ==1368367==         suppressed: 0 bytes in 0 blocks
    ==1368367== Rerun with --leak-check=full to see details of leaked memory
    ==1368367== 
    ==1368367== For lists of detected and suppressed errors, rerun with: -s
    ==1368367== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


