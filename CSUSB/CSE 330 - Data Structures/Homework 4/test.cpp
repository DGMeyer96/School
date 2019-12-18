// test.cpp - a simple test program for List.h with reverse_iterator

#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<int> l;

	l.push_back(44);  // list = 44
	l.push_back(33);  // list = 44, 33
	l.push_back(11);  // list = 44, 33, 11
	l.push_back(22);  // list = 44, 33, 11, 22

	List<int> m(l);

	cout << "List in order" << endl;
	for (int i = 0; i < m.size(); i++) {
		cout << m[i] << endl;
	}

	m.reverse(); // list = 22, 11, 33, 44
	cout << "List in order after being reversed" << endl;
	List<int>::iterator itr(m.begin());
	while (itr != m.end()) {
		cout << *itr << endl;
		itr++;
	}

	cout << "List in reverse order" << endl;
	List<int>::reverse_iterator rItr(m.rbegin());
	while (rItr != m.rend()) {
		cout << *rItr << endl;
		rItr++;
	}
	
	
	return 0;
}
