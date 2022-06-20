#include "Command.hpp"
#include "WhileLoop.hpp"
#include "Client.hpp"

OpenServerCommand::OpenServerCommand()
{
    
}

int OpenServerCommand::DoCommand(vector<vector<string>> &arr)
{
    printf("Server Command\n");

    
    int port;
    int ping;
    int counter = 0;

    
    try
    {
        port = stoi(arr[Parser::index][1]);
        ping = stoi(arr[Parser::index][2]);

        if(port != (int)port)
        {
            throw port;//"wrong typdef need an int type"; //port;    
        }
        if(ping != (int)ping)
        {
            throw ping;//"wrong typdef need an int type"; //port;    
        }
        counter++;
        counter++;

        if(counter != 2 )
        {
            throw counter;
        }
        
    }
    catch (int port)
    {
        cout<< "wrong typdef for port need an int type"<<"\n";
    }
    catch (int ping)
    {
        cout<< "wrong typdef for ping need an int type"<<"\n";
    }
    catch (int counter)
    {
        cout << "one or more parameters missing\n";
    }


    Server::getInstance()->connectServer(port,ping);
    
    
    return 0;
}

OpenServerCommand::~OpenServerCommand()
{
    
}

ConnectCommand::ConnectCommand()
{
    
}

int ConnectCommand::DoCommand(vector<vector<string>> &arr)
{
    

    string ip;
    int port;
    int counter = 0;

    try
    {
        ip = arr[Parser::index][1];
        port = stoi(arr[Parser::index][2]);

        if (port != (int)port)
        {
            throw port; 
        }
        if (ip != (string)ip)
        {
            throw ip;
        }
        counter++;
        counter++;

        if (counter != 2)
        {
            throw counter;
        }
    }
    catch (int port)
    {
        cout << "wrong typdef for port need an int type"
             << "\n";
    }
    catch (int ip)
    {
        cout << "wrong typdef for ip need a string type"
             << "\n";
    }
    catch (int counter)
    {
        cout << "one or more parameters missing\n";
    }

    printf("Conecting the client to the FS...\n");

    Client::getInstance()->connectClient(port);

    return 0;
}

ConnectCommand::~ConnectCommand()
{
    
}

VerCommand::VerCommand()
{
    
}

int VerCommand::DoCommand(vector<vector<string>> &arr)
{
    
    vector<string> var_arr;
    
    if (arr[Parser::index].size() == 5)
    {
        for (int i = 1; i < arr[Parser::index].size(); i++)
        {
            var_arr.push_back(arr[Parser::index][i]);
        }
        Variable::getInstance()->CreateVar(var_arr);
    }
    
    if (arr[Parser::index].size() == 4)
    {
        for (int i = 1; i < arr[Parser::index].size(); i++)
        {
            var_arr.push_back(arr[Parser::index][i]);
        }
        Variable::getInstance()->CreateVar(var_arr);
    }
    
    return 0;
}

VerCommand::~VerCommand()
{
    
}

EqualMapCommand::EqualMapCommand()
{
    
}

int EqualMapCommand::DoCommand(vector<vector<string>> &arr)
{
    
    if (arr[Parser::index].size() == 3)
    {
        int value = stoi(arr[Parser::index][2]);

        string set = "set";
        string activate = "\r\n";
        Client::getInstance()->Send(set + " " + Variable::getInstance()->base_map_DB.at(arr[Parser::index][0]) + " " + arr[Parser::index][2] + activate);
    }
    else
    {
        uptdateFromDB(arr);
    }

    return 0;
}

void EqualMapCommand::uptdateFromDB(vector<vector<string>> &arr)
{
    WhileLoop whileloop;
    
    int i = Parser::index;

    whileloop.copy_arr = arr;

    for (int i = 0; i < arr[Parser::index].size(); i++)
    {
        for (int j = 0; j < Variable::getInstance()->vec_all_symbels.size(); j++)
        {
            if (arr[Parser::index][i] == Variable::getInstance()->vec_all_symbels[j] && arr[Parser::index][0] != Variable::getInstance()->vec_all_symbels[j])
            {
                if (arr[Parser::index][i] == "h0")
                {
                    double d = SymbleVar::getInstance()->data_base.at(whileloop.copy_arr[Parser::index][i]);
                    int dtoi = d;
                    string s = to_string(dtoi);
                    whileloop.copy_arr[Parser::index][i] = s;
                    
                }
                else
                {
                    double d = SymbleVar::getInstance()->data_base.at(Variable::getInstance()->base_map_DB.at(whileloop.copy_arr[Parser::index][i]));
                    int dtoi = d;
                    string s = to_string(dtoi);
                    whileloop.copy_arr[Parser::index][i] = s;
                    
                }
            }
        }
    }
    
    string str_push_to_vec;

    for (i;i < whileloop.copy_arr.size() - 2;i++)
    {
        for (int j = 0; j < whileloop.copy_arr[i].size() - 2; j++)
        {
            str_push_to_vec += whileloop.copy_arr[i][j + 2];
        }
        whileloop.infix_vec.push_back(str_push_to_vec);
        str_push_to_vec.clear();
        break;
    }
    
    double infix;

    infix = SuntingYardToken::shunting_Yard(whileloop.infix_vec[0]);

    Client::getInstance()->SendVal(arr,infix);
    
    whileloop.infix_vec.clear();
}

EqualMapCommand::~EqualMapCommand()
{
    
}

WhileCommand::WhileCommand()
{
    
}

double WhileCommand::getVal(vector<vector<string>> &arr,int index)
{
    string path = Variable::getInstance()->base_map_DB.at(arr[index][1]);

    double val = SymbleVar::getInstance()->data_base.at(path);

    return val;
}

 int WhileCommand::skipRows(vector<vector<string>> &arr,int index)
 {
    
    int i = index+1;
    
    while (arr[i][0] != "}")
    {
        i++;    
    }
    cout << "\nHow meny rows to skip : " << i - index << "\n";
    
    return i;  
 }

int WhileCommand::DoCommand(vector<vector<string>> &arr)
{
    
    int skip_row = skipRows(arr,Parser::index);
    
    WhileLoop::whileLoop(arr);
    
    return skip_row;
}

WhileCommand::~WhileCommand()
{
    
}

SleepCommand::SleepCommand()
{
    
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

SleepCommand::~SleepCommand()
{
    
}

PrintCommand::PrintCommand()
{
    
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
        cout << val << "\n";
        
        
    }
    else
    {
        printFunc(arr[Parser::index][1]);
    }
    

    return 0;
}

void PrintCommand::printFunc(string val)
{
    string val_before = val;

    for (int i = 0; i < Variable::getInstance()->vec_all_symbels.size(); i++)
    {
        if (val == Variable::getInstance()->vec_all_symbels[i])
        {
            double d = SymbleVar::getInstance()->data_base.at(Variable::getInstance()->base_map_DB.at(val));
            string s = to_string(d);
            cout << val_before << ": " << d << "\n";
        }
    }
    if (val[0] == '"')
    {    
        cout << val << "\n";   
    }
}

PrintCommand::~PrintCommand()
{
    
}

ExitCommand::ExitCommand()
{
    
}

int ExitCommand::DoCommand(vector<vector<string>> &arr)
{
    system("kill -9 $(lsof -ti :5400)");

    return 0;
}

ExitCommand::~ExitCommand()
{
    
}

Command::~Command()
{
    
}




