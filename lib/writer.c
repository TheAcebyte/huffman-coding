#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "writer.h"

BitWriter* bitwriter_create() {
    BitWriter* writer = malloc(sizeof(BitWriter));
    assert(writer != NULL);

    writer->buffer = calloc(BUFFER_SIZE, 1);
    assert(writer->buffer != NULL);

    writer->size = BUFFER_SIZE;
    writer->index = 0;
    return writer;
}

void bitwriter_resize(BitWriter* writer) {
    writer->size *= 2;
    writer->buffer = realloc(writer->buffer, writer->size);
    assert(writer->buffer != NULL);
}

void bitwriter_free(BitWriter* writer) {
    free(writer->buffer);
    free(writer);
}

void bitwriter_write(BitWriter* writer, bool bit) {
    if (bit) {
        writer->buffer[writer->index / 8] |= 1 << (7 - writer->index % 8);
    }

    writer->index++;
    if (writer->index >= writer->size * 8) {
        bitwriter_resize(writer);
    }
}