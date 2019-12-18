/*******************************************************************
Kay Zemoudeh
Oct 10, 2017
Modulo.h

A simple modulo n arithmetic class.
An instance of this class is a modulo n object where n > 0.
Value of a modulo n object is always >= 0 and < n.
... (Dear students, add a little more comment here!)
********************************************************************/

/*******************************************************************
*Daniel Meyer
*10/11/17
*Modulo.cpp
*A simple modulo n arithmetic class.
*An instance of this class is a modulo n object where n > 0.
*Value of a modulo n object is always >= 0 and < n.
*
*CSE 330
*Fall 2017
********************************************************************/
#ifndef MODULO_H
#define MODULO_H

#include <iostream>

using namespace std;

class Modulo {
	int n;
	int value;
public:
	Modulo();                  // default constructor, mod 2 (binary)
	Modulo(int m);             // mod m object
	Modulo(const Modulo & op); // copy constructor
	Modulo(int m, int op);     // mod m, init to op

	Modulo& operator=(int);
	Modulo& operator=(const Modulo &);

	Modulo operator+(int);
	Modulo operator+(const Modulo &);
	Modulo& operator++();  // pre-increment
	Modulo operator++(int); // post-increment

	Modulo operator-(int);
	Modulo operator-(const Modulo &);
	Modulo& operator--();  // pre-decrement
	Modulo operator--(int); // post-decrement

	Modulo& operator+=(int);
	Modulo& operator+=(const Modulo &);
	Modulo& operator-=(int);
	Modulo& operator-=(const Modulo &);

	friend ostream& operator<<(ostream&, const Modulo &);
}; // Modulo

#endif
