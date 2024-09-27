#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "priority_queue.h"

void print_array(TreeNode** array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]->value);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    TreeNode* array[10];
    size_t length = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < length; i++) {
        array[i] = malloc(sizeof(TreeNode));
        array[i]->value = rand() % 100;
    }

    MinHeap* heap = heap_create(array, length, length);

    print_array(array, length);
    heap_heapify(heap);
    print_array(array, length);

    heap_free(heap);
    for (int i = 0; i < length; i++) {
        free(array[i]);
    }

    return 0;
}