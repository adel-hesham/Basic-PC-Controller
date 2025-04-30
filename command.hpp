#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <functional>
#include <string>


class control
{
public:
    bool seen_all_gmails();

    bool shutdown();
    
    bool cancel_shutdown();

    bool shutdown_timer(std::string time);

    bool shutdown_in_time(std::string clock);

    bool open_edge();

    bool open_code();

    bool open_whatsapp();
    
    bool open_tilix();

    bool search_web(std::string search);

    std::string battery_info();

    char buffer[256];
    static std::function<void (FILE*)> popen_deleter;
    
};


#endif 
