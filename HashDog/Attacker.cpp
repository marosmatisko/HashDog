#include "pch.h"
#include "Attacker.h"
#include "Utility.h"

using namespace std;

Attacker::Attacker(int thread_num) : thread_num(thread_num) {
	md5_hash = new Md5Hash();
}

Attacker::~Attacker() {
	delete md5_hash;
	delete bfg;

	delete[] md5_digest;
	delete[] searched_digest;
	delete[] input_string;
}

bool Attacker::attack_finished() {
	return Utility::hashCompare((const char*)searched_digest, (const char*)md5_digest, hash);
}

void Attacker::perform_attack(int password_length, attack_mode mode, attacked_hash hash,
	unsigned char* searched_digest) {
	
	initialize_attack(mode, hash, password_length, searched_digest);
	bfg = new BruteForceGenerator(password_length);
	//bfg->set_start_value(5, 0);

	do {
		bfg->set_password_candidate(input_string);
		md5_hash->hash_message(input_string, md5_digest);
	} while (!attack_finished());
	cout << "Found it!" << endl;
}

void Attacker::print_proof() {
	char* mdString = new char[33];
	char* mdString2 = new char[33];

	for (int i = 0; i < 16; i++) {
		sprintf(&mdString[i * 2], "%02X", (unsigned int)searched_digest[i]);
		sprintf(&mdString2[i * 2], "%02X", (unsigned int)md5_digest[i]);
	}

	cout << "Old hash: " << mdString << endl;
	cout << "New hash: " << mdString2 << endl;
	cout << "Original message was: " << input_string << endl;

	delete[] mdString; 
	delete[] mdString2;
}

void Attacker::initialize_attack(attack_mode mode, attacked_hash hash, int password_length, unsigned char* searched_digest) {
	this->mode = mode;
	this->hash = hash;
	md5_digest = new unsigned char[hash];
	this->searched_digest = searched_digest;
	input_string = new char[password_length + 1];
}

