#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "huffman_tree.h"
#include "utils.h"

typedef struct CodePoint {
    uint8_t count;
    uint64_t code;
} CodePoint;

uint8_t count_chars(char* text, TreeNode** counter);

CodePoint* code_point_create();

void code_table_build(CodePoint** table, TreeNode* node, uint64_t* code, uint8_t depth);

void code_table_free(CodePoint** table);

void encode(char* text);

#endif