/*****************************************************************************
Kay Zemoudeh
Oct 10, 2017
Modulo.cpp

Implementation of Modulo class given in Modulo.h.

This file implements most of the usual operators for modulo arithmatic such
as =, +, -, ++, etc. along with the constructors.
... (Dear students, add a little more comment here!)
******************************************************************************/

/*****************************************************************************
*Daniel Meyer
*10/11/17
*Modulo.cpp
*Implementation of Modulo class given in Modulo.h.
*This file implements most of the usual operators for modulo arithmatic such
*as =, +, -, ++, etc. along with the constructors.
*
*CSE 330
*Fall 2017
******************************************************************************/

#include <cassert>
#include "Modulo.h"

using namespace std;

//Default constructor for Modulo class
Modulo::Modulo() : n(2), value(0) { }

//Constructor for creating a Modulo class from a givin divisor
Modulo::Modulo(int m) : n(m), value(0) { assert(n > 0); }

//Constructor for creating a Modulo class from an existing Modulo class
Modulo::Modulo(const Modulo & op) : n(op.n), value(op.value) { }

//Constructor for creating a Modulo class from a givin divisor and remainder
Modulo::Modulo(int m, int op)
{
	assert(m > 0);
	n = m;
	value = op;
	if (value >= 0)
		value = value % n;
	else
		while (value < 0)
			value += n;
}

//Overloaded operator for setting current divisor to new divisor and adjusting remainder
Modulo& Modulo::operator=(int op)
{
	value = op;
	value %= n;
	return *this;
}

//Overloaded operator for setting divisor to existing divisor and adjusting remainder
Modulo& Modulo::operator=(const Modulo & op)
{
	value = op.value;
	value %= n;
	return *this;
}

//Overloaded operator for adding current and new divisor and adjusting remainder
Modulo Modulo::operator+(int op)
{
	Modulo temp = *this;
	temp.value += op;
	temp.value %= temp.n;
	return temp;
}

//Overloaded operator for adding current and existing divisor and adjusting remainder
Modulo Modulo::operator+(const Modulo & op)
{
	Modulo temp = *this;
	temp.value += op.value;
	temp.value %= temp.n;
	return temp;
}

//Overlaoded pre-increment operator to account for new type
Modulo& Modulo::operator++()
{
	value++;
	value %= n;
	return *this;
}

//Overlaoded post-increment operator to account for new type
Modulo Modulo::operator++(int op)
{
	Modulo temp = *this;
	++(*this); // calls pre-increment above
	return temp;
}

//Overloaded operator to subtract divisor from current divisor and adjust the remainder
Modulo Modulo::operator-(int op)
{
	Modulo temp = *this;
	temp.value -= op;
	temp.value %= temp.n;
	return temp;
}

//Overloaded operator to subtract existing divisor from current divisor and adjust the remainder
Modulo Modulo::operator-(const Modulo &op)
{
	Modulo temp = *this;
	temp.value -= op.value;
	temp.value %= temp.n;
	return temp;
}

//Overlaoded pre-decrement operator to account for new type
Modulo& Modulo::operator--()  
{
	value--;
	value %= n;
	return *this;
}

//Overlaoded post-decrement operator to account for new type
Modulo Modulo::operator--(int op) 
{
	Modulo temp = *this;
	--(*this); // calls pre-decrement above
	return temp;
}

//Overloaded operator to add new and current divisors and set the result to existing operator and adjust the remainder
Modulo& Modulo::operator+=(int op)
{
	Modulo temp = *this;
	temp.value += op;
	temp.value %= temp.n;
	*this = temp;
	return *this;
}

//Overloaded operator to add existing and current divisors and set the result to existing operator and adjust the remainder
Modulo& Modulo::operator+=(const Modulo &op)
{
	Modulo temp = *this;
	temp.value += op.value;
	temp.value %= temp.n;
	*this = temp;
	return *this;
}

//Overloaded operator to subtract new and current divisors and set the result to existing operator and adjust the remainder
Modulo& Modulo::operator-=(int op)
{
	Modulo temp = *this;
	temp.value -= op;
	temp.value %= temp.n;
	*this = temp;
	return *this;
}

//Overloaded operator to subtract existing and current divisors and set the result to existing operator and adjust the remainder
Modulo& Modulo::operator-=(const Modulo &op)
{
	Modulo temp = *this;
	temp.value -= op.value;
	temp.value %= temp.n;
	*this = temp;
	return *this;
}

//Overloaded output operator to account for new Modulo class
ostream& operator<<(ostream&os, const Modulo &op)
{
	os << op.n << " remainder " << op.value;

	return os;
}
