#include "SymbleVar.hpp"


SymbleVar* SymbleVar::instance = 0;
SymbleVar* SymbleVar::getInstance()
{
    if (instance == 0)
    {
        instance = new SymbleVar();
    }
    return instance;
}



SymbleVar::SymbleVar() {}


template<typename Ks, typename Vs>
void SymbleVar::print_mapDB(std::unordered_map<Ks, Vs> const &m)
{
    
    if (m.empty())
    {
        cout << "The map is empty\n";
    }
    else
    {
        for (auto const &pair: m) 
        {
            std::cout << "{" << pair.first << " : " << pair.second << "}\n";
        }
    }
}

unordered_map<string,double> SymbleVar::data_base;

unordered_map<string,double> SymbleVar::creatDataBaseMap(string key,double val)
{    
    SymbleVar::getInstance()->data_base[key] = val;

    return SymbleVar::getInstance()->data_base;    
}
