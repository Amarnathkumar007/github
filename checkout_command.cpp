#ifndef CHECKOUT_COMMAND
#define CHECKOUT_COMMAND

#include <bits/stdc++.h>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "utilities.cpp"
#include "cat_command.cpp"
using namespace std;

/**
 * @brief this function seperates blob/0a4454cccc70e0073e1dab2dbc8bacb93ed9448f6/0Makefile.save/0447 hash adn file name
 *
 * @param hash
 * @return pair<string, string>
 */
pair<string, string> get_hash_and_path_from_hash(string hash)
{
    // cout << "debug hash: " << hash << endl;
    string hash_file = hash.substr(6, 40);
    int pre = 48;
    int pos = hash.find("/0", pre);
    string file_name = hash.substr(pre, pos - pre);

    pair<string, string> res = {hash_file, file_name};
    return res;
}

void make_structure(string hash, string file_path)
{
    // check if "/" exist means make file
    int pre = 0, pos = file_path.find("/");
    while (pos != string::npos && pos <= file_path.size())
    {
        string dir = file_path.substr(pre, pos - pre);
        // check if directory exists
        if (!filesystem::exists(dir) && mkdir(dir.c_str(), 0777) == -1)
        {
            throw string("checkout_command -> create_tree : Error in Making directory");
        }
        // if not then make
        pre = pos + 1;
        pos = file_path.find("/", pre);
    }
    // string file_name = file_path.substr(pre, pos);
    std::ofstream file(file_path);
    // cout << "debug make_str " << file_name << endl;
    // put content to newly created file
    string hash_dir_path = get_path_from_hash(hash);
    string hash_content = file_to_string(hash_dir_path);
    // decompress hash
    string decompressed_data = decompressString(hash_content);
    file << decompressed_data;
}
/**
 * @brief Driver function of checkout
 *
 * @param current_path
 * @param hash
 */
void checkout(string current_path, string hash)
{
    DIR *dirp = opendir(current_path.c_str());

    if (dirp == nullptr)
        throw "checkout_command -> create_tree : failed to open directory: " + current_path;

    struct dirent *dp;

    while ((dp = readdir(dirp)) != nullptr)
    {
        if (string(dp->d_name) == "." || string(dp->d_name) == ".." || string(dp->d_name).at(0) == '.' || strcmp(string(dp->d_name).c_str(), "mygit") == 0)
        {
            continue;
        }
        cout << dp->d_name << endl;

        // remove all
        cout << "/tremoving contents " << dp->d_name << " ..." << endl;

        filesystem::remove_all(dp->d_name);
        sleep(0.1); // sleep for 1 second
        // restore all
        string tree_path = ".init/objects/" + hash.substr(0, 2) + "/" + hash.substr(2);
        // cout << "debug printing tree path" << file_to_string(tree_path);
        string tree_content = file_to_string(tree_path);

        //         blob/0a4454cccc70e0073e1dab2dbc8bacb93ed9448f6/0Makefile.save/0447
        //         blob/0c4bef4470b40f309f22efc08686ca099b958abb8/0ReadMe.md/0296

        vector<pair<string, string>> vector_hash_path; // hash, path
        cout << "/tAdding previous version of " << dp->d_name << " ..." << endl;

        int pre = 0;
        auto pos = tree_content.find("\n");
        while (pos != string::npos && pos < tree_content.size())
        {
            vector_hash_path.push_back(get_hash_and_path_from_hash(tree_content.substr(pre, pos - pre)));
            pre = pos + 1;
            pos = tree_content.find("\n", pre);
        }
        // still last line reminaing

        for (int i = 0; i < vector_hash_path.size(); i++)
            make_structure(vector_hash_path[i].first, vector_hash_path[i].second);
        // lets do the first one
        sleep(0.1); // sleep for 1 second
    }
}

#endif