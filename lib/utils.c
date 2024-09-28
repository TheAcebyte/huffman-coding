#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "huffman_tree.h"
#include "utils.h"

void swap(TreeNode** array, int i, int j) {
    TreeNode* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void set_bit(uint64_t* code, int i) {
    *code = *code | (1 << i);
}

void unset_bit(uint64_t* code, int i) {
    *code = *code & (~(1 << i));
}

bool get_bit(uint64_t* code, int i) {
    return (*code >> i) & 1;
}

void print_bits(uint64_t* code) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", get_bit(code, i));
    }
    printf("\n");
}