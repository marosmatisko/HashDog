#include "Md5Hash.h"
#include "pch.h"


Md5Hash::Md5Hash() { hash_size = 128; }

Md5Hash::~Md5Hash() {}

void Md5Hash::hash_message(char* message, unsigned char* md5_digest) {
	unsigned char* md5_digest_temp = new unsigned char[hash_size + 1];
	MD5_Init(&md5_hash);
	MD5_Update(&md5_hash, message, strlen(message));
	MD5_Final(md5_digest_temp, &md5_hash);
	md5_digest_temp[128] = '\0';
	memcpy(md5_digest, md5_digest_temp, hash_size + 1);
	delete[] md5_digest_temp;
}
