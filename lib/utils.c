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

bool get_bit(uint128_t code, int i) {
    return (code >> i) & 1;
}

void print_nbits(uint128_t code, uint8_t n) {
    for (int i = 0; i < n; i++) {
        printf("%d", get_bit(code, i));
    }
    printf("\n");
}

bool get_bits(uint8_t* code, int i) {
    return (code[i / 8] >> (7 - i % 8)) & 1;
}

void print_bits(uint8_t* code, uint8_t n) {
    for (int i = 0; i < n; i++) {
        printf("%d", get_bits(code, i));
    }
    printf("\n");
}