//Andrew Cervantes
//SixDegrees class
//hw 5
#include "Actor.h"
#include "Graph.h"
#include<iostream>
#include<string>

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_

using namespace std;

class SixDegrees
{
public:
    //Constructor
    SixDegrees();
   
    //populate the graph
    void populateGraph();

    //run function
    void run(istream &, ostream &);

    //BFS
    void BFS(Actor, Actor, ostream &);

private:
    Graph<Actor> g;
    void fillVertices(ifstream &, Actor actors[]);	
};
#endif
