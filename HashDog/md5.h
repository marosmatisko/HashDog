#pragma once
#include <chrono>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include "Md5Hash.h"
#include<cuda.h>
#include <cuda_runtime_api.h>
#include <curand_kernel.h>
#include <device_functions.h>


/* F, G and H are basic MD5 functions: selection, majority, parity */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) \
  {(a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }



#define CONST_WORD_LIMIT 10
#define CONST_CHARSET_LIMIT 100

#define CONST_CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,-_.?'&@#$%^*:~{}"
#define CONST_CHARSET_LENGTH (sizeof(CONST_CHARSET) - 1)

#define CONST_WORD_LENGTH_MIN 4
#define CONST_WORD_LENGTH_MAX 6

#define TOTAL_BLOCKS 1024
#define TOTAL_THREADS 1024
#define HASHES_PER_KERNEL 128UL




__device__ char g_deviceCharset[CONST_CHARSET_LIMIT];

__device__ void md5_hash(unsigned char* data, uint32_t length, uint32_t *a1, uint32_t *b1, uint32_t *c1, uint32_t *d1);

__device__ __host__ bool next(uint8_t* length, char* word, uint32_t increment);

__global__ void md5_crack(uint8_t* wordLength, char* charsetWord, uint32_t* hash, char* g_device_cracked);

void crack_md5();

char *bin2hex(const unsigned char *bin, size_t len);

