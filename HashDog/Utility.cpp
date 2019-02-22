#include "pch.h"
#include "Utility.h"


Utility::Utility() {
}


Utility::~Utility() {
}

bool Utility::hashCompare(const char* first_hash, const char* second_hash, int size) {
	for (int i = 0; i < size; ++i) {
		if (first_hash[i] != second_hash[i]) {
			return false;
		}
	}
	return true;
}
