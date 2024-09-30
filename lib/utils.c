#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "huffman_tree.h"
#include "utils.h"

void swap(TreeNode** array, int i, int j) {
    TreeNode* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int search_string(char* string, char ch) {
    for (int i = strlen(string) - 1; i >= 0; i--) {
        if (string[i] == ch) {
            return i;
        }
    }

    return -1;
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