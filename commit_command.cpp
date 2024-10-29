#ifndef COMMIT_COMMAND
#define COMMIT_COMMAND

#include <bits/stdc++.h>

#include "hash_command.cpp"
#include "add_command.cpp"
using namespace std;

void update_log_file(string hash)
{

    string log_file_path = ".init/LOG";
    string content = file_to_string(log_file_path);

    // check if empty
    if (content.size() < 40)
    {
        // empty
        hash += "\n";
        write_to_file(log_file_path, hash); // write hash to log file
    }
    else
    {
        // not empty
        string modified_content = hash;
        modified_content += "\n";
        modified_content += content;
        write_to_file(log_file_path, modified_content);
    }
    // if not then
}

void commit_operation(string commit_message)
{
    string index_file_path = ".init/index.txt";
    string index_file_content = file_to_string(index_file_path); // hash of add object
    // clean_index_file();
    save_to_index(""); // cleans index file
    cout << "debug HERE" << endl;
    update_log_file(index_file_content); // update log

    // store meta data
    string meta_data_directory = ".init/refs/" + index_file_content.substr(0, 2);
    string meta_data_file_name = meta_data_directory + "/" + index_file_content.substr(2);
    // now make directory and file
    std::ofstream meta_data_file;
    if ((!filesystem::exists(meta_data_directory)) && mkdir(meta_data_directory.c_str(), 0777) == -1)
    {
        meta_data_file.open(meta_data_file_name); // Opens or creates the file
        if (!meta_data_file)
        {
            std::cerr << "Failed to create or open meta data file: " << meta_data_file_name << std::endl;
        }
    }
    else
    {
        meta_data_file.open(meta_data_file_name);
    }
    //<commit hash>/0<parent_hash>/0<commit_message>/0<Time stamp>/0<commiter info>
    string time_stamp = "";
    time_stamp = get_time_stamp();
    cout << "debug: current data and time " << time_stamp << endl; // debug

    string parent_commit = "";
    parent_commit = file_to_string(".init/HEAD"); // get parent commit
    if (parent_commit.size() < 40)
        parent_commit = "NONE";
    cout << "debug: parent commit " << parent_commit << endl;

    string commiter_info = get_current_user();
    cout << "debug: current user" << commiter_info << endl;

    string meta_data_content = index_file_content      // hash of current commit
                               + "/0" + parent_commit  // hash of parent commit
                               + "/0" + commit_message // commiter message
                               + "/0" + time_stamp     // hash of time stamp
                               + "/0" + commiter_info + "\n";
    // write meta data
    write_to_file(meta_data_file_name, meta_data_content); // write meta data to  current hash

    // change head
    write_to_file(".init/HEAD", index_file_content); // hash of current tree
}

#endif