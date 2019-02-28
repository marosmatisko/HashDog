#include "pch.h"
#include "DictionaryReader.h"

std::deque<char*> DictionaryReader::buffer;
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
	locker.lock();
	if (!buffer.empty()) {
		memcpy(candidate, buffer.front(), length + 1);
		buffer.pop_front();
	}
	locker.unlock();
}

void DictionaryReader::read_file() { //fix length
	char* temp_buffer = new char[11];
	while(!file->getline(temp_buffer, 10).eof()) {
		if (strlen(temp_buffer) == (length)) {
			char* password_buffer = new char[length + 1];
			memcpy(password_buffer, temp_buffer, length + 1);
			locker.lock();
			buffer.push_back(password_buffer);
			locker.unlock();
		}
	}
}
