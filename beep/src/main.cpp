#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 0;
    Beep(atoi(argv[1]),atoi(argv[2]));
    return 0;
}
