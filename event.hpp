#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <string>
#include <ctime>

class EVENT {
private:
    std::string name;
    time_t start;
    time_t end;

public:
    void set_name(const std::string& name);
    void set_time(time_t start, time_t duration_in_days);
    std::string get_name() const;
    time_t get_StartTime() const;
    time_t get_endtime() const;
};

#endif
