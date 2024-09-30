#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "utils.h"
#include "encoder.h"
#include "decoder.h"

int main(int argc, char** argv) {
    assert(argc == 3 || argc == 4);

    char* input_file = argv[2];
    int index = search_string(input_file, '.');
    assert(index != -1);

    char output_file[index + 5];
    strncpy(output_file, input_file, index);

    if (strcmp(argv[1], "encode") == 0) {
        strncpy(output_file + index, ".bin", 5);
        printf("Starting compression...\n");

        FILE* file = fopen(input_file, "r");
        assert(file != NULL);

        fseek(file, 0L, SEEK_END);
        uint32_t input_size = ftell(file);
        fclose(file);

        uint32_t output_size = encode(input_file, output_file);
        printf("Successfully compressed %s from %d to %d bytes.\n", input_file, input_size, output_size);
    }
    else if (strcmp(argv[1], "decode") == 0) {
        strncpy(output_file + index, ".txt", 5);
        printf("Starting decompression...\n");
        decode(input_file, output_file);
        printf("Successfully decompressed %s.\n", input_file);
    }
    else {
        return 1;
    }

    if (argc == 4) {
        char* flag = argv[3];
        assert(strcmp(flag, "-d") == 0);
        assert(remove(input_file) == 0);
    }

    return 0;
}