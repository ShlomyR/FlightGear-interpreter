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

template<typename Ks, typename Vs>
void SymbleVar::printMapDB(std::unordered_map<Ks, Vs> const &m)
{
    for (auto const &pair: m) 
    {
        std::cout << "{" << pair.first << " : " << pair.second << "}\n";
    }
    
}

unordered_map<string,double> SymbleVar::creatDataBaseMap(string key,double val)
{    
    SymbleVar::getInstance()->data_base[key] = val;

    return SymbleVar::getInstance()->data_base;    
}
