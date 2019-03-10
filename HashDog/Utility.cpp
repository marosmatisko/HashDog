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
		index = rand() % char_count;
		password[i] = all_symbols[index];
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

char Utility::hex_pair_to_ascii_char(const char* hex) {
	char result = hex_char_to_hex_value(hex[0]) << 4;
	return (result | hex_char_to_hex_value(hex[1]));
}

void Utility::ascii_char_to_hex_pair(const char ascii, char* pair) {
	pair[0] = hex_value_to_hex_char((ascii >> 4) & 0xF);
	pair[1] = hex_value_to_hex_char(ascii & 0xF);
}

char Utility::hex_value_to_hex_char(const char hex_value) {
	return (hex_value < 10) ? (hex_value + '0') : (hex_value + 'A' - 10);
}

char Utility::hex_char_to_hex_value(const char hex_char) {
	return (hex_char < 'A') ? (hex_char - '0') : (hex_char - 'A' + 10);
}

