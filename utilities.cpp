#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <string>
#include <cstring> // For memset
#include <zlib.h>  // zlib header
using namespace std;
// Compress a string using zlib

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