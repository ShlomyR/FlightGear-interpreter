#pragma once

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <chrono>
#include <thread>
#include <future>

using namespace std;
using namespace std::chrono;

#include "SymbleVar.hpp"



class Server
{
private:

    Server();
    ~Server();
	static Server* instance;

    
		

public:
    std::string bindArr[37];
    std::thread t1;
    std::thread t2;

    

    int makeBindArray();

	static int connectServer(int port, int ping);
    static string read_data(std::string msg);
    static vector<double> getValVector(string s);
    
	static Server* getInstance();
    
    
    
			
};

enum vars {
    airspeed = 0,
    warp,
    magnetos,
    heading,
    alt,
    pressure,
    pitch,
    roll,
    internal_pitch,
    internal_roll,
    encoder_alt,
    encoder_pressure,
    gps_alt,
    gps_ground_speed,
    gps_vertical_speed,
    indicated_heading,
    compass,
    slip_skid,
    turn_rate,
    indicated_speed,
    aileron,
    elevator,
    rudder,
    flaps,
    engine_throttle,
    curr_engine_throttle,
    master_avionics,
    starter,
    auto_start,
    speedbrake,
    brake_parking,
    engine_primer,
    engine_mixture,
    master_bat,
    master_alt,
    engine_rpm,
    brakes
};