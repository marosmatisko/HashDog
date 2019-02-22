#pragma once
#include <openssl/md5.h>

class Md5Hash
{
private:
	MD5_CTX md5_hash;
	int hash_size;

public:
	Md5Hash();
	~Md5Hash();
	void hash_message(char* message, unsigned char* md5_digest);
};

