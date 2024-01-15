#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <grp.h>
using namespace std;

string output = my_pwd();
int count1 = 0;
bool my_search_helper(string test, string b)
{
    bool flag = false;
    count1++;
    DIR *directory = opendir(b.c_str());
    if (directory == nullptr)
    {
        // perror("opendir");
        return false;
    }

    struct dirent *entry;

    while ((entry = readdir(directory)) != nullptr)
    {
        string a = entry->d_name;

        if (a == test)
        {
            flag = true;
        }
        if (entry->d_type == DT_DIR)
        {
            string c = b + "/" + a;
            
            if (my_search_helper(test, c))
            {
                flag = true;
                break;
            }
        }
    }

    closedir(directory);
    return flag;
}
bool my_search(string a)
{
    istringstream isss(a);
    int pos = 0;
    output = a.substr(6, a.size());
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

    return my_search_helper(output, my_pwd());
}
