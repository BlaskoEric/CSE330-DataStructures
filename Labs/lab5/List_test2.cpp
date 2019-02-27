/*********************************************************************************
 * Eric Blasko
 * List_test2.cpp
 * 02/14/2018
 * This program test the functionality of the class List.h. Main functions to be 
 * tested are the push_back, pop_front, pop_back functions and iterator functions.
 * If program works properly it will display the contents of the list
 ********************************************************************************/ 

#include <iostream>
#include "List.h"

using namespace std;

//Main function that tests the methods of the class List.h
int main()
{
    List<int> l;
    
    l.push_back(44);
    l.push_back(33);
    l.push_back(11);
    l.push_back(22);

    List<int> m(l);
    
    List<int>::iterator itr(m.begin());
    for( ; itr != m.end(); itr++)
        cout << *itr << " ";
    cout << "\n------------\n";

    l.pop_back();
    m = l;
    for(itr = m.begin(); itr != m.end(); itr++)
        cout << *itr << " ";
    cout << "\n------------\n";
    
    m.pop_front();
    for(itr = m.begin(); itr != m.end(); itr++)
        cout << *itr << " ";
    cout << "\n------------\n";

    m.clear();
    for(itr = m.begin(); itr != m.end(); itr++)
        cout << *itr << " ";
    cout << endl;
}
