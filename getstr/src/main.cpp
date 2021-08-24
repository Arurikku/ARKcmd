#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include "windows.h"
using namespace std;


string vecToStr(vector<char> s) //Theres probably another of doing this but i don't want to look it up rn
{
    string ss = "";
    for(int i = 0; i < s.size(); i++)
    {
        ss += s[i];
    }
    return ss;
}

void tryOpenDir(string pth, string sear, string entryName)
{
    if(entryName == "." || entryName == "..")
        return;

    DIR *dir;

    struct dirent *ent;

    dir = opendir(pth.c_str());

    if (dir != nullptr)
    {
        while ((ent = readdir (dir)) != nullptr)
        {
            string ss = pth + "\\" + ent->d_name;
            tryOpenDir(ss, sear, ent->d_name);
            ifstream theFile;
            theFile.open(ss);
            if (!theFile)
                continue;

            //Set the stream cursor to the end
            theFile.seekg(0,std::ios::end);

            //Get the cursor's position
            streampos length = theFile.tellg();

            //Move the cursor back to the beginning
            theFile.seekg(0,std::ios::beg);

            //The buffer
            vector<char> buffer(length);

            //Read all bytes into the buffer
            theFile.read(&buffer[0],length);

            string x = vecToStr(buffer);

            //Look for the string in all the text it found
            if (x.find(sear) != string::npos)
            {
                cout << "Found string in " << (pth + "\\" + ent->d_name) << endl;
            }
        }
        closedir(dir);
    }
}

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        TCHAR NPath[256];
        GetCurrentDirectory(256, NPath);
        tryOpenDir(NPath, argv[1], NPath);
    }
    else if(argc == 3)
        tryOpenDir(argv[1], argv[2], argv[1]);

    return 0;
}
