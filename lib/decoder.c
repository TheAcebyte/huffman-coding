#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "reader.h"
#include "encoder.h"
#include "decoder.h"
#include "utils.h"

void decode_metadata(BitReader* reader, uint16_t* tree_size_bits, uint8_t* last_bits) {
    for (int i = 0; i < METADATA_TREE_BITS; i++) {
        *tree_size_bits |= bitreader_read(reader) << i;
    }

    for (int i = 0; i < METADATA_LAST_BITS; i++) {
        *last_bits |= bitreader_read(reader) << i;
    }
}

void decode(char* filename) {
    FILE* file = fopen(filename, "rb");
    assert(file != NULL);

    uint32_t total_size_bytes;
    fread(&total_size_bytes, 1, METADATA_TOTAL_BYTES, file);

    // Convert Big-Endian to Little-Endian
    total_size_bytes = __builtin_bswap32(total_size_bytes);

    BitReader* reader = bitreader_create(total_size_bytes);
    fread(reader->buffer, 1, total_size_bytes, file);

    uint16_t tree_size_bits = 0;
    uint8_t last_bits = 0;
    decode_metadata(reader, &tree_size_bits, &last_bits);

    print_bits(reader->buffer, 32);
    bitreader_free(reader);
}