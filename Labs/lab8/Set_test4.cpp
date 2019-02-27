/*****************************************************************************************
 * Eric Blasko
 * Set_test4.cpp
 * 03/07/2018
 * This program test the size(),empty(),insert() and erase() as well as the iterator 
 * methods for find(), post and pre increments and erase() from Set.h. After
 * performing some operations, results will be printed to console.
 *****************************************************************************************/ 

#include <iostream>

#include "Set.h"

using namespace std;

int main()
{
    Set<int> tree;

    cout << "Size = " << tree.size() << endl;
    cout << "Empty? " << tree.empty() << endl;

    tree.insert(6);
    tree.insert(8);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5); // duplicate, will be ignored
    tree.printTree();

    cout << "Count 5 = " << tree.count(5) << endl;
    cout << "Size = " << tree.size() << endl;
    cout << "Empty? " << tree.empty() << endl;
    cout << "Erase 2\n";
    tree.erase(2);
    tree.printTree();

    cout << "Size = " << tree.size() << endl;
    cout << "Empty? " << tree.empty() << endl;
    cout << "Count 2 = " << tree.count(2) << endl;
    cout << "Erase 6\n";
    tree.erase(6);
    tree.printTree();

    cout << "Copy Constructor\n";
    Set<int> copy(tree);
    copy.printTree();

    cout << "Copy Size = " << copy.size() << endl;
    cout << "Clear Copy\n";
    copy.clear();
    cout << "Size = " << copy.size() << endl;
    cout << "Empty? " << copy.empty() << endl;

    Set<int>::iterator i;
    cout << "Iterate Over and Print Elements\n";
    for (i = tree.begin(); i != tree.end(); i++)
        cout << *i << " ";
    cout << endl;

    cout << "Find, return iterator, advance it\n";
    i = tree.find(5);
    if (i != tree.end()) {
        cout << "Found 5\n";
        ++i;
        cout << "Next value = " << *i << endl;
    } else
        cout << "Didn't find 5\n";
    i = tree.find(6);
    if (i != tree.end())
        cout << "Found 6\n";
    else
        cout << "Didn't find 6\n";
    
    cout << "Insert 2, advance iter\n";
    i = tree.insert(2);
    cout << *++i << endl;
    tree.printTree();
    cout << "Size = " << tree.size() << endl;
    cout << "Insert 2 again\n";
    i = tree.insert(2);
    cout << *i << endl;
    cout << "Size = " << tree.size() << endl;

    cout << "Iterate Over and Print Elements\n";
    for (i = tree.begin(); i != tree.end(); i++)
        cout << *i << " ";
    cout << endl;

    cout << "Erase 2 with iter\n";
    i = tree.find(2);
    tree.erase(i);
    tree.printTree();

}
