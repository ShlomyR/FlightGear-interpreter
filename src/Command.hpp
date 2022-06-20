#pragma once


#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <bits/stdc++.h>

#include "Server.hpp"
#include "Variable.hpp"
#include "SymbleVar.hpp"
#include "SuntingYardToken.hpp"


using namespace std;
using namespace std::chrono;

class Command
{
public:
    virtual int DoCommand(vector<vector<string>> &arr) = 0;
    virtual ~Command();
    
};

class OpenServerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    OpenServerCommand();
    ~OpenServerCommand();
    
};

class ConnectCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;
    
    ConnectCommand();
    ~ConnectCommand();
};

class VerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    VerCommand();
    ~VerCommand();
};

class EqualMapCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;
    void uptdateFromDB(vector<vector<string>> &arr);

    EqualMapCommand();
    ~EqualMapCommand();
};

class WhileCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    static double getVal(vector<vector<string>> &arr,int index);
    int skipRows(vector<vector<string>> &arr,int index);

    WhileCommand();
    ~WhileCommand();
};

class SleepCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    void sleepFunc(string val);

    SleepCommand();
    ~SleepCommand();
};

class PrintCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    void printFunc(string val);

    PrintCommand();
    ~PrintCommand();
};

class ExitCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

    ExitCommand();
    ~ExitCommand();
};