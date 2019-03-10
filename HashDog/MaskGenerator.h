#pragma once
#include "CandidateGenerator.h"


class MaskGenerator : public CandidateGenerator
{
private:
	const int character_mask_size = 6;
	enum character_mask {
		small_alphabet = 1, big_alphabet, full_alphabet, special_chars, numbers, any_char
	};
	std::bitset<pointer_size> *internal_pointers;
	char* candidate_template;
	int mask_size;

protected:
	char get_character_by_mask(character_mask mask, int index);
	void increment_pointer(int index);
	int get_inkrement_limit(int index);

public:
	MaskGenerator(const char* mask);
	~MaskGenerator();
	void set_password_candidate(char *candidate);
	void set_start_value(int value, int pointer_index);
	int get_first_index_limit();
};

