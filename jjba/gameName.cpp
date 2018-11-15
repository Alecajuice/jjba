//
// Created by aleca on 11/15/2018.
//
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

string chooseLineFromFile(ifstream& file)
{
    //Return value
    string line;

    //Count number of lines
    int numLines = 0;
    while(getline(file, line))
    {
        numLines++;
    }

    //Return to beginning of file
    file.clear();
    file.seekg(0, ios::beg);

    //Get random line
    int random = rand() % numLines;

    for(int i = 0; i < random; i++)
    {
        getline(file, line);
    }

    //Return to beginning of file
    file.clear();
    file.seekg(0, ios::beg);
    return line;
}

char* chooseGameName()
{
    //Return value
    char* retval;

    //Open input file streams
    ifstream names_j, names_b;
    names_j.open("assets/other/names_j.txt", ios::in);
    names_b.open("assets/other/names_b.txt", ios::in);

    //Get random names from files
    srand(static_cast<unsigned int>(time(nullptr)));
    string name_j1 = chooseLineFromFile(names_j);
    string name_j2 = chooseLineFromFile(names_j);
    string name_b = chooseLineFromFile(names_b);

    //Close ifstreams
    names_j.close();
    names_b.close();

    //Create name
    string name = name_j1 + " " + name_j2 + "'s " + name_b + " Adventure";
    retval = strdup(name.c_str());;

    return retval;
}
