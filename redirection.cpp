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
#include <fcntl.h>

using namespace std;

void redirect(string a)
{
    int pos = 0;
    bool append = false;
    bool input = false;
    bool output = false;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '>' || a[i] == '<')
        {
            pos = i;
            break;
        }
    }

    if (a[pos] == '<')
    {
        input = true;
    }

    if (a[pos] == '>')
    {
        output = true;
    }

    if (a[pos + 1] == '>')
    {
        append = true;
        pos = pos + 1;
    }
    if (output == true || append == true)
    {
        string file = a.substr(pos + 1, a.size());
        string command = a.substr(0, pos - 1);
        pos = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (file[i] == ' ')
            {
                pos++;
            }
            else
            {
                break;
            }
        }

        file.erase(0, pos);

        int child_pid;

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            int outputF;
            if (append == true)
            {
                outputF = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            }

            else
            {
                outputF = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            }
            if (outputF == -1)
            {
                perror("open");
            }
            if (dup2(outputF, 1) == -1)
            {
                perror("dup2");
            }
            vector<char *> args;
            char *token = strtok(const_cast<char *>(command.c_str()), " ");
            while (token != NULL)
            {
                args.push_back(token);
                token = strtok(NULL, " ");
            }
            args.push_back(nullptr);

            execvp(args[0], args.data());
            close(outputF);
        }

        else
        {
            waitpid(child_pid, nullptr, 0);
        }
    }

    if (input == true)
    {
    
        string file = a.substr(pos + 1, a.size());

        string command = a.substr(0, pos - 1);

        pos = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (file[i] == ' ')
            {
                pos++;
            }
            else
            {
                break;
            }
        }
        file.erase(0, pos);

        int child_pid;

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            int inputF;

            inputF = open(file.c_str(), O_RDONLY);
          
            if (inputF == -1)
            {
                perror("open");
            }
            if (dup2(inputF, 0) == -1)
            {
                perror("dup2");
            }
            vector<char *> args;
            char *token = strtok(const_cast<char *>(command.c_str()), " ");
            while (token != NULL)
            {
                args.push_back(token);
                token = strtok(NULL, " ");
            }
            args.push_back(nullptr);

            execvp(args[0], args.data());
            close(inputF);
        }
        else
        {
            waitpid(child_pid, nullptr, 0);
        }
    }
}