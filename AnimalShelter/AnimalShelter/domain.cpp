#include "domain.h"
#include <iostream>
#include <string>
#include <sstream>

Dog::Dog()//char name[50], char breed[50], int age, char photo[100])
{
	
	this->name = "";
	this->breed = "";
	this->age = "";
	this->photo = ""; 

} 

Dog::Dog(string name, string breed, string age, string photo)
{
	
	this->name = name;
	this->breed = breed;
	this->age = age;
	this->photo = photo;
	

}

Dog::Dog(const Dog& d)
{
	this->name = d.name;
	this->breed = d.breed;
	this->age = d.age;
	this->photo = d.photo;
}
/*
void Dog::updateName(char name[50])
{
	strcpy_s(this->name, 50, name);
}
*/
void Dog::updateAge(string age)
{
	this->age = age;
}


void Dog::updatePhoto(string photo)
{
	this->photo = photo;
}

std::string Dog::toString() {
	std::stringstream txt;
	txt << "Dog's name: " << this->name << ", breed: " << this->breed << ", age: " << this->age << ", photo: " << this->photo << std::endl;
	return txt.str();
}

Dog::~Dog()
{}


std::ostream& operator<<(std::ostream& stream, const Dog& d)
{
	stream << d.name << "," << d.breed << "," << d.age << "," << d.photo << std::endl;
	return stream;
}

std::istream& operator>>(std::istream& stream, Dog& d)
{
	
	getline(stream, d.name, ',');
	getline(stream, d.breed, ',');
	getline(stream, d.age, ',');
	getline(stream, d.photo);
	return stream;
}