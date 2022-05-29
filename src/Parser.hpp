#pragma once

#include "Command.hpp"

class Parser
{
private:
    unordered_map<string,Command*> command_map;

public:
    Parser();
    void parse (vector<vector<string>>& arr);
    static vector<vector<string>> vector_commands;
};