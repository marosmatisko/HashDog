#pragma once
#include "pch.h"

class CustomHash {
public:
	CustomHash() {};
	~CustomHash() {};
	virtual void hash_message(char* message, unsigned char* computed_digest) {};

protected:
	int hash_size;
};
