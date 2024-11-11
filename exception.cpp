#include "exception.h"

RepoException::RepoException(std::string message)
{
	this->message = message;
}

std::string RepoException::what()
{
	return message;
}
