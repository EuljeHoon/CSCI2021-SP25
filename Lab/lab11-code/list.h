#ifndef LIST_H
#define LIST_H

// Linked list node definition
typedef struct node {
    int data;
    struct node *next;
} node_t;

// Linked list definition
typedef struct list {
    node_t *head;
    unsigned size;
} list_t;

// Initialize a new empty linked list
void list_init(list_t *list);

// Add a new element to a linked list
void list_add(list_t *list, int new_data);

// Free memory associated with the linked list
void list_free(list_t *list);

#endif
