#ifndef CAT_COMMAND
#define CAT_COMMAND

#include <bits/stdc++.h>
#include "hash_command.cpp"

using namespace std;

string get_path_from_hash(string hash)
{
    string file_path = ".init/objects/";
    file_path += hash.substr(0, 2);
    file_path += "/";
    file_path += hash.substr(2);
    return file_path;
}
/**
 * @brief Get the content object from the given file path
 *
 * @param hash
 * @return string
 */

string content_type(string hash)
{

    string file_path = get_path_from_hash(hash);

    string content = file_to_string(file_path);
    if (!content.empty())
    {
        if (content[0] == 'b')
        {
            return "tree";
        }
        else
        {
            return "blob";
        }
    }
    throw string("cat_command->content_type: File is empty hence cant tell about the object");
}

#endif