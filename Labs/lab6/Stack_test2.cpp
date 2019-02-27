/**********************************************************************
 * Eric Blasko
 * Stack_test2.cpp
 * 02/21/2018
 * This program test the functions of the class Stack.h. assert will 
 * verifiy that each function is working as intended
 **********************************************************************/
#include <iostream>
#include <cassert>
#include "Stack.h"
#include "../lab3/String.h"
#include "../lab4/Vector.h"
#include "../lab5/List.h"

using namespace std;

//Main function that test if Stack.h is working properly
int main()
{
    Stack<int, Vector> s1;
    assert(s1.size() == 0);
    assert(s1.empty());
    
    s1.push(16);
    assert(s1.size() == 1);
    assert(s1.top() == 16);
    
    s1.pop();
    assert(s1.size() == 0);
    
    s1.push(11);
    assert(s1.size() == 1);
    assert(s1.top() == 11);
    
    s1.push(22);
    assert(s1.size() == 2);
    assert(s1.top() == 22);

    s1.push(33);
    assert(s1.size() == 3);
    assert(s1.top() == 33);
    
    s1.pop();
    assert(s1.size() == 2);
    assert(s1.top() == 22);
    
    Stack<String, List> s2;
    s2.push("abc");
    s2.push("de");
    s2.pop();
    assert(s2.top() == "abc");

    cout << "SUCCESS\n";
}
