#include "pch.h"
#include "Attacker.h"
#include "Utility.h"

using namespace std;

Attacker::Attacker(int thread_num) : thread_num(thread_num) {
	thread_pool = new thread[thread_num];
	successful_thread = -1;
}

Attacker::~Attacker() {
	hashes.clear();
	generators.clear();

	for (int i = 0; i < thread_num; ++i) {
		delete[] input_string[i];
		delete[] computed_digest[i];
	}

	delete[] input_string;
	delete[] computed_digest;
	delete[] searched_digest;
}

bool Attacker::attack_finished(int index) {
	return Utility::hashCompare((const char*)searched_digest, (const char*)computed_digest[index], hash);
}

void Attacker::thread_attack(int thread_id) {
	do {
		generators.at(thread_id)->set_password_candidate(input_string[thread_id]);
		hashes.at(thread_id)->hash_message(input_string[thread_id], computed_digest[thread_id]);
	} while (!attack_finished(thread_id) && successful_thread < 0);

	if (successful_thread < 0) {
		locker.lock();
		successful_thread = thread_id;
		locker.unlock();
	}
}

void Attacker::perform_attack(int password_length, attack_mode mode, attacked_hash hash,
	unsigned char* searched_digest) {

	initialize_attack(mode, hash, password_length, searched_digest);
	for (int i = 0; i < thread_num; ++i) {
		generators.push_back(new BruteForceGenerator(password_length));
		switch (hash)
		{
		case Attacker::md5:
			hashes.push_back(new Md5Hash());
			break;
		case Attacker::sha1:
			hashes.push_back(new Sha1Hash());
			break;
		default:
			break;
		}
		
	}
	
	compute_thread_offset();

	for (int i = 0; i < thread_num; ++i) {
		thread_pool[i] = thread(&Attacker::thread_attack, this, i);
	}

	for (int i = 0; i < thread_num; ++i) {
		thread_pool[i].join();
	}

	if (successful_thread >= 0) {
		cout << "Found it!" << endl;
	}
	else {
		cout << "Cannot found password!" << endl;
	}
}

void Attacker::print_proof() {
	char* mdString = new char[hash/4+1];
	char* mdString2 = new char[hash/4+1];

	for (int i = 0; i < hash/8; ++i) {
		sprintf(&mdString[i * 2], "%02X", (unsigned int)searched_digest[i]);
		sprintf(&mdString2[i * 2], "%02X", (unsigned int)computed_digest[successful_thread][i]);
	}

	cout << "Old hash: " << mdString << endl;
	cout << "New hash: " << mdString2 << endl;
	cout << "Original message was: " << input_string[successful_thread] << endl;

	delete[] mdString; 
	delete[] mdString2;
}

void Attacker::initialize_attack(attack_mode mode, attacked_hash hash, int password_length, unsigned char* searched_digest) {
	this->mode = mode;
	this->hash = hash;

	input_string = new char*[thread_num];
	computed_digest = new unsigned char*[thread_num];

	for (int i = 0; i < thread_num; ++i) {
		computed_digest[i] = new unsigned char[hash];
		input_string[i] = new char[password_length + 1];
	}
	this->searched_digest = searched_digest;
}

void Attacker::compute_thread_offset() {
	int offset, index, characters_count = BruteForceGenerator::get_characters_count();
	for (int i = 0; i < thread_num; ++i) {
		offset = i*(characters_count / thread_num); index = 0;
		generators.at(i)->set_start_value(offset, index);
	}
}
