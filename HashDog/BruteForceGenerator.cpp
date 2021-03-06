#include "BruteForceGenerator.h"
#include "pch.h"


BruteForceGenerator::BruteForceGenerator(size_t password_size) {
	length = password_size;
	internal_pointers = new std::bitset<pointer_size>[password_size];
}

BruteForceGenerator::~BruteForceGenerator() {
	delete[] internal_pointers;
}

void BruteForceGenerator::increment_pointer(int index) {
	for (size_t i = 0; i < pointer_size; ++i) {
		if (internal_pointers[index][i] == 0) {
			for (int j = 0; j <= i; ++j) {
				internal_pointers[index][j].flip();
			}
			break;
		}
	} //set character to starting character and increment upper char pointer
	if (internal_pointers[index].to_ulong() >= char_count) {
		internal_pointers[index].reset();
		increment_pointer(index - 1);
	}
}

void BruteForceGenerator::set_password_candidate(char *candidate) {
	for (size_t i = 0; i < length; ++i) {
		candidate[i] = all_symbols[(uint8_t)internal_pointers[i].to_ulong()];
	}
	candidate[length] = '\0';
	increment_pointer((int)length - 1);
}

void BruteForceGenerator::set_start_value(int value, int pointer_index) {
	int temp_value;
	for (int i = pointer_size; i > 0; ) {
		temp_value = (int)pow(2, --i);
		if (value >= temp_value) {
			internal_pointers[pointer_index].set(i);
			value -= temp_value;
		} else {
			internal_pointers[pointer_index].reset(i);
		}
	}
}
