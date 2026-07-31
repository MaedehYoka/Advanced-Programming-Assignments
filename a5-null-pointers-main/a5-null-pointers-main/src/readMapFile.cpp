#include "readMapFile.hpp"

vector<vector<char>> readMapFile(string file_path)
{
    fstream map_file(file_path);
    string line;
    vector<vector<char>> map;
    while (getline(map_file, line))
    {
        vector<char> temp;
        for (char a : line)
        {
            temp.push_back(a);
        }
        map.push_back(temp);
    }

    return map;
}