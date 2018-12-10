//Andrew Cervantes
//hw5
//Actor.cpp class

#include "Actor.h"
#include <iostream>
#include <string>

using namespace std;

//Default Constructor
//Inserts: none
//Returns: none
//Does: default constructs the varaibles
Actor::Actor()
{
    string name = "";    
}

//Paramterized Constructor
//Inputs: string
//Returns: none
//Does: creates the name
Actor::Actor(string input)
{
   name = input;
}

//Insert
//Inputs: movie name
//returns: void
//does: inserts the movie into the actor's list
void Actor::insert(string movie)
{
    movies.insert(movie);	
}

//Function: changeName
//Inputs: new name
//Returns: Actor
//Does: changes the name
void Actor::changeName(string newName)
{
    name = newName;
    
}

//isIn
//inserts: string movie
//returns: bool
//Does: checks if the movie is in the actors list
//of movies he's in
bool Actor::isIn(string movie)
{
    bool isIn;
    movies.find(movie, isIn);
    return isIn; 
}

//connect
//inserts:Actor
//returns: string movie
//Does: returns a movie if the 2 actors share a movie
string Actor::connect(const Actor &guy)
{
    int length1 = movies.get_length();
    LinkedList<string> guyMovies = guy.movies;
    string movie1;
    bool isIn;
    for (int i = 0; i < length1; i++)
    {
	movie1 = movies.get_value_at(i);
	guyMovies.find(movie1, isIn);
	if (isIn == true)
	    return movie1;
    }
    return "";   
}

//== Operator
//Inserts: Actor object
//Returns: bool
//Does: compares if the two actors are the same
bool Actor::operator== (const Actor &guy)
{
    if (name == guy.name)
	return true;
    else
	return false;
	
}

//!= Operator
//Inserts: Actor object
//Returns: bool
//Does: returns the opposite of ==
bool Actor::operator!= (const Actor &guy)
{
    if (name == guy.name)
	return false;
    else
	return true;
}

//<< operator
//inserts:
//returns:
//does: Prints the name of the actor
ostream & operator<< (ostream &out, const Actor &guy)
{
    out << guy.name;
    return out;
}
