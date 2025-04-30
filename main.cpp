

/**************************************main.cpp file*****************************************
 * Project: Remote PC Controller (Linux System Controller)
 * Description: This server receives commands from a client to perform actions 
 *              like shutdown, open apps (Tilix, Edge, WhatsApp, VS Code), check battery, 
 *              search the web, and check emails via socket communication.
 * Author: [Eng/Adel elnimr]
 * Date: [30/4/2025]
 ******************************************************************************************/


/***********************define libraries*********************/
#include <iostream>
#include <regex>
#include "server.hpp"
#include "command.hpp"

/************************************************************/

//define numbers

constexpr int port_number=55555;
constexpr int queue_size=2;

int main()
{
    //create object of class makesocket to create a new socket 
    //create object of class control to use command functions  
    makesocket s(port_number,AF_INET,SOCK_STREAM); 
    control c;  

    //define regex to match the incoming input from client

    std::regex shutdown_now("^shutdown now$");
    std::regex shutdown_intime("^shutdown after [1-9][0-9]*$");
    std::regex shutdown_inclock("^shutdown at (0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    std::regex search_web("^search web:.+$");
    
    //start listening clients

    s.server_listening(queue_size);
    
    while (true) 
    {
        //variable to break out of loop
        bool state=true;

        //accept the clients according to the queue size
        s.accepts_request();

        while (true) 
        {
            //receive a message from a client
            if(s.receive_msg()==0)
            {
                std::cout<<"client disconnected"<<std::endl;
                break;
            }

            else if(std::regex_match(s.buffer.c_str(),shutdown_now)==true)
            {
                std::cout<<"power of"<<std::endl;
                s.capture<<"power of"<<std::endl;
                s.sendout(s.capture.str());
                c.shutdown();
            }
            else if(s.buffer.find("cancel shutdown")!=std::string::npos)
            {
                if(c.cancel_shutdown())
                {
                    std::cout<<"cancel scheduled shutdown"<<std::endl;
                    s.capture<<"cancel scheduled shutdown"<<std::endl;
                    s.sendout(s.capture.str());
                }
            }
            else if(std::regex_match(s.buffer.c_str(),shutdown_intime)==true)
            {
                if(c.shutdown_timer(s.buffer.substr(15)))
                {
                    std::cout<<"the OS will shut down in "<<s.buffer.substr(15)<<" minutes"<<std::endl;
                    s.capture<<"the OS will shut down in "<<s.buffer.substr(15)<<" minutes"<<std::endl;
                } 
            }
            else if(std::regex_match(s.buffer.c_str(),shutdown_inclock)==true)
            {
                if(c.shutdown_in_time(s.buffer.substr(12)))
                {
                    std::cout<<"the OS will shut down at "<<s.buffer.substr(12)<<" o'clock"<<std::endl;
                    s.capture<<"the OS will shut down at "<<s.buffer.substr(12)<<" o'clock"<<std::endl;
                }
            }
            else if(s.buffer.find("seen emails")!=std::string::npos)
            {
                std::cout<<"processing..."<<std::endl;
                s.capture<<"processing..."<<std::endl;
                s.sendout(s.capture.str());
                if(c.seen_all_gmails())
                {
                    s.capture<<"Done!"<<std::endl;
                    s.sendout(s.capture.str());
                }
                

            }
            else if(s.buffer.find("close")!=std::string::npos)
            {
                s.capture<<"closing..."<<std::endl;
                s.sendout(s.capture.str());
                state=s.close_program();
                break;
                
                    
            }
            else if(s.buffer.find("open whatsapp")!=std::string::npos)
            {
                if(c.open_whatsapp())
                {
                    s.capture<<"Done!"<<std::endl;
                }
            }
            else if(s.buffer.find("open tilix")!=std::string::npos)
            {
                if(c.open_tilix())
                {
                    s.capture<<"Done!"<<std::endl;
                }
            }
            else if(s.buffer.find("open edge")!=std::string::npos)
            {
                if(c.open_edge())
                {
                    s.capture<<"Done!"<<std::endl;
                }
            }
            else if(s.buffer.find("open code")!=std::string::npos)
            {
                if(c.open_code())
                {
                    s.capture<<"Done!"<<std::endl;
                }
            }
            else if(std::regex_match(s.buffer.c_str(),search_web)==true)
            {
                if(c.search_web(s.buffer.substr(11)))
                {
                    s.capture<<"Done!"<<std::endl;
                }
            }
            else if(s.buffer.find("battery info")!=std::string::npos)
            {
                    c.battery_info();
                    s.capture<<" Done!"<<std::endl;  
            }
            else
            {
                std::cout<<"invalid pattern try again"<<std::endl;
                s.capture<<"invalid pattern try again"<<std::endl;
            }
            if(!s.capture.str().empty())
            {
                s.sendout(s.capture.str());
            }
            s.buffer.clear();

        }
        if(state==false)
        {
            s.capture<<"bye bye!";
            s.sendout(s.capture.str());
            break;
        }
    }
    
    return 0;
}