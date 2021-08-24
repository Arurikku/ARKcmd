#include <iostream>
#include "windows.h"
using namespace std;

int main()
{
    //The buffer for the working directory
    TCHAR buf[256];
    GetCurrentDirectory(256, buf);
    cout << buf;
    return 0;
}
