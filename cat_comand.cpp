#ifndef CAT_COMMAND
#define CAT_COMMAND

#include <bits/stdc++.h>
#include "hash_command.cpp"

using namespace std;

/**
 * @brief Get the content object from the given file path
 *
 * @param hash
 * @return string
 */
string get_content(string hash)
{
    string file_path = ".init/objects/";
    file_path += hash.substr(0, 2);
    file_path += "/";
    file_path += hash.substr(2);

    string content = file_to_string(file_path);
    return content;
}

#endif 