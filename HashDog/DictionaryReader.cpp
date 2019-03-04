#include "pch.h"
#include "DictionaryReader.h"
#include "FifoBuffer.h"
#include <thread>

FifoBuffer<arr> DictionaryReader::buffer;
std::ifstream* DictionaryReader::file;

DictionaryReader::DictionaryReader(size_t password_size, const char* filename) {
	length = password_size;
	if (filename) {
		file = new std::ifstream(filename, std::ifstream::out);
		if (!file->is_open())
			file->open(filename, std::ifstream::out);
	}
}

DictionaryReader::~DictionaryReader() {
	if (file->is_open())
		file->close();
}

void DictionaryReader::set_password_candidate(char *candidate) {
	if (!buffer.empty()) {
		temp_storage = buffer.pop();
		Utility::std_array_to_c_array(temp_storage, candidate, length);
	}
}

void DictionaryReader::read_file(std::atomic<int>& successful_thread) { //fix length
	char* temp_buffer = new char[256];
	arr temp;

	while(!file->getline(temp_buffer, 255).eof() && (successful_thread == -1)) {
		if (strlen(temp_buffer) == (length)) {
			std::this_thread::sleep_for(std::chrono::microseconds(20));
			char* password_buffer = new char[length + 1];
			memcpy(password_buffer, temp_buffer, length + 1);		
			Utility::c_array_to_std_array(password_buffer, temp, length);
			buffer.push(temp);
		}
	}
	if (successful_thread == -1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::lock_guard<std::mutex> lock(locker);
		successful_thread = -2;
	}
}
