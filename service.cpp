#include "service.h"

#include<cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

bool Service::is_month(char* e, char* month) {
    //checks if the date has the month given
    char* e_mon = strtok(e, "/");
    e_mon = strtok(nullptr, "/");
    if (strcmp(e_mon, month) == 0)
        return true;
    return false;
}

Service::Service(): undo(new UndoStack), redo(new RedoStack)
{
    
}

bool Service::day_compare(Event& e1, Event& e2) {
    char d1[12], d2[12];
    strcpy(d1, e1.getDate());
    strcpy(d2, e2.getDate());
    std::string date1 = d1;
    std::string date2 = d2;
    char* str1 = strtok(d1, "/");
    char* str2 = strtok(d2, "/");
    int day1 = atoi(str1);
    int day2 = atoi(str2);

    return day1 < day2;
}

int Service::search_title(EventRepo& er, char* title) {
    int i = 0;
    while (i < er.getSize()) {
        if (strcmp(er.getEvent(i).getTitle(), title) == 0)
            return i;
        i++;
    }
    return -1;
}

void Service::service_add(EventRepo& er, Event& e) {
    auto val = EventValidator{};
    val.validate_event(&e);
    int pos;
    auto siz = er.getSize();
    pos = siz;
    

    action a;
    a.event = e;
    a.performed = 0;
    a.position = pos;
    undo->add_action(a);

    if (er.getSize() == 0)
        er.add_event(e);
    else
        er.add_position(e,pos);

}

bool Service::service_remove(EventRepo& er, char* title) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }

    action a;
    auto curr = er.getEvent(ok);
    a.event = curr;
    a.performed = 1;
    a.position = ok;
    undo->add_action(a);

    er.remove_event(ok);
    return true;
}

bool Service::service_update_descr(EventRepo& er, char* title, char* new_desc) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }
    Event e = er.getEvent(ok);

    action a;
    a.event = e;
    a.performed = 2;
    a.position = ok;
    undo->add_action(a);

    e.setDescription(new_desc);
    er.update_event(ok, e);
    return true;
}

bool Service::service_update_date(EventRepo& er, char* title, char* new_date) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }
    Event e = er.getEvent(ok);

    action a;
    a.event = e;
    a.performed = 2;
    a.position = ok;
    undo->add_action(a);

    e.setDate(new_date);
    er.update_event(ok, e);
    return true;
}

bool Service::service_update_time(EventRepo& er, char* title, char* new_time) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }
    Event e = er.getEvent(ok);

    action a;
    a.event = e;
    a.performed = 2;
    a.position = ok;
    undo->add_action(a);

    e.setTime(new_time);
    er.update_event(ok, e);
    return true;
}

bool Service::service_update_people(EventRepo& er, char* title, int new_people) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }
    Event e = er.getEvent(ok);

    action a;
    a.event = e;
    a.performed = 2;
    a.position = ok;
    undo->add_action(a);

    e.setPeople(new_people);
    er.update_event(ok, e);
    return true;
}

bool Service::service_update_link(EventRepo& er, char* title, char* new_link) {
    int ok = search_title(er, title);
    if (ok == -1) {
        return false;
    }
    Event e = er.getEvent(ok);

    action a;
    a.event = e;
    a.performed = 2;
    a.position = ok;
    undo->add_action(a);

    e.setLink(new_link);
    er.update_event(ok, e);
    return true;
}

void Service::service_undo(EventRepo& er)
{
    redo->add_action(undo->get_last());
    undo->undo(&er);
}

void Service::service_redo(EventRepo& er)
{
    undo->add_action(redo->get_last());
    redo->redo(&er);
}

EventRepo Service::sort_month_repo(EventRepo& er, char* month) {
    char aux_fn[20];
    strcpy(aux_fn, "au.txt");
    EventRepo auxrepo(aux_fn);
    for (Event& event : er)
    {
        char date[20];
        strcpy(date, event.getDate());
        if (is_month(date, month)) {
            auxrepo.add_event(event);
        }
    }
    std::sort(auxrepo.begin(), auxrepo.end(), [&](const Event& e1, const Event& e2) {
        return day_compare(const_cast<Event&>(e1), const_cast<Event&>(e2));
        });

    return auxrepo;
}
