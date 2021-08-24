#include <iostream>
#include <fstream>
#include <dirent.h>
#include "windows.h"

using namespace std;

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

bool isDir(string pth)
{
    return opendir(pth.c_str()) != nullptr;
}

void tryOpenDir(string pth, string entryName)
{
    if(entryName == "." || entryName == "..")
        return;

    DIR* dir;
    struct dirent* ent;
    dir = opendir(pth.c_str());
    if (dir != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            string ss = pth + "\\" + ent->d_name;
            if(isDir(ss))
            {
                cout << "\e[42m\e[34m" << ss << "\e[0m" << endl;
            }
            ifstream theFile;
            theFile.open(ss);
            if (!theFile)
               continue;
            cout << "\e[92m" << ss << "\e[0m" << endl;
        }
        closedir(dir);
    }
}

using namespace std;
int main(int argc, char* argv[])
{
HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);

    //Already explained in the search command
    DWORD theMode;
    GetConsoleMode(hOUT, &theMode);
    SetConsoleMode(hOUT, theMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
    TCHAR buf[256];
    GetCurrentDirectory(256, buf);
    string path = buf;
    tryOpenDir(path, path);
}
