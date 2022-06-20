#include "Server.hpp"
#include <thread>

Server::Server()
{
    
}

Server* Server::instance = 0;
Server* Server::getInstance()
{
    if (instance == 0)
    {
        instance = new Server();
    }
    return instance;
}

int new_socket,client_socket;

void Server::run_FG()
{  
    system("fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small");
}

int Server::connectServer(int port,int ping)
{
    
    Server::getInstance()->makeBindArray();

	int server_fd; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address);

    (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ;

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); 
     
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
 
    bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0;

    listen(server_fd, 3) < 0 ;
    
    printf("Waiting for connection\n");

    Server::getInstance()->t2 = thread(run_FG);

    (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0 ;
   
    printf("connecting...\n");

    Server::getInstance()->t1  = thread(runServerDB); 
    
    return 0;
	
}

string Server::read_data(std::string msg)
{
    read(new_socket,(char*)msg.c_str(),msg.length());

    cout << msg << "\n";

    return msg;  
}

void Server::runServerDB() 
{
    char buffer[1024];
    bzero(buffer, 1024);
    string data, curr_data;
    vector<double> valVector;

    while (true) 
    {
        int i = 0;
        int valread = read(new_socket, buffer, 1024);
        
        data.append(buffer, valread);
        
        while (!data.find('\n')) 
        {
            valread = read(new_socket, buffer, 1024);
            data.append(buffer, valread);
        }

        curr_data = data.substr(0, data.find('\n'));
        data.erase(0, data.find('\n') + 1);
        valVector = Server::getInstance()->getValVector(curr_data);
        SymbleVar* symbolTable = SymbleVar::getInstance();

        for (double value : valVector) 
        {
            symbolTable->creatDataBaseMap(Server::getInstance()->bindArr[i%36],value);
            i++;
        }
    }
}

vector<double> Server::getValVector(string s) 
{
    char delimiter = ',';
    size_t pos = 0;
    std::string token;
    vector<double> vector;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        vector.push_back(stof(token));
        s.erase(0, pos + 1);
    }
    vector.push_back(stof(s));
    return vector;
}

void Server::makeBindArray()
{
    bindArr[airspeed] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    bindArr[warp] = "/sim/time/warp";
    bindArr[magnetos] = "/controls/switches/magnetos";
    bindArr[heading] = "/instrumentation/heading-indicator/offset-deg";
    bindArr[alt] = "/instrumentation/altimeter/indicated-altitude-ft";
    bindArr[pressure] = "/instrumentation/altimeter/pressure-alt-ft";
    bindArr[pitch] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    bindArr[roll] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    bindArr[internal_pitch] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    bindArr[internal_roll] = "/instrumentation/attitude-indicator/internal-roll-deg";
    bindArr[encoder_alt] = "/instrumentation/encoder/indicated-altitude-ft";
    bindArr[encoder_pressure] = "/instrumentation/encoder/pressure-alt-ft";
    bindArr[gps_alt] = "/instrumentation/gps/indicated-altitude-ft";
    bindArr[gps_ground_speed] = "/instrumentation/gps/indicated-ground-speed-kt";
    bindArr[gps_vertical_speed] = "/instrumentation/gps/indicated-vertical-speed";
    bindArr[indicated_heading] = "/instrumentation/heading-indicator/indicated-heading-deg";
    bindArr[compass] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    bindArr[slip_skid] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    bindArr[turn_rate] = "/instrumentation/turn-indicator/indicated-turn-rate";
    bindArr[indicated_speed] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    bindArr[aileron] = "/controls/flight/aileron";
    bindArr[elevator] = "/controls/flight/elevator";
    bindArr[rudder] = "/controls/flight/rudder";
    bindArr[flaps] = "/controls/flight/flaps";
    bindArr[engine_throttle] = "/controls/engines/engine/throttle";
    bindArr[curr_engine_throttle] = "/controls/engines/current-engine/throttle";
    bindArr[master_avionics] = "/controls/switches/master-avionics";
    bindArr[starter] = "/controls/switches/starter";
    bindArr[auto_start] = "/engines/active-engine/auto-start";
    bindArr[speedbrake] = "/controls/flight/speedbrake";
    bindArr[brake_parking] = "/sim/model/c172p/brake-parking";
    bindArr[engine_primer] = "/controls/engines/engine/primer";
    bindArr[engine_mixture] = "/controls/engines/current-engine/mixture";
    bindArr[master_bat] = "/controls/switches/master-bat";
    bindArr[master_alt] = "/controls/switches/master-alt";
    bindArr[engine_rpm] = "/engines/engine/rpm";
}

Server::~Server()
{

}