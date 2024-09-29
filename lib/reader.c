#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "reader.h"

BitReader* bitreader_create(uint32_t size) {
    BitReader* reader = malloc(sizeof(BitReader));
    assert(reader != NULL);

    reader->buffer = calloc(size, 1);
    assert(reader->buffer != NULL);

    reader->index = 0;
    return reader;
}

void bitreader_free(BitReader* reader) {
    free(reader->buffer);
    free(reader);
}

bool bitreader_read(BitReader* reader) {
    return (reader->buffer[reader->index / 8] >> (7 - reader->index % 8)) & 1;
}