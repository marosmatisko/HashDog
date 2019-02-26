#pragma once
#include "pch.h"

class DictionaryReader : public CandidateGenerator
{
public:
	DictionaryReader(int password_size);
	~DictionaryReader();
};

