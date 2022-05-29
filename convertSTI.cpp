#include "convertSTI.hpp"



int convertSTOI(string s)
{
    stringstream convertor(s);
    int x = 0;
	convertor >> x;
    
    return x;
}
