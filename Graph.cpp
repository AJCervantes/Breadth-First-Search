
/*
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "Graph.h"
#include "Stack.h"
#include "Actor.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor. Initializes with zero vertices
template<class Vertex>
Graph<Vertex>::Graph()
{
    curr_vertex = 0;
    edges = NULL;
    path = NULL;
    vertices = NULL;
    marks = NULL;
}

// Function: parametrized constructor
// Parameters: integer (size of graph)
// Returns: nothing
// Does: default constructor. Initializes with num_v vertices
template<class Vertex>
Graph<Vertex>::Graph(int num_v)
{
    initialize_graph(num_v);
}

//Function: copy constructor
//parameters: The original graph
//Returns: none
//Does: copies over the graph
template<class Vertex>
Graph<Vertex>::Graph(const Graph &g)
{
    copyingGraph(g);
}

//copyingGraph
//inserts: Graph
//returns: none
//Does: Copies over the info
template<class Vertex>
void Graph<Vertex>::copyingGraph(const Graph &g)
{
    num_vertices = g.num_vertices;
    curr_vertex = g.curr_vertex;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];
    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
	edges[i] = new string[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
	marks[i] = g.marks[i];
	path[i] = g.path[i];
	vertices[i] = g.vertices[i];
	for (int j = 0; j < num_vertices; j++)
	{
	    edges[i][j] = g.edges[i][j];
	}
    } 
}

//Function: Assignment Operator
//Inputs: Graph
//Returns: This
//Does: deletes the original graph and replaces it
template<class Vertex>
Graph<Vertex> & Graph<Vertex>::operator= (const Graph &source)
{
    if (this != &source)
    {
	deleteGraph();
	copyingGraph(source);
    }
    return *this;
}

//Destructor
//Inserts:none
//Returns:none
//Does:calls deleteGraph
template<class Vertex>
Graph<Vertex>::~Graph()
{
    deleteGraph();
}

//deleteGraph
//inputs: none
//returns: void
//Does: deletes the graph:
template<class Vertex>
void Graph<Vertex>::deleteGraph()
{
    for (int i = 0; i < num_vertices; i++)
    {
	delete [] edges[i];
    }
    delete [] edges;
    delete [] vertices;
    delete [] marks;
    delete [] path;
}

// Function: initialize_graph
// Input: integer, number of vertices
// Returns: void
// Does: dynamically allocates all memory
//       for a graph of num_v vertices 
//       without any vertices
//       and prepares all DFS,BFS variables
template<class Vertex>
void Graph<Vertex>::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }
}

// Function: add_vertex
// Parameters: Vertex, by value
// Returns: void
// Does: Add a new vertex to the end of the 2d array
//       Initializes every from/to edge to be NULL
template<class Vertex>
void Graph<Vertex>::add_vertex(Vertex v)
{
     vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++)
     {
         edges[curr_vertex][i] = NULL_EDGE;
         edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }

// Function: add_edge
// Parameters: Two vertices, and integer (weight)
// Returns: void
// Does: Adds an edge between the two vertices and 
//       assigns their weight equal to the given integer
//       (in case the edge did not exist) 
template<class Vertex>
void Graph<Vertex>::add_edge(Vertex f, Vertex t, string weight) const
{
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    if (edges[row][col] == NULL_EDGE)
        edges[row][col] = weight;
}


// Function: print_matrix
// Parameters: ostream
// Returns: void
// Does: Prints the 2d adjacency matrix of the graph
template <class Vertex>
void Graph<Vertex>::print_matrix(ostream & out) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
            out << edges[i][j] << " ";
        out << endl;
    }
}


// Function: clear_marks
// Parameters: none
// Returns: none
// Does: sets all the marks to be false
//       For algorithms that need to mark vertices (BFS, DFS)
template<class Vertex>
void Graph<Vertex>::clear_marks()
{
    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
    }
}

// Function: initialize_path
// Parameters: none
// Returns: none
// Does: sets every value in the predecessor path to be NULL edge
template<class Vertex>
void Graph<Vertex>::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

// Function: update_predecessor
// Parameters: Two vertices
// Returns: None
// Does: sets pred as the predecessor of curr in the path
//       (in case that curr did not have any predecessor)
//       Nothing otherwise.
template<class Vertex>
void Graph<Vertex>::update_predecessor(Vertex pred, Vertex curr)
{
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == pred)
            pred_index = i;
        if (vertices[i] == curr)
            curr_index = i;
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

// Function: report_path
// Parameters: ostream to print, start and end vertices
// Returns: none
// Does: finds path from start to end and prints it
//       uses the information stored on predecessor path 
template<class Vertex>
void Graph<Vertex>::report_path(ostream &out, Vertex start, Vertex end) const
{  
    Stack<Vertex> s;
    int index = index_is(vertices, end);
    s.push(vertices[index]);
    bool done = false;
    while (!done)
    {
        index = path[index];
        if (vertices[index] == start)
            done = true;
        s.push(vertices[index]);
    }

    int dist = s.get_size() - 1;
    out << start << " and " << end << " have a costar distance of "
	 << dist << endl;

    while (s.get_size() > 1)
    {
        Vertex v1 = s.top();
        s.pop();
	Vertex v2 = s.top();
	string movie = getEdge(v1, v2);
        out << v1 << " was in " << movie
	    << " with " << v2 << endl;
    }
}

//Function: getEdge
//inserts: 2 Vertices
//Returns: string
//Does: returns the string in between the vertices
template<class Vertex>
string Graph<Vertex>::getEdge(Vertex v1, Vertex v2) const
{
    int index1 = index_is(vertices, v1);
    int index2 = index_is(vertices, v2);

    return edges[index1][index2];
}

// Function: mark_vertex
// Parameters: Vertex
// Returns: none
// Does: sets the mark of the given vertex to true
template<class Vertex>
void Graph<Vertex>::mark_vertex(Vertex v)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

// Function: is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns true if the vertex is marked
//       false otherwise
template<class Vertex>
bool Graph<Vertex>::is_marked(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

// Function: is_vertex
// Parameters: vertex
// Returns: bool
// Does: returns true if vertex exists in the graph,
//       false otherwise.
template <class Vertex>
bool Graph<Vertex>::is_vertex(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

// Function: get_to_vertices
// Parameters: Vertex, queue of vertices by reference
// Returns: void
// Does: Finds all neighbors of the the given vertex
//       enqueues all of its neighbors to the queue
 template<class Vertex>
 void Graph<Vertex>::get_to_vertices(Vertex v, Queue<Vertex> &adj) const
 {
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++)
        if (edges[from][to] != NULL_EDGE)
            if (vertices[to] != vertices[from])
                   adj.enqueue(vertices[to]);
}


// wrapper function definitions
// Function: index_is
// Parameters: array of vertices, Vertex
// Returns: integer
// Does: Finds the target vertex in the list of vertices
//       returns the index of v
template<class Vertex>
int index_is(Vertex *vertices, Vertex v)
{
    int index = 0;
    while (!(v == vertices[index]))
        index++;
    return index;
}

template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
template class Graph<Actor>;
