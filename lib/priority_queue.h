#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdint.h>
#include "huffman_tree.h"
#include "utils.h"

typedef struct MinHeap {
    TreeNode** array;
    uint8_t capacity;
    uint8_t size;
} MinHeap;

MinHeap* heap_create(TreeNode** array, uint8_t capacity, uint8_t size);

void heap_free(MinHeap* heap);

void heap_push(MinHeap* heap, TreeNode* node);

TreeNode* heap_pop(MinHeap* heap);

void heap_heapify(MinHeap* heap);

void heap_siftup(MinHeap* heap, int i);

void heap_siftdown(MinHeap* heap, int i);

#endif