#ifndef SIGNAL_HANDLER_HPP
#define SIGNAL_HANDLER_HPP
#include <string>
class handler
{
public:
    explicit handler(const int sig_num);
    void static sigint_handler(const int sig_num);
    void static sigterm_handler(const int sig_num);
    operator std::string();
private:
    int sig_num;
};

#endif