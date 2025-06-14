#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned malloc_calls = 0;
static unsigned free_calls = 0;

static int handler_registered = 0;

// Print out total number of calls to malloc()/free()
void print_mem_info() {
    printf("Total calls to malloc(): %d\n", malloc_calls);
    printf("Total calls to free(): %d\n", free_calls);
}

//  Our own version of malloc() that will run when code calls the "normal" malloc()
void *malloc(size_t size) {
    // If needed, set print_mem_info() to run when program terminates
    if (!handler_registered) {
        atexit(print_mem_info);
        handler_registered = 1;
    }
    malloc_calls++;

    void *(*mallocp)(size_t size);
    char *error;

    // Get a pointer to the original malloc() function
    mallocp = dlsym(RTLD_NEXT, "malloc");
    error = dlerror();
    if (error != NULL) {
        puts(error);
        exit(1);
    }

    // Call original malloc() and return its result
    void *ptr = mallocp(size);
    return ptr;
}

void free(void *ptr) {
    // TODO Complete the implementation of this function

    // 1. Increment the global variable counting total calls to free()
    free_calls++;
    // 2. Obtain a pointer to the original version of free
    // You may want to use the two variable declarations below:
    // void (*freep)(void *);
    // char *error;
    void (*freep)(void *);
    char *error;
    freep = dlsym(RTLD_NEXT, "free");
    error = dlerror();
    if (error != NULL) {
        puts(error);
        exit(1);
    }
    // 3. Call the original version of free()
    freep(ptr);
}
