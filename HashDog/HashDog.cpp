// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


using namespace std;
using namespace std::chrono;

const short PASSWORD_LENGTH = 6;
const Attacker::attacked_hash HASH = Attacker::attacked_hash::sha256;
const Attacker::attack_mode ATTACK = Attacker::attack_mode::dictionary;


int main() {
	srand((unsigned int)time(NULL));	

	char* searched_string = new char[PASSWORD_LENGTH + 1];
	unsigned char* searched_digest = new unsigned char[HASH + 1]; 

	switch (PASSWORD_LENGTH) {
	case 4: memcpy(searched_string, "what", PASSWORD_LENGTH + 1); break; //~0,25s
	case 5: memcpy(searched_string, "Op1ca", PASSWORD_LENGTH + 1); break; //md5 ~ 36s, sha-1 ~ 39s, sha ~ 40s
	case 6: memcpy(searched_string, "*Amy69", PASSWORD_LENGTH + 1); break; //md5 ~ 1:09:30, 808080 (5k in rockyou) ~ 2.6s, wiggle(20k) ~ 8.6s, drew10 (150k) ~ 60.5s, *Amy69
																			//bud111 (1M) ~ 5:21.7, norado (1M4 - 10% rockyou) ~ 7:18.8, flirt4 (1M8) ~ 8:20, yupa88 (2M5) ~ 11:20
	default:
		Utility::generate_random_password(searched_string, PASSWORD_LENGTH - 3);
	}
		
	cout << "Searching for password: " << searched_string << endl;

	Attacker *black_hat = new Attacker(2);
	CustomHash* hash;
	switch (HASH) {
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
	hash->hash_message(searched_string, searched_digest);

	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(PASSWORD_LENGTH, ATTACK, HASH, searched_digest, "E:\\Documents\\FEKT\\8.sem\\MKRI\\Projekt\\HashDog\\HashDog\\HashDog\\rockyou.txt");
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	if (black_hat->was_attack_successful())
		black_hat->print_proof();

	long duration = (long)duration_cast<milliseconds>(t2 - t1).count();
	Utility::print_human_time(duration);
}