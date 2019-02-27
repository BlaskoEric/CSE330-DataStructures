/*********************************************************************************************************
 * Eric Blasko
 * BinarySearchTree.h
 * 02/28/2018
 * This class is a replica of the Binary Search tree in the standard library. Each node of the tree
 * has at most two children, with the left being of lesser value and the right being of higher value.
 * Most functions constist of a helper function to tell the main function where to start, which is always
 * at the root
 *********************************************************************************************************/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ostream>
#include <cassert>

using namespace std;

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree(): root{nullptr} {}
    BinarySearchTree(const BinarySearchTree & rhs) {root = clone(rhs.root);}
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree() {makeEmpty(root);}
    BinarySearchTree & operator=(const BinarySearchTree & rhs);
    BinarySearchTree & operator=(BinarySearchTree && rhs);

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    bool isEmpty() const {return root == nullptr;}
    void printTree(ostream & out = cout) const;

    void makeEmpty() {makeEmpty(root);}
    void insert(const Comparable & x) { insert(x,root);}
    void insert(Comparable && x) {insert(move(x),root);}
    void remove(const Comparable & x) {remove(x,root);}
    void inorder() const {inorder(root);}
    void postorder() const {postorder(root);}
    void preorder() const {preorder(root);}

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * left;
        BinaryNode * right;
      
        BinaryNode(const Comparable & theElement, BinaryNode * lt, BinaryNode * rt):
            element{theElement}, left{lt}, right{rt} {}
        BinaryNode(Comparable && theElement, BinaryNode * lt, BinaryNode * rt):
            element{move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode * root;

    void insert(const Comparable & x, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * & t);
    void remove(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode * t) const;
    BinaryNode * findMax(BinaryNode * t) const;
    bool contains(const Comparable & x, BinaryNode * t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const;
    BinaryNode * clone(BinaryNode * t) const;
    void inorder(BinaryNode * t) const;
    void postorder(BinaryNode * t) const;
    void preorder(BinaryNode * t) const;
};

//Copies entire contents of a binary search tree to create another identical instance
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone(BinaryNode * t) const
{
    if(t == nullptr)
        return nullptr;
    else
    {
        BinaryNode * newNode = new BinaryNode(t->element, clone(t->left), clone(t->right));
        assert(newNode);
        return newNode;
    }
}

//Move constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
}

//deletes every element in the BST starting with leaves, and working there way back to root. root
//is left null
template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * & t)
{
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

//Copies contents of source BST to current BST
template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs)
{
    BinarySearchTree copy = rhs;
    swap(*this, copy);
    return *this;
}

//Moves contents of source BST to current BST
template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(BinarySearchTree && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

//helper function which tells findMin to start at root
template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
    BinaryNode * t = findMin(root);
    
    if(t == nullptr)
    {
        BinaryNode * temp = new BinaryNode(Comparable(),nullptr,nullptr);
        return temp->element;
    }
    return t->element;
}

//helper function which tells findMax to start at root
template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
    BinaryNode * t = findMax(root);
    
    if(t == nullptr)
    {
        BinaryNode * temp =  new BinaryNode(Comparable(),nullptr,nullptr);
        return temp->element;
    }
    return t->element;
}

//Recursivly calls until reaches bottom left leaf. 
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

//Recursivly calls until reaches bottom right leaf.
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->right == nullptr)
        return t;
    return findMax(t->right);
}

//helper functions for printing contents of tree. Tells to start at root
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(ostream & out) const
{
    cout << "Print Tree\n";
    printTree(out,root, "", "");
}

//Recursivly goes through elements of tree to print to console. Each deeper call increases indent
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const
{
    if (t == nullptr)
        return;
    out << indent << tag << t->element << endl;
    indent += "    ";
    printTree(out, t->left, indent, "L ");
    printTree(out, t->right, indent, "R ");
}

//recursivily compares values to find correct place to insert in tree
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (x < t->element)
        insert(x, t->left);
    else if (x > t->element)
        insert(x, t->right);
    else
        ;
}

//recursivily compares value to find correct place to insert in tree
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode * & t)
{
    if(t == nullptr)
	    t = new BinaryNode(move(x),nullptr,nullptr);
    else if(x < t->element)
	    insert(move(x), t->left);
    else if(x > t->element)
	    insert(move(x), t->right);
    else
	;
}

//prints elements in tree in order (left,node,right)
template <typename Comparable>
void BinarySearchTree<Comparable>::inorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;
    inorder(t->left);
    cout << t->element << " ";
    inorder(t->right);
}

//prints elements in tree post order (left,right,node)
template <typename Comparable>
void BinarySearchTree<Comparable>::postorder(BinaryNode * t) const
{
    if(t == nullptr)
        return;
    postorder(t->left);
    postorder(t->right);
    cout << t->element << " ";
}

//prints elements in tree pre order (node, left, right)
template <typename Comparable>
void BinarySearchTree<Comparable>::preorder(BinaryNode * t) const
{
    if(t == nullptr)
        return;
    cout << t->element << " ";
    preorder(t->left);
    preorder(t->right);
}

//helper function which tells contain to start at root
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x) const
{
    return contains(x,root);
}

//recursively calls to one side of tree till found or at nullptr
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr)
	    return false;
    else if(x < t->element)
	    return contains(x,t->left);
    else if(x > t->element)
	    return contains(x,t->right);
    else
	    return true;
}

//first part searches tree bases on size of element. If element has two children, find
//the min value to the right of that node and assing to that position. then find that 
//node and remove. If one child move child to spot being deleted. If no children
//delete node. 
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr)
	    return;
    if(x < t->element)
	    remove(x,t->left);
    else if(x > t->element)
	    remove(x,t->right);
    else if(t->left != nullptr && t->right != nullptr)
    {
	    t->element = findMin(t->right)->element;
	    remove(t->element,t->right);
    }
    else
    {
	    BinaryNode *oldNode = t;
	    t = (t->left != nullptr) ? t->left : t->right;
	    delete oldNode;
    }
}


#endif
