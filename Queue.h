/*
 * Filename: Queue.h
 * Contains: Interface for (template) queue class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "NodeType.h"
using namespace std;

#ifndef QUEUE_H_
#define QUEUE_H_

// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullQueue : public exception {
public:
  const char *what() const throw() { return "NO MEMORY LEFT. CANNOT INSERT";}
};

class EmptyQueue : public exception {
public:
  const char *what() const throw() { return "QUEUE IS EMPTY";}
};


template<class E>
class Queue
{
private:
    NodeType<E> *front;
    NodeType<E> *rear;

public:
    Queue();

    // The Big Three!
    ~Queue();
    Queue(const Queue &);
    Queue & operator = (const Queue &);

    //Standard operations on queue class
    void make_empty();
    void enqueue(E);
    void dequeue(E &);
    bool is_empty() const;
    bool is_full() const;
};

#endif
