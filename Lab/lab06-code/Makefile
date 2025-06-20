AN = lab06
CFLAGS = -Wall -Werror -g -z noexecstack
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')
ARCH = $(shell uname -m)

ifeq ($(ARCH), x86_64)
	CC = gcc $(CFLAGS)
else
	CC = x86_64-linux-gnu-gcc $(CFLAGS)
endif

.PHONY: clean clean-tests help zip test test-quiz test-code test-setup

main: main.c funcs.s
	$(CC) -o $@ $^

clean:
	rm -f main

clean-tests:
	rm -rf test_results

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'

# 'make zip' to create zip file for submission
zip: clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)" -x "$(CWD)/testius" "$(CWD)/test_cases/*"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

ifeq ($(ARCH), x86_64)
test: test-setup main
	./testius test_cases/tests.json

test-quiz: test-setup
	./testius test_cases/tests.json -v -n 1

test-code: test-setup main
	./testius test_cases/tests.json -v -n 2

run: main
	./main
else
test: test-setup main
	./testius test_cases/non_x86_tests.json

test-quiz: test-setup
	./testius test_cases/non_x86_tests.json -v -n 1

test-code: test-setup main
	./testius test_cases/non_x86_tests.json -v -n 2

run: main
	qemu-x86_64 ./main
endif

test-setup:
	@chmod u+x testius test_cases/resources/socrates
