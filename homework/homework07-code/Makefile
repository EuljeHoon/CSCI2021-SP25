SHELL = /bin/bash
ARCH = $(shell uname -m)
CFLAGS = -Wall -Werror -g
PORT = 2021

ifeq ($(ARCH), x86_64)
	CC = gcc $(CFLAGS)
else
	CC = x86_64-linux-gnu-gcc $(CFLAGS)
endif

.PHONY: all clean run_quote gdb

quote_main: quote_main.o quote_data.o
	$(CC) -o $@ $^

quote_main.o: quote_main.c
	$(CC) -c $<

ifeq ($(ARCH), x86_64)
run: quote_main
	./quote_main

gdb: quote_main
	gdb -tui ./quote_main
else
run: quote_main
	qemu-x86_64 ./quote_main

gdb: quote_main
	qemu-x86_64 -g $(PORT) ./quote_main &
	gdb-multiarch ./quote_main -tui -ex 'target remote localhost:$(PORT)'
endif

clean:
	rm -f quote_main.o quote_main
