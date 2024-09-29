#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "writer.h"

BitWriter* bitwriter_create() {
    BitWriter* writer = malloc(sizeof(BitWriter));
    writer->buffer = calloc(BUFFER_SIZE, 1);
    writer->size = BUFFER_SIZE;
    writer->index = 0;

    return writer;
}

void bitwriter_write(BitWriter* writer, bool bit) {
    if (bit) {
        writer->buffer[writer->index / 8] |= 1 << writer->index % 8;
    }

    writer->index++;
    if (writer->index >= writer->size) {
        writer->size *= 2;
        writer->buffer = realloc(writer->buffer, writer->size);
    }
}

void bitwriter_skip(BitWriter* writer, uint32_t bytes) {
    writer->index += bytes * 8;
    while (writer->index >= writer->size) {
        writer->size *= 2;
        writer->buffer = realloc(writer->buffer, writer->size);
    }
}

void bitwriter_free(BitWriter* writer) {
    free(writer->buffer);
    free(writer);
}