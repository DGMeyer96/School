/*****************************************************************
*Daniel Meyer
*String.cpp
*10/9/17
*Lab 3: String
*Implementation of String class in String.h
*This file implements the functions needed to use a non-null
*terminated cstring style class with c++ string functionality
*using a size value and char array.
*CSE 330
*Fall 2017
*****************************************************************/

#include "String.h"

using namespace std;

//Default constructor for String class
String::String()
{
    size = 0;
    buffer = '\0';
}

//Constructor for creating a String using an existing String class
String::String(const String &s)
{
    buffer = s.buffer;
    size = s.size;
}

//Constructor for creating a String from a char array
String::String(const char *c)
{
    int temp_size = strlen(c);
    buffer = new char[temp_size];
    for (int i = 0; i < temp_size; i++) {
        buffer[i] = c[i];
    }
    size = temp_size;
}

//String deconstructor
String::~String()
{
    delete[] buffer;
}

//Used to return a pointer to the beginning of the array
char* String::begin()
{
    return &this->buffer[0];
}

//Used to return a pointer to the end of the array
char* String::end()
{
    return &this->buffer[size - 1];
}

//Return the size of the char buffer
int String::length()
{
    return size;
}

//Overloaded operator for accessing indivual chars in String class
char& String::operator[](const unsigned int i)
{
    return buffer[i];
}

//Overloaded operator for assigning existing String class to existing one
void String::operator=(const String &s)
{
    size = s.size;
    buffer = new char[size];
    for (int i = 0; i < size; i++) {
        buffer[i] = s.buffer[i];
    }
}

//Overloaded operator to check equality of two String class's lengths & contents
bool operator==(const String &s1, const String &s2)
{
    if (s1.size == s2.size) {
        for (int i = 0; i < s1.size; i++) {
            if (s1.buffer[i] != s2.buffer[i])
                return false;
        }
        return true;
    }
    return false;
}

//Overloaded operator for added a String class to existing one
String& String::operator+=(const String &s)
{
    int temp_size = size + s.size;
    char *temp = new char[temp_size];
    int i = 0;
    for (; i < size; i++) {
        temp[i] = buffer[i];
    }
    for (int j = 0; j < s.size; j++, i++) {
        temp[i] = s.buffer[j];
    }

    delete[] buffer;
    size = temp_size;
    buffer = temp;
    return *this;
}

//Overlaoded operator to check if two Strings are equal or less than
bool operator<=(const String &s1, const String &s2)
{
    return (s1 < s2 || s1 == s2);
}

//Overlaoded operator to check if two Strings are less than
bool operator<(const String &s1, const String &s2)
{
    return (s1.size < s2.size);
}

//Overlaoded operator to check if two Strings are equal or greater than
bool operator>=(const String &s1, const String &s2)
{
    return (s1 < s2 || s1 == s2);
}

//Overlaoded operator to check if two Strings are greater than
bool operator>(const String &s1, const String &s2)
{
    return (s1.size < s2.size);
}

//Overlaoded output operator to handle new String class
ostream &operator<<(ostream &os, const String &s)
{
    for (int i = 0; i < s.size; i++)
    {
        os << s.buffer[i];
    }

    return os;
}