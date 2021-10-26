#include "repo_exception.h"


RepoException::RepoException() : exception{}, message{ "" }
{
}

RepoException::RepoException(const std::string& msg) : message{ msg }
{
}

const char* RepoException::what()
{
	return this->message.c_str();
}

const char* DuplicateDogException::what()
{
	return "A dog with this name already exists! \n";
}