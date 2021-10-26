#pragma once
#include "memory_repo.h"

class FileRepo :
	public MemRepo
{
private:
	string filename;
	void load();
	

public:
	FileRepo();
	FileRepo(const string& filename): MemRepo() { this->filename = filename; load(); }
	FileRepo(const FileRepo& r);
	~FileRepo();

	//FileRepo& operator=(const FileRepo& r);
	string* splitString(string str);
	void save() override;
	void openInApp() ;
}; 