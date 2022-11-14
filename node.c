#include "node.h"
#include <string.h>
#include <stdlib.h>

Node* new_node(const char* AM, const char* full_name, const int semester) {
    char* node_AM = (char*) malloc(strlen(AM) + 1);
    strcpy(node_AM, AM);
    char* node_full_name = (char*) malloc(strlen(full_name) + 1);
    strcpy(node_full_name, full_name);
    Node* node = (Node*) malloc(sizeof(Node));
    node->AM = node_AM;
    node->full_name = node_full_name;
    node->semester = semester;
    node->last = NULL;
    node->next = NULL;
    return node;
}

Node* new_empty_node(Node* last, Node* next) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->AM = NULL;
    node->full_name = NULL;
    node->last = NULL;
    node->next = NULL;
    return node;
}

void free_node(Node* node) {
    if (node->AM) { free(node->AM); }
    if (node->full_name) { free(node->full_name); }
    free(node);
}