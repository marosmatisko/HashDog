// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


using namespace std;
using namespace std::chrono;

const short PASSWORD_LENGTH = 6;
const Attacker::attacked_hash HASH = Attacker::attacked_hash::md5;
const Attacker::attack_mode ATTACK = Attacker::attack_mode::dictionary;


int main() {
	srand((unsigned int)time(NULL));	

	char* searched_string = new char[PASSWORD_LENGTH + 1];
	unsigned char* searched_digest = new unsigned char[HASH + 1];

	switch (PASSWORD_LENGTH) {
	case 4: memcpy(searched_string, "1234", PASSWORD_LENGTH + 1); break; //~0,25s
	case 5: memcpy(searched_string, "Op1ca", PASSWORD_LENGTH + 1); break; //md5 ~ 36s, sha-1 ~ 39s, sha ~ 40s
	case 6: memcpy(searched_string, "123456", PASSWORD_LENGTH + 1); break; //md5 ~ 1:09:30, 
	default:
		Utility::generateRandomPassword(searched_string, PASSWORD_LENGTH - 3);
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
	black_hat->perform_attack(PASSWORD_LENGTH, ATTACK, HASH, searched_digest, "E:\\Documents\\FEKT\\8.sem\\MKRI\\Projekt\\HashDog\\HashDog\\HashDog\\Dic500.txt");
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	black_hat->print_proof();

	long duration = (long)duration_cast<milliseconds>(t2 - t1).count();
	Utility::printHumanTime(duration);
}