#pragma once
#include "BruteForceGenerator.h"
#include "CustomHash.h"
#include "pch.h"
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
		md5 = 128, sha1 = 160
	};

	Attacker(int thread_num);
	~Attacker();
	void perform_attack(int password_length, attack_mode mode, attacked_hash hash, unsigned char* searched_digest);
	void print_proof();

protected:
	void initialize_attack(attack_mode mode, attacked_hash hash, int password_length, unsigned char* searched_digest);
	void compute_thread_offset();
	void thread_attack(int thread_id);
	bool attack_finished(int index);

private:
	int thread_num;
	int password_length;
	int successful_thread;

	attack_mode mode;
	attacked_hash hash;

	unsigned char* searched_digest;
	unsigned char** computed_digest;
	char** input_string;

	std::thread *thread_pool;
	std::vector<CustomHash*> hashes;
	std::vector<BruteForceGenerator*> generators;

	std::mutex locker;
};

