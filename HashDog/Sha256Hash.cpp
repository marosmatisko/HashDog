#include "pch.h"
#include "Sha256Hash.h"


Sha256Hash::Sha256Hash() { hash_size = 256; }

Sha256Hash::~Sha256Hash() {}

void Sha256Hash::hash_message(char * message, unsigned char * computed_digest) {
	SHA256_Init(&sha256_hash);
	SHA256_Update(&sha256_hash, message, strlen(message));
	SHA256_Final(computed_digest, &sha256_hash);
	computed_digest[hash_size/8] = '\0';
}
