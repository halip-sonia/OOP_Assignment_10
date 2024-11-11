
#include <cstring>
#include <algorithm>
#include "repo.h"

EventRepo::EventRepo(char file_name[]) :events(0)
{
    strcpy(this->file_name, file_name);
}

EventRepo& EventRepo::initialise_repo(EventRepo& er)
// initialises the repo er by adding 10 events to it
{
    Event e1 = Event("Security BSides Transylvania",
        "Join one of the largest communities of cybersecurity professionals for a day of fun activities, networking and knowledge sharing.",
        "23/3/2024",
        "9:00",
        50,
        "https://www.facebook.com/events/1483622325519463/");
    this->add_event(e1);
    Event e2 = Event("Open Mic @ Klausen Pubhouse",
        "Open mic stand up comedy event at Klausen Pubhouse",
        "24/3/2024",
        "19:30",
        10,
        "https://www.facebook.com/events/2765877983711769/");
    this->add_event(e2);
    Event e3 = Event("Indie Party",
        "Get on your dancing shoes and embark with us on a roller coaster of mesmerizing danceable indie/rock/alternative/britpop tunes.",
        "2/4/2024",
        "19:00",
        316,
        "https://www.facebook.com/events/417638127344163/");
    this->add_event(e3);
    Event e4 = Event("DENTis Congress 2024",
        "The International Congress of Dental Medicine for Students and Young Doctors.",
        "4/4/2024",
        "9:00",
        482,
        "https://www.facebook.com/events/1078530319994621/");
    this->add_event(e4);
    Event e5 = Event("MAKE FRIENDS in Cluj-Napoca",
        "Come and meet fun people, join us for a drink, chat, share your stories etc. Anyone is welcomed.",
        "30/3/2024",
        "20:00",
        53,
        "https://www.facebook.com/events/390818193698212/");
    this->add_event(e5);
    Event e6 = Event("Bosquito @ Form Space",
        "Bosquito concert at Form Space",
        "20/4/2024",
        "20:00",
        300,
        "https://zilesinopti.ro/evenimente/bosquito-form-space-2/");
    this->add_event(e6);
    Event e7 = Event("PetGuru Grooming Show",
        "The 5th Edition of PetGuru Grooming Show, 2024!",
        "14/6/2024",
        "8:00",
        399,
        "https://www.facebook.com/events/279269841580152/");
    this->add_event(e7);
    Event e8 = Event("We Love STEM Day",
        "A cool festival where you can dive into the fascinating world of Science, Technology, Engineering, and Mathematics - from captivating experiments to interactive games and thought-provoking discussions, there's so much to explore and discover!",
        "24/5/2024",
        "10:00",
        149,
        "https://www.facebook.com/events/220858404446362/");
    this->add_event(e8);
    Event e9 = Event("3 Years Of Heart",
        "Celebrating 3 Years of Magic and Memories! On the 19th of April we party inside the Bt Arena!",
        "19/4/2024",
        "21:00",
        104,
        "https://www.facebook.com/events/1355678528469975/");
    this->add_event(e9);
    Event e10 = Event("Witchcraft & Wizardry Cluj-Napoca",
        "Embark on a captivating journey through Cluj-Napoca on Saturday 27th April, 2024 with Witchcraft & Wizardry: Murder by Magic!",
        "27/4/2024",
        "12:00",
        6,
        "https://www.facebook.com/events/897238348497030/");
    this->add_event(e10);
    write_to_file(this->file_name);
    return *this;
}

int EventRepo::getSize()
{
    return this->events.size();
}

Event EventRepo::getEvent(int index)
{
    return this->events.at(index);
}

bool EventRepo::is_existent_add(Event& e)
{
    auto eventTitles = [&](Event& event) {
        return strcmp(event.getTitle(), e.getTitle()) == 0;
        };

    auto it = std::find_if(events.begin(), events.end(), eventTitles);
    return it != events.end();
}


void EventRepo::add_event(Event e)
// adds an event to the repo
{
    if (is_existent_add(e)) {
        throw RepoException("Event already exists!");
    }
    else {
        this->events.push_back(e);
        write_to_file(this->file_name);
    }
}

void EventRepo::add_position(Event e, int position)
//add event to the repo at a given position
{
    if (is_existent_add(e)) {
        throw RepoException("Event already exists!");
    }
    else {
        /*events.insert(events.begin() + position, e);
        write_to_file(this->file_name);*/
        if (position >= 0 && position <= events.size()) {
            events.insert(events.begin() + position, e);
            write_to_file(this->file_name);
        }
        else {
            throw std::out_of_range("Position out of range!");
        }
    }
    

}

void EventRepo::remove_event(int position)
// removes an event from the repo at a given position
{

    this->events.erase(this->events.begin() + position);
    write_to_file(this->file_name);
}

void EventRepo::update_event(int position, Event new_event)
// updates an event at a given position with a new event
{
    this->events[position] = new_event;
    write_to_file(this->file_name);
}

EventRepo::~EventRepo() = default;

void EventRepo::write_to_file(const std::string& file_name) {
    std::ofstream outfile(file_name);
    if (outfile.is_open()) {
        for (Event& event : this->events) {
            outfile << event.getTitle() << ";" << event.getDescription() << ";" << event.getDate() << ";" << event.getTime() << ";" << event.getPeople() << ";" << event.getLink() << std::endl;
            //outfile << event << std::endl;
        }
        outfile.close();
    }
    else {
        std::cout << "Unable to open file for writing!" << std::endl;
    }
}

void EventRepo::read_from_file(const std::string& file_name) {
    std::ifstream infile(file_name);
    if (infile.is_open()) {
        this->events.clear();
        Event event;
        while (infile >> event) {
            events.push_back(event);
        }
        infile.close();
    }
    else {
        std::cout << "Unable to open file for reading!" << std::endl;
    }
}

void EventRepo::open_link() {

}


