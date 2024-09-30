#ifndef WRITER_H
#define WRITER_H
#define BUFFER_SIZE 1024

#include <stdbool.h>
#include <stdint.h>

typedef struct BitWriter {
    uint8_t* buffer;
    uint32_t size;
    uint32_t index;
} BitWriter;

BitWriter* bitwriter_create();

void bitwriter_resize(BitWriter* writer);

void bitwriter_free(BitWriter* writer);

void bitwriter_write_bit(BitWriter* writer, bool bit);

void bitwriter_write_byte(BitWriter* writer, char byte);

#endif