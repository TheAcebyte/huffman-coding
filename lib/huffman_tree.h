#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stddef.h>
#include <stdint.h>

struct TreeNode {
    size_t count;
    char character;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

TreeNode* huffman_tree_node_create(size_t count, char character, TreeNode* left, TreeNode* right);

void huffman_tree_node_free(TreeNode* node);

TreeNode* huffman_tree_build(TreeNode** counter, uint8_t size);

void huffman_tree_free(TreeNode* node);

#endif