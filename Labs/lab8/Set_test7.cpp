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

    cout << i.begin();
    cout << i.end();
    assert(i.find(100) == 100);

    tree.insert(110);
    tree.insert(40);

    cout << i.begin();
    cout << i.end();

    tree.insert(75);
    tree.insert(30);

    cout << i.begin();
    cout << i.end();

    tree.insert(60);
    tree.insert(80);

    cout << i.begin();
    cout << i.end();

    tree.insert(55);
    tree.insert(90);

    cout << i.begin();
    cout << i.end();

    tree.insert(59);
    tree.insert(57);

    cout << i.begin();
    cout << i.end();

    tree.insert(56);
    tree.insert(58);
}
