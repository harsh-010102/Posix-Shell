#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <pwd.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
string home;

void setHome(string home1)
{
    home = home1;
}
string getHome1()
{
    return home;
}
bool getInput()
{
    char input[100];
    cin.getline(input, 100);

    istringstream iss(input);
    string token;
    vector<string> tokens;
    while (getline(iss, token, ';'))
    {
        tokens.push_back(token);
    }
    addHistory(input);

    for (int i = 0; i < tokens.size(); i++)
    {
        bool flag = false;
        if (tokens[i].find("&") != string::npos)
        {
            flag = true;
        }
        auto t = tokens[i];
        int pos = 0;
        string a = t.c_str();
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == ' ')
            {
                pos++;
            }
            else
            {
                break;
            }
        }
        a.erase(0, pos);
        // cout << a;

        if (a.compare(0, 4, "exit") == 0)
        {
            return false;
        }
        else
        {
            if (a.find(">") != string::npos || a.find("<") != string::npos)
            {
                redirect(a);
            }
            else if (strcmp(t.c_str(), "pwd") == 0)
            {

                string a = my_pwd();
                cout << a << endl;
            }
            else if (a.compare(0, 4, "echo") == 0)
            {
                if (a[4] != ' ')
                {
                    cout << "Command not found" << endl;
                }
                else
                {
                    my_echo(a);
                }
            }

            else if (a.compare(0, 7, "history") == 0)
            {
                // cout << "hello";
                if (a[8] == '\0')
                {
                    my_history();
                }
                else
                {
                    string new1 = a.substr(8, a.size());
                    int pos = 0;
                    for (int i = 0; i < new1.size(); i++)
                    {
                        if (new1[i] == ' ')
                        {
                            pos++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    new1.erase(0, pos);

                    my_history2(new1);
                }
            }
            else if (a.compare(0, 2, "cd") == 0)
            {
                string prev = my_pwd();
                string next = my_pwd();
                if (a[2] != ' ')
                {
                    cout << "Command not found" << endl;
                }
                else
                {
                    my_cd(a, prev);
                }
            }
            else if (a.compare(0, 2, "ls") == 0)
            {
                if (a.size() == 2)
                {
                    list_files(a);
                }
                else if (a[2] != ' ')
                {
                    cout << "Command not found" << endl;
                }
                else
                {
                    list_files(a);
                }
            }

            else if (a.compare(0, 5, "pinfo") == 0)
            {
                my_pinfo(a);
            }
            else if (a.compare(0, 6, "search") == 0)
            {
                bool flag = my_search(a);
                if (flag)
                {
                    cout << "True" << endl;
                    break;
                }
                cout << "false" << endl;
            }
            else
            {
                makeProcess(a);
            }
        }
    }
    return true;
}

void sysInfo(string home)
{
    char *username = getlogin();
    char hostname[64];
    gethostname(hostname, 64);
    char buffer[64];
    getcwd(buffer, FILENAME_MAX);
    string buffer2 = buffer;
    if (buffer2.compare(home) == 0)
    {
        buffer2 = "";
    }
    cout << username << "@" << hostname << ":~" << buffer2
         << "$ ";
}