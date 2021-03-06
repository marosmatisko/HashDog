#pragma once
#include <openssl/md5.h>
#include "pch.h"


class Md5Hash : public CustomHash
{
private:
	MD5_CTX md5_hash;

public:
	Md5Hash();
	~Md5Hash();
	void hash_message(char* message, unsigned char* computed_digest);
};

