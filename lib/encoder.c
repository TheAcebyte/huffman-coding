#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "utils.h"
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
            *code <<= 1;
            code_table_build(table, node->left, code, depth + 1);
            *code |= 1;
            code_table_build(table, node->right, code, depth + 1);
            *code >>= 1;
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

size_t encode_text(char* text, uint8_t** buffer, CodePoint** table) {
    size_t size = BUFFER_SIZE;
    size_t count = 0;

    uint8_t* shift = *buffer;
    uint8_t offset = 0;

    FILE* file = fopen(text, "r");
    assert(file != NULL);

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count += table[ch]->count;
        if (count >= size) {
            size *= 2;
            *buffer = realloc(*buffer, size);
            assert(*buffer != NULL);
            shift = *buffer + count / 8;
        }

        *shift |= (table[ch]->code << offset);
        shift += (offset + table[ch]->count) / 8;
        offset = (offset + table[ch]->count) % 8;
    }

    return count;
}

size_t encode_tree(TreeNode* node, uint8_t** buffer) {
    uint8_t* shift = *buffer;
    uint8_t offset = 0;

    return huffman_tree_serialize(node, buffer, &shift, &offset);
}

void encode(char* text) {
    TreeNode* counter[128];
    CodePoint* table[128];
    uint128_t code = 0;

    uint8_t size = count_chars(text, counter);
    TreeNode* root = huffman_tree_build(counter, size);

    code_table_fill(table);
    code_table_build(table, root, &code, 0);

    uint8_t* code_buffer = calloc(BUFFER_SIZE, 1);
    assert(code_buffer != NULL);
    size_t code_count = encode_text(text, &code_buffer, table);

    uint8_t* key_buffer = calloc(BUFFER_SIZE, 1);
    assert(key_buffer != NULL);
    size_t key_count = encode_tree(root, &key_buffer);

    free(key_buffer);
    free(code_buffer);
    code_table_free(table);
    huffman_tree_free(root);
}