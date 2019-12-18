/*****************************************************************************
*Daniel Meyer
*10/11/17
*Modulo.cpp
*This program tests the Modulo class written in Modulo.h and Modulo.cpp.
*... (Dear students, add a little more comment here!)
*CSE 330
*Fall 2017
******************************************************************************/

#include <iostream>
#include <cassert>

#include "Modulo.h"

using namespace std;

int main()
{
	Modulo o(5, -2), p(5, 6);
	cout << "o = " << o << " p = " << p << endl;
	p = p + 7;
	cout << "p = " << p << endl;
	p = p + 15;
	cout << "p = " << p << endl;
	++p;
	cout << "p = " << p << endl;
	p++;
	cout << "p = " << p << endl;

	Modulo q(p);
	cout << "q = " << q << endl;

	Modulo r(4), s;
	r = 1;
	s = s + r;
	cout << "r = " << r << " s = " << s << endl;
	s = r++;
	cout << "r = " << r << " s = " << s << endl;

	Modulo t(3, 2);
	t--;
	t--;
	cout << "t = " << t << endl;
	t--;
	cout << "t = " << t << endl;

	Modulo u;
	u = u - t;
	cout << "u = " << u << endl;

	Modulo v(5);
	v -= 3;
	cout << "v = " << v << endl;
	v += t;
	cout << "v = " << v << endl;

	return 0;
} // main