#include "calendar.hpp"
#include <fstream>
#include <sstream>
#include <ctime>

std::vector<EVENT> CALENDAR::deletedEvents; 
void CALENDAR::set_events() {
    upload_from_file();
    std::string name;
    time_t start, duration;
    std::cout << "How many events do you want to add? ";
    int count;
    std::cin >> count;

    while (count--) {
        std::cout << "Enter event name: ";
        std::cin >> name;

        std::cout << "Enter event start time (in days from now): ";
        std::cin >> start;
        if (start <= 0) { 
            std::cerr << "Start time must be greater than 0.\n";
            continue;
        }

        std::cout << "Enter event duration (in days): ";
        std::cin >> duration;
        if (duration <= 0) { 
            std::cerr << "Duration must be greater than 0.\n";
            continue;
        }

        if (add_event(start, duration)) {
            EVENT ev;
            try {
                ev.set_name(name);
                ev.set_time(start, duration);
                events.push_back(ev);
            } catch (const std::exception& e) { 
                std::cerr << "Error: " << e.what() << "\n";
                continue;
            }
        } else {
            std::cerr << "Event conflicts with an existing event.\n";
        }
    }
    save_to_file(); 
}


bool CALENDAR::add_event(time_t start, time_t duration_in_days) {
    for (const auto& e : events) {
        if ((start >= e.get_StartTime() && start <= e.get_endtime()) ||
            (start + duration_in_days * 86400 >= e.get_StartTime() && start + duration_in_days * 86400 <= e.get_endtime()) ||
            (start <= e.get_StartTime() && start + duration_in_days * 86400 >= e.get_endtime())) {
            return false;
        }
    }
    return true;
}

void CALENDAR::upload_from_file() {
    std::ifstream file("events.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file.\n";
        return;
    }

    std::string line, name;
    time_t start, end;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> name >> start >> end;

        if (start <= 0 || end <= 0 || start >= end) { 
            std::cerr << "Invalid data in file. Skipping...\n";
            continue;
        }

        EVENT ev;
        try {
            ev.set_name(name);
            ev.set_time((start - time(0)) / 86400, (end - start) / 86400);
            events.push_back(ev);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    file.close();
}

void CALENDAR::save_to_file() {
    std::ofstream file("events.txt", std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Could not open file.\n";
        return;
    }

    for (const auto& e : events) {
        file << e.get_name() << " " << e.get_StartTime() << " " << e.get_endtime() << "\n";
        if (!file) {
            std::cerr << "Error writing to file.\n";
        }
    }

    file.close();
    std::cout << "Events saved to file successfully.\n";
}

void CALENDAR::refresh() {
    time_t now = time(0);
    for (const auto& e : events) {
        if (now >= e.get_endtime()) {
            deletedEvents.push_back(e);
        }
    }
}

void CALENDAR::get_DeletedEvents() const {
    for (const auto& e : deletedEvents) {
        std::cout << "Deleted event: " << e.get_name() << "\n";
    }
}

CALENDAR::~CALENDAR() {
    std::cout << "Deleted Events:\n";
    get_DeletedEvents();
}
