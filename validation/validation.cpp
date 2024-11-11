#include "validation.h"
#include <regex>
#include <cstring>

bool EventValidator::validate_name(char* titleStr)
{
    if (strlen(titleStr) < 3)
        return false;
    return true;
}

bool EventValidator::validate_date(char* dateStr)
{
    std::string str(dateStr);
    std::regex pattern("^\\d{1,2}/\\d{1,2}/\\d{4}$");
    if (!regex_match(str, pattern)) {
        return false;
    }

    int day, month, year;
    sscanf(dateStr, "%d/%d/%d", &day, &month, &year);

    if (day < 1 || day > 30 || month < 1 || month > 12 || year < 2024) {
        return false;
    }

    return true;
}

bool EventValidator::validate_time(char* timeStr)
{
    std::string str(timeStr);
    std::regex pattern("^\\d{1,2}:\\d{2}$");
    if (!std::regex_match(str, pattern)) {
        return false;
    }

    int hour, minute;
    sscanf(timeStr, "%d:%d", &hour, &minute);
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }
    return true;
}

bool EventValidator::validate_link(const char* link)
{
    std::regex pattern("(http|https)://[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,3}(/\\S*)?");
    std::string str(link);
    return std::regex_match(str, pattern);
}

bool EventValidator::validate_ppl(int ppl)
{
    return ppl >= 0;
}

void EventValidator::validate_event(Event* e)
{
    std::vector<std::string> errors;
    if (!validate_name(e->getTitle())) {
        errors.push_back("Name should not have less than 3 characters!!\n");
    }
    if (!validate_date(e->getDate())) {
        errors.push_back("Date should respect the format dd/mm/yyyy and also respect common sense!!\n");
    }
    if (!validate_time(e->getTime())) {
        errors.push_back("Time should respect common sense!!\n");
    }
    if (!validate_ppl(e->getPeople())) {
        errors.push_back("Cannot have negative amount of people!!\n");
    }
    if (!validate_link(e->getLink())) {
        errors.push_back("Link should start with http or https and be valid!!\n");
    }
    if (errors.size() > 0)
        throw EventException(errors);
}

EventException::EventException(std::vector<std::string> errors)
{
    this->errors = errors;
}

std::vector<std::string> EventException::getErrors()
{
    return this->errors;
}
