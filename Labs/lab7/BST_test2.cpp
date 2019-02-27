/*****************************************************************************************
 * Eric Blasko
 * BST_test2.cpp
 * 02/28/2018
 * This program test the different traversal options available int the BinarhSearchTree.h
 * class. The following traversals follow the pattersn: inorder(left,root,right), 
 * postorder(left,right,root), and preorder(root,left,right)
 *****************************************************************************************/ 
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

//Main function that test methods of BinarySearchTree.h
int main()
{
    BinarySearchTree<int> complete_tree;
    
    complete_tree.insert(20);
    complete_tree.insert(10);
    complete_tree.insert(30);
    complete_tree.insert(35);
    complete_tree.insert(25);
    complete_tree.insert(5);
    complete_tree.insert(15);
    complete_tree.printTree();

    cout << "Inorder Traversal\n";
    complete_tree.inorder();
    cout << endl;
    
    cout << "Postorder Traversal\n";
    complete_tree.postorder();
    cout << endl;
    
    cout << "Preorder Traversal\n";
    complete_tree.preorder();
    cout << endl;
}
