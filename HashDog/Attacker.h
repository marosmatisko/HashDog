#pragma once
#include "Md5Hash.h"
#include "BruteForceGenerator.h"

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
	bool attack_finished();

private:
	int thread_num;
	int password_length;
	attack_mode mode;
	attacked_hash hash;

	unsigned char* md5_digest, *searched_digest;
	char* input_string;

	Md5Hash *md5_hash;
	BruteForceGenerator *bfg;
};

