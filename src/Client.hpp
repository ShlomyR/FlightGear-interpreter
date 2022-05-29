#pragma once

#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


class Client
{
    private:
        static Client* instance;
        
        Client();
        ~Client();
    public:
        /* Static access method. */
        static Client* getInstance();
        static int testinClientConection();
        void Send(std::string msg);
		static int connect1(int port);
		
};

