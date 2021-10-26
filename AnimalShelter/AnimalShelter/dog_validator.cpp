#include "dog_validator.h"
#include <iostream>

DogValidator::DogValidator()
{
}

DogValidator::~DogValidator()
{
}

void DogValidator::validate_dog( Dog d)
{
	vector<string> errors;

	if (d.getName().size() < 2)
		errors.push_back("The name of the dog cannot be less than 2 characters!\n");
	if (!isupper(d.getName()[0]))
		errors.push_back("The name of the dog should start with an uppercase letter!\n");
	if (d.getBreed().size() < 3)
		errors.push_back("The breed of the dog cannot be less than 3 characters!\n");
	if (!isupper(d.getBreed()[0]))
		errors.push_back("The breed of the dog should start with an uppercase letter!\n");

	try {
		int age_ = stoul(d.getAge());
	}
	catch (invalid_argument) {
		errors.push_back( "Age should be an integer number! \n");
	}

	int i1 = d.getPhoto().find("www");
	int i2 = d.getPhoto().find("http");
	if (i1 != 0 && i2 != 0)
		errors.push_back("The link of the photo must start with 'www' or 'http' !\n");

	if (errors.size() > 0)
		throw DogException(errors);
}

DogException::DogException(vector<string> errors_)
{
	this->errors = errors_;
}

vector<string> DogException::getErrors() const
{
	return this->errors;
}