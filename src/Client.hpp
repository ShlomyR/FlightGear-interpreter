#pragma once

#include <iostream>
#include <sys/socket.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#include "Parser.hpp"


using namespace std;


class Client
{
private:
    static Client* instance;
    void testinClientConection();
        
public:
    static Client* getInstance();
    void Send(string msg);
    void SendVal(vector<vector<string>> &arr,double infix);
    void SendVal(vector<vector<string>> &arr,string val);
	int connectClient(int port,const char* ip);
};

