#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "utils.h"
#include "writer.h"
#include "encoder.h"

uint8_t count_chars(char* text, TreeNode** counter) {
    FILE* file = fopen(text, "r");
    assert(file != NULL);

    for (int i = 0; i < 128; i++) {
        counter[i] = NULL;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (counter[ch] == NULL) {
            counter[ch] = huffman_tree_node_create(0, ch, NULL, NULL);
        }

        counter[ch]->count++;
    }

    int size = 0;
    for (int i = 0; i < 128; i++) {
        if (counter[i] != NULL) {
            swap(counter, size, i);
            size++;
        }
    }

    return size;
}

CodePoint* code_point_create() {
    CodePoint* point = malloc(sizeof(CodePoint));
    point->count = 0;
    point->code = 0;

    return point;
}

void code_table_fill(CodePoint** table) {
    for (int i = 0; i < 128; i++) {
        table[i] = NULL;
    }
}

void code_table_build(CodePoint** table, TreeNode* node, uint128_t* code, uint8_t depth) {
    if (node != NULL) {
        if (node->character != EOF) {
            table[node->character] = code_point_create();
            table[node->character]->count = depth;
            table[node->character]->code = *code;
        } 
        else {
            code_table_build(table, node->left, code, depth + 1);
            *code |= 1 << depth;
            code_table_build(table, node->right, code, depth + 1);
            *code ^= 1 << depth;
        }
    }
}

void code_table_free(CodePoint** table) {
    for (int i = 0; i < 128; i++) {
        if (table[i] != NULL) {
            free(table[i]);
        }
    }
}

void code_table_print(CodePoint** table) {
    for (int i = 0; i < 128; i++) {
        if (table[i] != NULL) {
            printf("CHAR %c (%3d) -> COUNT: %d, CODE: ", i, i, table[i]->count);
            print_nbits(table[i]->code, table[i]->count);
        }
    }
}

void encode_metadata(BitWriter* writer, uint32_t total_size_bytes, uint16_t tree_size_bits, uint8_t last_bits) {
    for (int i = METADATA_TOTAL_BITS - 1; i >= 0; i--) {
        bitwriter_write(writer, (total_size_bytes >> i) & 1);
    }

    for (int i = METADATA_TREE_BITS - 1; i >= 0; i--) {
        bitwriter_write(writer, (tree_size_bits >> i) & 1);
    }

    for (int i = METADATA_REMAINING_BITS - 1; i >= 0; i--) {
        bitwriter_write(writer, (last_bits >> i) & 1);
    }
}

void encode_tree(TreeNode *node, BitWriter *writer) {
    if (node->character != EOF) {
        bitwriter_write(writer, 1);

        for (int i = 0; i < 7; i++) {
            bitwriter_write(writer, (node->character >> i) & 1);
        }
    }
    else {
        bitwriter_write(writer, 0);
        encode_tree(node->left, writer);
        encode_tree(node->right, writer);
    }
}

void encode_text(char* text, BitWriter* writer, CodePoint** table) {
    FILE* file = fopen(text, "r");
    assert(file != NULL);

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        for (int i = 0; i < table[ch]->count; i++) {
            bitwriter_write(writer, (table[ch]->code >> i) & 1);
        }
    }
}

void encode(char* text) {
    TreeNode* counter[128];
    CodePoint* table[128];
    uint128_t code = 0;

    uint8_t size = count_chars(text, counter);
    TreeNode* root = huffman_tree_build(counter, size);

    code_table_fill(table);
    code_table_build(table, root, &code, 0);
    code_table_print(table);

    BitWriter* writer = bitwriter_create();
    bitwriter_skip(writer, METADATA_SIZE);

    encode_tree(root, writer);
    uint16_t tree_size_bits = writer->index - METADATA_SIZE * 8;

    encode_text(text, writer, table);
    uint32_t total_size_bytes = writer->index / 8 + 1;
    uint8_t last_bits = writer->index % 8;

    writer->index = 0;
    encode_metadata(writer, total_size_bytes, tree_size_bits, last_bits);

    FILE* file = fopen("output.bin", "wb");
    fwrite(writer->buffer, 1, total_size_bytes, file);

    bitwriter_free(writer);
    code_table_free(table);
    huffman_tree_free(root);
}