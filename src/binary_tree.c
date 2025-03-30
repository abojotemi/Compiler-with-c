#include "../include/binary_tree.h"
Node *create_node(char *val)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        puts("Error Allocating Node");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->val = val;

    return new_node;
}

Node *insert_btree_node(Node *node, char *val)
{
    if (!node)
    {
        node = create_node(val);
    }
    else if (strcmp(node->val, val) > 0)
    {
        node->left = insert_btree_node(node->left, val);
    }
    else if (strcmp(node->val, val) < 0)
    {
        node->right = insert_btree_node(node->right, val);
    }
    return node;
}

bool find_node(Node *node, char *val)
{
    if (!node)
    {
        return false;
    }
    else if (strcmp(node->val,val) > 0)
    {
        return find_node(node->left, val);
    }
    else if (strcmp(node->val,val) < 0)
    {
        return find_node(node->right, val);
    }
    return true;
}

void free_tree(Node *node)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        free(node);
    }
    else
    {
        free(node->left);
        free(node->right);
        free(node);
    }
}