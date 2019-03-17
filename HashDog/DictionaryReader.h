#pragma once
#include "pch.h"
#include "FifoBuffer.h"
#include <array>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <string>


#define arr std::array<char, MAX_INPUT_LENGTH + 1>

class DictionaryReader : public CandidateGenerator
{
public:
	DictionaryReader(size_t password_size, const char* filename);
	~DictionaryReader();
	void set_password_candidate(char *candidate);
	void read_file(std::atomic<int>& successful_thread);

	static FifoBuffer<arr> buffer;
	static std::ifstream* file;

private:
	bool reading_complete;
	arr temp_storage;
	std::mutex locker;
	std::condition_variable condition;
};

