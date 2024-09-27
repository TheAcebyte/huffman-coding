#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "priority_queue.h"

TreeNode* huffman_tree_node_create(size_t count, char character, TreeNode* left, TreeNode* right) {
    TreeNode* node = malloc(sizeof(struct TreeNode));
    assert(node != NULL);

    node->count = count;
    node->character = character;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void huffman_tree_node_free(TreeNode* node) {
    free(node);
}

TreeNode* huffman_tree_build(TreeNode** counter, uint8_t size) {
    MinHeap* heap = heap_create(counter, 128, size);
    heap_heapify(heap);

    while (heap->size > 1) {
        TreeNode* left = heap_pop(heap);
        TreeNode* right = heap_pop(heap);

        TreeNode* node = huffman_tree_node_create(left->count + right->count, EOF, left, right);
        heap_push(heap, node);
    }

    TreeNode* root = heap_pop(heap);
    heap_free(heap);
    return root;
}

void huffman_tree_free(TreeNode* node) {
    if (node != NULL) {
        huffman_tree_free(node->left);
        huffman_tree_free(node->right);
        huffman_tree_node_free(node);
    }
}