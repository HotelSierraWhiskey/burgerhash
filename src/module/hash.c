#include "hash.h"

#include <stdlib.h>
#include <string.h>

char ciphertext_buffer[CIPHERTEXT_BUFFSIZE];

void hash(char *input_buffer, uint32_t length) {
    memset(ciphertext_buffer, 0, CIPHERTEXT_BUFFSIZE);
}
