#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "header.h"

using namespace std;

int main(int argc, char *argv[])
{
    string home = my_pwd();
    setHome(home);

    while (true)
    {
        sysInfo(home);
        bool a = getInput();
        if (!a)
        {
            break;
        }
    }
    return 0;
}