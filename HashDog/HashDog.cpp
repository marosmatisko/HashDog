// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


using namespace std;
using namespace std::chrono;

//brute-force: HashDog.exe <input word> -m/ -b/d/m

// %a - abedeca	%l - lowercase	%u - uppercase	%d - digit	%s - special char	%c - any char
char* searched_input, *additional_param;
unsigned char* searched_digest;
unsigned short pass_length = 6;
Attacker::attacked_hash used_hash = Attacker::attacked_hash::md5;
Attacker::attack_mode attack = Attacker::attack_mode::brute_force;

int param_process(int argc, char* argv[]) {
	if (argc != 4 && argc != 5) {
		cout << "Bad number of arguments!" << endl;
		return -1;
	} else {
		if (strlen(argv[1]) > 20) { //hash mode   
			searched_digest = new unsigned char[strlen(argv[1]) + 1];
			strcpy((char *)searched_digest, argv[1]);

			pass_length = (unsigned short)atoi(argv[2]);
			switch (strlen(argv[1]) * 4)
			{
			case 128:
				used_hash = Attacker::attacked_hash::md5;
				break;
			case 160:
				used_hash = Attacker::attacked_hash::sha1;
				break;
			case 256:
			default:
				used_hash = Attacker::attacked_hash::sha256;
				break;
			}
		} else {
			searched_input = new char[strlen(argv[1]) + 1];
			strcpy((char *)searched_input, argv[1]);
			pass_length = (unsigned short)strlen(argv[1]);

			switch (argv[2][1]) {
			case 'm': 
				used_hash = Attacker::attacked_hash::md5;
				break;
			case 's':
				if (argv[2][2] == '1') {
					used_hash = Attacker::attacked_hash::sha1;
					break;
				}
			default:
				used_hash = Attacker::attacked_hash::sha256;
				break;
			}
		}
			switch (argv[3][1]) {
			case 'm': 
				attack = Attacker::attack_mode::mask; 
				break;
			case 'd':
				attack = Attacker::attack_mode::dictionary; 
				break;
			case 'b': 
			default:
				attack = Attacker::attack_mode::brute_force; 
				break;
			}

			if (attack != Attacker::attack_mode::brute_force) {
				if (argc != 5) {
					cout << "Missing additional parameter!" << endl;
					return -1;
				}
				additional_param = new char[strlen(argv[4])];
				strcpy((char *)additional_param, argv[4]);
			}
	}
	return 1;
}

	//*Amy69 - 37:20
	//d5 ~ 1:09:30, 808080 (5k in rockyou) ~ 2.6s, wiggle(20k) ~ 8.6s, drew10 (150k) ~ 60.5s, *Amy69
	//bud111 (1M) ~ 5:21.7, norado (1M4 - 10% rockyou) ~ 7:18.8, flirt4 (1M8) ~ 8:20, yupa88 (2M5) ~ 11:20
	//Utility::generate_random_password(searched_string, pass_length - 3);

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	if (param_process(argc, argv) < 0) return 1;
	cout << "Searching for password: " << searched_input << endl;

	if (searched_digest == nullptr)
		searched_digest = new unsigned char[used_hash/8 + 1];
	Attacker *black_hat = new Attacker(2);

	if (searched_input != nullptr) {
		CustomHash* hash;
		switch (used_hash) {
		case Attacker::attacked_hash::md5:
			hash = new Md5Hash();
			break;
		case Attacker::attacked_hash::sha1:
			hash = new Sha1Hash();
			break;
		case Attacker::attacked_hash::sha256:
			hash = new Sha256Hash();
			break;
		default:
			hash = new CustomHash();
		}
		hash->hash_message((char *)searched_input, searched_digest);
	}
	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(pass_length, attack, used_hash, searched_digest, (char *)additional_param);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	if (black_hat->was_attack_successful())
		black_hat->print_proof();

	long duration = (long)duration_cast<milliseconds>(t2 - t1).count();
	Utility::print_human_time(duration);
}