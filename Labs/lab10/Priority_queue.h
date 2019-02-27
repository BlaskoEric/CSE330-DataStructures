/**********************************************************************************
 * Eric Blasko
 * Priorit_queue.h
 * 03/19/2018
 * The class minics the prioriety_queue found in the STL. In this class the first
 * node in the list is always the highest valued element. This class uses a vector 
 * to hold data, but uses the concept of a complete binary tree to link parent nodes
 * to children. Child nodes are found by 2n+1 and 2n+2 in the index. Parent nodes
 * are found by (n-1)2. When nodes are inserted they are compareded to there
 * parent nod and swapped if needed. Similare process but reversed for poping first
 * element.
 *********************************************************************************/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

using namespace std;

template <class T>
class Priority_queue
{
public:
    // default constructor
    Priority_queue(): c() {}

    //copy constructor
	Priority_queue(const Priority_queue & p): c(p.c) {}
   
    //move constructor
    Priority_queue(Priority_queue && p): c(move(p.c)) {}
    
    //copy assigment 
    Priority_queue & operator=(const Priority_queue & p) {c = p.c; return *this;}
   
    //move assignment
    Priority_queue & operator=(Priority_queue && p) {swap(c, p.c); return *this;}
    
    //destrucctor
    ~Priority_queue() = default;

    //returns bool if vector is empty or not
    bool empty() {return c.empty();}

    //returns size of vector
    unsigned size() {return c.size();}
    
    //copy insert
    void push(const T & x);
    
    //move insert
    void push(T && x);

    //remove element at front of vector
    void pop();

    //returns element at front of vector
    T & top() {return c.front();}

    //returns element at front of vector
    const T & top() const {return c.front();}

private:
    vector<T> c;
};

//Inserts value at back of vector. the new value is campared with its parent and swapped
//if needed. done until its in right place.
template <class T>
void Priority_queue<T>::push(const T & x)
{
    c.push_back(x);
    unsigned i = c.size() - 1;
    unsigned parent = (i-1)/2;
    while(i>0 && c[i] > c[parent])
    {
        swap(c[i],c[parent]);
        i = parent;
        parent = (i-1)/2;
    }
}

//Inserts value at back of vector. The new value is compared with its parent and swapped
//if needed. done until its in right place.
template <class T>
void Priority_queue<T>::push(T && x) 
{
    c.push_back(move(x));
    unsigned i = c.size() - 1;
    unsigned parent = (i-1)/2;
    while(i>0 && c[i] > c[parent])
    {
        swap(c[i], c[parent]);
        i = parent;
        parent = (i-1)/2;
    }
}

//Assigns last element in vector to the front and pops last element. The root node is then
//compared and swapped with its children until node is in correct position
template <class T>
void Priority_queue<T>::pop()
{
    if(c.empty())
        return;

    c[0] = c.back();
    c.pop_back();
    unsigned i = 0;
    unsigned left = 1;
    unsigned right = 2;
    while(left < c.size())
    {
        unsigned biggest = left;
        if(right < c.size() && c[right] > c[left])
            biggest = right;
        if(c[i] < c[biggest])
        {
            swap(c[i], c[biggest]);
            i = biggest;
            left = (2*i)+1;
            right = (2*i)+2;
        }
        else
            break;
    }
}
        
#endif
