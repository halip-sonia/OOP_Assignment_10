#pragma once
#include <vector>
#include <string>
#include "repo/repo.h"

class RepoException {
private:
	std::string message;
public:
	RepoException(std::string message);
	std::string what();
};
