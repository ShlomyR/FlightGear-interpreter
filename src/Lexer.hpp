#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "Parser.hpp"

using namespace std;

class Lexer 
{
private:
    void splitbyWord(string const &str,vector<string> &vec_str,const char Delim);
    void printVec(vector<vector<string>> &vec_arr);
    void deleteSpace(vector<vector<string>> &arr);

public:
    Lexer();
    vector<vector<string>> do_lexer (string file_name);
};