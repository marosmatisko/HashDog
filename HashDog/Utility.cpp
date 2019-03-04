#include "Utility.h"
#include "pch.h"


Utility::Utility() {}

Utility::~Utility() {}

bool Utility::hash_compare(const char* first_hash, const char* second_hash, int size) {
	for (int i = 0; i < size; ++i) {
		if (first_hash[i] != second_hash[i]) {
			return false;
		}
	}
	return true;
}

void Utility::generate_random_password(char * password, int length) {
	int index;
	for (int i = 0; i < length; ++i) {
		index = rand() % BruteForceGenerator::get_characters_count();
		password[i] = BruteForceGenerator::getCharacter(index);
	}
	password[length] = '\0';
}

void Utility::print_human_time(long duration) {
	int hours = (int)(duration / (1000 * 3600));
	int minutes = (int)(duration / (1000 * 60)) % 60;
	int seconds = (int)(duration / 1000) % 60;
	std::cout << "Hash computation time: " << hours << ":" << minutes << ":" <<
		seconds << "." << duration % 1000 << std::endl;
}

void Utility::std_array_to_c_array(const arr& input, char* output, size_t length) {
	memcpy(output, &input, length + 1);
}

void Utility::c_array_to_std_array(const char* input, arr& output, size_t length) {
	memcpy(&output, input, length + 1);
}

