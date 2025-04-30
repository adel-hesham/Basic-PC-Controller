/**************************************server.cpp file*****************************************
 * Project: Remote PC Controller (Linux System Controller)
 * Description: This server receives commands from a client to perform actions 
 *              like shutdown, open apps (Tilix, Edge, WhatsApp, VS Code), check battery, 
 *              search the web, and check emails via socket communication.
 * Author: [Eng/Adel elnimr]
 * Date: [30/4/2025]
 ******************************************************************************************/


/***********************************************/
#include <cstdio>
#include <iostream>
#include <regex>
#include "server.hpp"
/***********************************************/

std::stringstream makesocket::capture("0");
int makesocket::client_socket_fd=0;
makesocket::makesocket(int port, sa_family_t ipversion,int protocol)
{
    server_socket=create_server_socket(ipversion, protocol);
    sockaddr_in server_add;
    server_add.sin_family=ipversion;
    server_add.sin_port=htons(port);
    server_add.sin_addr.s_addr=INADDR_ANY;
    if(bind(server_socket,(struct sockaddr*)&server_add, sizeof(server_add))==-1)
    {
        perror("bind()");
        close(server_socket); 
        exit(1);
    }
    else
    {
        std::cout<<"bind successful"<<std::endl;
    }
}
makesocket::makesocket(int port, sa_family_t ipversion,int protocol,std::string address)
{
    server_socket=create_server_socket(ipversion, protocol);
    sockaddr_in server_add;
    server_add.sin_family=ipversion;
    server_add.sin_port=htons(port);
    inet_pton(ipversion,address.c_str() , &server_add.sin_addr);
    if(bind(server_socket,(struct sockaddr*)&server_add, sizeof(server_add))==-1)
    {
        perror("bind()");
        close(server_socket); 
        exit(1);
    }
    else
    {
        std::cout<<"bind successful"<<std::endl;
    }
}
int makesocket::server_listening(int max_clients)
{
    if(listen(server_socket, max_clients)==-1)
    {
        perror("listen()");
        close(server_socket); 
        return -1;
    }
    else
    {
        std::cout<<"listening..."<<std::endl;
        return 0;
    }
}
int makesocket::accepts_request()
{
    client_socket_fd=accept(server_socket, (struct sockaddr*)&client_ip, &client_ip_len);
    if(client_socket_fd==-1)
    {
        perror("accept request failed: ");
        return -1;
    }
    else
    {
        std::cout<<"ip: "<<inet_ntoa(client_ip.sin_addr)<<" port: "<<ntohs(client_ip.sin_port)<<std::endl;
        std::cout<<"request accepted"<<std::endl;
        return 0;
    }
}
int makesocket::receive_msg()
{
    int received_bytes=recv(client_socket_fd,&temp_buffer[0],sizeof(temp_buffer),0);
    if(received_bytes==-1)
    {
        perror("receiving failed");
        close(server_socket);
        exit(1);
    }
    else
    {
        temp_buffer[received_bytes]='\0';
        buffer.append(temp_buffer);
        buffer = std::regex_replace(buffer, std::regex(R"(\s+$)"), "");
        std::cout<<"ip: "<<inet_ntoa(client_ip.sin_addr)<<" port: "<<ntohs(client_ip.sin_port)<<" is sending a message"<<std::endl;
        std::cout<<buffer<<"  "<<received_bytes<<std::endl;
        std::transform(buffer.begin(),buffer.end(),buffer.begin(),::tolower);
        return received_bytes;
    }
}
bool makesocket::close_program()
{
    if(close(server_socket)!=0)
    {
        perror("close()");
    }
    return false;
}
const int makesocket::create_server_socket(sa_family_t &ipversion,int &protocol)
{
    int server_socket=socket(ipversion, protocol, 0);
    if(server_socket==-1)
    {
        perror("creating socket failed");
        exit(1);
    }
    else
    {
        std::cout<<"socket created successfully"<<std::endl;
        return server_socket;
    }
}
int makesocket::sendout(std::string msg)
{
    if(msg.empty()==false)
    {
        if(send(client_socket_fd, msg.c_str(), msg.size(), 0)==-1)
        {
            perror("send()");
            return-1;
        }
        else
        {
            capture.str("");
            capture.clear();
            return 0;
        }
    }
    return -2;
}
makesocket::~makesocket()
{
    if(server_socket!=-1)
    {
        close(server_socket);
    }
}











