/*********************************************************************************************************
 * Eric Blasko
 * BinaryTree.h
 * 03/12/18
 * This class imitates methods found in BST except that inserttion of data in not ordered. Instead of 
 * comparing left and right values, a level order traversal is used to insert a new item. this is done
 * through the use of a queue. This class also has methods to check if it passes for a BST, counts for
 * nodes, leaves, and full nodes
 ********************************************************************************************************/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <queue>
#include <cassert>
#include <string>
#include <ostream>
#include <limits>

using namespace std;

//Main class
template <typename Comparable>
class BinaryTree
{
public:
    BinaryTree(): root{nullptr} {}
    //helper methods
    void insert(const Comparable & x) {return insert(x,root);}      
    void insert(Comparable && x) {return insert(move(x),root);}
    int nodeCount()  {return nodeCount(root);}                 
    int leavesCount()  {return leavesCount(root);}            
    int fullNodeCount() {return fullNodeCount(root);}
    void printTree(ostream & out = cout) const; 
    bool isBST() {return isBST(root);}
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

    void insert(const Comparable &, BinaryNode * &);
    void insert(Comparable &&,BinaryNode * &);
    int nodeCount(BinaryNode *);
    int leavesCount(BinaryNode *);
    int fullNodeCount(BinaryNode * &);
    void printTree(ostream & out, BinaryNode* t, string indent, const string & tag) const;
    bool isBST(BinaryNode * t);
};

//Copy insert. uses queue to traverse through levels of binary tree to find where to insert
template <typename Comparable>
void BinaryTree<Comparable>::insert(const Comparable & x, BinaryNode * & t)
{
    BinaryNode * newNode = new BinaryNode(x,nullptr,nullptr);
    assert(newNode);

    if(t == nullptr)
    {
        t = newNode;
        return;
    }

    queue<BinaryNode *> q;
    q.push(t);

    while(!q.empty())
    {
        BinaryNode* temp = q.front();
        q.pop();
        
        if(!temp->left)
        {
            temp->left = newNode;
            break;
        }
        else
            q.push(temp->left);

        if(!temp->right)
        {
            temp->right = newNode;
            break;
        }
        else
            q.push(temp->right);
    }
}

//move insert. uses queue to traverse through levels of binary tre to find where to insert
template <typename Comparable>
void BinaryTree<Comparable>::insert(Comparable && x, BinaryNode * & t)
{
    BinaryNode * newNode = new BinaryNode(move(x),nullptr,nullptr);
    assert(newNode);
    
    if(t == nullptr)
    {
        t = newNode;
        return;
    }

    queue<BinaryNode *> q;
    q.push(t);

    while(!q.empty())
    {
        BinaryNode* temp = q.front();
        q.pop();

        if(!temp->left)
        {
            temp->left = newNode;
            break;
        }
        else
            q.push(temp->left);

        if(!temp->right)
        {
            temp->right = newNode;
            break;
        }
        else
            q.push(temp->right);
    }
}

//using a queue to traverse through the tree, count is increased before each element is popped
//off of queue
template <typename Comparable>
int BinaryTree<Comparable>::nodeCount( BinaryNode * t) 
{
    if(t == nullptr)
        return 0;

    queue<BinaryNode *> q;
    int count = 0;
    q.push(t);
    while(!q.empty())
    {
	count++;
        BinaryNode * temp = q.front();
        q.pop();
        
        if(temp->left != nullptr)   
            q.push(temp->left);
        if(temp->right != nullptr)
            q.push(temp->right);
    }
    return count;    
}

//using a queue to traverse through the tree, if temp has nullptrs for both left and
//right child, count is increased
template <typename Comparable>
int BinaryTree<Comparable>::leavesCount( BinaryNode * t) 
{
    if(t == nullptr)
        return 0;

    queue<BinaryNode *> q;
    int count = 0;
    q.push(t);
    while(!q.empty())
    {
        BinaryNode * temp = q.front();
        q.pop();
        
        if(temp->left == nullptr && temp->right == nullptr)
            count++;
        if(temp->left != nullptr)   
            q.push(temp->left);
        if(temp->right != nullptr)
            q.push(temp->right);
    }
    return count;    
}

//using a queue to traverse through the tree, if left and right are not nullptrs, count
//is increase.
template <typename Comparable>
int BinaryTree<Comparable>::fullNodeCount(BinaryNode * & t)
{   
    if(t == nullptr)
        return 0;

    queue<BinaryNode *> q;
    int count = 0;
    q.push(t);
    while(!q.empty())
    {
        BinaryNode * temp = q.front();
        q.pop();
        
        if(temp->left && temp->right)
            count++;
        if(temp->left != nullptr)   
            q.push(temp->left);
        if(temp->right != nullptr)
            q.push(temp->right);
    }
    return count;    
}

//helper method to call print tree
template <typename Comparable>
void BinaryTree<Comparable>::printTree(ostream & out) const
{
    cout << "Print Tree\n";
    printTree(out,root, "", "");
}

//recusively prints the entire contents of BinaryTree
template <typename Comparable>
void BinaryTree<Comparable>::printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const
{
    if(t == nullptr)
        return;
    out << indent << tag << t->element << endl;
    indent += "    ";
    printTree(out,t->left, indent, "L ");
    printTree(out,t->right, indent, "R ");
}

//using a queue to traverse throught tree, if child is not null, compare its element
//to the parent element. left should be less than parent, and right should be greater
//than parent 
template <typename Comparable>
bool BinaryTree<Comparable>::isBST(BinaryNode * t)
{
    if(t == nullptr)
        return true;

    queue<BinaryNode *> q;
    int count = 0;
    q.push(t);
    while(!q.empty())
    {
        BinaryNode * temp = q.front();
        q.pop();
        
        if(temp->left != nullptr)
            if(temp->left->element > temp->element)
                return false;
        if(temp->right != nullptr)
            if(temp->right->element < temp->element)
                return false;
        if(temp->left != nullptr)   
            q.push(temp->left);
        if(temp->right != nullptr)
            q.push(temp->right);
    }
    return true;    
}
#endif
