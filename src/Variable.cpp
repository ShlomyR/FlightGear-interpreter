#include "Variable.hpp"

Variable* Variable::instance = 0;
Variable* Variable::getInstance()
{
    if (instance == 0)
    {
        instance = new Variable();
    }
    return instance;
}


Variable::Variable()
{
       
}

template<typename K, typename V>
void Variable::print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

unordered_map<string,string> Variable::CreateVar(vector<string> var_arr)
{
    
    
    
    if (var_arr[2] == "bind")
    {
        Variable::getInstance()->base_map_DB.insert({var_arr[0],var_arr[3]});
        Variable::getInstance()->vec_all_symbels.push_back(Variable::getInstance()->base_map_DB.find(var_arr[0])->first);
    }
    
    else
    {
        getVarValue(var_arr);
    }   
    
    return Variable::getInstance()->base_map_DB;
}

void Variable::getVarValue(vector<string> var_arr)
{          
    SymbleVar::getInstance()->data_base[var_arr[0]];
    SymbleVar::getInstance()->data_base.at(var_arr[0]) = SymbleVar::getInstance()->data_base.find(Variable::getInstance()->base_map_DB.at(var_arr[2]))->second;
    Variable::getInstance()->vec_all_symbels.insert(Variable::getInstance()->vec_all_symbels.begin(), SymbleVar::getInstance()->data_base.find(var_arr[0])->first);
}

Variable::~Variable()
{
      
}