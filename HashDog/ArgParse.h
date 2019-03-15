#pragma once
#include "pch.h"
#include "Attacker.h"
#include <fstream>

class ArgParse
{
private: 
	int argc;
	bool args_corrupted;
	char*** argvs;

protected:
	void process_hash_function();
	void process_input_hash();
	void process_input();
	void process_hash();
	void process_bruteforce();
	void process_dictionary();
	void process_mask();

public:
	ArgParse(int argc, char* argv[]);
	~ArgParse();
	bool args_are_valid();
	int get_password_lenght();
	bool input_is_hash();
	Attacker::attack_mode get_mode();
	Attacker::attacked_hash get_hash();
	void set_optional_param(char *param);
	void set_input(char *input);
};

