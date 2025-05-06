#include<iostream>
#include<csignal>
#include <string>
#include "signal_handler.hpp"

handler::operator std::string(){return std::to_string(sig_num);}
handler::handler(const int sig_num) : sig_num(sig_num)
{
    if(sig_num==2)
    {
        std::signal(sig_num, sigint_handler);
    }
    if(sig_num==15)
    {
        std::signal(sig_num, sigterm_handler);
    }

}
void handler::sigint_handler(const int sig_num)
{
    std::string msg{"the program terminated by signal number: "};
    std::string str_sig_num=static_cast<std::string>(handler(sig_num));
    std::cout<<msg<<str_sig_num<<std::endl;
    throw msg+str_sig_num;
}
void handler::sigterm_handler(const int sig_num)
{
    std::string msg{"the program terminated by signal number: "};
    std::string str_sig_num=static_cast<std::string>(handler(sig_num));
    std::cout<<msg<<str_sig_num<<std::endl;
    throw msg+str_sig_num;
}