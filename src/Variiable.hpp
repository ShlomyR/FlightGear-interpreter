#pragma once

#include "Command.hpp"




using namespace std;
    



class Variiable
{
private:

    
    static Variiable* instance;
    Variiable();
    ~Variiable();
    

    
public:
    static void getVarValue(vector<string> var_arr);
    
    static unordered_map<string,string> baseMapDB;
    static vector<string>  vecSY;
    template<typename K, typename V>
    static void print_map(std::unordered_map<K, V> const &m);

    static Variiable* getInstance();
    
    static unordered_map<string,string> Vari(vector<string> var_arr);
    
    
    
    
};





