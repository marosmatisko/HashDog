#pragma once
#include <openssl/sha.h>
#include "CustomHash.h"

class Sha1Hash : public CustomHash
{
private:
	SHA_CTX sha1_hash;

public:
	Sha1Hash();
	~Sha1Hash();
	void hash_message(char* message, unsigned char* computed_digest);
};

