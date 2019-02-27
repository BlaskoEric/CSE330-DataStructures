/*****************************************************************************************
 * Eric Blasko
 * Set_test5.cpp
 * 03/07/2018
 * This program test the size(),empty(),insert() and erase() as well as the iterator 
 * methods for find(), post and pre increments and erase() from Set.h. After
 * performing some operations, contents will be displayed to console were user can
 * enter value to erase from Set
 *****************************************************************************************/ 

#include <iostream>

#include "Set.h"

using namespace std;

int main()
{
    Set<int> tree;
    Set<int>::iterator i;
    int n;

    tree.insert(100);
    tree.insert(50);
    tree.insert(110);
    tree.insert(40);
    tree.insert(75);
    tree.insert(30);
    tree.insert(60);
    tree.insert(80);
    tree.insert(55);
    tree.insert(90);
    tree.insert(59);
    tree.insert(57);
    tree.insert(56);
    tree.insert(58);

    tree.printTree();
    cout << "Iterate Over and Print Elements\n";
    for (i = tree.begin(); i != tree.end(); i++)
        cout << *i << " ";
    cout << endl;

    //Set<int> copy(tree); // save a copy
    cin >> n;
    while (n >= 0) {
        i = tree.find(n);
        tree.erase(i);
        //tree.erase(n); // test the other erase()

        tree.printTree();
        cout << "Iterate Over and Print Elements\n";
        for (i = tree.begin(); i != tree.end(); i++)
            cout << *i << " ";
        cout << endl;

        //tree = copy; // restore original tree
        cin >> n;
    }
}
