#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

// including files
#include "init.cpp"
#include "hash_command.cpp"

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
    ofstream file_obj("treeobj.txt");

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

    // ./ mygit cat-file <flag> <file_sha>
    // ./ mygit write - tree
    // ./ mygit ls - tree[--name-only]<tree_sha>

    // ./mygit add .
    // ./mygit add main.cpp utils.cpp

    // ./mygit commit -m "Commit message"
    // ./mygit commit

    // ./mygit log

    if (argc >= 2) //./main <arg1>
    {
        cout << "Reading input" << endl;

        if (strcmp(argv[1], "init") == 0)
        {
            cout << "init" << endl;
            if (!init())
            {
                throw string("problem in makeing file");
            }
            return;
        }
        else if (strcmp(argv[1], "hash-object") == 0)
        {
            cout << "hash_object" << endl;
            // check argc size whether flag or not
            string hash;
            if (argc == 3) // flag not included
            {
                cout << "flag not included" << endl;
                hash = hash_string(file_to_string(argv[2]));
                return;
            }
            else // flag includes
            {
                cout << "flag included" << endl;
                hash = hash_string(file_to_string(argv[3]));
            }
            cout << hash << endl;
            // process file
            cout << "processing flag" << endl;
            //save to hash along with compressed version of file

            save_object(hash,argv[3]); //sending hash and file name 

        }
        else if (strcmp(argv[1], "cat-file"))
        {
            cout << "cat-file" << endl;
            if (argc != 4)
            {
                // flag not included
                cout << "flag not included";
                return;
            }
            cout << "cat-file operation";
        }
        else if (strcmp(argv[1], "write-tree"))
        {
            cout << "write-tree" << endl;
            if (argc != 2)
            {
                cout << "wrong number of argument";
                return;
            }
            cout << "write-tree operation";
        }
        else if (strcmp(argv[1], "add"))
        {
            cout << "add operation";
            if (argc == 3)
            {
                cout << ". operation ";
            }
            else
            {
                cout << "include these files" << endl;

                for (int i = 2; i < argc; i++)
                {
                    cout << argv[i] << endl;
                }
            }
        }
        else if (strcmp(argv[1], "commit"))
        {
            cout << "commit operation";
            if (argc == 2)
            {
                cout << "commit without message" << endl;
            }
            else
            {
                cout << "commit with message" << endl;
            }
        }
        else if (strcmp(argv[1], "log"))
        {
            cout << "log operation";
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
        string file_name = "treeobj.txt";

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