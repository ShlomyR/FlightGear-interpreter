#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "Command.hpp"

using namespace std;

class Parser
{
private:
    unordered_map<string,Command*> command_map;

public:
    Parser();
    ~Parser();
    static int index;
    void parse(vector<vector<string>> &arr);
    static vector<vector<string>> vector_commands;
};