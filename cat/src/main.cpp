#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

static vector<char> ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
        return 0;

    vector<char> bytes = ReadAllBytes(argv[1]);

    cout << endl;

    for(int i = 0; i < bytes.size(); i++)
    {
        cout << bytes[i];
    }

    cout << endl;

    return 0;
}
