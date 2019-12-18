/*
Daniel Meyer
10-31-17
CSE 330
Fall 2017
Lab 6: Stack and Queue

Problem: Implement classes for "Stack" and "Queue" that have the functionality of their STL
counterparts but as template and container classes.

Algorithm: 

Status: 100%
Time Complexity: O(n)  Storage Complexity: O(n)
*/

#include <iostream>
#include <cassert>
#include "Queue.h"
#include "../Lab3/String.h"
#include "../Lab4/Vector.h"
#include "../Lab5/List.h"

using namespace std;

//Test class using instances of Queue as an int and double with default List container,
//as well as an instance using the String class from Lab 3 with the default List container.
int main()
{
	Queue<int> i;      // uses List as the default container
	i.push(5);
	i.push(6);
	cout << i.top() << endl;

	Queue<String, List> s; // uses Vector as the container
	s.push("abc");
	s.push("de");
	s.pop();
	cout << s.top() << endl;

	Queue<double> d;
	d.push(123.45);
	d.push(78.90);
	d.push(1.2);
	d.push(3.4);

	int size = d.size();
	for (int i = 0; i < size; i++)
	{
		cout << d.top() << endl;
		d.pop();
	}

	return 0;
}
