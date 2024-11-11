#pragma once
#include <vector>
#include <string>
#include "domain.h"

class EventException {
private:
	std::vector<std::string> errors;

public:
	EventException(std::vector<std::string> errors);
	std::vector<std::string> getErrors();
};

class EventValidator {
public:
	bool validate_name(char* titleStr);
	bool validate_date(char* dateStr);
	bool validate_time(char* timeStr);
	bool validate_link(const char* link);
	bool validate_ppl(int ppl);
	void validate_event(Event* e);
};