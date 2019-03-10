#pragma once
#include "pch.h"

class Utility
{
public:
	Utility();
	~Utility();
	static bool hash_compare(const char* first_hash, const char* second_hash, int size);
	static void generate_random_password(char* password, int length);
	static void print_human_time(long duration);
	static void std_array_to_c_array(const arr& input, char* output, size_t length);
	static void c_array_to_std_array(const char* input, arr& output, size_t length);
	static char hex_pair_to_ascii_char(const char* hex);
	static void ascii_char_to_hex_pair(const char ascii, char* pair);
};

