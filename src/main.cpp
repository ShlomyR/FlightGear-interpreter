#include "Parser.hpp"
#include "Lexer.hpp"

#define PHAT "/home/charles/Documents/flight_sim_uav/FlightGear-Interpreter-master/good/src/Script.txt"

int main(int argc, char *argv[]) 
{
    std::string file_name;
    
    if(argc > 1) 
    {
        file_name = argv[1];
    }
    
    else
    {
        file_name = PHAT;
    }
    
    Lexer lexer ;
    Parser parser;

    vector<vector<string>> arr = lexer.do_lexer(file_name);
    parser.parse(arr);
    
}
