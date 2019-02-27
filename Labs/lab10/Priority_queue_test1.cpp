/********************************************************************
 * Eric Blasko
 * Priority_queue_test1.cpp
 * 03/14/2018
 * The program test the methods found in Priority_queue.h. User inputs
 * values into queue, copied to another instance, then printed and
 * popped from queue.
 ********************************************************************/

#include <iostream>
#include "Priority_queue.h"

using namespace std;

//Main function to test methods of Priority_queue.h
int main()
{
    Priority_queue<int> p, q, pq;
    
    int x;
    while(cin >> x)
        p.push(x);
    
    pq = q = p;

    while(!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}
