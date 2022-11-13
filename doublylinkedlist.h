#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "node.h"

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

DoublyLinkedList init_list();

// Returns 0 if key is found : node contains found node
// Returns 1 if key is not found : node contains node with higher key
// Returns -1 on error 
int search_list(DoublyLinkedList* list, const char* key, Node** node);

void insert_node_before(Node* node, Node* target);
void remove_node(Node* node);

// Advances the list by n nodes for traversing.
Node* advance(Node* start, int n);

void free_resources(DoublyLinkedList* list);

#endif