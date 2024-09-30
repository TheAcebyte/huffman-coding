#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "huffman_tree.h"
#include "reader.h"
#include "writer.h"
#include "encoder.h"
#include "decoder.h"
#include "utils.h"

TreeNode* decode_tree(BitReader* reader) {
    if (bitreader_read(reader)) {
        char ch = 0;
        for (int i = 0; i < 7; i++) {
            ch |= bitreader_read(reader) << i;
        }

        return huffman_tree_node_create(0, ch, NULL, NULL);
    }
    else {
        TreeNode* left = decode_tree(reader);
        TreeNode* right = decode_tree(reader);
        return huffman_tree_node_create(0, EOF, left, right);
    }
}

void decode_text(TreeNode* node, BitReader* reader, BitWriter* writer) {
    if (node->character != EOF) {
        bitwriter_write_byte(writer, node->character);
    }
    else {
        if (!bitreader_read(reader)) {
            decode_text(node->left, reader, writer);
        } 
        else {
            decode_text(node->right, reader, writer);
        }
    }
}

void decode(char* filename) {
    FILE* file = fopen(filename, "rb");
    assert(file != NULL);

    uint32_t file_size_bytes;
    uint8_t last_bits;

    fread(&file_size_bytes, METADATA_FILE_SIZE, 1, file);
    fread(&last_bits, METADATA_LAST_SIZE, 1, file);

    BitReader* reader = bitreader_create(file_size_bytes - METADATA_SIZE);
    fread(reader->buffer, file_size_bytes - METADATA_SIZE, 1, file);

    uint16_t start = reader->index;
    TreeNode* root = decode_tree(reader);
    
    BitWriter* writer = bitwriter_create();
    while (reader->index < 8 * (file_size_bytes - METADATA_SIZE - 1) + last_bits) {
        decode_text(root, reader, writer);
    }

    uint32_t output_file_size = writer->index / 8;
    FILE* output_file = fopen("ok.txt", "w");
    assert(output_file != NULL);

    fwrite(writer->buffer, output_file_size, 1, output_file);
    fclose(output_file);
    fclose(file);

    bitwriter_free(writer);
    huffman_tree_free(root);
    bitreader_free(reader);
}