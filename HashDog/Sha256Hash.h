#pragma once
#include <openssl/sha.h>
#include "pch.h"


class Sha256Hash : public CustomHash
{
public:
	Sha256Hash();
	~Sha256Hash();
	void hash_message(char* message, unsigned char* computed_digest);

private:
	SHA256_CTX sha256_hash;
};

