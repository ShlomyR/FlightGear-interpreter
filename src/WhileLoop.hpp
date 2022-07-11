#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "Parser.hpp"



class WhileLoop
{
private:
    static void pushToVec(vector<vector<string>> &arr,int i);
public:
    static int whileLoop(vector<vector<string>> &arr);
    static string infix_str;
    static vector<vector<string>> copy_arr;

};