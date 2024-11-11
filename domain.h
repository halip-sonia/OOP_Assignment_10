#pragma once

#include <iostream>
#include <string>
#include <limits>


class Event
{
private:
    char title[100];
    char description[250];
    char date[20];
    char time[12];
    int nr_people;
    char link[100];

public:
    Event();
    Event(const char* title, const char* description, const char* date, const char* time, int nr_people, const char* link);
    ~Event();

    //getters
    char* getTitle();
    char* getDescription();
    char* getDate();
    char* getTime();
    int getPeople();
    char* getLink();

    //setters
    void setTitle(const char* newTitle);
    void setDescription(const char* newDescription);
    void setDate(const char* newDate);
    void setTime(const char* newTime);
    void setPeople(int newPeople);
    void setLink(const char* newLink);

    bool operator==(const Event& other) const;
    friend std::ostream& operator<<(std::ostream& os, Event& event)
    {
        os << "Title: " << event.title << std::endl;
        os << "Description: " << event.description << std::endl;
        os << "Date: " << event.date << std::endl;
        os << "Time: " << event.time << std::endl;
        os << "Number of people: " << event.nr_people << std::endl;
        os << "Link: " << event.link << std::endl;
        return os;
    }
    friend std::istream& operator>>(std::istream& in, Event& event) {
        std::cout << "Title: ";
        in.getline(event.title, sizeof(event.title));
        std::cout << "Description: ";
        in.getline(event.description, sizeof(event.description));
        std::cout << "Date: ";
        in.getline(event.date, sizeof(event.date));
        std::cout << "Time: ";
        in.getline(event.time, sizeof(event.time));
        std::cout << "Number of people: ";
        in >> event.nr_people;
        in.ignore();
        std::cout << "Link: ";
        in.getline(event.link, sizeof(event.link));
        return in;
    }
};
