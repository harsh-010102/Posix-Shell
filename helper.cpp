#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

string my_pwd()
{
    char current[100];
    getcwd(current, 100);
    return current;
}

void my_echo(string a)
{
    istringstream isss(a);
    int pos = 0;
    string output = a.substr(4, a.size());
    for (int i = 0; i < output.size(); i++)
    {
        if (output[i] == ' ')
        {
            pos++;
        }
        else
        {
            break;
        }
    }
    output.erase(0, pos);

    cout << output << endl;
}
void my_cd(string a, string b)
{
    string prev;
    string curr;
    string next;
    istringstream isss(a);
    int pos = 0;
    string output = a.substr(3, a.size());
    for (int i = 0; i < output.size(); i++)
    {
        if (output[i] == ' ')
        {
            pos++;
        }
        else
        {
            break;
        }
    }
    output.erase(0, pos);

    if (strcmp(output.c_str(), "~") == 0 || output.size() == 0)
    {
        string home = getHome1();
        chdir(home.c_str());
    }

    else if (strcmp(output.c_str(), "..") == 0)
    {
        chdir("..");
    }
    else if (strcmp(output.c_str(), ".") == 0)
    {
        chdir(".");
    }
    else if (output == "-")
    {
        chdir(prev.c_str());
    }
    else
    {
        if (chdir(output.c_str()) != 0)
        {
            perror("chdir");
        }
    }
    prev = curr;

    curr = my_pwd();
}