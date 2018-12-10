/*
 * Filename: LinkedList.cpp
 * Contains: Implementation of the template LinkedList class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Actor.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor. Initializes empty
template<class E>
LinkedList<E>::LinkedList()
{
    head = NULL;
}

// Function: destructor
// Parameters: none
// Returns: nothing
// Does: Standard destructor. Releases all memory
template<class E>
LinkedList<E>::~LinkedList()
{
    NodeType<E> *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}


// Function: Assignment operator
// Parameters: a linked list
// Returns: another linked list
// Does: makes a copy of the given list 
//       into this. Returns reference to itself
template<class E>
LinkedList<E> & LinkedList<E>::operator = (const LinkedList<E> &l)
{
    NodeType<E> *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    if (l.head == NULL)
        head = NULL;
    else
    {
        try
        {
            head = new NodeType<E>;
            head->info = l.head->info;
            head->next = NULL;
            NodeType<E> *curr = head;
            NodeType<E> *orig = l.head;
            while (orig->next != NULL)
            {
                curr->next = new NodeType<E>;
                curr->next->info = orig->next->info;
                curr->next->next = NULL;
                orig = orig->next;
                curr = curr->next;
            }
        }
        catch (bad_alloc exception)
        {
            cerr << "Failed to copy list, out of memory\n";
        }
    }
    return *this;
}

// Function: Copy constructor
// Parameters: a linked list
// Returns: nothing
// Does: Standard copy constructor. Part of big three
template<class E>
LinkedList<E>::LinkedList(const LinkedList<E> &l)
{
    if (l.head == NULL)
        head = NULL;
    else
    {
        try
        {
            head = new NodeType<E>;
            head->info = l.head->info;
            head->next = NULL;
            NodeType<E> *curr = head;
            NodeType<E> *orig = l.head;
            while (orig->next != NULL)
            {
                curr->next = new NodeType<E>;
                curr->next->info = orig->next->info;
                curr->next->next = NULL;
                orig = orig->next;
                curr = curr->next;
            }
        }
        catch (bad_alloc exception)
        {
            cerr << "Failed to copy list, out of memory\n";
        }
    }
}

// Function: find
// Parameters: an item and a boolean (by reference)
// Returns: found item
// Does: searches for the item given by parameter in the list.
//       the reference boolean will be true or false accordingly
//       returns a copy of the object searched 
//       (or default element if it was not found)
template<class E>
E LinkedList<E>::find(E item, bool &found) const
{
    bool more_to_search;
    NodeType<E> *node;

    node = head;
    found = false;
    more_to_search = (node != NULL);

    while (more_to_search && !found)
    {
        if (item == node->info)
        {
            found = true;
            item = node->info;
            break;
        }
        node = node->next;
        more_to_search = (node != NULL);
    }
    return item;
}

// Function: print
// Parameters: none
// Returns: nothing
// Does: Prints each element of the list in cout,
//       Elements are separated by a space
template<class E>
void LinkedList<E>::print(ostream &out) const
{
    NodeType<E> *temp = head;
    while (temp != NULL)
    {
        out << temp->info << " ";
        temp = temp->next;
    }
    out << endl;
}

// Function: delete_value_at
// Input: integer, position to remove
// Returns: nothing
// Does: Removes the element at given position,
//       deallocates memory, and updates pointers
//       if given an invalid number it does nothing
template<class E>
void LinkedList<E>::delete_value_at(int index)
{
    if (get_length() == 0 || index >= get_length()) 
    {
        return;
    }

    NodeType<E> *temp, *current = head;
    int current_index = 1;

    // Special case: delete the head
    if (index == 0)
    {
        temp = current;
        head = head->next;
    }
    else
    {
        while (current_index < index)
        {
            current = current->next;
            current_index++;
        }
        temp = current->next;
        current->next = current->next->next;
    }
    delete temp;
}

// Function get_length, const
// Parameters: None
// Returns: integer
// Does: returns the number of elements in the list
template<class E>
int LinkedList<E>::get_length() const
{
    NodeType<E> *current = head;
    int count = 0;
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    return count;
}

// Function is_empty, const
// Parameters: None
// Returns: boolean
// Does: returns true if the list is empty
template<class E>
bool LinkedList<E>::is_empty() const
{
    return (head == NULL);
}

// Function is_full, const
// Parameters: None
// Returns: boolean
// Does: returns true if queue is full
//       (if memory cannot be allocated)
template<class E>
bool LinkedList<E>::is_full() const
{
    try
    {
        NodeType<E> *temp = new NodeType<E>;
        delete temp;
        return false;
    }
    catch (bad_alloc exception)
    {
        return true;
    }
}

// Function get_value_at, const
// Parameters: int, an index
// Returns: an item
// Does: returns the value in the list
//       located at the index position
//       returns FAIL value if not found
template<class E>
E LinkedList<E>::get_value_at(int index) const
{
    if (is_empty())
        throw EmptyList();
    NodeType<E> *current = head;
    int current_index = 0;

    while ((current_index < index) && (current != NULL)) 
    {
        current = current->next;
        current_index++;
    }
    return current->info;
}

// Function insert
// Input: Integer
// Returns: nothing
// Does: inserts item at the front of the list
template<class E>
void LinkedList<E>::insert(E value)
{
    if (is_full())
        throw FullList();
    NodeType<E> *temp = new NodeType<E>;
    temp->info = value;
    temp->next = head;
    head = temp;
}

// Function make_empty
// Parameters: none
// Returns: none
// Does: deletes list and deallocates all memory
template<class E>
void LinkedList<E>::make_empty()
{
    if (head!=NULL){
        NodeType<E> *temp = head;
        NodeType<E> *next_ptr = head->next;

        while (temp != NULL){
            delete temp;
            temp = next_ptr;

            if (next_ptr != NULL)
                next_ptr = next_ptr->next;
        }
    }
    head = NULL;
}

template class LinkedList<int>;
template class LinkedList<double>;
template class LinkedList<string>;
template class LinkedList<Actor>;
