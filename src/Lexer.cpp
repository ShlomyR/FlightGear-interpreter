#include "Lexer.hpp"

Lexer::Lexer()
{
    
}

vector<vector<string>> Lexer::do_lexer(string file_name)
{
    vector<vector<string>> main_vector_arr;
    fstream file;
    string line;
    file.open(file_name, ios::in | ios::binary);

    if (!file.is_open())
    {
        throw "An error";
    }

    while (getline(file, line))
    {

        vector<string> vec_row;
        splitbyWord(line, vec_row, ' ');
        main_vector_arr.push_back(vec_row);
    }
    file.close();

    deleteSpace(main_vector_arr);

    printVec(main_vector_arr);

    return main_vector_arr;
}

void Lexer::deleteSpace(vector<vector<string>> &arr)
{
    Parser parser;

    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            if (arr[i][j] == "{")
            {
                i++;
                while (arr[i][0] != "}")
                {
                    if (arr[i].size() == 6)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            arr[i].erase(arr[i].begin());
                        }
                        parser.vector_commands.push_back(arr[i]);
                    }
                    if (arr[i].size() != 2)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            arr[i].erase(arr[i].begin());
                        }
                        parser.vector_commands.push_back(arr[i]);
                    }
                    i++;
                }
            }
        }
    }
}

void Lexer::splitbyWord(string const &str, vector<string> &vec_str, const char Delim)
{
    stringstream str_to_split(str);
    string str_file;

    while (getline(str_to_split, str_file, Delim))
    {
        vec_str.push_back(str_file);
    }
}

void Lexer::printVec(vector<vector<string>> &vec_arr)
{
    for (int i = 0; i < vec_arr.size(); i++)
    {
        cout << "[";
        for (int j = 0; j < vec_arr[i].size(); j++)
        {
            cout << vec_arr[i][j] << " ";
        }
        cout << "]"
             << "\n";
    }
}