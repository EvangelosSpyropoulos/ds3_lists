#ifndef NODE_H
#define NODE_H

typedef struct Node {
    char* AM;
    char* full_name;
    int semester;
    struct Node* last;
    struct Node* next;
} Node;

Node* new_node(const char* AM, const char* full_name, const int semester);
Node* new_empty_node();
void free_node(Node* node);

#endif