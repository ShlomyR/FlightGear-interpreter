#include "Client.hpp"


Client* Client::instance = 0;
Client* Client::getInstance()
{
    if (instance == 0)
    {
        instance = new Client();
    }
    return instance;
}

Client::Client(){}

int sock = 0, valread; 

int Client::connect1(int port)
{
	struct sockaddr_in serv_addr; 
	
	char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return 0; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
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

int Client::testinClientConection()
{
    
	Client::getInstance()->Send("set controls/flight/rudder -1\r\n");
	
    return 0;
}

void Client::Send(std::string msg)
{
	send(sock , msg.c_str() , msg.length() , 0 );
    cout << msg << "\n";
    
}

Client::~Client()
{

}