#include "Parser.hpp"

Parser::Parser()
{
    command_map["openDataServer"] = new OpenServerCommand();
    command_map["connect"] = new ConnectCommand();
    command_map["var"] = new VerCommand();
    command_map["="] = new EqualMapCommand();
    command_map["while"] = new WhileCommand();
    command_map["print"] = new PrintCommand();
    command_map["sleep"] = new SleepCommand();
    command_map["exit"] = new ExitCommand();
}

vector<vector<string>> Parser::vector_commands;

int Parser::index;

void Parser::parse(vector<vector<string>> &arr)
{
    for (Parser::index = 0; Parser::index < arr.size(); Parser::index++)
    {
        Command *c;
        if (arr[Parser::index][1] == "=")
        {
            c = command_map.at(arr[Parser::index][1]);
        }
        else
        {
            c = command_map.at(arr[Parser::index][0]);
        }
        Parser::index += c->DoCommand(arr);
    }
}

Parser::~Parser()
{
    command_map["openDataServer"]->~Command();
    command_map["connect"]->~Command();
    command_map["var"]->~Command();
    command_map["="]->~Command();
    command_map["while"]->~Command();
    command_map["print"]->~Command();
    command_map["sleep"]->~Command();
    command_map["exit"]->~Command();
}