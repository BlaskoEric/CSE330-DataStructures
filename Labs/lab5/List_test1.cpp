/******************************************************************************
 * Eric Blasko
 * List_test1.cpp
 * 02/14/2018
 * The program test the functions within the class List.h. Different ways of
 * adding and removing data to list objects will be test, returning assert error
 * if the test fails. If successful, end of test will print successs to console
 ******************************************************************************/

#include <iostream>
#include <cassert>
#include "List.h"

using namespace std;

//Main function that test function methods from the class List.h
int main()
{
    List<int> l;

    assert(l.size() == 0);
    assert(l.empty());

    l.push_front(44);
    assert(!l.empty());
    assert(l.front() == 44);
    assert(l.back() == 44);

    l.push_front(33);
    assert(l.size() == 2);
    assert(l.front() == 33);
    assert(l.back() == 44);

    l.push_front(22);
    List<int>::iterator it = l.begin();
    l.insert(it, 11);
    it = l.begin();
    assert(*it == 11);
    assert(*++it == 22);
    assert(*++it == 33);
    assert(*++it == 44);

    it = l.begin();
    ++it;
    ++it;
    ++it;
    l.insert(it, 38);
    List<int>::iterator it2 = l.begin();
    assert(*it2 == 11);
    assert(*++it2 == 22);
    assert(*++it2 == 33);
    assert(*++it2 == 38);
    assert(*++it2 == 44);
   
    l.pop_front();
    it2 = l.begin();
    assert(*it2 == 22);
    assert(*++it2 == 33);
    assert(*++it2 == 38);
    assert(*++it2 == 44);
 
    l.pop_back();
    List<int> copy = l;
    assert(copy.size() == 3);
    List<int>::iterator it3 = copy.begin();
    assert(*it3 == 22);
    assert(*++it3 = 33);

    copy.erase(it3);
    assert(copy.size() == 2);
    it3 = copy.begin();
    assert(*it3 == 22);
    assert(*++it3 == 38);

    cout << "SUCCESS\n";
}
