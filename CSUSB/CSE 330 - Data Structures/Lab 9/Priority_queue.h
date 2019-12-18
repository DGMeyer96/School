#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Priority_queue.h  -- a priority_queue implemented as a heap

#include <vector>

using namespace std;

template <class T> 
class Priority_queue {
public:
   Priority_queue() : c() { }
   Priority_queue(const Priority_queue & p): c(p.c) { }
   Priority_queue & operator=(const Priority_queue & p) { c = p.c; return *this; }
   // vector destructor is automatically called when an obj of type Priority_queue is destroyed

   bool empty() { return c.empty(); }
   unsigned int size() { return c.size(); }
   void push(const T & x);
   void pop(); 
   T & top() { return c.front(); }
private:
   vector<T> c;
};

template <class T>
void Priority_queue<T>::push(const T &x)
{
    c.push_back(x);
    unsigned int n = c.size() - 1;
    unsigned int parent = (n - 1) / 2;

    while(c[n] < c[parent] && n > 0) {
        swap(c[n], c[parent]);
        n = parent;
        parent = (n - 1) / 2;
    }
}

template <class T>
void Priority_queue<T>::pop()
{
    if(empty()) {
        return;
    }

    c[0] = c.back(); //root = last value
    c.pop_back(); //remove last

    /*
    unsigned int n = 0; //root
    unsigned int lc = 1; //left child
    unsigned int rc = 2; //right child
    unsigned int largest;

    while(lc < c.size()) {
        largest = lc; //assume left, accounts for only 2 elements
        if(rc < c.size() && c[lc] < c[rc]) { //check if right child exists and left < right
            largest = rc; //largest = right
        }

        if(c[n] > c[largest]) {
            return;
        }
        else {
            swap(c[n], c[largest]);
        }
        

        //Setup for next run in loop
        n = largest;
        lc = (2 * n) + 1;
        rc = (2 * n) + 2;
    }
    */

    unsigned int n = 0;

    while(n < c.size()) {
        unsigned int largest = (n * 2) + 1;
        if(largest < c.size()) {
            if((largest + 1 < c.size()) &&  c[largest + 1] > c[n]) {
                largest++;
            }

            if(c[n] > c[largest]) {
                return;
            }
            else {
                swap(c[n], c[largest]);
            }
            n = largest;
        }
    }
}

#endif