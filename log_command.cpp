#ifndef LOG

#define LOG

#include <bits/stdc++.h>

#include "utilities.cpp"

using namespace std;

void log_operation()
{
    string log_history_content = file_to_string(".init/LOG");
    cout << "\ndebug: " << log_history_content << endl;
    vector<string> log_history_vector;

    if (log_history_content.size() < 40)
    {
        // empty
        cout << "No log history found" << endl;
        return;
    }
    else
    {
        int pre = 0;
        auto pos = log_history_content.find("\n");

        while (pos != string::npos && pos < log_history_content.size())
        {
            // cout << "debug: printing pre pos:" << pre << " " << pos << endl;
            // cout << "debug loop: " << log_history_content.substr(pre, pos - pre) << "  " << log_history_content.substr(pre, pos - pre).size() << endl;
            log_history_vector.push_back(log_history_content.substr(pre, pos - pre));
            pre = pos + 1;
            pos = log_history_content.find("\n", pre + 1);
        }
    }

    cout << "debug: " << log_history_vector.size() << endl;

    for (auto i : log_history_vector)
    {
        // cout << "debug 1: " << i << endl;
        // printing detail
        string path = ".init/refs/" + i.substr(0, 2) + "/" + i.substr(2);
        // cout << "debug 2: " << path << " size: " << path.size() << endl;
        string content = file_to_string(path);
        // cout << content << endl;
        // print prettier
        int pre = 0;
        auto pos = content.find("/0");
        vector<string> message;
        while (pos != string::npos)
        {
            message.push_back(content.substr(pre, pos - pre));
            pre = pos + 2;
            pos = content.find("/0", pre);
        }
        message.push_back(content.substr(pre, content.size() - pre));
        cout << "Commit SHA: " + message[0] + "\nParent SHA: " + message[1] + "\nCommit Message: " + message[2] + "\nDate and Time: " + message[3] + "\nCommiter Info: " + message[4] + "\n"
             << endl;
    }
}

#endif