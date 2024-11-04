#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <string>
#include <cstring> // For memset
#include <zlib.h>  // zlib header
using namespace std;
// Compress a string using zlib

/**
 * @brief give the name of file it willl return content of file
 *
 * @param file_name
 * @return string
 */
string file_to_string(string file_path)
{
    string actual_string = "";
    ifstream file(file_path);

    if (!file)
        throw string("Utilies->file_to_string: Error in opening file");

    ostringstream contentStream;
    contentStream << file.rdbuf(); // Read the entire file buffer into the stream
    return contentStream.str();
}

/**
 * @brief returns current user name
 *
 * @return std::string
 */
std::string get_current_user()
{
    // Try to get the username from the environment variable
    const char *user = getenv("USER");
    if (user != nullptr)
        return std::string(user);

    // Fallback to using getlogin if getenv didn't work
    user = getlogin();
    if (user != nullptr)
        return std::string(user);

    // If both methods fail, return an empty string or an error message
    return "Unknown User";
}

/**
 * @brief Gets the time of commit
 *
 * @return string
 */

string get_time_stamp()
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert to a tm structure
    std::tm local_tm = *std::localtime(&now_time);

    // Format the time as a string
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S"); // Format: YYYY-MM-DD HH:MM:SS
    return oss.str();
}

/**
 * @brief This function overwirte to given file
 *
 * @param file_name
 * @param hash_content
 */
void write_to_file(string file_name, string hash_content)
{

    if (!std::filesystem::exists(file_name))
        throw string("add_command->save_to_file: Error in locating file");

    std::ofstream file(file_name); // makes file
    file << hash_content;
}

string compressString(const string &str, int compressionLevel = Z_BEST_COMPRESSION)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionLevel) != Z_OK)
    {
        throw runtime_error("deflateInit failed while compressing.");
    }

    zs.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(str.data()));
    zs.avail_in = static_cast<uInt>(str.size());

    int ret;
    const size_t bufferSize = 32768;
    char outbuffer[bufferSize];
    string outstring;

    // Compress the data
    do
    {
        zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
        zs.avail_out = bufferSize;

        ret = deflate(&zs, Z_FINISH);

        if (ret != Z_OK && ret != Z_STREAM_END)
        {
            deflateEnd(&zs);
            throw string("Exception during zlib compression: " + to_string(ret));
        }

        outstring.append(outbuffer, bufferSize - zs.avail_out);
    } while (ret != Z_STREAM_END);

    deflateEnd(&zs);

    return outstring;
}
/**
 * @brief Problem in decompression
 *
 * @param compressedString
 * @return string
 */
// Decompress a string using zlib
string decompressString(const string &compressedString)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
    {
        throw string("inflateInit failed while decompressing.");
    }

    zs.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(compressedString.data()));
    zs.avail_in = static_cast<uInt>(compressedString.size());

    int ret;
    const size_t bufferSize = 32768;
    char outbuffer[bufferSize];
    string outstring;

    // Decompress the data
    do
    {
        zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
        zs.avail_out = bufferSize;

        ret = inflate(&zs, 0);

        if (ret != Z_OK && ret != Z_STREAM_END)
        {
            inflateEnd(&zs);
            throw string("Exception during zlib decompression: " + to_string(ret));
        }

        outstring.append(outbuffer, bufferSize - zs.avail_out);
    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);

    return outstring;
}

#endif