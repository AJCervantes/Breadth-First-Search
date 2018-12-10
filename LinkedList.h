/*
 * Filename: LinkedList.h
 * Contains: Interface of the template LinkedList class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <exception>
#include "NodeType.h"
using namespace std;

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

const int FAIL = -1;

// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullList : public exception{
public:
    const char * what() const throw() {return "Oh no, the list is full!\n";}; 
};

class EmptyList : public exception{
public:
    const char * what() const throw() {return "Sad, the list is empty!\n";}
};

template<class E> class LinkedList
{
 public:
    //The big three and an empty constructor
    LinkedList();
    LinkedList(const LinkedList &);
    ~LinkedList();
    LinkedList & operator =(const LinkedList &);

    //Standard linked list operations
	void insert(E);
	int get_length() const;
    bool is_empty() const;
    bool is_full() const;
    E get_value_at(int) const;

	void make_empty();             //empties the linked list
    void print(ostream &) const;   //writes the list in cout
    void delete_value_at(int);     //Removes element at given position  
    E find(E, bool &) const;       //Looks for E in the list


  private:
	NodeType<E> *head;
};

#endif
