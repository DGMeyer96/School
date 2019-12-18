#ifndef VECTOR2_H
#define VECTOR2_H

// Vector2.h

using namespace std;

template <class T>
class Vector2
{
public:

   typedef T * iterator;

   Vector2();
   Vector2(unsigned int size);
   Vector2(unsigned int size, const T & initial);
   Vector2(const Vector2<T> & v);           // copy constructor
   ~Vector2();

   unsigned int capacity() const;         // return capacity of vector (in elements)
   unsigned int size() const;             // return the number of elements in the vector
   bool empty() const;

   iterator begin();                      // return an iterator pointing to the first element
   iterator end();                        // return an iterator pointing to one past the last element
   T & front();                           // return a reference to the first element
   T & back();                            // return a reference to the last element
   void push_back(const T & value);       // add a new element
   void pop_back();                       // remove the last element

   void reserve(unsigned int capacity);   // adjust capacity
   void resize(unsigned int size);        // adjust size

   T & operator[](unsigned int index);    // return reference to numbered element
   Vector2<T> operator=(const Vector2<T> &);

private:
   unsigned int my_size;
   unsigned int my_capacity;
   T * buffer;
};

template <class T>
Vector2<T>::Vector2()
{
	my_size = 0;
	my_capacity = 0;
	buffer = 0;
}

template <class T> 
Vector2<T>::Vector2(unsigned int size)
{
    my_size = size;
    my_capacity = size;
    buffer = new T[size];
    for(int i = 0; i < size; i++) {
        buffer[i] = T();
    }
}

template <class T> 
Vector2<T>::Vector2(unsigned int size, const T &initial)
{
    my_size = size;
    my_capacity = size;
    buffer = new T[size];
    for(int i = 0; i < size; i++) {
        buffer[i] = initial;
    }
}

template <class T> 
Vector2<T>::Vector2(const Vector2<T> &v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = v.buffer;
}

template <class T> 
Vector2<T>::~Vector2()
{
    delete[] buffer;
}

template <class T> 
unsigned int Vector2<T>::capacity() const
{
    return my_capacity;
}

template <class T> 
unsigned int Vector2<T>::size() const
{
    return my_size;
}

template <class T> 
bool Vector2<T>::empty() const
{
    return (my_size == 0);
}

template <class T>
typename Vector2<T>::iterator Vector2<T>::begin()
{
    return buffer;
}

template <class T> 
typename Vector2<T>::iterator Vector2<T>::end()
{
    return buffer + my_size;
}

template <class T> 
T& Vector2<T>::front()
{
    return buffer[0];
}

template <class T> 
T& Vector2<T>::back()
{
    return buffer[my_size - 1];
}

template <class T> 
void Vector2<T>::push_back(const T &value)
{
    if(my_size == my_capacity) {
        reserve(my_capacity + 5);
    }
    buffer[my_size++] = value;
}

template <class T> 
void Vector2<T>::pop_back()
{
    my_size--;
}

template <class T> 
void Vector2<T>::reserve(unsigned int capacity)
{
    my_capacity = capacity;
}

template <class T> 
void Vector2<T>::resize(unsigned int size)
{
    my_size = size;
    if(my_capacity < my_size)
    {
        reserve(my_size + 5);
    }
}

template <class T> 
T& Vector2<T>::operator[](unsigned int index)
{
    return buffer[index];
}

template <class T> 
Vector2<T> Vector2<T>::operator=(const Vector2<T> &v)
{
    my_size = v.size;
    my_capacity = v.my_capacity;
    delete[] buffer;
    buffer = new T[my_size];
    for(int i = 0; i < v.size; i++) {
        buffer[i] = v.buffer[i];
    }

    return *this;
}

#endif
