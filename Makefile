SRC:=./src/cohort.c ./examples/tests.c
CC:=gcc
CFLAGS:= -Wall -g -I./src/
OUTDIR:=out/
OUTBIN:=test
VALGRIND_REPORT_NAME:=valgrind.txt

all: clean build_example run_example

build_example:
	@echo "Building example (any failures or segfaults are on purpose) ..."
	@mkdir -p $(OUTDIR)
	@ $(CC) $(SRC) $(CFLAGS) -o $(OUTDIR)/$(OUTBIN)

run_example:
	@ $(OUTDIR)/$(OUTBIN)

clean:
	@ rm -rf $(OUTDIR) $(VALGRIND_REPORT_NAME)

grind: build_example
	valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --verbose \
		--log-file=$(VALGRIND_REPORT_NAME) $(OUTDIR)/$(OUTBIN)

