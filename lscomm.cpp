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
bool hidden = true;
bool complete = true;
void find(int per)
{
    int arr[3] = {0};

    if (per == 1)
    {
        arr[2] = 1;
    }
    else if (per == 2)
    {
        arr[1] = 1;
    }
    else if (per == 3)
    {
        arr[1] = 1;
        arr[2] = 1;
    }

    else if (per == 4)
    {
        arr[0] = 1;
    }
    if (per == 5)
    {
        arr[0] = 1;
        arr[2] = 1;
    }
    else if (per == 6)
    {
        arr[0] = 1;
        arr[1] = 1;
    }
    else if (per == 7)
    {
        arr[0] = arr[1] = arr[2] = 1;
    }
    if (arr[0] == 1)
    {
        cout << "r";
    }
    else
    {
        cout << "-";
    }
    if (arr[1] == 1)
    {
        cout << "w";
    }
    else
    {
        cout << "-";
    }
    if (arr[2] == 1)
    {
        cout << "x";
    }
    else
    {
        cout << "-";
    }
}
int check_permission(const char *filePtr)
{
    struct stat fileStat;
    stat(filePtr, &fileStat);
    int per = (fileStat.st_mode & 0777);
    int octal = 0;
    int base = 1;
    while (per > 0)
    {
        int rem = per % 8;
        octal += rem * base;
        base *= 10;
        per /= 8;
    }
    return octal;
}
void findPer(string s1)
{
    const char *output_ptr = s1.data();
    int per_new = check_permission(output_ptr);
    find(per_new / 100);

    int z = per_new / 10;

    find(z % 10);

    find(per_new % 10);
}

void fun(string s1)
{
    struct stat fileStat;
    string filePath = string(s1);
    lstat(filePath.c_str(), &fileStat);
    struct passwd *owner = getpwuid(fileStat.st_uid);

    string modTime = ctime(&fileStat.st_mtime);
    modTime = modTime.substr(0, modTime.length() - 1);
    int fileSize = fileStat.st_size;
    cout << " ";
    cout << fileStat.st_nlink;
    cout << " ";
    cout << owner->pw_name << " ";
    struct group *grp_info = getgrgid(fileStat.st_gid);

    cout << grp_info->gr_name << " ";
    cout << fileSize << " ";
    cout << modTime;
}
void print(string s1)
{
    vector<struct dirent *> entries2;
    struct stat pathStat;

    if (stat(s1.c_str(), &pathStat) == 0)
    {
        if (S_ISREG(pathStat.st_mode))
        {
            cout << "-";
            findPer(s1);
            fun(s1);
            cout << " ";

            cout << s1 << endl;
        }
        else if (S_ISDIR(pathStat.st_mode))
        {
            cout << "Total" << endl;
            DIR *directory = opendir(s1.c_str());

            if (directory)
            {
                struct dirent *entry;
                while ((entry = readdir(directory)))
                {
                    entries2.push_back(entry);
                }

                sort(entries2.begin(), entries2.end(), [](struct dirent *a, struct dirent *b)
                     { return string(a->d_name) < string(b->d_name); });

                for (const auto &entry : entries2)
                {
                    string fileName = entry->d_name;
                    if (fileName.front() == '.' && hidden == true)
                    {
                        continue;
                    }
                    else if (entry->d_type == DT_DIR)
                    {
                        cout << "d";
                        string a = s1.append("/");
                        a = a.append(entry->d_name);
                        findPer(a);
                        fun(a);

                        cout << " ";
                        cout << fileName << endl;
                    }
                    else if (entry->d_type == DT_REG)
                    {
                        cout << "-";
                        string a = s1.append("/");
                        a = a.append(entry->d_name);
                        findPer(a);
                        fun(a);
                        cout << " ";

                        cout << fileName << endl;
                    }
                }
            }
            closedir(directory);
        }
    }
}
void list_files(string s)
{
    istringstream iss(s);
    int pos = 0;
    string token;
    vector<string> tokens;
    string output = s.substr(2, s.size());
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
    if (output.size() == 0)
    {
        string path = my_pwd();
        DIR *directory = opendir(path.c_str());
        if (directory)
        {
            struct dirent *entry;
            vector<string> entries;

            while ((entry = readdir(directory)) != nullptr)
            {
                string a = entry->d_name;
                if (a.front() == '.')
                {
                    continue;
                }
                else
                {
                    entries.push_back(entry->d_name);
                }
            }
            sort(entries.begin(), entries.end());
            for (int i = 0; i < entries.size(); i++)
            {
                cout << entries[i] << endl;
            }
        }
    }
    else
    {
        istringstream iss(output);
        string token;
        vector<string> tokens;
        vector<string> dir;
        while (getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "-a")
            {
                hidden = false;
            }
            else if (tokens[i] == "-l")
            {
                complete = false;
            }
            else if (tokens[i] == "-la" || tokens[i] == "-al")
            {
                complete = false;
                hidden = false;
            }
            else
            {
                dir.push_back(tokens[i]);
            }
        }

        string s1;
        if (dir.size() == 0)
        {
            s1 = my_pwd();
            print(s1);
        }
        else
        {
            for (int i = 0; i < dir.size(); i++)
            {

                s1 = dir[i];

                if (s1.compare("~") == 0)
                {
                    string s2 = getHome1();
                    print(s2);
                }
                else
                {
                    print(s1);
                }
            }
        }
    }
}