AN = lab07
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')
ARCH = $(shell uname -m)
CFLAGS = -Wall -Werror -g
CC = gcc $(CFLAGS)

ifeq ($(ARCH), x86_64)
	CC_ASM = gcc $(CFLAGS)
	TEST_FILE = test_cases/tests.json
else
	CC_ASM = x86_64-linux-gnu-gcc $(CFLAGS)
	TEST_FILE = test_cases/tests_non_x86.json
endif

.PHONY: all test-setup test-quiz test-code clean clean-tests run

all: order3_c order3_asm

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'
	@echo '  > make test                     # run all automated tests'
	@echo '  > make clean-tests              # remove all test results'
	@echo '  > make run						 # run order3_asm program'

zip: clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)" -x "$(CWD)/testius" "$(CWD)/test_cases/*"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

order3_c: order3.c
	$(CC) -o $@ $^

order3_asm: order3.s
	$(CC_ASM) -o $@ $^

ifeq ($(ARCH), x86_64)
run: order3_asm
	./order3_asm
else
run: order3_asm
	qemu-x86_64 ./order3_asm
endif

test-setup:
	@chmod u+rx testius test_cases/resources/socrates

test: test-setup all
	./testius $(TEST_FILE)

test-quiz: test-setup QUESTIONS.txt
	./testius $(TEST_FILE) -v -n 1

test-code: test-setup order3_asm
	./testius $(TEST_FILE) -v -n 2

clean:
	rm -f *.o order3_asm order3_c

clean-tests:
	rm -rf test_results/
