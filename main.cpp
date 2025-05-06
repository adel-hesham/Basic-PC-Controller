

/**************************************main.cpp file*****************************************
 * Project: Remote PC Controller (Linux System Controller)
 * Description: This server receives commands from a client to perform actions 
 *              like shutdown, open apps (Tilix, Edge, WhatsApp, VS Code), check battery, 
 *              search the web, and check emails via socket communication.
 * Author: [Eng/Adel elnimr]
 * Date: [30/4/2025]
 ******************************************************************************************/


/***********************define libraries*********************/
#include "server.hpp"
#include "command.hpp"
#include "signal_handler.hpp"
#include <cstring>
#include <functional>
#include <iostream>
#include <regex>
#include <map>
#include <stdexcept>
#include <string>

/************************************************************/

//define numbers
constexpr int port_number=55555;
constexpr int queue_size=2;

// global flag


int main()
{
    //variable to break out of loop
    bool state=true;

    //create object of class makesocket to create a new socket 
    //create object of class control to use command functions  
    //create object of class control to use signal handler  

    control c;  
    makesocket s(port_number); 
    handler h(2);

   
    //map to set every key word with it's function

    std::map<std::string, std::function<void()>> commands{
   {"seen emails",[&c](){c.seen_all_gmails();}},
   {"open whatsapp",[&c](){c.open_whatsapp();}},
   {"open tilix",[&c](){c.open_tilix();}},
   {"open browser",[&c](){c.open_browser();}},
   {"open code",[&c](){c.open_code();}},
   {"open terminal",[&c](){c.open_terminal();}},
   {"open facebook",[&c](){c.open_facebook();}},
   {"open youtube",[&c](){c.open_youtube();}},
   {"open linkedin",[&c](){c.open_linkedin();}},
   {"open github",[&c](){c.open_github();}},
   {"battery info",[&c](){c.battery_info();}},
   {"shutdown now",[&c](){c.shutdown();}},
   {"restart now",[&c](){c.restart();}},
   {"cancel shutdown",[&c](){c.cancel_shutdown();}},
   {"search web:",[&c](){c.search_web();}}, 
   {"close",[&s,&state](){ state=s.close_program();}},
    }; 

    //regex for web search
    std::regex search_web("^search web:.+$");
    
    //start listening clients

    s.server_listening(queue_size);
    
    while (state) 
    {
        //accept the clients according to the queue size
        s.accepts_request();

        while (state) 
        {
            //receive a message from a client
            if(s.receive_msg()==0)
            {
                std::cout<<"client disconnected"<<std::endl;
                break;
            }
            
            try 
            {   
                if(std::regex_match(s.buffer,search_web)==true)
                {
                    commands["search web:"]();
                }
                
                else
                {
                    
                    commands.at(s.buffer)();

                }

                std::cout<<"Done!"<<std::endl;
                s.capture<<"Done!"<<std::endl;

                s.sendout(s.capture.str());
            }
            catch (const std::out_of_range &e) 
            {

                if(!c.terminal_screen())
                {
                    std::cout<<e.what()<<std::endl;
                    std::cout<<"Wrong pattern! Try again"<<std::endl;
                }
            }

            catch (const std::runtime_error &e) 
            {
                std::cout<<e.what()<<std::endl;
                s.buffer.clear();
                continue;
            }

            if(!s.capture.str().empty())
            {
                s.sendout(s.capture.str());
            }

            s.buffer.clear();
            
        }
        if(!state)
        {
            s.capture<<"server shutting down!";
            s.sendout(s.capture.str());
            break;
        }
    }
    return 0;
}