#pragma once

#include "Command.hpp"

using namespace std;
    
class Variable
{
private:
    static Variable* instance;
    void getVarValue(vector<string> var_arr);
    template<typename K, typename V>
    void printMap(unordered_map<K, V> const &m);
    
public:
    unordered_map<string,string> base_map_DB;
    vector<string>  vec_all_vars;
    static Variable* getInstance();
    void createVar(vector<string> var_arr);
      
};





