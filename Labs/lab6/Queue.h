/*********************************************************************
 * Eric Blasko
 * Queue.h
 * 2/21/2018
 * This class contains functions similar to the STL library. As vectors
 * are not effecient with pop_front(), list is the default container 
 * for this class. Data in this class is followis First in First out
 ********************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include "../lab5/List.h"

using namespace std;

template <class T>
class Queue
{
public:
	bool empty() { return container.empty(); };         //check if empty
	unsigned int size() { return container.size(); };   //return size
	T & front() { return container.front(); };          //return front value
	T & back() { return container.back(); };            //return back value
	void push(const T & x) { container.push_back(x); }; //push to back lvalue
	void push(T && x) { container.push_back(move(x)); };//push to back rvalue
	void pop() {container.pop_front(); };               //pop front value
private:
	List<T> container;
};

#endif
