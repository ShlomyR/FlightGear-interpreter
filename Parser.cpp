#include "Parser.hpp"



Parser::Parser() 
{
    this->command_map["openDataServer"] = new OpenServerCommand();
    this->command_map["connect"] = new ConnectCommand();
    this->command_map["var"] = new VerCommand();
    this->command_map["="] = new EqualMapCommand();
    this->command_map["while"] = new WhileCommand();
    this->command_map[""] = new WhileCommand();
    this->command_map["print"] = new PrintCommand();
    this->command_map["sleep"] = new SleepCommand();
}
vector<vector<string>> Parser::vector_commands;


void Parser::parse(vector<vector<string>>& arr) 
{

    int index = 0;
    
    for (index ;index < arr.size();index++)
    {
        if ((arr[index][1] == "="))
        {
            Command* c = command_map.find(arr[index][1])->second;
            index += c->DoCommand(arr, index);
            
        }
        else
        {
            Command* c = command_map.find(arr[index][0])->second;
            index += c->DoCommand(arr, index);
        }
        
        
    }
    
}

