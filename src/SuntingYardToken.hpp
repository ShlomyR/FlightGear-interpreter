#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <stdio.h>
#include <math.h>

static const char* reportFmt = "|%-5s|%-37s|%17s| %s\n";

class SuntingYardToken {
public:

    enum class Type {
        Unknown,
        Number,
        Operator,
        LeftParen,
        RightParen,
    };
    
    SuntingYardToken(Type t, const std::string& s, int prec = -1, bool ra = false) 
        : type { t }, str ( s ), precedence { prec }, rightAssociative { ra }
        {}
    

    const Type type;
    const std::string str;
    const int precedence;
    const bool rightAssociative;
    
    static double shunting_Yard(std::string expre);
};