#include "Client.hpp"

#define SET (string)"set"
#define ACTIVATE (string)"\r\n"

Client* Client::instance = 0;
Client* Client::getInstance()
{
    if (instance == 0)
    {
        instance = new Client();
    }
    return instance;
}

int sock = 0, valread;
string Set = "set";
string Activate = "\r\n";


int Client::connectClient(int port,const char* ip)
{
	struct sockaddr_in serv_addr; 
	
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return 0; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return 0; 
    } 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return 0; 
    }
    return 0;
}

void Client::testinClientConection()
{ 
	Client::getInstance()->Send(Set+" controls/flight/rudder 1"+Activate);
}

void Client::Send(std::string msg)
{
	send(sock , msg.c_str() , msg.length() , 0 );

    cout << msg << "\n"; 
}

void Client::SendVal(vector<vector<string>> &arr,double infix)
{
    string val = to_string(infix);

   Client::getInstance()->Send(Set + " " + Variable::getInstance()->base_map_DB.at(arr[Parser::index][0]) + " " + val + Activate);  
}

void Client::SendVal(vector<vector<string>> &arr,string val)
{
   Client::getInstance()->Send(Set + " " + Variable::getInstance()->base_map_DB.at(arr[Parser::index][0]) + " " + val + Activate);
}