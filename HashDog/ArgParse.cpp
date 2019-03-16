#include "pch.h"
#include "ArgParse.h"

using namespace std;

ArgParse::ArgParse(int argc, char* argv[]) : argc(argc), args_corrupted(false), argvs(&argv) {
	switch (argv[3][1]) {
	case 'b': 
		process_bruteforce(); break;
	case 'd': 
		process_dictionary(); break;
	case 'm': 
		process_mask(); break;
	default: 
		cout << "Invalid attack mode!" << endl;
		args_corrupted = true;
	}
}

ArgParse::~ArgParse() {}

bool ArgParse::args_are_valid() {
	return !args_corrupted;
}

bool ArgParse::input_is_hash() {
	return strlen((*argvs)[1]) > 20;
}

Attacker::attack_mode ArgParse::get_mode() {
	Attacker::attack_mode mode = Attacker::attack_mode::brute_force;
	if ((*argvs)[3][1] == 'm') 
		mode = Attacker::attack_mode::mask;
	else if ((*argvs)[3][1] == 'd')
		mode = Attacker::attack_mode::dictionary;
	return mode;
}

Attacker::attacked_hash ArgParse::get_hash() {
	Attacker::attacked_hash hash = Attacker::attacked_hash::md5;
	if ((*argvs)[2][1] == 's' || strlen((*argvs)[1]) == 40 || strlen((*argvs)[1]) == 64) {
		if ((*argvs)[2][2] == '1' || strlen((*argvs)[1]) == 40) hash = Attacker::attacked_hash::sha1;
		else if ((*argvs)[2][2] == '2' || strlen((*argvs)[1]) == 64) hash = Attacker::attacked_hash::sha256;
	}
	return hash;
}

void ArgParse::set_optional_param(char* param) {
	strcpy(param, (*argvs)[4]);
}

void ArgParse::set_input(char* input) {
	strcpy(input, (*argvs)[1]);
}

int ArgParse::get_password_lenght() {
	int result = input_is_hash() ? atoi((*argvs)[2]) : (int)strlen((*argvs)[1]);
	result = result > 65500 ? (65536 - result) : abs(result);
	if (result < 4 || result > 20) return 0;
	else return result;
}

void ArgParse::process_bruteforce() {
	if (argc != 4) {
		cout << "Bad number of arguments for bruteforce attack!" << endl;
		args_corrupted = true;
	}
	else process_input_hash();
}

void ArgParse::process_dictionary() {
	if (argc != 5) {
		cout << "Bad number of arguments for dictionary attack!" << endl;
		args_corrupted = true;
	} else {
		ifstream tester((*argvs)[4]);
		if (!tester.is_open()) {
			cout << "Dictionary file is not valid!" << endl;
			args_corrupted = true;
		}
		else process_input_hash();
	}
}

void ArgParse::process_mask() {
	if (argc != 5) {
		cout << "Bad number of arguments for mask attack!" << endl;
		args_corrupted = true;
	} else {
		int mask_len = (int)strlen((*argvs)[4]);
		int input_len = get_password_lenght();
		if (mask_len < input_len || mask_len > (2*input_len)) {
			cout << "Mask length is not valid!" << endl;
			args_corrupted = true;
		}
		else process_input_hash();
	}
}

void ArgParse::process_input_hash() {
	(strlen((*argvs)[1]) > 20) ? process_hash() : process_input();
}

void ArgParse::process_hash_function() {
	if (!(((*argvs)[2][1] == 'm') || ((*argvs)[2][1] == 's' && ((*argvs)[2][2] == '1' || (*argvs)[2][2] == '2')))) {
		cout << "Bad hash function option!" << endl;
		args_corrupted = true;
	}
}

void ArgParse::process_input() {
	if (strlen((*argvs)[1]) >= 4) {
		process_hash_function();
	} else {
		cout << "Input must have at least 4 characters!" << endl;
		args_corrupted = true;
	}
}

void ArgParse::process_hash() {
	if (!(strlen((*argvs)[1]) == 32 || strlen((*argvs)[1]) == 40 || strlen((*argvs)[1]) == 64)) {
		cout << "Hash input must have 32, 40 or 64 uppercase hexadecimal characters!" << endl;
		args_corrupted = true;
	}
}

