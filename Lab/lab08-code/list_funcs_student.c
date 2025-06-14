#include <stdlib.h>

#include "linked_list.h"

int list_find_student(list_t *list, int value) {
    // TODO Implement a better version of list search here
    if (list == NULL || list->head == NULL) {
        return -1;
    }
    node_t *now = list->head;
    int index = 0;
    while (now != NULL) {
        if (now->value == value) {
            return index;
        }
        now = now->next;
        index++;
    }
    return -1;
}
