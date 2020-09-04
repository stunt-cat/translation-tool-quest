#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ArgsSummary(int argc, char** argv)
{
    cout << "Provide the following 4 arguments: method mapName source destination" << endl;
    cout << "So far you have provided the follwing " << argc - 1 << " arguments:" << endl;
    
    for (int i = 1; i < argc; ++i)
    {
        cout << argv[i] << endl;
    }
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
            // MASSIVE TODO!!
            /*  
            *   Parse file from 'source' command line argument and use to generate a tree object e.g. sourceFile.
            *   Parse all files from dst-core/ and create a tree object from each e.g. destFile1.
            *   Create a core-map.json file (empty for now).
            *   Iterate over sourceFile keys and in each iteration loop over destFile(s) keys
            *       if there is a string match, output some JSON to the core-map.json specifying key and destination file
            */


            // Testing creating and writing to a file
            // For testing purposes, let's assume the user put 'filename.txt' as their 2nd argument..
            ofstream outputFile;
            outputFile.open(string(argv[2]));
            for (int i=0; i<10; ++i)
            {
                outputFile << "Line number " << i << " that will be json one day." << endl;
            }
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