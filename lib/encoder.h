#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "huffman_tree.h"
#include "utils.h"

#define METADATA_SIZE 7
#define METADATA_FILE_SIZE 4
#define METADATA_LAST_SIZE 1

typedef struct CodePoint {
    uint8_t count;
    uint128_t code;
} CodePoint;

uint8_t count_chars(char* text, TreeNode** counter);

CodePoint* code_point_create();

void code_table_build(CodePoint** table, TreeNode* node, uint128_t* code, uint8_t depth);

void code_table_free(CodePoint** table);

void code_table_print(CodePoint** table);

void encode_tree(TreeNode *node, BitWriter *writer);

void encode_text(char* text, BitWriter* writer, CodePoint** table);

uint32_t encode(char* input_file, char* output_file);

#endif