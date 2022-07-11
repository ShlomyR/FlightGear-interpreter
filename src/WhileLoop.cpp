#include "WhileLoop.hpp"



Parser parser;

string WhileLoop::infix_str;
vector<vector<string>> WhileLoop::copy_arr;

int WhileLoop::whileLoop(vector<vector<string>> &arr)
{ 
    double val_from_DB;

    int i = Parser::index;

    pushToVec(arr,i);
    
    while ((val_from_DB = WhileCommand::getVal(arr,i)) < stoi(arr[i][3]))
    {
        parser.parse(parser.vector_commands);
    }
    parser.vector_commands.clear();

    parser.index = 0;
    
    printf("\nWhileLoop Parser finished\n");

    return 0;
}

void WhileLoop::pushToVec(vector<vector<string>> &arr,int i)
{
    i++;
    while (arr[i][0] != "}")
    {
        parser.vector_commands.push_back(arr[i]);
        i++;
    }
}
