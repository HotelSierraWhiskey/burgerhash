#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ciphertext_buffer[BUFFSIZE];
char prev_block[BUFFSIZE];

static void compression_function(char *input_buffer) {
    memcpy(ciphertext_buffer, input_buffer, BUFFSIZE);
    memcpy(prev_block, input_buffer, BUFFSIZE);
}

void hash(char *input_buffer, uint32_t length) {
    uint8_t padding = BUFFSIZE - (length % BUFFSIZE);
    uint32_t total_size = length + padding;
    uint32_t rounds = total_size / BUFFSIZE;

    char data_buffer[total_size];
    memmove(data_buffer, input_buffer, total_size);
    memset(prev_block, 0, BUFFSIZE);

    for (uint32_t i = 0; i < rounds; i++) {
        compression_function(data_buffer + (BUFFSIZE * i));
    }
}
