#include "list.h"

#include <stdlib.h>

void list_init(list_t *list) {
    list->head = NULL;
    list->size = 0;
}

void list_add(list_t *list, int new_data) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = new_data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    list->size++;
}

// The provided version of this function contains a bug
// TODO Fix this bug
void list_free(list_t *list) {
    node_t *current = list->head;
    while (current != NULL) {
        node_t *to_free = current;
        current = current->next;
        free(to_free);
    }
    list->head = NULL;
    list->size = 0;
}
