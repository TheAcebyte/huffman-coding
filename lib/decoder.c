#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "reader.h"
#include "encoder.h"
#include "decoder.h"
#include "utils.h"

void decode(char* filename) {
    FILE* file = fopen(filename, "rb");
    assert(file != NULL);

    uint32_t total_size_bytes;
    uint16_t tree_size_bits;
    uint8_t last_bits;

    fread(&total_size_bytes, METADATA_TOTAL_SIZE, 1, file);
    fread(&tree_size_bits, METADATA_TREE_SIZE, 1, file);
    fread(&last_bits, METADATA_LAST_SIZE, 1, file);

    BitReader* reader = bitreader_create(total_size_bytes);
    fread(reader->buffer, total_size_bytes - METADATA_TOTAL_SIZE, 1, file);

    bitreader_free(reader);
}