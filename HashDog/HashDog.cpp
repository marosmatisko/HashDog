// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


using namespace std;
using namespace std::chrono;

// global variables
char* searched_input, *additional_param, *input_digest;
unsigned char* searched_digest;
unsigned short pass_length = 6;
Attacker::attacked_hash used_hash = Attacker::attacked_hash::md5;
Attacker::attack_mode attack = Attacker::attack_mode::brute_force;

bool param_process(int argc, char* argv[]) {
	ArgParse* parser = new ArgParse(argc, argv);
	bool params_valid;

	if (params_valid = parser->args_are_valid()) {
		pass_length = parser->get_password_lenght();
		if (!parser->input_is_hash()) {
			searched_input = new char[strlen(argv[1])];
			parser->set_input(searched_input);
		}
		else {
			input_digest = new char[strlen(argv[1])];
			parser->set_input(input_digest);
		}
		used_hash = parser->get_hash();
		attack = parser->get_mode();
		if (attack != Attacker::brute_force) {
			additional_param = new char[strlen(argv[4])];
			parser->set_optional_param(additional_param);
		}
		cout << "Params set succesfully!" << endl;
	}
	return params_valid;
}

void write_log(int argc, char* argv[], long duration) {
	ofstream log_file;
	log_file.open(log_filename, std::fstream::app);
	for (int i = 1; i < argc; ++i) {
		log_file.write(argv[i], strlen(argv[i]));
		log_file << ";";
	}
	log_file << duration << ";" << endl;
	log_file.close();
}	

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	if (!param_process(argc, argv)) return 1;

	if (searched_input)
		cout << "Searching for password: " << searched_input << endl;
	else
		cout << "Searching for password with hash: " << endl << input_digest << endl;

	Attacker *black_hat = new Attacker(thread_num);
	searched_digest = new unsigned char[used_hash / 8 + 1];

	if (input_digest != nullptr) {
		for (int i = 0; i < strlen(input_digest); i += 2) {
			searched_digest[i / 2] = Utility::hex_pair_to_ascii_char(input_digest + i);
		}
		searched_digest[used_hash / 8] = '\0';
	} else {
		CustomHash* hash;
		switch (used_hash) {
		case Attacker::attacked_hash::md5:
			hash = new Md5Hash(); break;
		case Attacker::attacked_hash::sha1:
			hash = new Sha1Hash(); break;
		case Attacker::attacked_hash::sha256:
			hash = new Sha256Hash(); break;
		default:
			hash = new CustomHash();
		}
		hash->hash_message(searched_input, searched_digest);
	}

	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(pass_length, attack, used_hash, searched_digest, additional_param);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	if (black_hat->was_attack_successful())
		black_hat->print_proof(false);

	volatile long duration = (long)duration_cast<milliseconds>(t2 - t1).count();
	Utility::print_human_time(duration);

	if (logging_to_file) write_log(argc, argv, duration);
}
