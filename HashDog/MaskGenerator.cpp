#include "pch.h"
#include "MaskGenerator.h"


MaskGenerator::MaskGenerator(const char* input) {
	int mask_size = 0, template_index = 0, input_size = 0;
	for (int i = 0; i < strlen(input); ++i) {
		if (input[i] != '%') { ++input_size; }
	}

	candidate_template = new char[input_size + 1];
	for (int i = 0; i < strlen(input); ++i) {
		if (input[i] == '%') {
			++mask_size;
			++i;
			switch (input[i]) {
			case 'a': { candidate_template[template_index] = full_alphabet; break; }
			case 'd': { candidate_template[template_index] = numbers; break; }
			case 'l': { candidate_template[template_index] = small_alphabet; break; }
			case 's': { candidate_template[template_index] = special_chars; break; }
			case 'u': { candidate_template[template_index] = big_alphabet; break; }
			case 'c': { candidate_template[template_index] = any_char; break; }
			}
		} else {
			candidate_template[template_index] = input[i];
		}
		++template_index;
	}
	candidate_template[input_size] = '\0';
	length = input_size;
	this->mask_size = mask_size;
	internal_pointers = new std::bitset<pointer_size>[mask_size];
}

MaskGenerator::~MaskGenerator() {
	delete[] internal_pointers;
}

int MaskGenerator::get_inkrement_limit(int index) {
	int temp_index = 0, limit = alphabet_size;
	
	for (int i = 0; i < strlen(candidate_template); ++i) {
		if (candidate_template[i] <= character_mask_size) {
			if (index == temp_index) {
				switch (candidate_template[i]) {
				case full_alphabet: { limit = 2 * alphabet_size; break; }
				case special_chars: { limit = specials_size; break; }
				case numbers:  { limit = 10; break; }
				case any_char: { limit = char_count; break; }
				default: { break; }
				}
				break;
			} else {
				++temp_index;
			}
		}		
	}
	return limit;
}

void MaskGenerator::increment_pointer(int index) {
	for (size_t i = 0; i < pointer_size; ++i) {
		if (internal_pointers[index][i] == 0) {
			for (int j = 0; j <= i; ++j) {
				internal_pointers[index][j].flip();
			}
			break;
		}
	} //set character to starting character and increment upper char pointer
	if (internal_pointers[index].to_ulong() >= (unsigned long)get_inkrement_limit(index)) {
		internal_pointers[index].reset();
		increment_pointer(index - 1);
	}
}

void MaskGenerator::set_password_candidate(char * candidate) {
	int pointer_index = 0;
	for (size_t i = 0; i < length; ++i) {
		if (candidate_template[i] > character_mask_size) {
			candidate[i] = candidate_template[i];
		} else {
			candidate[i] = get_character_by_mask((character_mask)candidate_template[i], (uint8_t)internal_pointers[pointer_index].to_ulong());
			++pointer_index;
		}
	}
	candidate[length] = '\0';
	increment_pointer((int)mask_size - 1);
}

void MaskGenerator::set_start_value(int value, int pointer_index) {
	int temp_value;
	for (int i = pointer_size; i > 0; ) {
		temp_value = (int)pow(2, --i);
		if (value >= temp_value) {
			internal_pointers[pointer_index].set(i);
			value -= temp_value;
		}
		else {
			internal_pointers[pointer_index].reset(i);
		}
	}
}

int MaskGenerator::get_first_index_limit() {
	return get_inkrement_limit(0);
}

char MaskGenerator::get_character_by_mask(character_mask mask, int index) {
	char result_char;

	switch (mask) {
	case small_alphabet: { result_char = lowercase[index]; break; }
	case big_alphabet: { result_char = uppercase[index]; break; }
	case full_alphabet: { result_char = alphabet[index]; break; }
	case special_chars: { result_char = special_characters[index]; break; }
	case numbers: { result_char = index + '0'; break; }
	case any_char: { result_char = all_symbols[index]; break; }
	}

	return result_char;
}
