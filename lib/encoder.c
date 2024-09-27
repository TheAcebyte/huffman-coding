#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "utils.h"

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

void encode(char* text) {
    TreeNode* counter[128];
    uint8_t size = count_chars(text, counter);
    TreeNode* root = huffman_tree_build(counter, size);
    printf("%d", root->count);

    huffman_tree_free(root);
}