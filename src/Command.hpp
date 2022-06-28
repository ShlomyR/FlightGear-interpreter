#pragma once


#include <iostream>
#include <cstring>
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

};

class OpenServerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

};

class ConnectCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;
    
};

class VerCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

};

class EqualMapCommand : public Command
{
private:
    void uptdateFromDB(vector<vector<string>> &arr);
    void convertFromChToNum(vector<vector<string>> &arr);
    void strToInfix(int i);
    void checkMinus();

public:    
    int DoCommand(vector<vector<string>> &arr) override;

};

class WhileCommand : public Command
{
private:
    int skipRows(vector<vector<string>> &arr,int index);
public:
    int DoCommand(vector<vector<string>> &arr) override;

    static double getVal(vector<vector<string>> &arr,int index);

};

class SleepCommand : public Command
{
private:
    void sleepFunc(string val);
public:
    int DoCommand(vector<vector<string>> &arr) override;

};

class PrintCommand : public Command
{
private:
    void printFunc(string val);
public:
    int DoCommand(vector<vector<string>> &arr) override;

};

class ExitCommand : public Command
{
public:
    int DoCommand(vector<vector<string>> &arr) override;

};