#ifndef INIT
#define INIT

#include <bits/stdc++.h>
#include <iostream>

#include <fcntl.h>  // For open()
#include <unistd.h> // For close()

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
        std::ofstream index_file(".init/index.txt"); // makes file
        std::ofstream head_file(".init/HEAD");       // makes head file
        std::ofstream log_file(".init/LOG");         // makes log file

        // closing all files
        index_file.close();
        head_file.close();
        log_file.close();

        return true;
    }
}

#endif