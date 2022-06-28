#include "WhileLoop.hpp"



Parser parser;

string WhileLoop::infix_str;
vector<vector<string>> WhileLoop::copy_arr;

int WhileLoop::whileLoop(vector<vector<string>> &arr)
{ 
    double val_from_DB;

    int i = Parser::index;

    while ((val_from_DB = WhileCommand::getVal(arr,i)) < stoi(arr[i][3]))
    {
        parser.parse(parser.vector_commands);
    }
    parser.vector_commands.clear();

    parser.index = 0;
    
    printf("\nWhileLoop Parser finished\n");

    return 0;
}
