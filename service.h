#pragma once

#include "repo.h"
#include "undoredo.h"
#include <iostream>
#include <algorithm>
#include "validation.h"


//int is_existent_add(EventRepo& er, Event& e);
class Service {
private:
    UndoStack* undo;
    RedoStack* redo;
public:
    Service();
    bool uempty() { return undo->isEmpty(); };
    bool rempty() { return redo->isEmpty(); };
    bool is_month(char e[], char month[]);
    bool day_compare(Event& e1, Event& e2);
    int search_title(EventRepo& er, char* title);
    void service_add(EventRepo& er, Event& e);
    bool service_remove(EventRepo& er, char* title);
    bool service_update_descr(EventRepo& er, char* title, char* new_desc);
    bool service_update_date(EventRepo& er, char* title, char* new_date);
    bool service_update_time(EventRepo& er, char* title, char* new_time);
    bool service_update_people(EventRepo& er, char* title, int new_people);
    bool service_update_link(EventRepo& er, char* title, char* new_link);
    EventRepo sort_month_repo(EventRepo& er, char month[]);
    void service_undo(EventRepo& er);
    void service_redo(EventRepo& er);
};

