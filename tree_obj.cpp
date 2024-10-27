#ifndef TREE_OBJ
#define TREE_OBJ



/*

<mode> <type> <hash> <name> <file_size>
100644 blob <hash_of_file1>    file1.txt //mode of file with three char
100644 blob <hash_of_file2>    file2.txt
100644 blob <dir>/<file_name> file3.txt

*/

#include <iostream>
#include <string>
#include <filesystem>
#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;
namespace fs = std::filesystem;

const int buffer_size = 1024;

/**
 * @brief This function create vector of file name with level of file
 *
 * @param folder_name
 * @param level
 * @param v_files
 */
void create_tree_vector(string folder_name, int level, vector<pair<string, pair<int,int>>> &v_files)
{
    DIR *dirp = opendir(folder_name.c_str());

    if (dirp == nullptr)
        throw "create_tree : failed to open directory: " + folder_name;

    struct dirent *dp;

    while ((dp = readdir(dirp)) != nullptr)
    {
        if (string(dp->d_name) == "." || string(dp->d_name) == ".." || string(dp->d_name).at(0) == '.')
        {
            continue;
        }
        string t_path = folder_name + "/" + dp->d_name;

        struct stat file_type;

        if (stat(t_path.c_str(), &file_type) != 0)
            throw string("Inside ls -l: failed to info about path:");

        if (S_ISDIR(file_type.st_mode))
        {
            // q_folders.push(t_path);
            create_tree_vector(t_path, level + 1, v_files);
            // cout << t_path << " folder "<< level<< endl;
        }
        else
        {
            int file_size=file_type.st_size; //stores the size of newly created file
            v_files.push_back({t_path, {level,file_size}}); // add file to vector
        }
    }
    return;
}

/**
 * @brief Get the file name along with its level from path ex .init/amar/ravi.txt if level 2 then return amar/ravi.txt
 * 
 * @param file_path 
 * @param level 
 * @param file_size 
 * @return string 
 */
string get_file_name(string file_path,int level=0,int file_size=0){
    // if file is inside a directory
    auto pos = file_path.rfind("/");

    while (level > 0)
    {
        level--;
        pos = file_path.rfind("/",--pos);
    }

    return file_path.substr(pos+1);
    // cout << pos << endl;
}

/**
 * @brief This function gonna write while object at ones appening element will cause problem if new structure comes with same hash
 * 
 * @param file_path 
 * @param hash 
 * @param level 
 * @param file_size 
 */
void write_tree_object(string tree_hash,string content) //hash will help searching tree object file
{
    //get the file on which we want to write
        string dir_name = ".init/objects/";
        dir_name += tree_hash.substr(0, 2);
        string tree_file_name = dir_name;

        tree_file_name += "/";
        tree_file_name += tree_hash.substr(2); //hash from position 2 to end
        
        // check if directory exist or not
        if (!filesystem::exists(dir_name))
        {
            // if not exist
            if (mkdir(dir_name.c_str(), 0777) == -1) throw string("save_object: problem in creating file");
        }

    //write content to file
        std::ofstream file(tree_file_name); // makes file
        file << content;
}


#endif
