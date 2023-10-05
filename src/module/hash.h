#ifndef HASH_H
#define HASH_H

#include <stdint.h>

#define BUFFSIZE 32  // 256 bits

extern char ciphertext_buffer[BUFFSIZE];
extern void hash(char *plaintext, uint32_t length);

#endif