#pragma once
#include "domain.h"
#include <vector> 
#include <iostream>
#include <fstream>
#include "exception.h"

class EventRepo
{
protected:
    std::vector<Event> events;
    char file_name[20];
public:
    EventRepo(char file_name[]);
    ~EventRepo();
    std::vector<Event> getEvents() { return events; };
    typedef std::vector<Event>::iterator iterator;
    iterator begin() { return events.begin(); }
    iterator end() { return events.end(); }
    virtual void write_to_file(const std::string& file_name);
    void read_from_file(const std::string& file_name);
    EventRepo& initialise_repo(EventRepo& er);
    int getSize();
    Event getEvent(int index);
    bool is_existent_add(Event& e);
    void add_event(Event e);
    void add_position(Event e, int position);
    void remove_event(int position);
    void update_event(int position, Event new_event);
    virtual void open_link();
};