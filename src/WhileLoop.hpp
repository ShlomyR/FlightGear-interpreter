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
    static void deleteSpace(vector<vector<string>> &arr);
public:
    WhileLoop();
    static int whileLoop(vector<vector<string>> &arr);
        
    vector<string> infix_vec;
    vector<vector<string>> copy_arr;

};