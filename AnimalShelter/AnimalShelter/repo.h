#pragma once
#include "domain.h"
#include <vector>

class Repo
{
public:
	Repo();
	~Repo();

	virtual int searchByName(string name) = 0;

	virtual int addDog(Dog t) = 0;

	virtual void adoptDog(Dog t) = 0;

	virtual int removeDog(int pos) = 0;

	virtual int updateAge(string name, string age) = 0;

	virtual int updatePhoto(string name, string photo) = 0;

	//virtual Dog findDog(int pos) = 0;
	
	virtual vector<Dog> filterAgeBreed( string breed, int age) = 0;

	virtual void initialize() = 0;

	virtual vector<Dog> & getDA() = 0;
	
	virtual void save() = 0;

	virtual void openInApp() = 0;

};