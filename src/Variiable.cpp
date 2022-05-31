#include "Variiable.hpp"

Variiable* Variiable::instance = 0;
Variiable* Variiable::getInstance()
{
    if (instance == 0)
    {
        instance = new Variiable();
    }
    return instance;
}


Variiable::Variiable()
{
       
}

vector<string>  Variiable::vecSY;

unordered_map<string,string> Variiable::baseMapDB;

template<typename K, typename V>
void Variiable::print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

unordered_map<string,string> Variiable::Vari(vector<string> var_arr)
{
    
    
    
    if (var_arr[2] == "bind")
    {
        baseMapDB.insert({var_arr[0],var_arr[3]});
        vecSY.push_back(baseMapDB.find(var_arr[0])->first) ;
        //print_map(baseMapDB);
    }
    
    else
    {
        getVarValue(var_arr);
    }   
    

    return baseMapDB;
    
}

void Variiable::getVarValue(vector<string> var_arr)
{
    //sleep(70);
        
    
    SymbleVar::getInstance()->data_base[var_arr[0]];

    //cout << "h0 before = : " << SymbleVar::getInstance()->data_base.at(arr_var1[0]) << "\n";
    
        
    SymbleVar::getInstance()->data_base.at(var_arr[0]) = SymbleVar::getInstance()->data_base.find(baseMapDB.at(var_arr[2]))->second;
    //cout << "h0 after = : " << SymbleVar::getInstance()->data_base.at(arr_var1[0]) << "\n";
    vecSY.insert(vecSY.begin(), SymbleVar::getInstance()->data_base.find(var_arr[0])->first);
    vecSY.insert(vecSY.begin(),vecSY[6]);
    vecSY.insert(vecSY.begin(),vecSY[6]);
    // for (int i = 0; i < vecSY.size(); i++)
    // {
    //    cout << "vec: " << vecSY[i] << "\n";
    // }
    
    
}

Variiable::~Variiable()
{
    
    
}