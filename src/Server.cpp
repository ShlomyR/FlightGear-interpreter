#include "Server.hpp"
#include <thread>


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

void Server::runFG()
{  
    system("fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small");
}

int Server::connectServer(int port)
{
    
    Server::getInstance()->makeBindArray();

	int server_fd; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    } 
     
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
 
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for connection\n");

    Server::getInstance()->t1 = thread(runFG);

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
   
    printf("connecting...\n");

    Server::getInstance()->t2  = thread(runServerDB); 
    
    return 0;
	
}

string Server::readData(std::string msg)
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
    vector<double> val_vector;

    while (true) 
    {
        int i = 0;
        int val_read = read(new_socket, buffer, 1024);
        
        data.append(buffer, val_read);
        
        curr_data = data.substr(0, data.find("\n"));
        data.erase(0, data.find("\n") + 1);
        val_vector = Server::getInstance()->getValVector(curr_data);
        
        for (double value : val_vector) 
        {
            SymbleVar::getInstance()->creatDataBaseMap(Server::getInstance()->bind_arr[i%36],value);
            i++;
        }
    }
}

vector<double> Server::getValVector(string str) 
{
    char delimiter = ',';
    size_t pos = 0;
    string token;
    vector<double> vector;

    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        vector.push_back(stod(token));
        str.erase(0, pos + 1);
    }
    vector.push_back(stod(str));

    return vector;
}

void Server::makeBindArray()
{
    bind_arr[airspeed] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    bind_arr[warp] = "/sim/time/warp";
    bind_arr[magnetos] = "/controls/switches/magnetos";
    bind_arr[heading] = "/instrumentation/heading-indicator/offset-deg";
    bind_arr[alt] = "/instrumentation/altimeter/indicated-altitude-ft";
    bind_arr[pressure] = "/instrumentation/altimeter/pressure-alt-ft";
    bind_arr[pitch] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    bind_arr[roll] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    bind_arr[internal_pitch] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    bind_arr[internal_roll] = "/instrumentation/attitude-indicator/internal-roll-deg";
    bind_arr[encoder_alt] = "/instrumentation/encoder/indicated-altitude-ft";
    bind_arr[encoder_pressure] = "/instrumentation/encoder/pressure-alt-ft";
    bind_arr[gps_alt] = "/instrumentation/gps/indicated-altitude-ft";
    bind_arr[gps_ground_speed] = "/instrumentation/gps/indicated-ground-speed-kt";
    bind_arr[gps_vertical_speed] = "/instrumentation/gps/indicated-vertical-speed";
    bind_arr[indicated_heading] = "/instrumentation/heading-indicator/indicated-heading-deg";
    bind_arr[compass] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    bind_arr[slip_skid] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    bind_arr[turn_rate] = "/instrumentation/turn-indicator/indicated-turn-rate";
    bind_arr[indicated_speed] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    bind_arr[aileron] = "/controls/flight/aileron";
    bind_arr[elevator] = "/controls/flight/elevator";
    bind_arr[rudder] = "/controls/flight/rudder";
    bind_arr[flaps] = "/controls/flight/flaps";
    bind_arr[engine_throttle] = "/controls/engines/engine/throttle";
    bind_arr[curr_engine_throttle] = "/controls/engines/current-engine/throttle";
    bind_arr[master_avionics] = "/controls/switches/master-avionics";
    bind_arr[starter] = "/controls/switches/starter";
    bind_arr[auto_start] = "/engines/active-engine/auto-start";
    bind_arr[speed_brake] = "/controls/flight/speedbrake";
    bind_arr[brake_parking] = "/sim/model/c172p/brake-parking";
    bind_arr[engine_primer] = "/controls/engines/engine/primer";
    bind_arr[engine_mixture] = "/controls/engines/current-engine/mixture";
    bind_arr[master_bat] = "/controls/switches/master-bat";
    bind_arr[master_alt] = "/controls/switches/master-alt";
    bind_arr[engine_rpm] = "/engines/engine/rpm";
}