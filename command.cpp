

/**************************************command.cpp file*****************************************
 * Project: Remote PC Controller (Linux System Controller)
 * Description: This server receives commands from a client to perform actions 
 *              like shutdown, open apps (Tilix, Edge, WhatsApp, VS Code), check battery, 
 *              search the web, and check emails via socket communication.
 * Author: [Eng/Adel elnimr]
 * Date: [30/4/2025]
 ******************************************************************************************/


/********************************************/
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include "command.hpp"
#include "server.hpp"
/********************************************/



bool end=false;
std::function<void(FILE*)>control::popen_deleter=[](FILE* fd) {
    if (fd || end) pclose(fd);
    };


bool control::seen_all_gmails()
{
    std::stringstream ss;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("python3 seenemails.py", "r"),popen_deleter);
    if(!fd)
    {
        perror("python script failed");
        return false;
    }
    else
    {
        while(fgets(buffer, sizeof(buffer), fd.get()))
        {
            std::cout<<buffer<<std::endl;
            makesocket::capture<<buffer<<std::endl;   
            makesocket::sendout(makesocket::capture.str());
        }
        end=true;    
        return true;
    }
}
void control::shutdown()
{
    if(system("sudo shutdown -h now")!=0)
    {
        perror("shutdown failed");
    }
}
bool control::cancel_shutdown()
{
    if(system("sudo shutdown -c")!=0)
    {
        perror("shutdown cancel failed");
        return false;
    }
    return true;
}
bool control::shutdown_timer(std::string time)
{    
    std::string command="sudo shutdown -h +"+time;
    if(system(command.c_str())!=0)
    {
        perror("shutdown failed");
        return false;
    }
    else
    {
        return true;
    }
}
bool control::shutdown_in_time(std::string clock)
{
    std::string command="sudo shutdown -h "+clock;
    if(system(command.c_str())!=0)
    {
        perror("shutdown failed");
        return false;
    }
    else
    {
        return true;
    }
}

bool control::open_edge()
{
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("/opt/microsoft/msedge/msedge &", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        return false;
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    return true;
}

bool control::open_code()
{
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("code &", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        return false;
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    return true;

}
bool control::search_web(std::string search)
{
    search+="\"";
    std::string search_command="/opt/microsoft/msedge/msedge \"https://www.google.com/search?q=";
    search_command+=search;

    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(search_command.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        return false;
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    return true;

}

bool control::open_whatsapp()
{
    std::string whats_executable{"/opt/microsoft/msedge/microsoft-edge --profile-directory=Default --app-id=hnpfjngllnobngcgfapefoaidbinmjnm --app-url=https://web.whatsapp.com/ &"};
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(whats_executable.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        return false;
    }
    while (fgets(buffer, sizeof(buffer), fd.get()))
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    return true;

}
bool control::open_tilix()
{    
    if(system("tilix &")!=0)
    {
        perror("popen()");
        return false;
    }
    return true;
}
std::string control::battery_info()
{
    std::stringstream ss;
    std::string battery_command("upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep -E \"state|to\\ full|percentage|capacity\"");
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(battery_command.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
    }
    while (fgets(buffer, sizeof(buffer), fd.get()))
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    return ss.str();

}


