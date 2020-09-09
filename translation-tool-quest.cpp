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
    string method = "";
    string mapName = "";
    string source = "";
    string destination = "";
    
    if (argc == 0)
    {
        // no supplied arguments
        cout << "You really should proceed to section 14." << endl;
        ArgsSummary(argc, argv);
    }
    else
    {
        if (argc < 5)
        {
            // not enough supplied arguments
            ArgsSummary(argc, argv);
            cout << "You're close to section 14, you know." << endl;
        }
        else
        {
            // we have all information - proceed!
            method = argv[1];
            mapName = argv[2];
            source = argv[3];
            destination = argv[4]; // TODO - manipulate this to only take the final part after '-'
        
            // Bad method supplied! No biscuit!
            if (method != "apply" && method != "generate")
            {
                cout << "You must apply or generate!" << endl;
                ArgsSummary(argc, argv);
            }

            // generate
            if (method == "generate")
            {
                cout << "Let's generate some stuff!" <<endl;

                // Parse file from 'source' command line argument and use to generate a tree object.
                tree treeOfSource = TreeFromFile(source);
                
                // Parse all files from dst-core/ and create a tree from each.
                string filename;
                map <string, tree> dest_files = {};
                for (const auto & file : filesystem::directory_iterator(destination))
                {
                    filename = file.path().filename();
                    tree t = TreeFromFile(file.path());
                    dest_files.insert_or_assign(filename, t);
                }

                // Create a core-map.json file and fill it with matches.
                ofstream outputFile;
                outputFile.open(mapName);

                tree matches;

                // Iterate over treeOfSource values and in each iteration loop over dest_files(s) values
                //      if there is a string match, output some JSON to the core-map.json
                //      specifying key of treeOfSource and destination file
                for (auto &sourceChild : treeOfSource.children)
                {
                    for (auto &file : dest_files)
                    {
                        for (auto &fileChild : file.second.children)
                        {
                            if (sourceChild.second.as_string() == fileChild.second.as_string())
                            {
                                matches.set(sourceChild.first, file.first);
                            }  
                        }
                    }
                }
                outputFile << encode<prettyjson>(matches);
                outputFile.close();
                
                cout << "Everything generated perfectly" << endl;
            }

            // apply
            if (method == "apply")
            {
                cout << "Let's apply some stuff to some other stuff!" <<endl;
            
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
    }

    // End Quest
    cout << "Your quest is over for now." << endl;
    cout << "But remember, this was not a test." << endl;

    return 0;
}