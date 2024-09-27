#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>
#include "utils.h"

typedef struct MinHeap {
    TreeNode** array;
    size_t capacity;
    size_t size;
} MinHeap;

MinHeap* heap_create(TreeNode** array, size_t size);

void heap_free(MinHeap* heap);

void heap_push(MinHeap* heap, TreeNode* node);

TreeNode* heap_pop(MinHeap* heap);

void heap_heapify(MinHeap* heap);

void heap_siftup(MinHeap* heap, int i);

void heap_siftdown(MinHeap* heap, int i);

#endif