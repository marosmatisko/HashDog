#include "Md5Hash.h"
#include "pch.h"


Md5Hash::Md5Hash() { hash_size = 128; }

Md5Hash::~Md5Hash() {}

void Md5Hash::hash_message(char* message, unsigned char* digest) {
	unsigned char* digest_temp = new unsigned char[hash_size / 8 + 1];
	MD5_Init(&md5_hash);
	MD5_Update(&md5_hash, message, strlen(message));
	MD5_Final(digest_temp, &md5_hash);
	digest_temp[hash_size/8] = '\0';
	memcpy(digest, digest_temp, hash_size + 1);
	delete[] digest_temp;
}
