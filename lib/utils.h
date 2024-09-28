#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include "huffman_tree.h"
#include "utils.h"

void swap(TreeNode** array, int i, int j);

void set_bit(uint64_t* code, int i);

void unset_bit(uint64_t* code, int i);

bool get_bit(uint64_t* code, int i);

void print_bits(uint64_t* code);

#endif