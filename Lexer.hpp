#pragma once

#include "Command.hpp"






class Lexer 
{
    public:
        Lexer();
        vector<vector<string>> do_lexer (string file_name);
        void splitbyWord(std::string const &str,const char Delim,std::vector<std::string> &vec_str);
};