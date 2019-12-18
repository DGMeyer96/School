/*
Daniel Meyer
10-31-17
CSE 330
Fall 2017
Lab 5: List

Problem: Implement a class "List" that contains the functionality of a doubly-linked list template.

Algorithm: 3 primary classes are needed, the first being the List, a List_iterator 
used to navigate the List, and a Link for containing each element in the List. The List class 
contains functionality for accessing the front and back, pop/push front/back, insert element, erase
element, and an equality operator overload. The iterator class contains operator overloads for *, =,
==, !=, and post/pre increment/decrement. Each Link contains a value as well as a pointer to its 
next and previous link.

Status: 100%
Time Complexity: O(n)  Storage Complexity: O(n)
*/

#ifndef LIST_H
#define LIST_H

#include <algorithm>
using namespace std;

template <class T> class Link;
template <class T> class List_iterator;

//List class that contains each Link with a size value and pointer to first and last Link
template <class T>
class List
{
protected:
	Link<T> *first_link;
	Link<T> *last_link;
	unsigned int my_size;

public:
	typedef List_iterator<T> iterator;

	List();
	List(const List<T> &l);
	~List();

	void free();
	bool empty() const;
	unsigned int size() const;
	T& back() const;
	T& front() const;
	void push_front(const T &x);
	void push_back(const T &x);
	void pop_front();
	void pop_back();
	iterator begin() const;
	iterator end() const;
	void insert(iterator pos, const T &x); //insert x before pos
	void erase(iterator &pos);             //pos must be valid after erase() returns
	List<T> operator=(const List<T> &l);
};

//Default Constructor that sets first/last link and size to 0.
template <class T>
List<T>::List()
{
	first_link = 0;
	last_link = 0;
	my_size = 0;
}

//Overloaded constructor that sets current List to contents of existing List
template <class T>
List<T>::List(const List<T> &l)
{
	first_link = 0;
	last_link = 0;
	my_size = 0;
	for (Link<T> *current = l.first_link; current != 0; current = current->next_link)
		push_back(current->value);
}

//Destructor that calls free() function
template <class T>
List<T>::~List()
{
	free();
}

//Functions that removes all elements in List
template <class T>
void List<T>::free()
{
	while (my_size != 0)
	{
		pop_back();
	}
}

//Function to check if List is empty
template <class T>
bool List<T>::empty() const
{
	return (my_size == 0);
}

//Accessor function to return size of List
template <class T>
unsigned int List<T>::size() const
{
	return my_size;
}

//Returns value of the first element in List
template <class T>
T& List<T>::front() const
{
	return first_link->value;
}

//Returns value of the last element in List
template <class T>
T& List<T>::back() const
{
	return last_link->value;
}

//Adds element to front of List, sets new first_link, increments my_size
template <class T>
void List<T>::push_front(const T &x)
{
	Link<T> *new_link = new Link<T>(x);

	if (new_link == 0) {
		exit(1);
	}

	if (empty()) {
		first_link = last_link = new_link;
	}
	else {
		first_link->prev_link = new_link;	//n <- f
		new_link->next_link = first_link;	//n -> f
		first_link = new_link;				//n = f
	}

	my_size++;
}

//Adds element to back of List, sets new last_link, increments my_size
template <class T>
void List<T>::push_back(const T &x)
{
	Link<T> *new_link = new Link<T>(x);

	if (new_link == 0) {
		exit(1);
	}

	if (first_link == 0) {
		first_link = last_link = new_link;
	}
	else {
		last_link->next_link = new_link;//l -> n
		new_link->prev_link = last_link;//l <- n
		last_link = new_link;			//l = n
	}

	my_size++;
}

//Removes element from front of List, sets new first_link, decrements my_size
template <class T>
void List<T>::pop_front()
{
	Link<T> *new_link = first_link;
	first_link = first_link->next_link;

	if (empty()) {
		return;
	}
	else if (my_size == 1) {
		delete first_link;
		first_link = last_link = 0;
	}
	else if (first_link != 0) {
		first_link->prev_link = 0;
	}
	else {
		last_link = 0;
	}

	my_size--;
	delete new_link;
}

//Removes element from back of List, sets new last_link, decrements my_size
template <class T>
void List<T>::pop_back()
{
	Link<T> *new_link = last_link;
	last_link = last_link->prev_link;

	if (empty()) {
		return;
	}
	else if (my_size == 1) {
		delete last_link;
		first_link = last_link = 0;
	}
	else if (last_link != 0) {
		last_link->next_link = 0;
	}
	else {
		first_link = 0;
	}

	my_size--;
	delete new_link;
}

//Returns pointer to first element in List
template <class T>
typename List<T>::iterator List<T>::begin() const
{
	return iterator(first_link);
}

//Returns pointer to last element in List
template <class T>
typename List<T>::iterator List<T>::end() const
{
	return iterator(last_link);
}

//Inserts a new element before the pointer and increments my_size
template<class T>
inline void List<T>::insert(iterator pos, const T &x)
{
	Link<T> *new_link = new Link<T>(x);
	Link<T> *p = (pos.current_link)->prev_link;

	if (empty()) {
		return;
	}
	else if (pos == begin()) { //first element
		push_front(x);
	}
	else if (pos == ++end()) { //last element
		push_back(x);
	}
	else
	{
		new_link->next_link = (pos.current_link);
		new_link->prev_link = p;

		p->next_link = new_link;
		(pos.current_link)->prev_link = new_link;
		my_size++;
	}
}

//Removes element at pointer and adjusts previous and next element
template<class T>
inline void List<T>::erase(iterator &pos)
{
	if (empty()) {
		return;
	}
	else if (pos == begin()) { //first element
		pop_front();
	}
	else if (pos == end()) { //last element
		pop_back();
	}
	else {
		Link<T> *n = (pos.current_link)->next_link;
		Link<T> *p = (pos.current_link)->prev_link;

		n->prev_link = p;
		p->next_link = n;

		delete (pos.current_link);
	}

	my_size--;
}

//Overloaded assignment operator that erases current List content and adds contents from new List
template <class T>
List<T> List<T>::operator=(const List<T> &l)
{
	free();
	iterator temp = l.begin();

	while (my_size != l.my_size)
	{
		push_back((temp.current_link)->value);
		temp++;
	}

	return *this;
}



//Link class that contains data and pointers to neighboring Links
template <class T>
class Link
{
private:
	Link(const T &x) : value(x), next_link(0), prev_link(0) {}

	T value;
	Link<T> *next_link;
	Link<T> *prev_link;

	friend class List<T>;
	friend class List_iterator<T>;
};



//List_iterator class that is used to traverse the List
template <class T> class List_iterator
{
protected:
	Link<T> *current_link;

	friend class List<T>;

public:
	typedef List_iterator<T> iterator;

	List_iterator(Link<T> *source_link) : current_link(source_link) {}
	List_iterator() : current_link(0) {}
	List_iterator(List_iterator<T> *source_iterator) : current_link(source_iterator->current_link) { }

	T& operator*();  // dereferencing operator
	iterator operator=(const iterator &rhs);
	bool operator==(const iterator &rhs) const;
	bool operator!=(const iterator &rhs) const;
	iterator& operator++();  // pre-increment, ex. ++it
	iterator operator++(int); // post-increment, ex. it++
	iterator& operator--();  // pre-decrement
	iterator operator--(int); // post-decrement
};

//Overloaded dereference operator to get value stored in current Link
template <class T>
T& List_iterator<T>::operator*()
{
	return current_link->value;
}

//Overloaded assignment operator that sets value of current Link to the value in new Link
template <class T>
List_iterator<T> List_iterator<T>::operator=(const iterator &rhs)
{
	current_link = rhs.current_link;
	return this;
}

//Overloaded equal to operator that checks if two Links are equal
template <class T>
bool List_iterator<T>::operator==(const iterator &rhs) const
{
	return (current_link == rhs.current_link);
}

//Overloaded not equal to operator that checks if two Links are not equal
template <class T>
bool List_iterator<T>::operator!=(const iterator &rhs) const
{
	return (current_link != rhs.current_link);
}

//Overloaded pre-increment operator that increments pointer to next Link
template <class T>
List_iterator<T>& List_iterator<T>::operator++() // pre-increment
{
	current_link = current_link->next_link;
	return *this;
}

//Overloaded post-increment operator that increments pointer to next Link
template <class T>
List_iterator<T> List_iterator<T>::operator++(int) // post-increment
{
	List_iterator<T> new_link = current_link;
	current_link = current_link->next_link;
	return new_link;
}

//Overloaded pre-decrement operator that decrements pointer to previous Link
template <class T>
List_iterator<T>& List_iterator<T>::operator--() // pre-decrement
{
	current_link = current_link->prev_link;
	return *this;
}

//Overloaded post-decrement operator that decrements pointer to previous Link
template <class T>
List_iterator<T> List_iterator<T>::operator--(int) // post-decrement
{
	List_iterator<T> new_link = current_link;
	current_link = current_link->prev_link;
	return new_link;
}

#endif
