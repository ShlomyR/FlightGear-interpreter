#include <string>
#include <vector>

#include "Parser.hpp"
#include "Lexer.hpp"



using namespace std;



int main(int argc, char *argv[]) 
{
    string fileName;
    
    if(argc > 1) 
    {
        fileName = argv[1];
    }
    
    else
    {
        fileName = "/home/charles/Documents/flight_sim_uav/FlightGear-Interpreter-master/good/src/Script.txt";
    }
    
    Lexer* lexer = new Lexer();
    vector<vector<string>> arr = lexer->do_lexer(fileName);
    Parser* parser = new Parser();
    parser->parse(arr);

}
