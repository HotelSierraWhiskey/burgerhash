#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SCHEDULE_SIZE MESSAGE_DIGEST_SIZE * 4

#define rotate_left(n, i) (n << i) | (n >> (32 - i))
#define rotate_right(n, i) (n >> i) | (n << (32 - i))

char ciphertext_buffer[MESSAGE_DIGEST_SIZE];
static char prev_block[MESSAGE_DIGEST_SIZE];
static uint32_t message_schedule[MESSAGE_DIGEST_SIZE];

const uint32_t initial_words[8] = {
    0xf401e2ae, 0xb3b24ac4, 0x53386234, 0xe020bb13,
    0xbef1ee13, 0xee9221b8, 0x25788afe, 0xb04c0abe,
};

const uint32_t schedule_table_constants[24] = {
    0x37b5bb28, 0x2fcc8917, 0x95517ae9, 0x63fd610c, 0x3fec2f95, 0x61bfccb2,
    0xc55b8da1, 0x265fea33, 0x2ecd542d, 0x5d2a6235, 0xd00d9539, 0xb415b49e,
    0x16314ba6, 0xbed458a5, 0xca77a35e, 0xd7117800, 0x61229b60, 0x3c611071,
    0x669052ff, 0xa87f1909, 0x4a71c5fd, 0x96142852, 0x7aef0e4c, 0x21f58ab3,
};

static void build_message_schedule(void) {
    memcpy(message_schedule, prev_block, MESSAGE_DIGEST_SIZE);

    for (uint8_t i = 0; i < 24; i++) {
        message_schedule[8 + i] =
            schedule_table_constants[i];  // actually use sigma funcs
    }
}

static void compress_message_schedule(void) {
    char temp_buffer[MESSAGE_DIGEST_SIZE];
    memset(temp_buffer, 0, MESSAGE_DIGEST_SIZE);

    // 32 words in a message schedule
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < MESSAGE_DIGEST_SIZE; j++) {
            // temp_buffer[j] =
            //     rotate_right(temp_buffer[j] ^ message_schedule[i * j], 13);
            temp_buffer[j] = message_schedule[i * j];
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
