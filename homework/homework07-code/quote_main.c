#include <stdio.h>
#include <string.h>

#define INPUT_FILE "input.txt"

// Defined in list_data.c
int max_size();
char *get_it(int i);

char *correct = "C++ makes it harder, but when you do, it blows away your whole leg.";

int main() {
    printf("Complete this sentence by C++ creator Bjarne Stroustrup:\n");
    printf("C makes it easy to shoot yourself in the foot; ...\n");
    printf("\n");

    FILE *f = fopen(INPUT_FILE, "r");
    if (f == NULL) {
        printf("Failed to open input file. Bailing out.\n");
        return 1;
    }
    int index = 0;
    int res = fscanf(f, "%d", &index);
    fclose(f);
    printf("\n");

    if (res != 1) {
        printf("No, no: Put a NUMBER in %s\n", INPUT_FILE);
        return 1;
    }
    printf("Reading a value from \'%s\': %d\n", INPUT_FILE, index);

    char *selected = get_it(index);
    printf("%d: %s\n", index, selected);
    int diff = strcmp(selected, correct);
    printf("\n");

    if (diff == 0) {
        printf("Correct!\n");
    } else {
        printf("Have a nice tall glass of ... NOPE.\n");
    }

    return 0;
}
