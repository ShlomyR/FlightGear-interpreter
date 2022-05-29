#include "Command.hpp"
#include "WhileLoop.hpp"

ConnectCommand::ConnectCommand() : Command()
{
}

int ConnectCommand::DoCommand(vector<vector<string>> &arr, int index)
{
    

    string ip;
    int port;
    int counter = 0;

    try
    {
        ip = arr[index][1];
        port = convertSTOI(arr[index][2]);

        if (port != (int)port)
        {
            throw port; //"wrong typdef need an int type"; //port;
        }
        if (ip != (string)ip)
        {
            throw ip; //"wrong typdef need an int type"; //port;
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

    Client::getInstance()->connect1(port);

    return 0;
}

ConnectCommand::~ConnectCommand()
{
}

EqualMapCommand::EqualMapCommand() : Command()
{
}

bool EqualMapCommand::is_charecther(string val)
{
    string ch = "abcdefghijklmnopqrstuvwxyz";

    if (val.find(ch) != string::npos)
    {
        cout << "charecther: " << ch << "\n";
        return 1;
    }
    else
    {
        return 0;
    }
}


int EqualMapCommand::DoCommand(vector<vector<string>> &arr, int index)
{
    
    if (arr[index].size() == 3)
    {
        int value = convertSTOI(arr[index][2]);

        string set = "set";
        string activate = "\r\n";
        Client::getInstance()->Send(set + " " + Variiable::baseMapDB.at(arr[index][0]) + " " + arr[index][2] + activate);
    }
    else
    {
        uptdateFromDB(arr, index);
    }

    return 0;
}

string EqualMapCommand::uptdateFromDB(vector<vector<string>> &arr, int index)
{
    WhileLoop opp;

    double reg;

    opp.copyArr = arr;

    for (int i = 0; i < arr[index].size(); i++)
    {
        for (int j = 0; j < arr[index].size(); j++)
        {
            if (arr[index][i] == Variiable::getInstance()->vecSY[j] && arr[index][0] != Variiable::getInstance()->vecSY[j])
            {
                if (arr[index][i] == "h0")
                {
                    double d = SymbleVar::getInstance()->data_base.at(opp.copyArr[index][i]);
                    int p = d;
                    string s = to_string(p);
                    opp.copyArr[index][i] = s;
                    
                }
                else
                {
                    double d = SymbleVar::getInstance()->data_base.at(Variiable::getInstance()->baseMapDB.at(opp.copyArr[index][i]));
                    int p = d;
                    string s = to_string(p);
                    opp.copyArr[index][i] = s;
                    
                }
            }
        }
    }

    for (int p = 0; p < opp.copyArr.size() - 2; p++)
    {
        for (int r = 0; r < opp.copyArr[p].size() - 2; r++)
        {
            opp.vv[p].append(opp.copyArr[p][r + 2]);
        }
    }

    is_charecther(opp.vv[index]);

    if (is_charecther(opp.vv[index]) != 1)
    {

        reg = SuntingYardToken::shunting_Yard(opp.vv[index]);

        
        string val = to_string(reg);

        string set = "set";
        string activate = "\r\n";

        Client::getInstance()->Send(set + " " + Variiable::baseMapDB.at(arr[index][0]) + " " + val + activate);
    }

    opp.vv.clear();

    return "0";
}
EqualMapCommand::~EqualMapCommand()
{

}

OpenServerCommand:: OpenServerCommand() : Command() 
{

}

int OpenServerCommand::run_FG()
{
    string s = "fgfs --verbose -v";
    system(s.c_str());
    
    return 0;
}

int OpenServerCommand:: DoCommand(vector<vector<string>>& arr, int index)
{
    printf("Server Command\n");

    
    int port;
    int ping;
    int counter = 0;

    
    try
    {
        port = convertSTOI(arr[index][1]);
        ping = convertSTOI(arr[index][2]);

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

    printf("Conecting to the Server...\n");

    Server::getInstance()->connectServer(port,ping);
    
    
    return 0;
}
OpenServerCommand:: ~OpenServerCommand()
{ 
    
}

PrintCommand::PrintCommand() : Command()
{
    
}

int PrintCommand::DoCommand(vector<vector<string>> &arr, int index)
{
    printFunc(arr[index][1]);

    return 0;
}

void PrintCommand::printFunc(string val)
{
    string val1 = val;

    for (int i = 0; i < 13; i++)
    {
        if (val == Variiable::vecSY[i])
        {
            double d = SymbleVar::getInstance()->data_base.at(Variiable::getInstance()->baseMapDB.at(val));
            string s = to_string(d);
            cout << val1 << ": " << d << "\n";
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

SleepCommand::SleepCommand() : Command()
{

}

int SleepCommand::DoCommand(vector<vector<string>>& arr, int index)
{
    
    sleepFunc(arr[index][1]);

    return 0;

    
}

void SleepCommand::sleepFunc(string val)
{
    
    sleep(convertSTOI(val));
    cout << "Sleeping for " << val << " seconds" << "\n"; 
}

SleepCommand::~SleepCommand()
{

}

VerCommand:: VerCommand() : Command() 
{

}


int VerCommand:: DoCommand(vector<vector<string>>& arr, int index)
{
    
    vector<string> var_arr;
    
    if (arr[index].size() == 5)
    {
        for (int i = 1; i < arr[index].size(); i++)
        {
            var_arr.push_back(arr[index][i]);
        }
        Variiable::Vari(var_arr);
    }
    
    if (arr[index].size() == 4)
    {
        for (int i = 1; i < arr[index].size(); i++)
        {
            var_arr.push_back(arr[index][i]);
        }
        Variiable::Vari(var_arr);
    }
    
    return 0;
}
VerCommand:: ~VerCommand()
{
    
}

WhileCommand::WhileCommand() : Command()
{
    
}

double WhileCommand::getVal(vector<vector<string>>& arr, int index)
{
    string path = Variiable::getInstance()->baseMapDB.at(arr[index][1]);

    double val = SymbleVar::getInstance()->data_base.at(path);

    return val;
}

 int WhileCommand::sipRows(vector<vector<string>>& arr, int index)
 {
    
    int i = index+1;
    
    while (arr[i][0] != "}")
    {
        i++;    
    }
    cout << "How meny rows to skip : " << i - index << "\n";
    
    return i - index;
    
 }

int WhileCommand::DoCommand(vector<vector<string>>& arr, int index)
{
    sleep(5);

    int  sipRows1 = sipRows(arr,index);
    
    WhileLoop::whileLoop(arr,index);
    
    


    return sipRows1;
}

WhileCommand::~WhileCommand()
{
    
}

