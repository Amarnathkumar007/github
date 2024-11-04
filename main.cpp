#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

// including files
#include "init.cpp"
#include "hash_command.cpp"
#include "tree_obj.cpp"
#include "cat_command.cpp"
#include "ls_tree.cpp"
#include "add_command.cpp"
#include "commit_command.cpp"
#include "log_command.cpp"
#include "checkout_command.cpp"

using namespace std;

void make_map(string &filename, unordered_map<int, int> &u_m)
{
    // makein map
    string myText;
    unordered_map<int, int> resultMap;

    ifstream MyReadFile(filename);

    while (getline(MyReadFile, myText))
    {
        // Output the text from the file
        // cout << myText << endl;

        int key, value;
        auto pos = myText.find(",");
        key = stoi(myText.substr(0, pos));
        value = stoi(myText.substr(pos + 1, myText.length() - pos));
        u_m[key] = value;

        // cout << key << " " << value << endl;
    }

    MyReadFile.close();
    cout << endl;
}

void save_tree_map(string &filename, unordered_map<int, int> &u_m)
{
    ofstream file_obj(".init/TREEOBJ");

    // Write to the file
    // MyFile << "Files can be tricky, but it is fun enough!";

    for (auto m : u_m)
    {
        file_obj << m.first << "," << m.second << "\n";
    }

    // Close the file
    file_obj.close();
}

void menu(int argc, char const *argv[])
{
    // ./mygit init

    // ./mygit hash-object [-w] test.txt
    // ./mygit hash-object test.txt

    // ./mygit cat-file <flag> <file_sha>
    // ./mygit write - tree
    // ./mygit ls-tree [--name-only] <tree_sha>

    // ./mygit add .
    // ./mygit add main.cpp utils.cpp

    // ./mygit commit -m "Commit message"
    // ./mygit commit

    // ./mygit log

    if (argc >= 2) //./main <arg1>
    {
        cout << "Reading Arguments..." << endl;

        if (strcmp(argv[1], "init") == 0)
        {
            cout << "init command executing ..." << endl;
            if (!init())
            {
                throw string("problem in makeing file");
            }
            return;
        }
        else if (strcmp(argv[1], "hash-object") == 0)
        {
            cout << "hash_object command executing ..." << endl;
            // check argc size whether flag or not
            string hash;
            if (argc == 3) // flag not included
            {
                // cout << "flag not included" << endl;
                hash = hash_string(file_to_string(argv[2]));
                cout << "Hash: " << hash << endl;
                return;
            }
            else // flag includes
            {
                // cout << "flag included" << endl;
                hash = hash_string(file_to_string(argv[3]));
            }
            cout << hash << endl;
            // process file
            // cout << "processing flag" << endl;
            // save to hash along with compressed version of file

            save_blob_object(hash, argv[3]); // sending hash and file name
        }
        else if (strcmp(argv[1], "cat-file") == 0)
        {
            cout << "cat-file executing ..." << endl;
            if (argc != 4)
            {
                // flag not
                throw string("Main->Cat-file: Flag not included in cat-file command");
                // cout << "flag not included";
                // return;
            }
            // cout << "cat-file operation " << endl;

            if (strcmp(argv[2], "-p") == 0)
            {
                // cout << "-p flag" << endl;
                // string hash = argv[3];
                string content = file_to_string(get_path_from_hash(argv[3])); // sending hash
                cout << "Here is content:\n"
                     << decompressString(content) << endl;
            }
            else if (strcmp(argv[2], "-s") == 0)
            {
                // cout << "file size in byte" << endl;
                string content = content_type(argv[3]);
                // if blob object
                if (strcmp(content.c_str(), "blob") == 0)
                {
                    // means tree
                    //  uncompress it return the size of string
                    string blob_content = file_to_string(get_path_from_hash(argv[3]));
                    // uncompress it
                    // cout << "content of file: " << blob_content << endl;
                    cout << "file size: " << decompressString(blob_content).size();
                }
                // if tree object
                else if (strcmp(content.c_str(), "tree") == 0)
                {
                    string tree_content = file_to_string(get_path_from_hash(argv[3]));
                    cout << "file size: " << tree_content.size();
                }
                // return the size of file
            }
            else if (strcmp(argv[2], "-t") == 0)
            {
                cout << "showing type of content" << endl;
                string content = content_type(argv[3]); // sending hash
                cout << "object type is: " << content << endl;
            }
        }
        else if (strcmp(argv[1], "write-tree") == 0)
        {
            if (argc != 2)
            {
                cout << "Main: wrong number of argument\b";
                return;
            }
            cout << "Executing write-tree operation ...\n";

            vector<pair<string, pair<int, int>>> v_files; // file name and level and size
            // cout << "Main: print content of file";

            char current_path[buffer_size];
            getcwd(current_path, buffer_size);
            // cout << "path " << current_path << endl;
            create_tree_vector(current_path, 0, v_files); // get details of all files

            // make string to write in tee object
            string content, tree_object_hash;

            for (auto i : v_files)
            {
                // get hash and save to blob
                // cout << i.first << " " << i.second.first << " " << i.second.second << endl;
                string file_content = file_to_string(i.first);
                string file_hash = hash_string(file_content);
                if (!save_blob_object(file_hash, i.first))
                    throw string("write-tree: error in saving object to file");

                content += "blob"; //<type>
                content += "/0";
                content += file_hash; //<hash>
                content += "/0";
                content += get_file_name(i.first, i.second.first); //<name,level>
                content += "/0";
                content += to_string(i.second.second); //<size>
                content += "\n";
            }
            // make hash of content
            tree_object_hash = hash_string(content); // hash of content
            // writing tree object
            write_tree_object(tree_object_hash, content); // file name,hash,level,size_of_file
            cout << "Hash: " << tree_object_hash << endl;
        }
        else if (strcmp(argv[1], "ls-tree") == 0)
        {
            // check if hash is tree or not

            if (argc == 3)
            {
                // no flag
                if (!is_hash(argv[2]))
                    throw string("ls-tree: hash is not valid");

                string content = get_content_without_flag(argv[2]);
                cout << content << endl;
            }
            else if (argc == 4)
            {
                // flag included
                if (!is_hash(argv[3]))
                    throw string("ls-tree: hash is not valid");

                string content = get_content_with_flag(argv[3]);
                cout << "here is file name: \n"
                     << content << endl;
            }
        }
        else if (strcmp(argv[1], "add") == 0)
        {
            // make object tree

            // add to index folder

            cout << "add operation executing ...\n";
            if (argc == 2)
                throw string("wrong parameters");

            if (strcmp(argv[2], ".") == 0)
            {
                // cout << ". operation\n";

                vector<pair<string, pair<int, int>>> v_files; // file name and level and size

                char current_path[buffer_size];
                getcwd(current_path, buffer_size);
                // cout << "path " << current_path << endl;
                create_tree_vector(current_path, 0, v_files); // get details of all files

                // make string to write in tee object
                string content, tree_object_hash;

                for (auto i : v_files)
                {
                    // get hash and save to blob
                    // cout << i.first << " " << i.second.first << " " << i.second.second << endl;
                    string file_content = file_to_string(i.first);
                    string file_hash = hash_string(file_content);
                    if (!save_blob_object(file_hash, i.first))
                        throw string("write-tree: error in saving object to file");

                    content += "blob"; //<type>
                    content += "/0";
                    content += file_hash; //<hash>
                    content += "/0";
                    content += get_file_name(i.first, i.second.first); //<name,level>
                    content += "/0";
                    content += to_string(i.second.second); //<size>
                    content += "\n";
                }
                // make hash of content
                tree_object_hash = hash_string(content); // hash of content

                // cout << tree_object_hash << " \n" << content << endl; //hash and content

                write_tree_object(tree_object_hash, content); // file name,hash,level,size_of_file

                // got tree object hash now save to index
                //  cout << tree_object_hash << endl;
                save_to_index(tree_object_hash);
            }
            else
            {
                cout << "Include these files ..." << endl;
                bool status = true;
                if (!check_if_hash_exist())
                    status = false;

                char current_path[buffer_size];
                getcwd(current_path, buffer_size);

                for (int i = 2; i < argc; i++)
                {
                    if (!status)
                    {
                        save_file_to_tree_when_empty(argv[i], current_path); // here we need to make tree
                        status = true;
                        continue;
                    }
                    // cout << argv[i] << endl;
                    save_file_to_tree_when_not_empty(argv[i], current_path);
                }
            }
        }
        else if (strcmp(argv[1], "commit") == 0)
        {
            cout << "commit operation executing ...\n";

            string commit_message = "None"; // defualt message
            if (argc == 4)
                commit_message = argv[3];

            cout << commit_operation(commit_message); // printing hash
        }
        else if (strcmp(argv[1], "log") == 0)
        {
            cout << "Executing log operation ...";
            log_operation();
        }
        else if (strcmp(argv[1], "checkout") == 0)
        {
            cout << "Executing checkout operation ..." << endl;
            char current_path[buffer_size];
            getcwd(current_path, buffer_size);

            checkout(current_path, argv[2]);
        }
        else
        {
            cout << " wrong parameter " << endl;
            return;
        }
    }
    else
    {
        cout << "Too less command" << endl;
    }
}
int main(int argc, char const *argv[])
{
    try
    {
        menu(argc, argv); // rediect based on input

        unordered_map<int, int> u_m;
        string file_name = ".init/TREEOBJ";

        make_map(file_name, u_m);

        save_tree_map(file_name, u_m);
    }
    catch (const string &e)
    {
        cout << "Exception: " << e << endl; // catch and print error message
    }
    catch (...)
    {
        cout << "unhandled Exception";
    }

    return 0;
}