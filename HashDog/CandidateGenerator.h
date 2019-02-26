#pragma once
#include "pch.h"


class CandidateGenerator {
public:
	virtual void set_password_candidate(char *candidate) {};

protected:
	int length;
};

