#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <entity/entity.hpp>
#include <entity/json.hpp>
#include <entity/tree.hpp>

using namespace std;
using namespace ent;

void ArgsSummary(int argc, char** argv)
{
    cout << "Provide the following 4 arguments: method mapName source destination" << endl;
    cout << "So far you have provided the follwing " << argc - 1 << " arguments:" << endl;
    
    for (int i = 1; i < argc; ++i)
    {
        cout << argv[i] << endl;
    }
}

tree TreeFromFile(string fileName)
{
    ifstream ifile(fileName);
    ostringstream tmp;
    tmp << ifile.rdbuf();
    string stringOfSource = tmp.str();

    auto t = decode<json>(stringOfSource);

    return t;
}

int main(int argc, char** argv)
{
    // generate
    if (string(argv[1]).compare("generate") == 0)
    {
        cout << "Let's generate some stuff!" <<endl;

        if (argc < 5)
        {
            ArgsSummary(argc, argv);
        }
        else
        {
            // Parse file from 'source' command line argument and use to generate a tree object.
            tree treeOfSource = TreeFromFile(argv[3]);
            
            // Parse all files from dst-core/ and create a tree object from each.
            string path = argv[4];
            string filename;
            map <string, tree> dest_files = {};
            for (const auto & entry : filesystem::directory_iterator(path))
            {
                filename = entry.path().filename();
                tree t = TreeFromFile(entry.path());
                dest_files.insert_or_assign(filename, t);
            }

            // Create a core-map.json file and fill it with matches.
            ofstream outputFile;
            outputFile.open(string(argv[2]));
            
            outputFile << "{" << endl;
            // Iterate over treeOfSource keys and in each iteration loop over dest_files(s) keys
            //      if there is a string match, output some JSON to the core-map.json specifying key and destination file
            for (auto &i : treeOfSource.children)
            {
                map<string, tree>::iterator iter;
                for (iter = dest_files.begin(); iter != dest_files.end(); ++iter)
                {
                    for (auto k : iter->second.children)
                    {
                        if (i.first == k.first)
                        {
                            outputFile << "\"" << i.first << "\": \"" << iter->first << "\","<< endl;
                        }  
                    }
                }
            }

            outputFile << "}" << endl;

            outputFile.close();
            
            cout << "Everything generated perfectly" << endl;
        }
    }


    // apply
    if (string(argv[1]).compare("apply") == 0)
    {
        cout << "Let's apply some stuff to some other stuff!" <<endl;
        if (argc < 5)
        {
            ArgsSummary(argc, argv);
        }
        else 
        {
            // MASSIVE TODO!!
            /*
            *   Create tree object from command line argument specified core.json
            *   Create tree object from core-map.json
            *   Iterate over map tree to find unique destination file names
            *       Create these .json files in last command line argument directory (i.e. dst-core/)
            *   Iterate over core-map.json tree
            *       for each entry, use key to lookup value in core.json and put it into key/value pair in correct destination file
            * 
            */


            cout << "Everything applied perfectly" << endl;
        }
    }


    // fool
    if (string(argv[1]).compare("apply") != 0 && string(argv[1]).compare("generate") != 0)
    {
        cout << "You must apply or generate!" << endl;
        ArgsSummary(argc, argv);
    }


    // End Quest
    cout << "Proceed to section 14" << endl;

    return 0;
}