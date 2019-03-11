#include "Md5Hash.h"
#include "pch.h"


Md5Hash::Md5Hash() { hash_size = 128; }

Md5Hash::~Md5Hash() {}

void Md5Hash::hash_message(char* message, unsigned char* computed_digest) {
	MD5_Init(&md5_hash);
	MD5_Update(&md5_hash, message, strlen(message));
	MD5_Final(computed_digest, &md5_hash);
	computed_digest[hash_size / 8] = '\0';
}
