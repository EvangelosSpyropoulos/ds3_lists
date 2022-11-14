#include "doublylinkedlist.h"
#include <string.h>
#include <stdio.h>

DoublyLinkedList init_list() {
    DoublyLinkedList list = {
        new_empty_node(),
        new_empty_node()
    };
    list.head->next = list.tail;
    list.tail->last = list.head;
    return list;
}

int search_list(DoublyLinkedList* list, const char* key, Node** node) {
    if (!list) { return -1; }
    
    if (list->head->next == list->tail) { 
        (*node) = list->tail;
        return 1;
    }

    (*node) = list->head->next;
    while ((*node) != list->tail) {
        int found = strcmp((*node)->AM,key);
        if (found == 0) { return 0; } 

        (*node) = (*node)->next;
    }

    return 1;
}

void insert_node_before(Node* node, Node* target) {
    if (!(node && target)) { return; }
    
    if (!target->last) {
        printf("Inserting node before the head is not allowed\n");
        return;
    }

    target->last->next = node;
    node->last = target->last;
    target->last = node;
    node->next = target;
}

void remove_node(Node* node) {
    if ( !node ) { return; }

    if (!node->last) {
        printf("Removing the head is not allowed.\n");
        return;
    }
    
    if (!node->next) {
        printf("Removing the tail is not allowed.\n");
        return;
    }

    node->last->next = node->next;
    node->next->last = node->last;
    free_node(node);
}

Node* advance(Node* start, int n) {
    if (!start) { return start; }
    
    Node* node = start;
    while (n != 0) {
        if (n > 0) {
            if (!node->next) {
                printf("Reached the end of the list. Empty tail node returned.\n");
                return node;
            }
            node = node->next;
            n--;
        } else {
            if (!node->last) {
                printf("Reached the start of the list. Empty head node returned.\n");
                return node;
            }
            node = node->last;
            n++;
        }
    }

    return node;
}

void free_resources(DoublyLinkedList* list) {
    if (!list) { return; }
    
    Node* node = list->head;
    
    // Free resources up to tail.
    while (node != list->tail) {
        node = node->next;
        free_node(node->last);
    }

    // Free tail's resources.
    free_node(node);
}