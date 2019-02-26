#include "pch.h"
#include "Sha256Hash.h"


Sha256Hash::Sha256Hash() { hash_size = 256; }

Sha256Hash::~Sha256Hash() {}

void Sha256Hash::hash_message(char * message, unsigned char * digest) {
	unsigned char* digest_temp = new unsigned char[hash_size + 1];
	SHA256_Init(&sha256_hash);
	SHA256_Update(&sha256_hash, message, strlen(message));
	SHA256_Final(digest_temp, &sha256_hash);
	digest_temp[128] = '\0';
	memcpy(digest, digest_temp, hash_size + 1);
	delete[] digest_temp;
}
