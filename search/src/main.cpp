#include <iostream>
#include <fstream>
#include <dirent.h>
#include "windows.h"

using namespace std;

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

//Just for coloring purposes
bool isDir(string pth)
{
    return opendir(pth.c_str()) != nullptr;
}


void tryOpenDir(string pth, string sear, string entryName)
{
    if(entryName == "." || entryName == "..")
        return;

    DIR* folder;

    struct dirent* entry;

    folder = opendir(pth.c_str());

    if(folder != nullptr)
    {
        while ((entry = readdir(folder)) != nullptr) //Read every entry in a folder
        {
            string nam = entry->d_name;
            string ss = pth + "\\" + nam;

            if(isDir(ss))
                tryOpenDir(ss, sear, nam); //yay recursive

            if(nam.find(sear) != string::npos)
            {
                if(isDir(ss))
                {
                    /*
                     \e is the ansi escape code
                     with [...m you can specify which color
                     \e[30m is for black foreground
                     \e[0m is to reset foreground and background
                     you can combine these so \e[102m\e[30m does bright green background and black foreground
                    */
                    cout << "\e[42m\e[34m" << ss << "\e[0m" << endl;
                }
                else
                {
                    cout << "\e[92m" << ss << "\e[0m" << endl;
                }
            }

        }
        closedir(folder);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
        return 0;


    //get handle
    HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);

    //get mode
    DWORD theMode;
    GetConsoleMode(hOUT, &theMode);

    //set mode but change virtual processing for color codes to be easier
    SetConsoleMode(hOUT, theMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);

    //get current directory
    TCHAR buf[256];
    GetCurrentDirectory(256, buf);
    string path = buf;

    tryOpenDir(path, argv[1], path);
    return 0;
}
