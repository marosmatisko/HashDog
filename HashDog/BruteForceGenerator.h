#pragma once
#include <bitset>
#include "Dictionary.h"
#include "pch.h"


class BruteForceGenerator : public CandidateGenerator
{
private:
	std::bitset<pointer_size> *internal_pointers;
	
protected:
	void increment_pointer(int index);

public:
	BruteForceGenerator(size_t password_size);
	~BruteForceGenerator();
	void set_password_candidate(char *candidate);
	void set_start_value(int value, int pointer_index);
	static int get_characters_count();
	static char getCharacter(int index);
};

 