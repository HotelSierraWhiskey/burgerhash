#ifndef HASH_H
#define HASH_H

#include <stdint.h>

#define CIPHERTEXT_BUFFSIZE 32  // 256 bits

extern char ciphertext_buffer[CIPHERTEXT_BUFFSIZE];
extern void hash(char *plaintext, uint32_t length);

#endif