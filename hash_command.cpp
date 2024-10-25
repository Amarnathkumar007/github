#include <bits/stdc++.h>
#include <openssl/sha.h>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <fstream>

// own folders
#include "utilities.cpp"
using namespace std;

string hash_string(const string &str)
{
    const unsigned char *unsigned_str = reinterpret_cast<const unsigned char *>(str.c_str());

    unsigned char hash[SHA_DIGEST_LENGTH]; // SHA_DIGEST_LENGTH is 20
    SHA1(unsigned_str, str.size(), hash);

    // Convert hash to a readable hexadecimal string
    string hash_string;

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%02x", hash[i]);
        hash_string += buffer;
    }

    return hash_string; // Return the resulting hash as a hex string
}
string file_to_string(string file_name)
{
    string actual_string = "";
    ifstream file(file_name);

    if (!file)
    {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return "";
    }

    ostringstream contentStream;
    contentStream << file.rdbuf(); // Read the entire file buffer into the stream
    return contentStream.str();
}
// string hash_command(string file_name){
//     //basically we have assumption that our file will be small
//     //read the string from file

//     // call hash function
//     return hash_string(file_to_string(file_name));

// }
bool save_object(string &hash, string file_name)
{
    // making file with first 2 char and saving to .init/object file
    string dir_name = ".init/objects/";
    dir_name += hash.substr(0, 2);
    string compressed_file_name = dir_name;
    compressed_file_name += "/";
    compressed_file_name += hash.substr(2);
    // check if directory exist or not
    if (!filesystem::exists(dir_name))
    {
        // if not exist
        if (mkdir(dir_name.c_str(), 0777) == -1)
            throw string("save_object: problem in creating file");
    }
    // get compressed version

    string file_content = file_to_string(file_name);

    file_content = compressString(file_content.c_str());
    // save file with name as compressed_file_name
    std::ofstream file(compressed_file_name); //makes file
    file << file_content;
    return true;
};