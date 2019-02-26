#include "Sha1Hash.h"
#include "pch.h"


Sha1Hash::Sha1Hash() { hash_size = 160; }

Sha1Hash::~Sha1Hash() {}

void Sha1Hash::hash_message(char * message, unsigned char * computed_digest) {
	unsigned char* md5_digest_temp = new unsigned char[hash_size + 1];
	SHA1_Init(&sha1_hash);
	SHA1_Update(&sha1_hash, message, strlen(message));
	SHA1_Final(md5_digest_temp, &sha1_hash);
	md5_digest_temp[128] = '\0';
	memcpy(computed_digest, md5_digest_temp, hash_size + 1);
	delete[] md5_digest_temp;
}
