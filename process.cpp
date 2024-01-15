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
#include <sys/wait.h>
#include <dirent.h>
#include <cstring>

using namespace std;

void makeProcess(string a)
{

    string b = a;
    vector<char *> args;

    bool back = false;
    // cout << back<<endl;
    if (b.back() == '&')
    {
        back = true;
        b.pop_back();
    }
    // cout << back<<endl;
    if (back)
    {
        int child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            return;
        }

        else if (child_pid == 0)
        {
            char *token = strtok(const_cast<char *>(b.c_str()), " ");
            while (token != NULL)
            {
                args.push_back(token);
                token = strtok(NULL, " ");
            }
            args.push_back(nullptr);

            execvp(args[0], args.data());
        }
        else
        {
            cout << child_pid << endl;
        }
    }
    else
    {
        int pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return;
        }

        else if (pid == 0)
        {
            char *token = strtok(const_cast<char *>(b.c_str()), " ");
            while (token != NULL)
            {
                args.push_back(token);
                token = strtok(NULL, " ");
            }
            args.push_back(nullptr);

            execvp(args[0], args.data());
        }
        else
        {
            waitpid(pid, nullptr, 0);
        }
    }
}

void pinfo_helper()
{
    int pid = getpid();
    std ::cout << "pid -- " << pid << endl;
    string path = "/proc/";
    path.append(to_string(pid));
    path.append("/status");
    // cout << path;

    ifstream file(path);
    

    string line;
    while (getline(file, line))
    {
        if (line.find("State:") != string::npos)
        {
            istringstream iss(line);
            string key, value;
            iss >> key >> value;
            cout << "Process Status -- " << value << endl;
            continue;
        }
        if (line.find("VmSize:") != std::string::npos)
        {
            istringstream iss(line);
            string key, value;
            iss >> key >> value;
            std ::cout << "Memory -- " << value << endl;
        }
    }

    file.close();

    string exec = "/proc/";
    exec = exec.append(to_string(pid));
    exec = exec.append("/cmdline");
    ifstream file3(exec);
    string exec_path;
    getline(file3, exec_path);
    cout << "Executable Path -- " << exec_path << endl;
}
void pinfo_helper2(string pid)
{

    string path = "/proc/";
    path.append(pid);
    path.append("/status");
    // cout << path;
    FILE *file = fopen(path.c_str(), "r");
    if (!file)
    {
        perror("fopen");
        return;
    }
    cout << "pid -- " << pid << endl;

    ifstream file2(path);

    string line;
    while (getline(file2, line))
    {
        if (line.find("State:") != string::npos)
        {
            istringstream iss(line);
            string key, value;
            iss >> key >> value;
            cout << "Process Status -- " << value << endl;
            continue;
        }
        if (line.find("VmSize:") != std::string::npos)
        {
            istringstream iss(line);
            string key, value;
            iss >> key >> value;
            cout << "Memory -- " << value << endl;
        }
    }
    file2.close();

    string exec = "/proc/";
    exec = exec.append(pid);
    exec = exec.append("/cmdline");
    ifstream file3(exec);
    string exec_path;
    getline(file3, exec_path);
    cout << "Executable Path -- " << exec_path << endl;
}
void my_pinfo(string a)
{
    string output = a.substr(5, a.size());
    int pos = 0;
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
    // cout << output;
    istringstream iss(output);
    string token;
    vector<string> tokens;

    while (getline(iss, token, ' '))
    {
        tokens.push_back(token);
    }
    if (tokens.size() == 0)
    {
        pinfo_helper();
    }
    else if (tokens.size() == 1)
    {
        pinfo_helper2(tokens[0]);
    }
}