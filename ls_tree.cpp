#ifndef LS_TREE

#define LS_TREE

#include <bits/stdc++.h>

#include "cat_command.cpp"
using namespace std;

bool is_hash(string hash)
{
    if (hash.size() != 40)
        return false;

    // check if it exist
    string file_path = get_path_from_hash(hash);
    // is path exist
    // is it tree
    return true;
}

string get_content_without_flag(string hash)
{
    string file_path = get_path_from_hash(hash);
    string content = file_to_string(file_path);
    string result_string = "";
    // remove extra content
    if (content.empty())
        throw string("ls-tree->get_content_without_flag: file is empty\n");

    size_t start = 0;
    size_t line_end;

    // Process each line separately
    while ((line_end = content.find('\n', start)) != std::string::npos)
    {
        std::string line = content.substr(start, line_end - start);

        // Remove all "/0" occurrences
        size_t pos = line.find("/0");
        while (pos != std::string::npos)
        {
            line.erase(pos, 2);
            line.insert(pos, " ");
            pos = line.find("/0", pos);
        }

        // Remove trailing integer
        size_t last_non_digit = line.find_last_not_of("0123456789");
        if (last_non_digit != std::string::npos && last_non_digit + 1 < line.size())
        {
            line.erase(last_non_digit + 1);
        }

        // Append the processed line to the result
        result_string += line + "\n";
        start = line_end + 1;
    }

    // Process the last line (if there's no trailing newline in the input)
    if (start < content.size())
    {
        std::string line = content.substr(start);

        // Remove all "/0" occurrences
        size_t pos = line.find("/0");
        while (pos != std::string::npos)
        {
            line.erase(pos, 2);
            pos = line.find("/0", pos);
        }

        // Remove trailing integer
        size_t last_non_digit = line.find_last_not_of("0123456789");
        if (last_non_digit != std::string::npos && last_non_digit + 1 < line.size())
        {
            line.erase(last_non_digit + 1);
        }

        result_string += line;
    }

    return result_string;
}

string extractFileNames(string content)
{
    // cout << "debug " << content << endl;
    int pos = 0;
    string res_string = "";
    while (content.find("/0", pos + 2) != string::npos)
    {
        pos = content.find("/0", pos + 2) + 2;
        int pos2 = content.find("/0", pos) + 2;
        int pos3 = content.find("/0", pos2);
        res_string += content.substr(pos2, pos3 - pos2);
        res_string += "\n";
        pos = pos3;
    }
    // cout << "debug " << res_string << endl;
    return res_string;
}

string get_content_with_flag(string hash)
{
    string file_path = get_path_from_hash(hash);
    string content = file_to_string(file_path);

    return extractFileNames(content);
}

#endif