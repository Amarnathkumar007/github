#ifndef ADD_COMMAND
#define ADD_COMMAND

#include <bits/stdc++.h>

#include "hash_command.cpp"
#include "tree_obj.cpp"
#include "utilities.cpp"
using namespace std;

/**
 * @brief This function basically write hash of tree to index.txt
 *
 * @param hash
 */
void save_to_index(string hash)
{
    string file_name = ".init/INDEX";

    if (!std::filesystem::exists(file_name))
        throw string("add_command->save_to_index: Error in locating file");

    std::ofstream file(file_name); // makes file
    file << hash;
}
/**
 * @brief This function checks whether index.txt is empty or not
 *
 * @return true
 * @return false
 */
bool check_if_hash_exist()
{
    string file_name = ".init/INDEX";
    string content = file_to_string(file_name);
    if (content.size() < 40)
        return false;

    // cout << "status is true";
    return true;
}

/**
 * @brief This function generates line to add into tree object
 *
 * @param file_name
 * @return string
 */
string get_tree_object_line(string file_name)
{
    string content = file_to_string(file_name);
    string hash_content = hash_string(content);
    save_blob_object(hash_content, file_name);

    // make tree object
    string tree_content = "blob/0" + hash_content + "/0" + file_name + "/0" + to_string(file_to_string(file_name).size());
    return tree_content;
}
/**
 * @brief here we get file_name when file is empty i.e make blob object and save blob/0<hash>/0<file_name>/0<size>
 *
 * @param file_name
 */

void save_file_to_tree_when_empty(string file_name, string current_path)
{
    // cout << "debug: Inside save_file_to_tree_when_emtpy" << endl;
    // make blob object and save to file
    string tree_content = get_tree_object_line(file_name);

    // make hash of tree object
    string hash_tree_content = hash_string(tree_content);
    // save hash of tree object to index file
    save_to_index(hash_tree_content);

    // write tree object to tree file
    write_tree_object(hash_tree_content, tree_content);
}

/**
 * @brief here we get file name and save canged tabel hash to index file
 *
 * @param file_name
 */
void save_file_to_tree_when_not_empty(string file_name, string current_path)
{
    // take hash of table from index file
    string hash_table_hash = file_to_string(".init/INDEX");
    // cout << "debug: " << hash_table << endl;

    // cout << "debug: " << hash_table_hash << endl;
    // locate table and take string from file
    // string hash_table_path = current_path + "/" + hash_table_hash.substr(0, 2) + "/" + hash_table_hash.substr(2);
    string hash_table_path = ".init/objects/" + hash_table_hash.substr(0, 2) + "/" + hash_table_hash.substr(2);
    // cout << "\ndebug: hash table path -> " << hash_table_path << endl;
    // get hash
    string hash_content = file_to_string(hash_table_path);
    // cout << "\ndebug: " << hash_content << endl;
    // check if file exist in hash
    string line_to_add = get_tree_object_line(file_name);
    if (hash_content.find(file_name) != string::npos)
    {
        // remove that line from index file
        auto pos = hash_content.find(file_name);
        auto prev = hash_content.rfind("\n", pos);
        auto post = hash_content.find("\n", pos);

        if (prev == string::npos && post == string::npos)
        {
            // means only this line in file
            hash_content = line_to_add;
        }
        else if (prev == string::npos)
        {
            // this is the first line
            hash_content.erase(0, post + 2); // even erase \n
            hash_content += line_to_add;
        }
        else
        {
            // this is the last line
            hash_content.erase(prev + 2);
            hash_content += line_to_add;
        }
        // write to file
        // save_to_index(hash_content);
        write_to_file(hash_table_path, hash_content);
    }
    else
    {
        // add line to file
        hash_content += "\n";
        hash_content += line_to_add;

        // save to file
        // cout << "debug1: " << hash_content << "\n"
        //      << hash_table_path << endl;
        // save_to_index(hash_content);
        write_to_file(hash_table_path, hash_content);
    }
}

#endif