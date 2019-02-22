// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BruteForceGenerator.h"
#include "Md5Hash.h"
#include "Utility.h"
#include <iostream>
#include <chrono>

#include "openssl/md5.h"

using namespace std;
using namespace std::chrono;

const int TEST_ROUNDS = 36*1000*1000;
const short PASSWORD_LENGTH = 8;
const int HASH_SIZE = 129;


int main() {
	int main_index = 0;

	/*
	unsigned char* md5_digest = new unsigned char[HASH_SIZE], searched_digest[HASH_SIZE];
	char searched_string[PASSWORD_LENGTH + 1] = "gaaa";
	char* input_string = new char[PASSWORD_LENGTH + 1];
	*/
	
	unsigned char* md5_digest = new unsigned char[HASH_SIZE];
	unsigned char* searched_digest = new unsigned char[HASH_SIZE];
	char* searched_string = new char[PASSWORD_LENGTH + 1];
	char* input_string = new char[PASSWORD_LENGTH + 1];
	memcpy(searched_string, "aaaabC2?", PASSWORD_LENGTH + 1);
	

	Md5Hash *md5_hash = new Md5Hash();
	BruteForceGenerator *brg = new BruteForceGenerator(PASSWORD_LENGTH);

	md5_hash->hash_message(searched_string, searched_digest);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < TEST_ROUNDS; ++i) { 
		brg->get_password_candidate(input_string);

		if (strcmp((const char*)input_string, (const char*)searched_string) == 0) {
			cout << "This should be end!" << endl;
		}

		md5_hash->hash_message(input_string, md5_digest);
	
		if (Utility::hashCompare((const char*)searched_digest, (const char*)md5_digest, HASH_SIZE)) {
			cout << "Found it!" << endl;
			break;
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	char mdString[33], mdString2[33];

	for (int i = 0; i < 16; i++) {
		sprintf(&mdString[i * 2], "%02X", (unsigned int)searched_digest[i]);
		sprintf(&mdString2[i * 2], "%02X", (unsigned int)md5_digest[i]);
	}

    cout << "Old hash: " << mdString << endl;
	cout << "New hash: " << mdString2 << endl;

	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Hash computation time: " << duration << "us";

	delete[] md5_digest;
	delete[] searched_digest;
	delete[] searched_string;
	delete[] input_string;
}