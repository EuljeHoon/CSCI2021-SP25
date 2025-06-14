#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main() {
    int latest_input;
    list_t number_list;
    list_init(&number_list);

    printf("Type in a sequence of positive numbers.\n");
    printf("Type in 0 or a negative number to quit.\n");
    while (1) {
        printf("Next Number? > ");
        if (fscanf(stdin, "%d", &latest_input) != 1) {
            printf("Numbers only, please\n");
            exit(0);
        }

        if (latest_input <= 0) {
            break;
        } else {
            list_add(&number_list, latest_input);
        }
    }

    printf("The numbers you typed in were:\n");
    node_t *current = number_list.head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    list_free(&number_list);
    exit(0);
}
