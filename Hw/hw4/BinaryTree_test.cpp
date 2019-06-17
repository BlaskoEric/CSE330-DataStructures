/****************************************************************************************
 * Eric Blasko
 * BinaryTree_test.cpp
 * 03/12/18
 * This program will test the methods in BinaryTree.h. After inserting a new value into
 * the tree, the program will print its count of nodes, leaves, and full nodes. It will
 * also state if it meets requirments for being a BST. Tree will be printed as to have
 * a visual of how the tree looks to compare to the data
 ***************************************************************************************/

#include <iostream>
#include "BinaryTree.h"

using namespace std;

//Function to print counts for nodes, leaves, and full nodes
template <typename p>
void print(BinaryTree<p> & t)
{
    cout << "# of Nodes: " <<  t.nodeCount() << " " << endl;
    cout << "# of Leaves: " << t.leavesCount() << " " << endl;;
    cout << "# of Full Nodes: " <<t.fullNodeCount() << endl;
}

//function to print if tree meets BST standards
template <typename p>
void isBST(BinaryTree<p> & t)
{
    if(t.isBST() == true)
        cout << "is Binary Search Tree" << endl;
    else
        cout << "is not Binary Search Tree" << endl;
    cout << endl;
}

//Main Function which test functionallty of BinaryTree.h
int main()
{
    BinaryTree<int> tree;

    cout << "Results while tree is empty";
    print(tree);
    
    cout << "\n Inserting 19, 3, 20, 1, 4 into tree and with results after each insert\n";
    tree.insert(19);
    print(tree);
    isBST(tree);

    tree.insert(3);
    print(tree);
    isBST(tree);

    tree.insert(20);
    print(tree);
    isBST(tree);

    tree.insert(1);
    print(tree);
    isBST(tree);

    tree.insert(4);
    print(tree);
    isBST(tree);

    tree.printTree();

    cout << "\nInserting 100, 6, 60, 75, 1, 18, 22 into tree with results after each insert\n";
    tree.insert(100);
    print(tree);
    isBST(tree);

    tree.insert(6);
    print(tree);
    isBST(tree);

    tree.insert(60);
    print(tree);
    isBST(tree);

    tree.insert(75);
    print(tree);
    isBST(tree);

    tree.insert(1);
    print(tree);
    isBST(tree);

    tree.insert(18);
    print(tree);
    isBST(tree);

    tree.insert(22);
    print(tree);
    isBST(tree);
    tree.printTree();

}
