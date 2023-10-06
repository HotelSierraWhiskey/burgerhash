#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SCHEDULE_SIZE MESSAGE_DIGEST_SIZE * 4

#define rotate_left(n, i) ((n << i) | (n >> (32 - i)))
#define rotate_right(n, i) ((n >> i) | (n << (32 - i)))

char ciphertext_buffer[MESSAGE_DIGEST_SIZE];
static char prev_block[MESSAGE_DIGEST_SIZE];
static uint32_t message_schedule[MESSAGE_SCHEDULE_SIZE];

const uint32_t initial_words[8] = {
    0xf401e2ae, 0xb3b24ac4, 0x53386234, 0xe020bb13,
    0xbef1ee13, 0xee9221b8, 0x25788afe, 0xb04c0abe,
};

const uint32_t schedule_table_constants[32] = {
    0x37b5bb28, 0x2fcc8917, 0x95517ae9, 0x63fd610c, 0x3fec2f95, 0x61bfccb2,
    0xc55b8da1, 0x265fea33, 0x2ecd542d, 0x5d2a6235, 0xd00d9539, 0xb415b49e,
    0x16314ba6, 0xbed458a5, 0xca77a35e, 0xd7117800, 0x61229b60, 0x3c611071,
    0x669052ff, 0xa87f1909, 0x4a71c5fd, 0x96142852, 0x7aef0e4c, 0x21f58ab3,
    0xf401e2ae, 0xb3b24ac4, 0x53386234, 0xe020bb13, 0xbef1ee13, 0xee9221b8,
    0x25788afe, 0xb04c0abe,
};

static uint32_t sigma_0(uint32_t x) {
    return rotate_right(x, 7) ^ rotate_right(x, 18) ^ rotate_right(x, 3);
}

static uint32_t sigma_1(uint32_t x) {
    return rotate_right(x, 17) ^ rotate_right(x, 19) ^ rotate_right(x, 10);
}

static void build_message_schedule(void) {
    memcpy(message_schedule, prev_block, MESSAGE_DIGEST_SIZE);

    for (uint8_t i = 0; i < 8; i++) {
        uint32_t t = *(uint32_t *)(prev_block + i * sizeof(uint32_t));
        t ^= schedule_table_constants[i];
        memcpy(prev_block + i * sizeof(uint32_t), &t, sizeof(uint32_t));
    }

    for (uint8_t i = 8; i < MESSAGE_SCHEDULE_SIZE - 8; i++) {
        uint32_t w =
            ((sigma_0(message_schedule[i - 8]) ^ message_schedule[i - 8]) ^
             initial_words[0]) +  //
            ((sigma_1(message_schedule[i - 7]) ^ message_schedule[i - 7]) ^
             initial_words[1]) +  //
            ((sigma_0(message_schedule[i - 6]) ^ message_schedule[i - 6]) ^
             initial_words[2]) +  //
            ((sigma_1(message_schedule[i - 5]) ^ message_schedule[i - 5]) ^
             initial_words[3]) +  //
            ((sigma_0(message_schedule[i - 4]) ^ message_schedule[i - 4]) ^
             initial_words[4]) +  //
            ((sigma_1(message_schedule[i - 3]) ^ message_schedule[i - 3]) ^
             initial_words[5]) +  //
            ((sigma_0(message_schedule[i - 2]) ^ message_schedule[i - 2]) ^
             initial_words[6]) +  //
            ((sigma_1(message_schedule[i - 1]) ^ message_schedule[i - 1]) ^
             initial_words[7]);  //

        w = sigma_0(w);
        message_schedule[i] = w;
    }
}

static void compress_message_schedule(void) {
    char temp_buffer[MESSAGE_DIGEST_SIZE];
    memset(temp_buffer, 0, MESSAGE_DIGEST_SIZE);

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < MESSAGE_DIGEST_SIZE; j++) {
            temp_buffer[j] = message_schedule[i * j];
            temp_buffer[j] ^= prev_block[j];
            temp_buffer[j] ^= schedule_table_constants[j];
        }
    }
    memcpy(prev_block, temp_buffer, MESSAGE_DIGEST_SIZE);
}

static void compute(void) {
    build_message_schedule();
    compress_message_schedule();
}

void hash(char *input_buffer, uint32_t length) {
    uint8_t padding = MESSAGE_DIGEST_SIZE - (length % MESSAGE_DIGEST_SIZE);
    uint32_t total_size = length + padding;
    uint32_t n_blocks = total_size / MESSAGE_DIGEST_SIZE;

    char data_buffer[total_size];

    memmove(data_buffer, input_buffer, total_size);
    memset(data_buffer + (total_size - padding), 0, padding);

    memset(prev_block, 0, MESSAGE_DIGEST_SIZE);
    memcpy(prev_block, data_buffer, MESSAGE_DIGEST_SIZE);

    for (uint32_t i = 0; i < n_blocks; i++) {
        compute();
    }

    memcpy(ciphertext_buffer, prev_block, MESSAGE_DIGEST_SIZE);
}
