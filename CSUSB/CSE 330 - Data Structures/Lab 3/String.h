/*****************************************************************
*Daniel Meyer
*String.h
*10/9/17
*Lab 3: String
*Header file for a cstring style string class with c++ string
*functionality without a null or return terminated end instead
*using the size to remain within the buffer.  Contains the
*necessary fuinctions and constructors such as returning the 
*size of the buffer and accessing indiviual elements in the char
*array.
*CSE 330
*Fall 2017
*****************************************************************/

#ifndef STRING_H
#define STRING_H

// String.h

#include <iostream>
#include <cstring>

using namespace std;

class String {

private:
    int size;
    char *buffer;
public:
    String();
    String(const String &s);
    String(const char *c);
    ~String();

    char* begin();
    char* end();
    int length();

    char& operator[](const unsigned int i);
    void operator=(const String &s);
    friend bool operator==(const String &s1, const String &s2);
    String& operator+=(const String &s);
    friend bool operator<=(const String &s1, const String &s2);
    friend bool operator<(const String &s1, const String &s2);
    friend bool operator>=(const String &s1, const String &s2);
    friend bool operator>(const String &s1, const String &s2);
    friend ostream &operator<<(ostream &os, const String &s2);
};

#endif
