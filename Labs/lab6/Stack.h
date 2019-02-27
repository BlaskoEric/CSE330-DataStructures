/************************************************************************
 * Eric Blasko
 * Stack.h
 * 02/21/2018
 * This class contains functions silmilar to that of the STL library. 
 * The class can use containers of type vector and list, but list is the
 * default container. 
 ***********************************************************************/
#ifndef STACK_H
#define STACK_H

#include "../lab5/List.h"

using namespace std;

template <class T, template <class S> class Container = List>
class Stack
{
public:
    bool empty() const {return container.empty();};         //return if empty
    unsigned int size() const {return container.size();};   //return size
    void push(const T & x) {container.push_back(x);};       //push to top lvalue
    void push(T && x){container.push_back(move(x));};       //push to top rvalue
    void pop() {container.pop_back();};                     //pop off top
    T & top() {return container.back();};                   //return top value
private:
    Container<T> container;
};



#endif
