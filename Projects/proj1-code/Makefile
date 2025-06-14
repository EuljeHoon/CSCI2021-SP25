CFLAGS = -Wall -Werror -g
CC = gcc $(CFLAGS)
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')
AN = proj1

TEMPORARY_FILES = \
	RubiksCubeChallenge.txt \
	RubiksCubeChallenge.bin \
	Pogopalooza.bin \
	Pogopalooza.txt \
	Leadville100.txt \
	PreaknessStakes.bin \
	WesternStates.bin \
	WesternStates.txt \
	non_existent.txt \
	non_existent.bin

.PHONY: results_main

results_main: results_main.o race_results.o
	$(CC) -o $@ $^

results_main.o: results_main.c
	$(CC) -c $<

race_results.o: race_results.c race_results.h
	$(CC) -c $<

test-setup:
	@rm -rf $(TEMPORARY_FILES)
	@cp test_cases/resources/RubiksCubeChallenge.txt .
	@cp test_cases/resources/Pogopalooza.bin .
	@chmod u+x testius
	@chmod u-w RubiksCubeChallenge.txt Pogopalooza.bin

ifdef testnum
test: results_main test-setup
	./testius test_cases/tests.json -v -n $(testnum)
else
test: results_main test-setup
	./testius test_cases/tests.json
endif

clean:
	rm -f *.o results_main

clean-tests:
	rm -rf test_results $(TEMPORARY_FILES)

zip: clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)" -x "$(CWD)/testius" "$(CWD)/test_cases/*"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make clean-tests              # remove temporary testing files'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test                     # run all tests'
	@echo '  > make test testnum=n           # run only test number n'
