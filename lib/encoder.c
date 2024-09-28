#include <stdio.h>
#include <stdlib.h>
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
        }

        *code >>= 1;
    }
}

void code_table_free(CodePoint** table) {
    for (int i = 0; i < 128; i++) {
        if (table[i] != NULL) {
            free(table[i]);
        }
    }
}

void encode(char* text) {
    TreeNode* counter[128];
    CodePoint* table[128];
    uint128_t code = 0;

    uint8_t size = count_chars(text, counter);
    TreeNode* root = huffman_tree_build(counter, size);

    for (int i = 0; i < 128; i++) {
        table[i] = NULL;
    }
    code_table_build(table, root, &code, 0);

    for (int i = 0; i < 128; i++) {
        if (table[i] != NULL) {
            printf("%c %d ", i, table[i]->count);
            print_bits(&(table[i]->code));
        }
    }

    code_table_free(table);
    huffman_tree_free(root);
}