/*****************************************************************************************
 * Eric Blasko
 * Set_test5.cpp
 * 03/07/2018
 * This program test all methods from class Set.h. Each test will include an assert which
 * will verify that the each method works as intended
 *****************************************************************************************/ 

#include <iostream>
#include <cassert>

#include "Set.h"

using namespace std;

int main()
{
    Set<int> s;
 
    assert(s.size() == 0);
    assert(s.empty());
 
    s.insert(10);
 
    Set<int>::iterator iter = s.begin();
    assert(*iter == 10);
 
    s.insert(6);
    s.insert(6);
 
    assert(s.count(6) == 1);
    assert(s.count(10) == 1);
    assert(s.count(12) == 0);
 
    iter = s.begin();
    assert(*iter == 6);
    ++iter;
    assert(*iter == 10);
    ++iter;
    assert(iter == s.end());
 
    s.insert(7);
    s.insert(9);
    s.insert(9);
    s.insert(8);
    s.insert(11);
    iter = s.begin();
    assert(*iter == 6);
    ++iter;
    assert(*iter == 7);
    ++iter;
    assert(*iter == 8);
    ++iter;
    assert(*iter == 9);
    ++iter;
    assert(*iter == 10);
    ++iter;
    assert(*iter == 11);
 
    Set<int> s2;
    s2.insert(3);
    s2.insert(7);
    s2.insert(-1);
    s2.insert(16);
    s2.insert(11);
    s2.insert(4);
 
    iter = s2.find(3);
    assert(*iter == 3);
    iter = s2.find(888);
    assert(iter == s2.end());
 
    s2.erase(7);
    iter = s2.begin();
    assert(*iter == -1);
    ++iter;
    assert(*iter == 3);
    ++iter;
    assert(*iter == 4);
    ++iter;
    assert(*iter == 11);
    ++iter;
    assert(*iter == 16);
    ++iter;
    assert(iter == s2.end());
 
    s2.erase(16);
    iter = s2.begin();
    assert(*iter == -1);
    ++iter;
    assert(*iter == 3);
    ++iter;
    assert(*iter == 4);
    ++iter;
    assert(*iter == 11);
    ++iter;
    assert(iter == s2.end());
 
    s2.erase(3);
    iter = s2.begin();
    assert(*iter == -1);
    ++iter;
    assert(*iter == 4);
    ++iter;
    assert(*iter == 11);
    ++iter;
    assert(iter == s2.end());
 
    s2.erase(11);
    iter = s2.begin();
    assert(*iter == -1);
    ++iter;
    assert(*iter == 4);
    ++iter;
    assert(iter == s2.end());
 
    s2.erase(-1);
    iter = s2.begin();
    assert(*iter == 4);
    ++iter;
    assert(iter == s2.end());
 
    s2.erase(4);
    iter = s2.begin();
    assert(iter == s2.end());
 
    cout << "All tests passed." << endl;
}
