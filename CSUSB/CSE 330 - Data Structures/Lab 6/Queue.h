/*
Daniel Meyer
10-31-17
CSE 330
Fall 2017
Lab 6: Stack and Queue

Problem: Implement classes for "Stack" and "Queue" that have the functionality of their STL
counterparts but as template and container classes.

Algorithm: Using a default container of List from Lab 5, Queue contains functions for empty,
size, push, pop, and top. These functions are implemented using functions provided by the
container, i.e. List's push_back() and pop_front(). 

Status: 100%
Time Complexity: O(n)  Storage Complexity: O(n)
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "../Lab5/List.h"

using namespace std;

//Queue class with template and container type (List default type) and functions emulating FIFO Queue
template <class T, template <class T> class Container = List>
class Queue
{
public:
	bool empty() const;
	unsigned int size() const;
	void push(const T & x);
	void pop();
	T & top();

private:
	Container<T> container;
};

//Fuctions checking if the Queue is empty
template <class T, template <class T> class Container = List>
bool Queue<T, Container>::empty() const { return container.empty(); }

//Returns number of elements in the Queues
template <class T, template <class T> class Container = List>
unsigned int Queue<T, Container>::size() const { return container.size(); }

//Pushes (back) an element onto the Queue
template <class T, template <class T> class Container = List>
void Queue<T, Container>::push(const T &x) { container.push_back(x); }

//Pops (front) element from Queue 
template <class T, template <class T> class Container = List>
void Queue<T, Container>::pop() { container.pop_front(); }

//Returns value at the front of the Queue without removing it
template <class T, template <class T> class Container = List>
T& Queue<T, Container>::top() { return container.front(); }

#endif
