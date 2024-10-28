#ifndef INIT
#define INIT

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h> //for mkdir
#include <filesystem> //for check if file exist or not

using namespace std;
bool init()
{
    // check if file already exists

    // C++ program to create a directory in Linux
    if ((!filesystem::exists(".init")) && mkdir(".init", 0777) == -1 ||
        (!filesystem::exists(".init/objects")) && mkdir(".init/objects", 0777) == -1 ||
        (!filesystem::exists(".init/refs")) && mkdir(".init/refs", 0777) == -1)
        return false;
    else
    {
        std::ofstream file(".init/index.txt"); // makes file
        return true;
    }
}

#endif