#ifndef SERVER_HPP
#define SERVER HPP
#include <sstream>
#include <cctype>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>

class makesocket
{
public:
    
    makesocket(int port);
    
    makesocket(int port,std::string address);

    int server_listening(int max_clients);

    int accepts_request();

    int receive_msg();

    bool close_program();

    static int sendout(std::string);

    ~makesocket();



    static std::string buffer;
    static std::stringstream capture;
private:
    const int create_server_socket();
    char temp_buffer[1024] = {0};
    int server_socket;
    static int client_socket_fd;
    sockaddr_in client_ip;
    socklen_t client_ip_len = sizeof(client_ip);
    char client_ipaddr[INET_ADDRSTRLEN];
};

#endif