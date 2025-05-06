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
#include <stdexcept>
#include "command.hpp"
#include "server.hpp"
#include <regex>
#include <string>
/********************************************/


std::string makesocket::buffer{""};
bool end=false;
std::function<void(FILE*)>control::popen_deleter=[](FILE* fd) {
    if (fd || end) pclose(fd);
    };


void control::seen_all_gmails()
{
    end=false;
    std::stringstream ss;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("python3 seenemails.py", "r"),popen_deleter);
    if(!fd)
    {
        perror("");
        throw std::runtime_error("python script failed");
    }    
    while(fgets(buffer, sizeof(buffer), fd.get()))
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}
void control::shutdown()
{
    if(system("sudo shutdown -h now")!=0)
    {
        perror("system()");
        throw std::runtime_error("shutdown failed");
    }
    
}
void control::cancel_shutdown()
{
    if(system("sudo shutdown -c")!=0)
    {
        perror("system()");
        throw std::runtime_error("shutdown cancel failed");   
    }
}
void control::shutdown_timer()
{    
    std::string time;
    std::regex shutdown_intime("^shutdown after [1-9][0-9]*$");
    if(std::regex_match(makesocket::buffer,shutdown_intime))
    {
        time=makesocket::buffer.substr(15);
        std::string command="sudo shutdown -h +"+time;
        if(system(command.c_str())!=0)
        {
            perror("system()");
            throw std::runtime_error("shutdown failed");
        }
    }
    else
    {
        throw std::runtime_error("Wrong shutdown pattern!");
    }
}
void control::shutdown_in_time()
{
    std::regex shutdown_inclock("^shutdown at (0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    if(std::regex_match(makesocket::buffer,shutdown_inclock))
    {
        std::string clock=makesocket::buffer.substr(12);
        std::string command="sudo shutdown -h "+clock;
        if(system(command.c_str())!=0)
        {
            perror("system()");
            throw std::runtime_error("shutdown failed");
        }
    }
    else
    {
        throw std::runtime_error("Wrong shutdwn pattern!");
    }
    
}

void control::open_browser()
{
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("sensible-browser &", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open browser failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    
}

void control::open_code()
{
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("code &", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open code failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    

}
void control::search_web()
{
    end=false;
    std::string search=makesocket::buffer.substr(11);   
    std::string search_command="xdg-open https://www.google.com/search?q=";
    search_command+=search;

    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(search_command.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("search failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}

void control::open_whatsapp()
{
    end=false;
    std::string whats_executable{"/opt/microsoft/msedge/microsoft-edge --profile-directory=Default --app-id=hnpfjngllnobngcgfapefoaidbinmjnm --app-url=https://web.whatsapp.com/ &"};
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(whats_executable.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open whatsapp failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get()))
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
    

}
void control::open_tilix()
{    
    if(system("tilix &")!=0)
    {
        perror("popen()");
        throw std::runtime_error("open tilix failed");
    }
}
void control::battery_info()
{
    end=false;
    std::string battery_command("upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep -E \"state|to\\ full|percentage|capacity\"");
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen(battery_command.c_str(), "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("battery info failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get()))
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}
void control::open_terminal()
{   
    if(system("gnome-terminal&")!=0)
    {
        perror("popen()");
        throw std::runtime_error("open terminal failed");
    }

}

void control::open_facebook()
{   
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("xdg-open https://www.facebook.com", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open facebook failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}

void control::open_youtube()
{   
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("xdg-open https://www.youtube.com", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open youtube failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}

void control::open_linkedin()
{   
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("xdg-open https://www.linkedin.com", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open linkedin failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}

void control::open_github()
{   
    end=false;
    std::unique_ptr<FILE,decltype(popen_deleter)> fd(popen("xdg-open https://www.github.com", "r"),popen_deleter);
    if(!fd)
    {
        perror("popen()");
        throw std::runtime_error("open github failed");
    }
    while (fgets(buffer, sizeof(buffer), fd.get())) 
    {
        std::cout<<buffer<<std::endl;
        makesocket::capture<<buffer<<std::endl;   
        makesocket::sendout(makesocket::capture.str());
    }
    end=true;
}
void control::restart()
{
    
    if(system("sudo shutdown --reboot now")!=0)
    {
        perror("system()");
        throw std::runtime_error("restart failed");
    }
}

bool control::terminal_screen()
{
    end = false;

    // Clear previous capture content
    makesocket::capture.str("");
    makesocket::capture.clear();
    std::string cmd = makesocket::buffer + " 2>&1";
    std::unique_ptr<FILE, decltype(popen_deleter)>
        fd(popen(cmd.c_str(), "r"), popen_deleter);
    
    if (!fd)
    {
        perror("popen()");
        throw std::runtime_error("open terminal failed");
    }

    while (fgets(buffer, sizeof(buffer), fd.get()))
    {
        makesocket::capture << buffer << std::endl;
    }

    std::string output = makesocket::capture.str();

    if (output.find("not found") != std::string::npos)
    {
        return false;
    }

    std::cout<<output<<std::endl;
    makesocket::sendout(output);  
    end = true;
    return true;
}


