/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    
    SixDegrees sd;
    cout << "Enter two actor names separated by a new line.\n";
    cout << "Press ctrl-D to quit" << endl;
    if (argc == 1)
        sd.run(cin, cout);    
    else{
	ifstream infile;
	string filename = argv[1];
	infile.open(filename);
	if (!infile.is_open()){
	    cerr << "file not open" << endl;
	    return 0;
	}
	sd.run(infile, cout);
	infile.close();
    }	
    return 0;
}
