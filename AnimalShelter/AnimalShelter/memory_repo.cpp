#include "memory_repo.h"
#include "repo.h"
#include "domain.h"
#include "dog_validator.h"
#include "repo_exception.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

MemRepo::MemRepo()
{
	this->da = vector<Dog>();
	this->dog_validator = DogValidator();
}

MemRepo::~MemRepo()
{
}

int MemRepo::searchByName(string name)
{
	bool found = false;
	int pos = 0;
	for (auto i : this->da)
	{
		if (i.getName() == name)
		{
			found = true;
			return pos;
		}
		pos++;
	}
	if (!found)
		return -1;
}

int MemRepo::addDog(Dog t)
{
	if (searchByName(t.getName()) != -1)
		throw DuplicateDogException();
	else
	{
		dog_validator.validate_dog(t);
		this->da.push_back(t);
		return 1;
	}
}



void MemRepo::adoptDog(Dog t)
{
	this->da.push_back(t);
}

int MemRepo::removeDog(int pos)
{
	/*
	if (searchByName(name) == -1)
		return -1;
	else
	{
		this->da.erase(this->da.begin() + searchByName(name));
		return 1;
	} */
	this->da.erase(this->da.begin() + pos);
	return 1;
}

int MemRepo::updateAge(string name, string age)
{
	if (searchByName(name) == -1)
		return -1;
	else
	{
		int pos = searchByName(name);
		this->da[pos].updateAge(age);
		return 1;
	}
}


int MemRepo::updatePhoto(string name, string photo)
{
	if (searchByName(name) == -1)
		return -1;
	else
	{
		int pos = searchByName(name);
		this->da[pos].updatePhoto(photo);
		return 1;
	}
}

vector<Dog> MemRepo::filterAgeBreed(string breed, int age)
{
	vector<Dog> v2(this->da.size());
	vector<Dog>::iterator it = copy_if(this->da.begin(), this->da.end(), v2.begin(), [&](Dog d) {return stoul(d.getAge()) < age; });
	v2.resize(distance(v2.begin(), it));
	if (breed == "")
		return v2;
	else
	{
		vector<Dog> v3(v2.size());
		vector<Dog>::iterator it2 = copy_if(v2.begin(), v2.end(), v3.begin(), [&](Dog d) {return d.getBreed() == breed; });
		v3.resize(distance(v3.begin(), it2));
		return v3;
	}
}

MemRepo& MemRepo::operator=(const MemRepo& other)
{
	if (this == &other) return *this;
	this->da = other.da;
	return *this;
}

void MemRepo::initialize()
{

	Dog d1{ "Max","German Shepherd", "3" ,"http://keepcalmandadoptapet.com/Max" };
	this->da.push_back(d1);

	Dog d2{ "Milo","Corgi", "1","http://keepcalmandadoptapet.com/Milo" };
	this->da.push_back(d2);

	Dog d3{ "Billie","Pitbull","3","http://keepcalmandadoptapet.com/Billie" };
	this->da.push_back(d3);

	Dog d4{ "Ellie","Corgi","7", "http://keepcalmandadoptapet.com/Ellie" };
	this->da.push_back(d4);

	Dog d5{ "Daisy","Poodle", "8", "http://keepcalmandadoptapet.com/Daisy" };
	this->da.push_back(d5);

	Dog d6{ "Ricky","Husky", "11","http://keepcalmandadoptapet.com/Ricky" };
	this->da.push_back(d6);

	Dog d7{ "Hazel","Golden Retriever","3","http://keepcalmandadoptapet.com/Hazel" };
	this->da.push_back(d7);

	Dog d8{ "Biscuit","Corgi","5","http://keepcalmandadoptapet.com/Biscuit" };
	this->da.push_back(d8);

	Dog d9{ "Scooby","Great Dane","4","http://keepcalmandadoptapet.com/Scooby" };
	this->da.push_back(d9);

	Dog d10{ "Lucky","Corgi", "2","http://keepcalmandadoptapet.com/Lucky" };
	this->da.push_back(d10);

}

void MemRepo::save()
{

}
void MemRepo::openInApp() {}
