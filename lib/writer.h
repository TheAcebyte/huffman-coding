#ifndef WRITER_H
#define WRITER_H
#define BUFFER_SIZE 1024

#include <stdint.h>

typedef struct BitWriter {
    uint8_t* buffer;
    uint32_t size;
    uint32_t index;
} BitWriter;

BitWriter* bitwriter_create();

void bitwriter_write(BitWriter* writer, bool bit);

void bitwriter_skip(BitWriter* writer, uint32_t bytes);

void bitwriter_free(BitWriter* writer);

#endif