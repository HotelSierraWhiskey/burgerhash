#ifndef HASH_H
#define HASH_H

#include <stdint.h>

#define MESSAGE_DIGEST_SIZE 32  // 256 bits

extern char ciphertext_buffer[MESSAGE_DIGEST_SIZE];
extern void hash(char *plaintext, uint32_t length);

#endif