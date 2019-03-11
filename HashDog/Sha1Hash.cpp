#include "Sha1Hash.h"
#include "pch.h"


Sha1Hash::Sha1Hash() { hash_size = 160; }

Sha1Hash::~Sha1Hash() {}

void Sha1Hash::hash_message(char * message, unsigned char * computed_digest) {
	SHA1_Init(&sha1_hash);
	SHA1_Update(&sha1_hash, message, strlen(message));
	SHA1_Final(computed_digest, &sha1_hash);
	computed_digest[hash_size/8] = '\0';
}
