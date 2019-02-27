/********************************************************************************************************
 * Eric Blasko
 * BST_test1.cpp
 * 02/28/2018
 * This program test the methods of the class BinarySearcHTree.h. The program will demonstraight the 
 * insert, findMin, findMax, remove, and print methods. PrintTree will print elements according to the
 * depth that they are in the tree
 *******************************************************************************************************/
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

//Main function to test methods of BinarySearchTree.h
int main()
{
    BinarySearchTree<int> tree;

    tree.insert(6);
    tree.insert(8);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.printTree();

    cout << "Min = " << tree.findMin() << endl;
    cout << "Max = " << tree.findMax() << endl;

    cout << "Remove 2\n";
    tree.remove(2);
    tree.printTree();

    cout << "Contains 2? " << tree.contains(2) << endl;
    cout << "Contains 4? " << tree.contains(4) << endl;

    cout << "Copy Constructor\n";
    BinarySearchTree<int> copy(tree);
    cout << "Remove 6\n";
    copy.remove(6);
    copy.printTree();

    cout << "Inorder Traversal\n";
    copy.inorder();
    cout << endl;

    cout << "Clear tree\n";
    copy.makeEmpty();
    copy.printTree();
    cout << copy.findMin();
    cout << copy.findMax();
}
