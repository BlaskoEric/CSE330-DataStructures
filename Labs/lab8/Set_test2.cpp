/*****************************************************************************************
 * Eric Blasko
 * BST_test2.cpp
 * 03/07/2018
 * This program test the different traversal options available int the Set.h
 * class. The following traversals follow the pattersn: inorder(left,root,right), 
 * postorder(left,right,root), and preorder(root,left,right). later altercations to Set.h
 * will only have inorder traversal
 *****************************************************************************************/ 
#include <iostream>
#include "Set.h"
using namespace std;

//Main function that test methods of Set.h
int main()
{
    Set<int> complete_tree;
    
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
