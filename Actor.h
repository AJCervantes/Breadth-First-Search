//Actor class
//Hw5
//Andrew Cervantes

#include "LinkedList.h"
#include <iostream>
#include <string>

#ifndef ACTOR_H_
#define ACTOR_H_ 
using namespace std;

class Actor
{
public:
    //Constructor
    Actor();

    //Parameterized constructor
    Actor(string input);

    //insert a movie into the list
    void insert(string movie);

    //Determines if the actor was in the movie
    bool isIn(string movie);

    //Checks if 2 actors share a movie
    string connect(const Actor &guy);

    //Changes the name of an Actor object
    void changeName(string newName);

    //operators
    bool operator==(const Actor &guy);
    bool operator!=(const Actor &guy);
    friend ostream & operator << (ostream &, const Actor &guy);

private:
    string name;
    LinkedList<string> movies;
    
};
#endif
