#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include "huffman_tree.h"
#include "utils.h"

typedef unsigned __int128 uint128_t;

void swap(TreeNode** array, int i, int j);

int search_string(char* string, char ch);

bool get_bit(uint128_t code, int i);

void print_nbits(uint128_t code, uint8_t n);

#endif