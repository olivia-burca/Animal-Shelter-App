#pragma once
#include "domain.h"
#include <exception>
#include <vector>

class DogValidator
{
public:
	DogValidator();
	~DogValidator();

	void validate_dog( Dog d);
};

class DogException
{
private:
	vector<string> errors;
public:
	DogException(vector<string> errors_);
	vector<string> getErrors() const;
};