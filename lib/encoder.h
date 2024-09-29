#ifndef ENCODER_H
#define ENCODER_H

#define CODE_BUFFER_SIZE 1024
#define TREE_BUFFER_SIZE 256

#include <stdint.h>
#include "huffman_tree.h"
#include "utils.h"

typedef struct CodePoint {
    uint8_t count;
    uint128_t code;
} CodePoint;

uint8_t count_chars(char* text, TreeNode** counter);

CodePoint* code_point_create();

void code_table_build(CodePoint** table, TreeNode* node, uint128_t* code, uint8_t depth);

void code_table_free(CodePoint** table);

void code_table_print(CodePoint** table);

uint32_t encode_text(char* text, uint8_t** buffer, CodePoint** table);

void encode(char* text);

#endif