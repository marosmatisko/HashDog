#include "pch.h"
#include "BruteForceGenerator.h"


BruteForceGenerator::BruteForceGenerator(int password_size) { 
	lenght = password_size;
	internal_pointers = new std::bitset<7>[password_size];
}

BruteForceGenerator::~BruteForceGenerator() {
	delete[] internal_pointers;
}

void BruteForceGenerator::increment_pointer(int index) {
	
	for (size_t i = 0; i < 7; ++i) {
		if (internal_pointers[index][i] == 0) {  // There will be no carry
			for (int j = 0; j <= i; ++j) {
				internal_pointers[index][j].flip();
			}
			break;
		}
	}
	if (internal_pointers[index].to_ulong() >= char_count) {
		internal_pointers[index].reset();
		increment_pointer(index - 1);
	}
}

void BruteForceGenerator::get_password_candidate(char *candidate) {
	//char* candidate_temp = new char[lenght+1];
	for (int i = 0; i < lenght; ++i) {
		candidate[i] = letters[(uint8_t)internal_pointers[i].to_ulong()];
	}
	candidate[lenght] = '\0';
	increment_pointer(lenght - 1);
}


