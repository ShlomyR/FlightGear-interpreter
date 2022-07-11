#include "Command.hpp"
#include "WhileLoop.hpp"
#include "Client.hpp"


int OpenServerCommand::DoCommand(vector<vector<string>> &arr)
{
    printf("Server Command\n");

    int port;
    
    port = stoi(arr[Parser::index][1]);
    
    Server::getInstance()->connectServer(port);
    
    return 0;
}

int ConnectCommand::DoCommand(vector<vector<string>> &arr)
{
    

    string ip;
    int port;
   
    ip = arr[Parser::index][1];
    port = stoi(arr[Parser::index][2]);

    printf("Conecting the client to the FS...\n");

    Client::getInstance()->connectClient(port,ip.c_str());

    return 0;
}

int VerCommand::DoCommand(vector<vector<string>> &arr)
{
    
    vector<string> var_arr;
    
    for (int i = 1; i < arr[Parser::index].size(); i++)
    {
        var_arr.push_back(arr[Parser::index][i]);
    }
    Variable::getInstance()->createVar(var_arr);
    
    return 0;
}

int EqualMapCommand::DoCommand(vector<vector<string>> &arr)
{
    if (arr[Parser::index].size() == 3)
    {
        Client::getInstance()->SendVal(arr,arr[Parser::index][2]);
    }
    else
    {
        uptdateFromDB(arr);
    }

    return 0;
}

void EqualMapCommand::uptdateFromDB(vector<vector<string>> &arr)
{
    convertFromChToNum(arr);
    
    strToInfix(Parser::index);

    checkMinus();
    
    
    double infix = SuntingYardToken::shuntingYardF(WhileLoop::infix_str);

    Client::getInstance()->SendVal(arr,infix);
    
    WhileLoop::infix_str.clear();
}

void EqualMapCommand::convertFromChToNum(vector<vector<string>> &arr)
{
    WhileLoop::copy_arr = arr;
    
    for (int i = 0; i < arr[Parser::index].size(); i++)
    {
        for (int j = 0; j < Variable::getInstance()->vec_all_vars.size(); j++)
        {
            if (arr[Parser::index][i] == Variable::getInstance()->vec_all_vars[j] && arr[Parser::index][0] != Variable::getInstance()->vec_all_vars[j])
            {
                if (arr[Parser::index][i] == "h0")
                {
                    double d = SymbleVar::getInstance()->data_base.at(WhileLoop::copy_arr[Parser::index][i]);
                    int dtoi = d;
                    string s = to_string(dtoi);
                    WhileLoop::copy_arr[Parser::index][i] = s;
                    
                }
                else
                {
                    double d = SymbleVar::getInstance()->data_base.at(Variable::getInstance()->base_map_DB.at(WhileLoop::copy_arr[Parser::index][i]));
                    int dtoi = d;
                    string s = to_string(dtoi);
                    WhileLoop::copy_arr[Parser::index][i] = s;
                    
                }
            }
        }
    }
    

}

void EqualMapCommand::strToInfix(int i)
{
    string str_push_to_vec;

    for (i;i < WhileLoop::copy_arr.size() - 2;i++)
    {
        for (int j = 0; j < WhileLoop::copy_arr[i].size() - 2; j++)
        {
            str_push_to_vec += WhileLoop::copy_arr[i][j + 2];
        }
        WhileLoop::infix_str = str_push_to_vec;
        str_push_to_vec.clear();
        break;
    }
}

void EqualMapCommand::checkMinus()
{
    if (WhileLoop::infix_str[0] == '-' && WhileLoop::infix_str[1] == '-' )
    {
        WhileLoop::infix_str.erase(WhileLoop::infix_str.begin()+1) ;
        WhileLoop::infix_str[0] = '+';
    }
}

int WhileCommand::DoCommand(vector<vector<string>> &arr)
{
    
    int skip_row = skipRows(arr,Parser::index);
    
    WhileLoop::whileLoop(arr);
    
    return skip_row;
}

int WhileCommand::skipRows(vector<vector<string>> &arr,int index)
{ 
    int i = index+1;
    
    while (arr[i][0] != "}")
    {
        i++;    
    }
    cout << "\nHow meny rows to skip : " << i - index -1 << "\n";
    
    return i;  
}

double WhileCommand::getVal(vector<vector<string>> &arr,int index)
{
    string path = Variable::getInstance()->base_map_DB.at(arr[index][1]);

    double val = SymbleVar::getInstance()->data_base.at(path);

    return val;
}

int SleepCommand::DoCommand(vector<vector<string>> &arr)
{
    
    sleepFunc(arr[Parser::index][1]);

    return 0;
}

void SleepCommand::sleepFunc(string val)
{
    cout << "\nSleeping for " << val << " seconds" << "\n"; 
    sleep(stoi(val));
}

int PrintCommand::DoCommand(vector<vector<string>> &arr)
{
    if (arr[Parser::index].size() > 2)
    {
        string val = " "; 
        for (int i = 1; i < arr[Parser::index].size(); i++)
        {
            val+=  arr[Parser::index][i]+" ";

        }
        cout << "\n" << val << "\n";
         
    }
    else
    {
        printFunc(arr[Parser::index][1]);
    }
    
    return 0;
}

void PrintCommand::printFunc(string val)
{
    string val_name = val;

    for (int i = 0; i < Variable::getInstance()->vec_all_vars.size(); i++)
    {
        if (val == Variable::getInstance()->vec_all_vars[i])
        {
            double val_d = SymbleVar::getInstance()->data_base.at(Variable::getInstance()->base_map_DB.at(val));
            cout << val_name << ": " << val_d << "\n";
        }
    }
    if (val[0] == '"')
    {    
        cout << "\n" << val << "\n";   
    }

}

int ExitCommand::DoCommand(vector<vector<string>> &arr)
{
    system("kill -9 $(lsof -ti :5400)");

    return 0;
}