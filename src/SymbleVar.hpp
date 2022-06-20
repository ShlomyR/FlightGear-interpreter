#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <thread>
#include <unordered_map>



using namespace std;

using namespace std::chrono;


class SymbleVar
{
private:
    SymbleVar();
    static SymbleVar* instance;
    template<typename K, typename V>
    void print_mapDB(std::unordered_map<K, V> const &m);

public:
        
    static SymbleVar* getInstance();
    unordered_map<string,double> data_base;
    unordered_map<string,double> creatDataBaseMap(string key,double val);

};


