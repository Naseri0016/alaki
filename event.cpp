#include "event.hpp"
#include <stdexcept>
#include <ctime>

void EVENT::set_name(const std::string& name) {
    this->name = name;
}

void EVENT::set_time(time_t start, time_t duration_in_days) {
    if (start <= 0 || duration_in_days <= 0) {
        throw std::invalid_argument("Start time and duration must be positive and greater than 0.");
    }

    time_t now = time(0);
    time_t startTime = now + start * 86400; 
    time_t endTime = startTime + duration_in_days * 86400;

    if (startTime >= endTime) { 
        throw std::invalid_argument("Start time must be earlier than end time.");
    }

    this->start = startTime;
    this->end = endTime;
}



std::string EVENT::get_name() const {
    return name;
}

time_t EVENT::get_StartTime() const {
    return start;
}

time_t EVENT::get_endtime() const {
    return end;
}
