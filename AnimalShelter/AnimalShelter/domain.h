#pragma once
#include <string>
using namespace std;

class Dog {
private:

	string name;
	string breed;
	string age;
	string photo;

public:

	Dog(string name, string breed, string age, string photo);

	Dog();
	//default constructor

	// copy constructor
	Dog(const Dog &d);

	//destructor
	~Dog();

	string getName() { return this->name; }
	string getBreed() { return this->breed; }
	string getAge() { return this->age; }
	string getPhoto() { return this->photo; }

	//void updateName(char name[50]);
	void updateAge(string age);
	void updatePhoto(string photo);
	std::string toString();

	friend std::ostream& operator<<(std::ostream& stream, const Dog& d);
	friend std::istream& operator>>(std::istream& stream, Dog& d);

};