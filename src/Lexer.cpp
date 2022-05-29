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

    if(!file.is_open())
    {
        throw  "An error";
    }
    
    while (getline(file, line)) 
    {

        std::vector<std::string> vec_row;
        splitbyWord(line,' ',vec_row);
        main_vector_arr.push_back(vec_row);
        
        
    }
        
        for (int i = 0; i < main_vector_arr.size(); i++)
        {
            cout << "[";
            for (int j = 0; j < main_vector_arr[i].size(); j++)
            {
                std::cout<<main_vector_arr[i][j]<<" ";      
            }
            cout << "]"<<"\n";
        }
    file.close();
    return main_vector_arr;
}
void Lexer::splitbyWord(std::string const &str,const char Delim,std::vector<std::string> &vec_str){
    std::stringstream check1(str);
    std::string intermediate;
    while(getline(check1, intermediate, Delim))
    {
        vec_str.push_back(intermediate);
    }



}



