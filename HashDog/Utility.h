#pragma once
class Utility
{
public:
	Utility();
	~Utility();
	static bool hashCompare(const char* first_hash, const char* second_hash, int size);
};

