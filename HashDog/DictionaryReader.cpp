#include "pch.h"
#include "DictionaryReader.h"
#include "FifoBuffer.h"
#include <thread>

FifoBuffer<arr> DictionaryReader::buffer;
std::ifstream* DictionaryReader::file;

DictionaryReader::DictionaryReader(size_t password_size, const char* filename) {
	length = password_size;
	if (filename != "") {
		file = new std::ifstream(filename, std::ifstream::out);
		if (!file->is_open())
			file->open(filename, std::ifstream::out);
		reading_complete = false;
	}
}

DictionaryReader::~DictionaryReader() {
	if (file->is_open())
		file->close();
}

void DictionaryReader::set_password_candidate(char *candidate) {
	{
		std::unique_lock<std::mutex> lock(this->locker);
		if (!buffer.empty()) {
			temp_storage = buffer.pop();
			Utility::std_array_to_c_array(temp_storage, candidate, length);
		}
	}
	if (reading_complete && buffer.empty()) {
		condition.notify_one();
		std::unique_lock<std::mutex> lock(this->locker);
		reading_complete = false;
	}
}

void DictionaryReader::read_file(std::atomic<int>& successful_thread) { //search for pass with exact length
	char* temp_buffer = new char[1024];
	arr temp;

	while(!file->getline(temp_buffer, 1023).eof() && (successful_thread == -1)) {
		if (strlen(temp_buffer) == length) {
			Utility::c_array_to_std_array(temp_buffer, temp, length);
			buffer.push(temp);
			//std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	reading_complete = true;
	if (successful_thread == -1) {
		std::unique_lock<std::mutex> lock(this->locker);
		condition.wait(lock, [this] {return this->buffer.empty(); });
		successful_thread = -2;
	}
}
