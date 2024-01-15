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
void addHistory(string a)
{
    string file = "history.txt";

    ofstream outputFile;
    outputFile.open("history.txt", ios::app);
    string line;
    int count;
    ifstream fileD(file);
    while (getline(fileD, line))
    {
        count++;
    }

    if (!outputFile.is_open())
    {
        perror("open");
        return;
    }
    outputFile << a << endl;

    outputFile.close();
}

void my_history()
{
    string file = "history.txt";
    ifstream fileD(file);
    string line;
    // cout << "hello";
    int count = 0;
    while (getline(fileD, line))
    {
        count++;
    }
    int lastLine = count - 10;

    fileD.close();
    ifstream fileD2(file);

    int lineNo = 0;
    while (getline(fileD2, line))
    {
        lineNo += 1;
        if (lineNo >= lastLine)
        {
            cout << lineNo << " ";
            cout << line << endl;
        }
    }
}
void my_history2(string n)
{
    int num = stoi(n);
    string file = "history.txt";
    ifstream fileD(file);
    string line;
    int count = 0;
    while (getline(fileD, line))
    {
        count++;
    }
    int lastLine = count - num;

    fileD.close();
    ifstream fileD2(file);

    int lineNo = 0;
    while (getline(fileD2, line))
    {
        lineNo += 1;
        if (lineNo > lastLine)
        {
            cout << lineNo << " ";
            cout << line << endl;
        }
    }
}