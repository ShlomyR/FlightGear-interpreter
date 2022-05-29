#include "Server.hpp"
#include <thread>

Server::Server(){}

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

int run_FG()
{
    string s = "fgfs --verbose -v";
    system(s.c_str());

    return 0;
}

void runServer();

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
    
    printf("Waiting to connection\n");

    //Server::getInstance()->t2 = thread(run_FG);

    (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0 ;
   

    Server::getInstance()->t1  = thread(runServer); 
    
    return 0;
	
}


string Server::read_data(std::string msg)
{
    read(new_socket , (char*)msg.c_str(), msg.length());
    cout << msg << "\n";
    return msg;
    
}



void runServer() 
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
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        vector.push_back(stof(token));
        s.erase(0, pos + 1);
    }
    vector.push_back(stof(s));
    return vector;
}

int Server::makeBindArray()
{
    this->bindArr[airspeed] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    this->bindArr[warp] = "/sim/time/warp";
    this->bindArr[magnetos] = "/controls/switches/magnetos";
    this->bindArr[heading] = "/instrumentation/heading-indicator/offset-deg";
    this->bindArr[alt] = "/instrumentation/altimeter/indicated-altitude-ft";
    this->bindArr[pressure] = "/instrumentation/altimeter/pressure-alt-ft";
    this->bindArr[pitch] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    this->bindArr[roll] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    this->bindArr[internal_pitch] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    this->bindArr[internal_roll] = "/instrumentation/attitude-indicator/internal-roll-deg";
    this->bindArr[encoder_alt] = "/instrumentation/encoder/indicated-altitude-ft";
    this->bindArr[encoder_pressure] = "/instrumentation/encoder/pressure-alt-ft";
    this->bindArr[gps_alt] = "/instrumentation/gps/indicated-altitude-ft";
    this->bindArr[gps_ground_speed] = "/instrumentation/gps/indicated-ground-speed-kt";
    this->bindArr[gps_vertical_speed] = "/instrumentation/gps/indicated-vertical-speed";
    this->bindArr[indicated_heading] = "/instrumentation/heading-indicator/indicated-heading-deg";
    this->bindArr[compass] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    this->bindArr[slip_skid] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    this->bindArr[turn_rate] = "/instrumentation/turn-indicator/indicated-turn-rate";
    this->bindArr[indicated_speed] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    this->bindArr[aileron] = "/controls/flight/aileron";
    this->bindArr[elevator] = "/controls/flight/elevator";
    this->bindArr[rudder] = "/controls/flight/rudder";
    this->bindArr[flaps] = "/controls/flight/flaps";
    this->bindArr[engine_throttle] = "/controls/engines/engine/throttle";
    this->bindArr[curr_engine_throttle] = "/controls/engines/current-engine/throttle";
    this->bindArr[master_avionics] = "/controls/switches/master-avionics";
    this->bindArr[starter] = "/controls/switches/starter";
    this->bindArr[auto_start] = "/engines/active-engine/auto-start";
    this->bindArr[speedbrake] = "/controls/flight/speedbrake";
    this->bindArr[brake_parking] = "/sim/model/c172p/brake-parking";
    this->bindArr[engine_primer] = "/controls/engines/engine/primer";
    this->bindArr[engine_mixture] = "/controls/engines/current-engine/mixture";
    this->bindArr[master_bat] = "/controls/switches/master-bat";
    this->bindArr[master_alt] = "/controls/switches/master-alt";
    this->bindArr[engine_rpm] = "/engines/engine/rpm";

    return 0;
}


Server::~Server()
{

}