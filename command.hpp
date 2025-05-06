#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <functional>
#include <string>
//

class control
{
public:
    void seen_all_gmails();

    void shutdown();

    void cancel_shutdown();

    void shutdown_timer();

    void shutdown_in_time();

    void open_browser();

    void open_code();

    void open_whatsapp();

    void open_tilix();

    void open_facebook();

    void open_youtube();

    void open_linkedin();
    
    void open_github();

    void search_web();

    void battery_info();

    void open_terminal();

    bool terminal_screen();

    void restart();

    char buffer[256];
    static std::function<void (FILE*)> popen_deleter;
    
};


#endif 