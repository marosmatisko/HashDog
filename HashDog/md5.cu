/**
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#include "md5.h"


#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}


__device__ void md5_hash(unsigned char* data, uint32_t length, uint32_t *a1, uint32_t *b1, uint32_t *c1, uint32_t *d1) {
	const uint32_t a0 = 0x67452301;
	const uint32_t b0 = 0xEFCDAB89;
	const uint32_t c0 = 0x98BADCFE;
	const uint32_t d0 = 0x10325476;

	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t c = 0;
	uint32_t d = 0;

	uint32_t vals[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	int i = 0;
	for (i = 0; i < length; i++) {
		vals[i / 4] |= data[i] << ((i % 4) * 8);
	}

	vals[i / 4] |= 0x80 << ((i % 4) * 8);

	uint32_t bitlen = length * 8;

#define in0  (vals[0])//x
#define in1  (vals[1])//y
#define in2  (vals[2])//z
#define in3  (vals[3])
#define in4  (vals[4])
#define in5  (vals[5])
#define in6  (vals[6])
#define in7  (vals[7])
#define in8  (vals[8])
#define in9  (vals[9])
#define in10 (vals[10])
#define in11 (vals[11])
#define in12 (vals[12])
#define in13 (vals[13])
#define in14 (bitlen) //w = bit length
#define in15 (0)

	//Initialize hash value for this chunk:
	a = a0;
	b = b0;
	c = c0;
	d = d0;

	/* Round 1 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
	FF(a, b, c, d, in0, S11, 3614090360); /* 1 */
	FF(d, a, b, c, in1, S12, 3905402710); /* 2 */
	FF(c, d, a, b, in2, S13, 606105819); /* 3 */
	FF(b, c, d, a, in3, S14, 3250441966); /* 4 */
	FF(a, b, c, d, in4, S11, 4118548399); /* 5 */
	FF(d, a, b, c, in5, S12, 1200080426); /* 6 */
	FF(c, d, a, b, in6, S13, 2821735955); /* 7 */
	FF(b, c, d, a, in7, S14, 4249261313); /* 8 */
	FF(a, b, c, d, in8, S11, 1770035416); /* 9 */
	FF(d, a, b, c, in9, S12, 2336552879); /* 10 */
	FF(c, d, a, b, in10, S13, 4294925233); /* 11 */
	FF(b, c, d, a, in11, S14, 2304563134); /* 12 */
	FF(a, b, c, d, in12, S11, 1804603682); /* 13 */
	FF(d, a, b, c, in13, S12, 4254626195); /* 14 */
	FF(c, d, a, b, in14, S13, 2792965006); /* 15 */
	FF(b, c, d, a, in15, S14, 1236535329); /* 16 */

	/* Round 2 */
#define S21 5
#define S22 9
#define S23 14
#define S24 20
	GG(a, b, c, d, in1, S21, 4129170786); /* 17 */
	GG(d, a, b, c, in6, S22, 3225465664); /* 18 */
	GG(c, d, a, b, in11, S23, 643717713); /* 19 */
	GG(b, c, d, a, in0, S24, 3921069994); /* 20 */
	GG(a, b, c, d, in5, S21, 3593408605); /* 21 */
	GG(d, a, b, c, in10, S22, 38016083); /* 22 */
	GG(c, d, a, b, in15, S23, 3634488961); /* 23 */
	GG(b, c, d, a, in4, S24, 3889429448); /* 24 */
	GG(a, b, c, d, in9, S21, 568446438); /* 25 */
	GG(d, a, b, c, in14, S22, 3275163606); /* 26 */
	GG(c, d, a, b, in3, S23, 4107603335); /* 27 */
	GG(b, c, d, a, in8, S24, 1163531501); /* 28 */
	GG(a, b, c, d, in13, S21, 2850285829); /* 29 */
	GG(d, a, b, c, in2, S22, 4243563512); /* 30 */
	GG(c, d, a, b, in7, S23, 1735328473); /* 31 */
	GG(b, c, d, a, in12, S24, 2368359562); /* 32 */

	/* Round 3 */
#define S31 4
#define S32 11
#define S33 16
#define S34 23
	HH(a, b, c, d, in5, S31, 4294588738); /* 33 */
	HH(d, a, b, c, in8, S32, 2272392833); /* 34 */
	HH(c, d, a, b, in11, S33, 1839030562); /* 35 */
	HH(b, c, d, a, in14, S34, 4259657740); /* 36 */
	HH(a, b, c, d, in1, S31, 2763975236); /* 37 */
	HH(d, a, b, c, in4, S32, 1272893353); /* 38 */
	HH(c, d, a, b, in7, S33, 4139469664); /* 39 */
	HH(b, c, d, a, in10, S34, 3200236656); /* 40 */
	HH(a, b, c, d, in13, S31, 681279174); /* 41 */
	HH(d, a, b, c, in0, S32, 3936430074); /* 42 */
	HH(c, d, a, b, in3, S33, 3572445317); /* 43 */
	HH(b, c, d, a, in6, S34, 76029189); /* 44 */
	HH(a, b, c, d, in9, S31, 3654602809); /* 45 */
	HH(d, a, b, c, in12, S32, 3873151461); /* 46 */
	HH(c, d, a, b, in15, S33, 530742520); /* 47 */
	HH(b, c, d, a, in2, S34, 3299628645); /* 48 */

	/* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
	II(a, b, c, d, in0, S41, 4096336452); /* 49 */
	II(d, a, b, c, in7, S42, 1126891415); /* 50 */
	II(c, d, a, b, in14, S43, 2878612391); /* 51 */
	II(b, c, d, a, in5, S44, 4237533241); /* 52 */
	II(a, b, c, d, in12, S41, 1700485571); /* 53 */
	II(d, a, b, c, in3, S42, 2399980690); /* 54 */
	II(c, d, a, b, in10, S43, 4293915773); /* 55 */
	II(b, c, d, a, in1, S44, 2240044497); /* 56 */
	II(a, b, c, d, in8, S41, 1873313359); /* 57 */
	II(d, a, b, c, in15, S42, 4264355552); /* 58 */
	II(c, d, a, b, in6, S43, 2734768916); /* 59 */
	II(b, c, d, a, in13, S44, 1309151649); /* 60 */
	II(a, b, c, d, in4, S41, 4149444226); /* 61 */
	II(d, a, b, c, in11, S42, 3174756917); /* 62 */
	II(c, d, a, b, in2, S43, 718787259); /* 63 */
	II(b, c, d, a, in9, S44, 3951481745); /* 64 */

	a += a0;
	b += b0;
	c += c0;
	d += d0;

	*a1 = a;
	*b1 = b;
	*c1 = c;
	*d1 = d;
}


__device__ __host__ bool next(uint8_t* length, char* word, uint32_t increment) {
	uint32_t idx = 0;
	uint32_t add = 0;

	while (increment > 0 && idx < CONST_WORD_LIMIT) {
		if (idx >= *length && increment > 0) {
			increment--;
		}

		add = increment + word[idx];
		word[idx] = add % CONST_CHARSET_LENGTH;
		increment = add / CONST_CHARSET_LENGTH;
		idx++;
	}

	if (idx > *length) {
		*length = idx;
	}

	if (idx > CONST_WORD_LIMIT) {
		return false;
	}

	return true;
}

__global__ void md5_crack(uint8_t* wordLength, char* charsetWord, uint32_t* searched_hash, char* word_cracked) {
	uint32_t idx = (blockIdx.x * blockDim.x + threadIdx.x) * HASHES_PER_KERNEL;
	__shared__ char sharedCharset[CONST_CHARSET_LIMIT];

	/* Thread variables */
	char threadCharsetWord[CONST_WORD_LIMIT];
	char threadTextWord[CONST_WORD_LIMIT];
	uint8_t threadWordLength = *wordLength;
	uint32_t threadHash01, threadHash02, threadHash03, threadHash04;

	memcpy(threadCharsetWord, charsetWord, CONST_WORD_LIMIT);
	memcpy(sharedCharset, d_abedeca, sizeof(uint8_t) * CONST_CHARSET_LIMIT);

	/* Increment current word by thread index */
	next(&threadWordLength, threadCharsetWord, idx);

	for (uint32_t hash = 0; hash < HASHES_PER_KERNEL; hash++) {
		for (uint32_t i = 0; i < threadWordLength; i++) {
			threadTextWord[i] = sharedCharset[threadCharsetWord[i]];
		}



		md5_hash((unsigned char*)threadTextWord, threadWordLength, &threadHash01, &threadHash02, &threadHash03, &threadHash04);

		if (threadHash01 == searched_hash[0] && threadHash02 == searched_hash[1] && threadHash03 == searched_hash[2] && threadHash04 == searched_hash[3]) {

			memcpy(word_cracked, threadTextWord, threadWordLength);
		}
		if (!next(&threadWordLength, threadCharsetWord, 1)) {
			break;
		}
	}
}

void crack_md5(char* input, int pass_length) {
	char* word;
	int CONST_PASSWORD_LENGTH = pass_length;
	cudaMallocManaged(&word, CONST_PASSWORD_LENGTH);
	char abeceda[CONST_CHARSET_LIMIT];
	char* heslo = (char*)malloc(CONST_PASSWORD_LENGTH);

	uint8_t* wordLength;
	cudaMallocManaged(&wordLength, sizeof(uint8_t));



	unsigned char* hex = new unsigned char[256];
	memcpy(hex, input, 32 + 1);

	uint32_t* md5Hash;
	cudaMallocManaged(&md5Hash, 4 * sizeof(uint32_t));
	for (int i = 0; i < 4; i++)
	{
		char tmp[16];

		memcpy(tmp, hex + i*8, 8);
		sscanf(tmp, "%x", &md5Hash[i]);
		md5Hash[i] = (md5Hash[i] & 0xFF000000) >> 24 | (md5Hash[i] & 0x00FF0000) >> 8 | (md5Hash[i] & 0x0000FF00) << 8 | (md5Hash[i] & 0x000000FF) << 24;
	}



	printf("hladany hash: %s", hex);


	memset(word, 0, CONST_PASSWORD_LENGTH);
	memset(heslo, 0, CONST_PASSWORD_LENGTH);
	memcpy(abeceda, CONST_CHARSET, CONST_CHARSET_LENGTH);
	*wordLength = CONST_PASSWORD_LENGTH;

	printf("\nword length: %u", *wordLength);


	cudaSetDevice(0);



	char* d_word, *d_word_cracked;
	cudaMallocManaged((void**)&d_word, sizeof(uint8_t) * CONST_PASSWORD_LENGTH);
	cudaMallocManaged((void**)&d_word_cracked, sizeof(uint8_t) * CONST_PASSWORD_LENGTH);



	cudaMemcpyToSymbol(d_abedeca, abeceda, sizeof(uint8_t) * CONST_CHARSET_LIMIT, 0, cudaMemcpyHostToDevice);


	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	while (true) {

		bool result = false;
		bool found = false;


		
		(md5_crack<<<TOTAL_BLOCKS, TOTAL_THREADS>>> (wordLength, d_word, md5Hash, d_word_cracked));
		cudaDeviceSynchronize();
		
		result = next(wordLength, d_word, TOTAL_THREADS * HASHES_PER_KERNEL * TOTAL_BLOCKS);


		
		if ((*d_word_cracked != NULL) && (d_word_cracked[0] != '\0')) {
			std::cout << "\nCracked " << d_word_cracked << std::endl;
			break;
		}


		if (!result || found) {
			if (!result && !found) {
				std::cout << "\nFound nothing (host)" << std::endl;
			}

			break;
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();




	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "Hash computation time: " << duration << "us";



	cudaFree(word);
}

char *bin2hex(const unsigned char *bin, size_t len)
{
	char   *out;
	size_t  i;

	if (bin == NULL || len == 0)
		return NULL;

	out = (char *) malloc(len * 2 + 1);
	for (i = 0; i < len; i++) {
		out[i * 2] = "0123456789ABCDEF"[bin[i] >> 4];
		out[i * 2 + 1] = "0123456789ABCDEF"[bin[i] & 0x0F];
	}
	out[len * 2] = '\0';

	return out;
}
