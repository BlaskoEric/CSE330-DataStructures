/*******************************************************************
 * Eric Blasko
 * Stack_test1.cpp
 * 02/21/2018
 * This program test the push and pop functions of Stack.h. values 
 * printed to console are values on top of stack
 *****************************************************************/
#include <iostream>
#include "../lab4/Vector.h"
#include "Stack.h"

using namespace std;

//Main function which pushs and pops value to stack
int main()
{
    Stack<int> s;
    s.push(5);
    s.push(6);
    cout << s.top() << endl;
    
    Stack<double, Vector> v;
    v.push(1.5);
    v.push(2.3);
    v.pop();
    cout << v.top() << endl;
}
