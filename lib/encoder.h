#ifndef H_ENCODER
#define H_ENCODER

#include <stdint.h>
#include "huffman_tree.h"

uint8_t count_chars(char* text, TreeNode** counter);

void encode(char* text);

#endif