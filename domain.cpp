#include "domain.h"
#include <cstring>

Event::Event() :nr_people(0)
{
    title[0] = '\0';
    description[0] = '\0';
    date[0] = '\0';
    time[0] = '\0';
    link[0] = '\0';
}

Event::Event(const char* title, const char* description, const char* date, const char* time, int nr_people, const char* link)
{
    strcpy(this->title, title);
    strcpy(this->description, description);
    strcpy(this->date, date);
    strcpy(this->time, time);
    this->nr_people = nr_people;
    strcpy(this->link, link);
}

Event::~Event()
{

}

char* Event::getTitle()
{
    return this->title;
}

char* Event::getDescription()
{
    return this->description;
}

char* Event::getDate()
{
    return this->date;
}

char* Event::getTime()
{
    return this->time;
}

int Event::getPeople()
{
    return this->nr_people;
}

char* Event::getLink()
{
    return this->link;
}

void Event::setTitle(const char* newTitle) {
    strncpy(this->title, newTitle, sizeof(this->title) - 1);
    this->title[sizeof(this->title) - 1] = '\0';
}

void Event::setDescription(const char* newDescription)
{
    strncpy(this->description, newDescription, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
}

void Event::setDate(const char* newDate)
{
    strncpy(this->date, newDate, sizeof(this->date) - 1);
    this->date[sizeof(this->date) - 1] = '\0';
}

void Event::setTime(const char* newTime)
{
    strncpy(this->time, newTime, sizeof(this->time) - 1);
    this->time[sizeof(this->time) - 1] = '\0';
}

void Event::setPeople(int newPeople)
{
    this->nr_people = newPeople;
}

void Event::setLink(const char* newLink)
{
    strncpy(this->link, newLink, sizeof(this->link) - 1);
    this->link[sizeof(this->link) - 1] = '\0';
}

bool Event::operator==(const Event& other) const {
    return (strcmp(this->title, other.title) == 0 &&
        strcmp(this->description, other.description) == 0 &&
        strcmp(this->date, other.date) == 0 &&
        strcmp(this->time, other.time) == 0 &&
        this->nr_people == other.nr_people &&
        strcmp(this->link, other.link) == 0);
}

