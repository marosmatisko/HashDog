#include "Attacker.h"
#include "pch.h"


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
	return Utility::hash_compare((const char*)searched_digest, (const char*)computed_digest[index], hash/8);
}

void Attacker::thread_attack(int thread_id) {
	do {
		generators.at(thread_id)->set_password_candidate(input_string[thread_id]);
		hashes.at(thread_id)->hash_message(input_string[thread_id], computed_digest[thread_id]);
	} while (!attack_finished(thread_id) && successful_thread == -1);

	if (successful_thread == -1) {
		std::lock_guard<std::mutex> lock(locker);
		successful_thread = thread_id;
	}
}

void Attacker::reader_thread_attack(const char* dictionary_filename, std::atomic<int>& succesful_thread) {
	DictionaryReader *reader = new DictionaryReader(password_length, dictionary_filename);
	reader->read_file(succesful_thread);
}

void Attacker::perform_attack(int password_length, attack_mode mode, attacked_hash hash,
	unsigned char* searched_digest, const char* additional_param) {

	initialize_attack(mode, hash, password_length, searched_digest);
	initialize_vectors(additional_param);
	
	std::vector<thread> readers;
	if (mode == Attacker::attack_mode::dictionary) {
		readers.push_back(thread(&Attacker::reader_thread_attack, this, additional_param, std::ref(successful_thread)));
	} else {
		compute_thread_offset(mode);
	}

	for (int i = 0; i < thread_num; ++i) {
		thread_pool[i] = thread(&Attacker::thread_attack, this, i);
	}

	if (mode == Attacker::attack_mode::dictionary && !readers.empty()) {
		readers.front().join();
	}

	for (int i = 0; i < thread_num; ++i) {
		thread_pool[i].join();
	}

	if (successful_thread >= 0) {
		cout << "Found it!" << endl;
	} else {
		cout << "Cannot found password!" << endl;
	}
}

bool Attacker::was_attack_successful() {
	return successful_thread >= 0;
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
	this->password_length = password_length;

	input_string = new char*[thread_num];
	computed_digest = new unsigned char*[thread_num];

	for (int i = 0; i < thread_num; ++i) {
		computed_digest[i] = new unsigned char[hash];
		input_string[i] = new char[password_length + 1];
	}
	this->searched_digest = searched_digest;
}

void Attacker::initialize_vectors(const char* additional_param) {
	for (int i = 0; i < thread_num; ++i) {
		switch (mode) {
		case Attacker::brute_force:
			generators.push_back(new BruteForceGenerator(password_length));
			break;
		case Attacker::dictionary:
			generators.push_back(new DictionaryReader(password_length, ""));
			break;
		case Attacker::mask:
			generators.push_back(new MaskGenerator(additional_param));
		}

		switch (hash) {
		case Attacker::md5:
			hashes.push_back(new Md5Hash());
			break;
		case Attacker::sha1:
			hashes.push_back(new Sha1Hash());
			break;
		case Attacker::sha256:
			hashes.push_back(new Sha256Hash());
			break;
		}
	}
}

void Attacker::compute_thread_offset(attack_mode mode) { //TODO: multiplexing over more bits
	int offset, index = 0;
	int characters_count = (mode == brute_force) ? char_count : static_cast<MaskGenerator*>(generators.at(0))->get_first_index_limit();
	for (int i = 0; i < thread_num; ++i) {
		offset = i*(characters_count / thread_num);
		if (mode == brute_force) {
			static_cast<BruteForceGenerator*>(generators.at(i))->set_start_value(offset, index);
		} else {
			static_cast<MaskGenerator*>(generators.at(i))->set_start_value(offset, index);
		}
	}
}
