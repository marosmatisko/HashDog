#pragma once
#include "pch.h"
#include <deque>
#include <fstream>
#include <shared_mutex>
#include <string>

class DictionaryReader : public CandidateGenerator
{
public:
	DictionaryReader(size_t password_size, const char* filename);
	~DictionaryReader();
	void set_password_candidate(char *candidate);
	void read_file();

//protected:
	static std::deque<char*> buffer;
	static std::ifstream* file;

private:
	std::shared_mutex locker;
};

