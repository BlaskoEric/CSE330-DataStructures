/****************************************************************************************
 * Eric Blasko
 * Vector_test2.cpp
 * 02/07/2018
 * This program test the functionality of the templated class Vector.h. If any member
 * functions fail to perform as desired, assert will stop the program and display an 
 * error
 ***************************************************************************************/

#include <iostream>
#include <string>
#include <cassert>
#include "Vector.h"

using namespace std;

//Main function that test various instances of Vector.h and its member functions
//if member function fails to perform as desired, assert ends program with error
int main()
{
    Vector<int> v;

    v.reserve(2);
    assert(v.capacity() == 2);
    
    Vector<string> v1(2);
    assert(v1.capacity() == 2);
    assert(v1.size() == 2);
    assert(v1[0] == "");
    assert(v1[1] == "");
    
    v1[0] = "hi";
    assert(v1[0] == "hi");

    Vector<int> v2(2,7);
    assert(v2[1] == 7);
    
    Vector<int> v10(v2);
    assert(v10[1] == 7);
    
    Vector<string> v3(2,"hello");
    assert(v3.size() == 2);
    assert(v3.capacity() == 2);
    assert(v3[0] == "hello");
    assert(v3[1] == "hello");
    
    v3.resize(1);
    assert(v3.size() == 1);
    assert(v3[0] == "hello");
    
    Vector<string> v4 = v3;
    assert(v4.size() == 1);
    assert(v4[0] == v3[0]);
    v3[0] = "test";
    assert(v4[0] != v3[0]);
    assert(v4[0] == "hello");

    v3.pop_back();
    assert(v3.size() == 0);
    
    Vector<int> v5(7,9);
    Vector<int>::iterator it = v5.begin();
    while(it != v5.end())
    {
        assert(*it == 9);
        ++it;
    }
    
    Vector<int> v6;
    v6.push_back(100);
    assert(v6.size() == 1);
    assert(v6[0] == 100);
    v6.push_back(101);
    assert(v6.size() == 2);
    assert(v6[0] == 100);
    v6.push_back(101);

    cout << "SUCCESS\n";
}
