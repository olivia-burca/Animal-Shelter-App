#include "file_repo.h"
#include <sstream>
#include <fstream>
#include <iostream>


FileRepo::FileRepo()
{
}

FileRepo::FileRepo(const FileRepo& r) : MemRepo(r)
{
	this->filename = r.filename;
	load();
}

FileRepo::~FileRepo()
{
}

string* FileRepo::splitString(string str)
{
	string* args = new std::string[5];
	istringstream ss(str);
	string arg;
	int i = 0;

	while (getline(ss, arg, ','))
		args[i++] = arg;

	return args;
}

void FileRepo::load()
{
	std::ifstream fin(this->filename );

	//this->getDA().clear();
	Dog d{};
	while (fin >> d)
	{
		this->addDog(d);
	}

	fin.close();
}

void FileRepo::save()
{
	std::ofstream fout(this->filename);
	for (auto i : this->getDA())
		fout << i; 
	fout.close();
}
/*
FileRepo& FileRepo::operator=(const FileRepo& r)
{
	if (this == &r)
		return *this;
	Repo::operator=(r);
	this->filename = r.filename;

	return *this;
}
*/
void FileRepo::openInApp()
{
	
}