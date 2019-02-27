#ifndef VECTOR_H
#define VECTOR_H

/****************************************************************************************
 * Eric Blasko
 * Vector.h
 * 02/07/2018
 * This class replicates the functions of the vector class. It allows user to change
 * size of an array of elements as well as display, add, or remove elements from any
 * location of array. Templated class, so interface and implamincation are in same file
 ***************************************************************************************/

#include<cassert>
using namespace std;

template <class T>
class Vector
{
public:
    typedef T * iterator;

    Vector(unsigned int size = 0, const T & initial = T()); //default constructor
    Vector(const Vector<T> & v);                            //copy constructor
    Vector(Vector<T> && v);                                 //move constructor
    ~Vector();                                              //destructor
    Vector<T> & operator=(const Vector<T> & v);             //copy assignment
    Vector<T> & operator=(Vector<T> && v);                  //move assignment

    unsigned int capacity() const;                          //increase capacity
    unsigned int size() const;                              //change size
    bool empty() const;                                     //check if empty

    iterator begin();                   //return iterator to first element
    iterator end();                     //return iterator to past last element
    T & front();                        //return reference to first element
    T & back();                         //return reference to last element
    void push_back(const T & value);    //add element to end
    void pop_back();                    //remove element from end

    void reserve(unsigned int capacity);    //adjust capacity
    void resize(unsigned int size);         //adust size
    
    T & operator[](unsigned int index); 
    void erase(iterator);               //erase elem iterator points to(then shift)

private:
    unsigned int my_size;
    unsigned int my_capacity;
    T * buffer;
};

//default constructor
template <class T>
Vector<T>::Vector(unsigned int size, const T & initial)
{
    my_size = size;
    my_capacity = size;
    if(size == 0)
        buffer = nullptr;
    else
    {
        buffer = new T[my_size];
        assert(buffer != nullptr);
    }

    for(int i = 0; i < my_size; i++)
        buffer[i] = initial;
}

//copy constructor
template <class T>
Vector<T>::Vector(const Vector<T> &v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_capacity];
    assert(buffer != nullptr);

    for(int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
}

//move constructor
template <class T>
Vector<T>::Vector(Vector<T> && v) : my_size(v.my_size), my_capacity(v.my_capacity), buffer(v.buffer)
{
    v.my_size = 0;
    v.my_capacity = 0;
    v.buffer = nullptr;
}

//destructor
template <class T>
Vector<T>::~Vector()
{
    my_size = 0;
    my_capacity = 0;
    delete [] buffer;
}

//copy assignemnt
template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & v)
{
    T * temp = new T[v.my_capacity];
    assert(temp != nullptr);
    
    for(int i = 0; i < v.my_size; i++)
        temp[i] = v.buffer[i];

    delete [] buffer;
    buffer = temp;
    my_size = v.my_size;
    my_capacity = v.my_capacity;

    return *this;
}

//move assingment
template <class T>
Vector<T> & Vector<T>::operator=(Vector<T> && v)
{
    swap(my_size, v.my_size);
    swap(my_capacity, v.my_capacity);
    swap(buffer, v.buffer);
}

//increase to new capacity
template <class T>
void Vector<T>::reserve(unsigned int capacity)
{
    if(capacity <= my_capacity)
        return;
    T * new_buffer = new T[capacity];
    assert(new_buffer != nullptr);
    
    my_capacity = capacity;
    int size;
    for(size = 0; size < my_size; size++)
        new_buffer[size] = buffer[size];

    delete [] buffer;
    buffer = new_buffer;
}

//change to new size
template <class T>
void Vector<T>::resize(unsigned int size)
{
    if(size > my_capacity)
        reserve(size * 2);
    if(size > my_size)
        for(; my_size < size; my_size++)
            buffer[my_size] = T();
    else my_size = size;
}

//return capacity
template <class T>
unsigned int Vector<T>::capacity() const
{
    return my_capacity;
}

//return size
template <class T>
unsigned int Vector<T>::size() const
{
    return my_size;
}

//check if vector is empty
template <class T>
bool Vector<T>::empty() const
{
    if(my_size == 0)
        return true;
    return false;
}

//set iterator to start of vector
template <class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return buffer;
}

//set iterator to end of vector
template <class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return buffer + my_size;
}

//return value at front of vector
template <class T>
T& Vector<T>::front()
{
    return buffer[0];
}

//return value at end of vector
template <class T>
T& Vector<T>::back()
{
    return buffer[my_size-1];
}

//add element to back. Increase capacity if needed and increase size by one
template <class T>
void Vector<T>::push_back(const T& value)
{
    if(my_size == 0)
        reserve(10);
    if(my_size == my_capacity)
        reserve(my_capacity * 2);
    my_size += 1;
    buffer[my_size - 1] = value;
}

//remove last element and decrease size by one
template <class T>
void Vector<T>::pop_back()
{
    buffer[my_size - 1];
    my_size -= 1;
}

//return valuse at index 
template <class T>
T& Vector<T>::operator[](unsigned int index)
{
    return buffer[index];
}

//erase value at iterator position and shift remaining values left
template <class T>
void Vector<T>::erase(iterator it)
{
    T * temp = new T[my_size - 1];
    for(int i = 0; i < it; i ++)
        temp[i] = buffer[i];

    for(int i =it + 1; i < my_size; i++)
        temp[i] = buffer[i];

    my_size -= 1;
    delete [] buffer;
    buffer = temp;
}
#endif

