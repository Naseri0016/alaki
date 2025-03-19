#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <iostream>
#include <vector>
#include "event.hpp"

class CALENDAR {
private:
    std::vector<EVENT> events;
    static std::vector<EVENT> deletedEvents;

public:
    void set_events();
    void upload_from_file();
    void save_to_file();
    bool add_event(time_t start, time_t duration_in_days);
    void refresh();
    void get_DeletedEvents() const;
    ~CALENDAR();
};

#endif
