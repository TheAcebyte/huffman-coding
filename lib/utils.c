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

bool get_bit(uint128_t* code, int i) {
    return (*code >> i) & 1;
}

void print_n_bits(uint128_t* code, uint8_t n) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d", get_bit(code, i));
    }
    printf("\n");
}