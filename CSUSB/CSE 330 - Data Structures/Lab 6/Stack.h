/*
Daniel Meyer
10-31-17
CSE 330
Fall 2017
Lab 6: Stack and Queue

Problem: Implement classes for "Stack" and "Queue" that have the functionality of their STL
counterparts but as template and container classes.

Algorithm: Using a default container of List from Lab 5, Stack contains functions for empty,
size, push, pop, and top. These functions are implemented using functions provided by the
container, i.e. List's push_back() and pop_back(). 

Status: 100%
Time Complexity: O(n)  Storage Complexity: O(n)
*/

#ifndef STACK_H
#define STACK_H

// Stack.h  -- a stack implemented as an adapter (of vector or list or ...)

#include "../Lab5/List.h"

using namespace std;

//Use the following line for STL containers.
//template <class T, template <class T, class = allocator<T> > class Container = list>
template <class T, template <class T> class Container = List>
class Stack
{
public:
	//We don't need a constructor or destructor because the Container has/should have one
	//Stack(): container() { }
	//~Stack() { ~container(); }
	bool empty() const;
	unsigned int size() const;
	void push(const T & x);
	void pop();
	T & top();

private:
	Container<T> container;
};

//Checks if the Stack is empty
template <class T, template <class T> class Container = List>
bool Stack<T, Container>::empty() const { return container.empty(); }

//Returns the number of elements in the Stack
template <class T, template <class T> class Container = List>
unsigned int Stack<T, Container>::size() const { return container.size(); }

//Pushes (back) an element on the Stack
template <class T, template <class T> class Container = List>
void Stack<T, Container>::push(const T &x) { container.push_back(x); }

//Pops (back) element from the Stack
template <class T, template <class T> class Container = List>
void Stack<T, Container>::pop() { container.pop_back(); }

//Returns value at the back of the Stack without removing it
template <class T, template <class T> class Container = List>
T& Stack<T, Container>::top() { return container.back(); }

#endif
