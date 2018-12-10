//Andrew Cervantes
//Comp15 hw 5
//SIXDEGREES.cpp

#include "Actor.h"
#include "Graph.h"
#include "Queue.h"
#include <iostream>
#include <string>
#include <fstream>
#include "SixDegrees.h"
using namespace std;

//Function: Constructor
//Inputs: none
//Returns: none
//does: constructs the graph
SixDegrees::SixDegrees()
{
    populateGraph();
}

//Function: populateGraph
//Inputs: none
//return: none
//Does: populates the graph with actors and movies
void SixDegrees::populateGraph()
{
    ifstream infile;
    infile.open("actors.txt");
    int num_verts = 0;
    string input;
    while (getline(infile, input)){
	if (input == "*")
	    num_verts++;
    }
    g.initialize_graph(num_verts);
    Actor actors[num_verts];
    fillVertices(infile, actors);
    for (int i = 0; i < num_verts; i++){
	for (int j = 0; j < num_verts; j++){
	    string edge = actors[i].connect(actors[j]);
	    if (edge != NULL_EDGE)
		g.add_edge(actors[i], actors[j], edge);
	}
    }
    infile.close();
}

//Function fillVertices
//inserts: infile reference, actor array
//return: none
//does: enters the Actors and fills vertices and actor array
void SixDegrees::fillVertices(ifstream &infile, Actor actors[])
{
    infile.clear();
    infile.seekg(0, infile.beg);
    string input;
    int count = 0;
    while (getline(infile, input))
    {
	Actor ac(input);
	getline(infile, input);
	while (input != "*"){
	    ac.insert(input);
	    getline(infile, input);
	}
    g.add_vertex(ac);
    actors[count] = ac;
    count++;
    }
}

//Function: run
//inputs: istream & and ostream &
//returns: none
//does: Runs through the files and calls the search
void SixDegrees::run(istream &infile, ostream &outfile)
{
    string name1, name2;
    while (!infile.eof())
    {
        getline(infile, name1);
        getline(infile, name2);
	if (name1 == name2)
	    getline(infile, name2);
	Actor a(name1);
	Actor b(name2);
	while (!g.is_vertex(a) && !infile.eof()){
	    outfile << "Sorry, " << a << " is not in the list\n" << endl;
	    a = b;
	    getline(infile, name2);
	    b.changeName(name2);
	}
	while (!g.is_vertex(b) && !infile.eof()){
	    outfile << "Sorry, " << b << " is not in the list\n" << endl;
	    getline(infile, name2);
	    b.changeName(name2);
	}
	if (g.is_vertex(a) && g.is_vertex(b))
	    BFS(a, b, outfile);
    }
}
//Function: BFS
//inputs: 2 actors and a ostream reference
//returns: none
//Does: finds the shortest path from A to B
void SixDegrees::BFS(Actor a, Actor b, ostream &outfile){
    g.clear_marks();
    g.initialize_path();
    Queue <Actor> prim;
    Queue <Actor> sec; 
    Actor curr = a;
    prim.enqueue(curr);
    Actor neighbor;
    while (!(curr == b))
    {
	if (prim.is_empty()){
	    outfile << a << " and " << b << ": No connection" << endl << endl;
	    return;
	}   
	prim.dequeue(curr);
	if (curr == b)
	    break;
	g.mark_vertex(curr);
	g.get_to_vertices(curr, sec);
	while (!sec.is_empty()){
	    sec.dequeue(neighbor);
	    g.update_predecessor(curr, neighbor);
	    if (neighbor == b)
		curr = b;
	    else if (!g.is_marked(neighbor))
		prim.enqueue(neighbor);
	}
    }
    g.report_path(outfile, a, b);
    outfile << endl;
}
