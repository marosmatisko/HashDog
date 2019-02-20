// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <chrono>

#include "openssl/md5.h"

using namespace std;
using namespace std::chrono;

const int TEST_ROUNDS = 35*1000*1000;
const short PASSWORD_LENGTH = 4;
const int HASH_SIZE = 128;

char letters[] = {   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
					 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
					 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
					 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
					 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
					 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
					 '0', '1', '2', '3', '4', '5', '6', '7', '8',
					 '9', ' ', ',', '-', '_', '.', '?', '!', '&',
					 '@', '#', '$', '%', '^', '*', ':'};

bool hashCompare(const char* first_hash, const char* second_hash ) {
	for (int i = 0; i < HASH_SIZE; ++i) {
		if (first_hash[i] != second_hash[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	unsigned char md5_digest[HASH_SIZE];
	int main_index = 0;

	char searched_string[PASSWORD_LENGTH + 1] = ":z^6";
	char input_string[PASSWORD_LENGTH + 1] = "";
	int letter_size = sizeof(letters) / sizeof(char);

	MD5_CTX md5_hash;
	MD5_Init(&md5_hash);

	unsigned char searched_digest[HASH_SIZE];
	MD5_Update(&md5_hash, searched_string, strlen(searched_string));
	MD5_Final(searched_digest, &md5_hash);
	//MD5((unsigned char*)&searched_string, strlen(searched_string), (unsigned char*)&searched_digest);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < TEST_ROUNDS; ++i) {
		for (int j = 0; j < PASSWORD_LENGTH; ++j) {
			int denominator = (unsigned int) pow(letter_size, (PASSWORD_LENGTH - j - 1));
			int index = main_index / denominator;
			input_string[j] = letters[index % letter_size];
		}

		if (strcmp((const char*)input_string, (const char*)searched_string) == 0) {
			cout << "This should be end!" << endl;
		}

		
		MD5_Init(&md5_hash);
		MD5_Update(&md5_hash, input_string, strlen(input_string));
		MD5_Final(md5_digest, &md5_hash);//*/
		//MD5((unsigned char*)&input_string, strlen(input_string), (unsigned char*)&md5_digest);
		++main_index;

		if (hashCompare((const char*)searched_digest, (const char*)md5_digest)) {
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
	cout << duration;

}