#pragma once

#include "Command.hpp"

using namespace std;
    
class Variable
{
private:

    Variable();
    ~Variable();
    static Variable* instance;
    void getVarValue(vector<string> var_arr);
    template<typename K, typename V>
    void print_map(std::unordered_map<K, V> const &m);
    
public:
    
    unordered_map<string,string> base_map_DB;
    vector<string>  vec_all_symbels;
    static Variable* getInstance();
    unordered_map<string,string> CreateVar(vector<string> var_arr);
      
};





