#include <iostream>
//#include <string>

using namespace std;

void argsSummary(int argc, char** argv){
    cout << "Provide the following 4 arguments: method mapName source destination" << endl;
    cout << "So far you have provided the follwing " << argc - 1 << " arguments:" << endl;
    for (int i = 1; i < argc; ++i){
        cout << argv[i] << endl;
    }
}

int main(int argc, char** argv)
{
    // generate
    if (string(argv[1]).compare("generate") == 0){
        cout << "Let's generate some stuff" <<endl;
        if(argc < 5){
            argsSummary(argc, argv);
        } else {
            // MASSIVE TODO!!
            cout << "Everything generated perfectly" << endl;
        }
    }


    // apply
    if (string(argv[1]).compare("apply") == 0){
        cout << "Let's apply some stuff to some other stuff!" <<endl;
        if(argc < 5){
            argsSummary(argc, argv);
        } else {
            // MASSIVE TODO!!
            cout << "Everything applied perfectly" << endl;
        }
    }


    // Fool
    if (string(argv[1]).compare("apply") != 0 && string(argv[1]).compare("generate") != 0){
        cout << "You must apply or generate!" << endl;
        argsSummary(argc, argv);
    }


    // End Quest
    cout << "Proceed to section 14" << endl;

    return 0;
}