#include "WhileLoop.hpp"

WhileLoop::WhileLoop()
{

}


Parser *parser = new Parser();

void WhileLoop::readyToPars(vector<vector<string>> &arr, int index)
{
    int i = index + 1;
    
    while (arr[i][0] != "}")
    {
        if (arr[i].size() == 6)
        {
            for (int j = 0; j < 4; j++)
            {
                arr[i].erase(arr[i].begin());
            }
            parser->vector_commands.push_back(arr[i]);
        }

        if (arr[i].size() != 2)
        {
            for (int j = 0; j < 4; j++)
            {
                arr[i].erase(arr[i].begin());
            }
            parser->vector_commands.push_back(arr[i]);
           
            
        }
        i++;
    }
    i++;

    
}





int WhileLoop::whileLoop(vector<vector<string>> &arr, int index)
{
    int i = index + 1;
    double valFromDB;
    
    readyToPars(arr, index);

    
    
    while ((valFromDB = WhileCommand::getVal(arr,index)) < convertSTOI(arr[index][3]))
    {
        parser->parse(parser->vector_commands);
    }

    printf("Parser finitu\n");

    
    

    delete parser;
    return i - index;
}
