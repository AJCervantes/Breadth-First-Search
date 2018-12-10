//Andrew Cervantes
//hw5
//File testing Graph.cpp

#include "Graph.h"
#include "Actor.h"
#include <iostream>
#include <string>


using namespace std;

int main()
{
    Graph<string> g1(10);
    Graph<string> g2(10);
    //blank graph test
    g1.print_matrix(cout);
    g2 = g1;
    g2.print_matrix(cout);

    //copy constructor test
    g1.add_vertex("andrew");
    g1.add_vertex("jon");
    g1.add_vertex("paul");
    g1.add_vertex("fred");
    g1.add_vertex("george");
    g1.add_vertex("harry");
    g1.add_vertex("ron");
    g1.add_vertex("joseph");
    g1.add_vertex("michael");
    g1.add_vertex("dwight");
    cout << "adding edges" <<endl;

    g1.add_edge("andrew", "paul", "a");
    g1.add_edge("andrew", "jon", "b");
    g1.add_edge("fred", "paul", "c");
    g1.add_edge("joseph", "andrew", "d");
    g1.add_edge("harry", "ron", "e");
    g1.add_edge("michael", "dwight", "f");
    g1.add_edge("ron", "joseph", "g");
    g1.add_edge("harry", "fred", "h");
    g1.add_edge("paul", "jon", "i");
    g1.add_edge("joseph", "paul", "j");
    g1.add_edge("michael", "andrew", "k");

    cout << "part2" << endl;
    g1.print_matrix(cout);
    g2 = g1;
    g2.print_matrix(cout);

    //operator test
    g1.add_edge("george", "ron", "x");
    g1.add_edge("dwight", "jon", "y");
    
    cout << "part3" << endl;
    g1.print_matrix(cout);
    g2 = g1;
    g2.print_matrix(cout);

    //Copy constructor
    Graph<string> g3(10); 
    Graph<string> g4(g2);
    g4.print_matrix(cout);

    cout << "part 4" << endl;
    //should be empty
    Graph<string> g5(g3);
    g5.print_matrix(cout);
}
