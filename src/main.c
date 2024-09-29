#include <stdio.h>
#include "encoder.h"
#include "decoder.h"

int main(int argc, char** argv) {
    encode("foo.txt");
    decode("foo.txt.bin");
    return 0;
}