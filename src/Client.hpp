#pragma once

#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Parser.hpp"


using namespace std;


class Client
{
private:
    Client();
    ~Client();
    static Client* instance;
    int testinClientConection();
        
public:
    static Client* getInstance();
    void Send(std::string msg);
    void SendVal(vector<vector<string>> &arr,double infix);
	int connectClient(int port);
		
};

