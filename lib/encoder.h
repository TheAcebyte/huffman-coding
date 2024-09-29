#ifndef ENCODER_H
#define ENCODER_H

#define METADATA_SIZE 6
#define METADATA_TOTAL_BITS 32
#define METADATA_TREE_BITS 12
#define METADATA_LAST_BITS 4

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

void encode_metadata(BitWriter* writer, uint32_t total_size_bytes, uint16_t tree_size_bits, uint8_t remaining_bits);

void encode_tree(TreeNode *node, BitWriter *writer);

void encode_text(char* text, BitWriter* writer, CodePoint** table);

void encode(char* text);

#endif