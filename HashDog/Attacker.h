#pragma once
#include "CandidateGenerator.h"
#include "CustomHash.h"
#include "pch.h"
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>


class Attacker
{
public:
	enum attack_mode {
		brute_force, dictionary
	};

	enum attacked_hash {
		md5 = 128, sha1 = 160, sha256 = 256
	};

	Attacker(int thread_num);
	~Attacker();
	void perform_attack(int password_length, attack_mode mode, attacked_hash hash, unsigned char* searched_digest, const char* dictionary_filename);
	bool was_attack_successful();
	void print_proof();

protected:
	void initialize_attack(attack_mode mode, attacked_hash hash, int password_length, unsigned char* searched_digest);
	void initialize_vectors(const char* dictionary_filename);
	void compute_thread_offset();
	void thread_attack(int thread_id);
	bool attack_finished(int index);
	void reader_thread_attack(const char* dictionary_filename, std::atomic<int>& succesful_thread);

private:
	int thread_num;
	int password_length;
	std::atomic<int> successful_thread;

	attack_mode mode;
	attacked_hash hash;

	unsigned char* searched_digest;
	unsigned char** computed_digest;
	char** input_string;

	std::thread *thread_pool;
	std::vector<CustomHash*> hashes;
	std::vector<CandidateGenerator*> generators;

	std::mutex locker;
};

