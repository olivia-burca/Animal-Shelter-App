#pragma once
#include <exception>
#include <string>

class RepoException : public std::exception
{
protected:
	std::string message;

public:
	RepoException();
	RepoException(const std::string& msg);
	virtual ~RepoException() {}
	virtual const char* what();
};

class DuplicateDogException : public RepoException
{
public:
	const char* what();
};
