// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BruteForceGenerator.h"
#include "Md5Hash.h"
#include "Utility.h"
#include "Attacker.h"

using namespace std;
using namespace std::chrono;

const short PASSWORD_LENGTH = 4;
const int HASH_SIZE = 129;


int main() {
	int main_index = 0;
	
	Attacker *black_hat = new Attacker(1);

	char* searched_string = new char[PASSWORD_LENGTH + 1];
	unsigned char* searched_digest = new unsigned char[HASH_SIZE];
	memcpy(searched_string, "fero", PASSWORD_LENGTH + 1);
	Md5Hash *md5_hash = new Md5Hash();
	md5_hash->hash_message(searched_string, searched_digest);

	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(PASSWORD_LENGTH, Attacker::attack_mode::brute_force, Attacker::attacked_hash::md5, searched_digest);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	black_hat->print_proof();

	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Hash computation time: " << duration << "us";
}