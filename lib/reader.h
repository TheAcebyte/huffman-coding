#ifndef READER_H
#define READER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct BitReader {
    uint8_t* buffer;
    uint32_t index;
} BitReader;

BitReader* bitreader_create(uint32_t size);

void bitreader_free(BitReader* reader);

bool bitreader_read(BitReader* reader);

#endif