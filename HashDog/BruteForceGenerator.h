#pragma once
#include <bitset>

constexpr auto char_count = 77;

class BruteForceGenerator
{
private:
	const char letters[char_count] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
					 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
					 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
					 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
					 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
					 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
					 '0', '1', '2', '3', '4', '5', '6', '7', '8',
					 '9', ' ', ',', '-', '_', '.', '?', '!', '&',
					 '@', '#', '$', '%', '^', '*', ':' };
	int lenght;
	std::bitset<7> *internal_pointers;
	
	void increment_pointer(int index);

public:
	BruteForceGenerator(int password_size);
	~BruteForceGenerator();
	void get_password_candidate(char *candidate);
};

 