#include <iostream>
#include <fstream>
using namespace std;


bool eq(char a[], char b[], int aL, int bL)
{
    if(aL != bL)
    {
        return false;
    }
    int x = max(aL, bL);
    for(int i = 0; i < x; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 0;

    ifstream a;
    ifstream b;
    a.open(argv[1]);
    b.open(argv[2]);

    if(!a || !b)
    {
        cout << "File error";
        return 0;
    }


    a.seekg(0, std::ios::end);
    size_t aLen = a.tellg();
    a.seekg(0, std::ios::beg);

    char aBuf[aLen];
    a.read(aBuf, aLen);

    b.seekg(0, std::ios::end);
    size_t bLen = b.tellg();
    b.seekg(0, std::ios::beg);

    char bBuf[bLen];
    b.read(bBuf, bLen);

    cout << eq(aBuf, bBuf, aLen, bLen);
    return 0;
}
