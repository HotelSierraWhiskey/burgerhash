#include "hash.h"

#include <stdlib.h>

void hash(char *input_buffer, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        if (input_buffer[i] == 'A') {
            input_buffer[i] = '9';
        }
    }
}
