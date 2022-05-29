#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <ctype.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

#include "Server.hpp"
#include "Client.hpp"
#include "convertSTI.hpp"
#include "Variiable.hpp"
//#include "WhileLoop.hpp"
#include "SymbleVar.hpp"
#include "SuntingYardToken.hpp"


using namespace std;
using namespace std::chrono;


class Command
{
public:
    virtual int DoCommand(vector<vector<string>> &arr, int index) = 0;
    
};

class ConnectCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;
    
    ConnectCommand();
    ~ConnectCommand();
};

class EqualMapCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;
    string uptdateFromDB(vector<vector<string>> &arr, int index);
    bool is_charecther(string val);

    EqualMapCommand();
    ~EqualMapCommand();
};

class OpenServerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;

    static int run_FG();

    OpenServerCommand();
    ~OpenServerCommand();
};

class PrintCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;

    void printFunc(string val);

    PrintCommand();
    ~PrintCommand();
};

class SleepCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;

    void sleepFunc(string val);

    SleepCommand();
    ~SleepCommand();
};

class VerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;

    VerCommand();
    ~VerCommand();
};

class WhileCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr, int index) override;

    static double getVal(vector<vector<string>> &arr, int index);
    int sipRows(vector<vector<string>> &arr, int index);

    WhileCommand();
    ~WhileCommand();
};