#include <stdio.h> // remove this
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "utils.h"
#include "priority_queue.h"

MinHeap* heap_create(TreeNode** array, uint8_t capacity, uint8_t size) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    assert(heap != NULL);

    heap->array = array;
    heap->capacity = capacity;
    heap->size = size;

    return heap;
}

void heap_free(MinHeap* heap) {
    free(heap);
}

void heap_push(MinHeap* heap, TreeNode* node) {
    heap->size++;
    assert(heap->size <= heap->capacity);

    heap->array[heap->size - 1] = node;
    heap_siftup(heap, heap->size - 1);
}

TreeNode* heap_pop(MinHeap* heap) {
    assert(heap->size > 0);
    TreeNode* output = heap->array[0];

    swap(heap->array, 0, heap->size - 1);
    heap->size--;
    heap_siftdown(heap, 0);
    return output;
}

void heap_heapify(MinHeap* heap) {
    for (int i = heap->size / 2; i >= 0; i--) {
        heap_siftdown(heap, i);
    }
}

void heap_siftup(MinHeap* heap, int i) {
    while (heap->array[i]->count < heap->array[i / 2]->count) {
        swap(heap->array, i, i / 2);
        i = i / 2;
    }
}

void heap_siftdown(MinHeap* heap, int i) {
    while (2 * i + 1 < heap->size) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap->size && heap->array[l]->count < heap->array[smallest]->count) {
            smallest = l;
        }

        if (r < heap->size && heap->array[r]->count < heap->array[smallest]->count) {
            smallest = r;
        }

        if (smallest == i) {
            break;
        }

        swap(heap->array, i, smallest);
        i = smallest;
    }
}