#ifndef BINARY_TREE_DEF
#define BINARY_TREE_DEF
#include "util.h"

typedef struct Node
{
    char *val;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{
    Node *root;
} Tree;
Node *create_node(char *val);
Node *insert_btree_node(Node *node, char *val);
bool find_node(Node *node, char *val);

#endif