/*
 * Filename: Stack.h
 * Contains: Interface for template stack class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <exception>
#include "NodeType.h"
using namespace std;


#ifndef STACK_H_
#define STACK_H_

// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullStack : public exception {
public:
    const char *what() const throw() { return "NO MEMORY LEFT. CANNOT PUSH";}
    };

class EmptyStack : public exception {
public:
    const char *what() const throw() { return "OPERATION NOT ALLOWED ON AN EMPTY STACK"; } 
};


// Stack class uses templates. That is, we could use it to stack
// integers, strings or any other object.
template<class E> class Stack
{
public:
    Stack();

    // The Big Three!
    ~Stack();
    Stack(const Stack &);
    Stack & operator = (const Stack &);

    // Standard stack operations
    void push(E);
    void pop();
    E top() const;
    int get_size() const;

    bool is_full() const;
    bool is_empty() const;

    void make_empty();  //completely empties the stack

private:
    NodeType<E> *top_ptr;  
    int size;
};



#endif
