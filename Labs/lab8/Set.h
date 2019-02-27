/*********************************************************************************************************
 * Eric Blasko
 * Set.h
 * 02/28/2018
 * This class is a replica of the class set in the standard library. While similar to the binary search
 * tree, each node also has a pointer to its parent, along with its pointers to its children. Iterators
 * allow for easy traversal of the tree.
 *********************************************************************************************************/

#ifndef SET_H
#define SET_H

#include <ostream>
#include <cassert>

using namespace std;

template <typename Comparable> class Set_iterator;

template <typename Comparable>
class Set
{
public:
    typedef Set_iterator<Comparable> iterator;
	
    Set(): root{nullptr}, theSize{0} {}
    Set(const Set & rhs) {root = clone(rhs.root); theSize = rhs.theSize;}
    Set(Set && rhs);
    ~Set() {clear(root);}
    Set & operator=(const Set & rhs);
    Set & operator=(Set && rhs);

    const Comparable & findMin() const;
    unsigned int count(const Comparable & x) const;
    bool empty() const {return root == nullptr;}
    void printTree(ostream & out = cout) const;

    void clear() {clear(root);}
    iterator insert(const Comparable & x) { insert(x,nullptr, root);}
    iterator insert(Comparable && x) {insert(move(x),nullptr,root);}
    void erase(const Comparable & x) {erase(x,root);}

    unsigned int size() {return theSize;}
    iterator begin() const;
    iterator end() const;
    iterator find(const Comparable &) const;
    void erase(iterator itr); 

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * parent;
        BinaryNode * left;
        BinaryNode * right;      

        BinaryNode(const Comparable & theElement, BinaryNode * p, BinaryNode * lt, BinaryNode * rt):
            element{theElement}, parent{p}, left{lt}, right{rt} {}
        BinaryNode(Comparable && theElement, BinaryNode * p, BinaryNode * lt, BinaryNode * rt):
            element{move(theElement)}, parent{p}, left{lt}, right{rt} {}
    };

    BinaryNode * root;
    unsigned int theSize;

    iterator insert(const Comparable & x, BinaryNode * p, BinaryNode * & t);
    iterator insert(Comparable && x, BinaryNode * p, BinaryNode * & t);
    void erase(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode * t) const;
    unsigned int count(const Comparable & x, BinaryNode * t) const;
    void clear(BinaryNode * & t);
    void printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const;
    BinaryNode * clone(BinaryNode * t) const;
    iterator find(const Comparable & x, BinaryNode * t) const;
    
friend class Set_iterator<Comparable>;
};

//Copies entire contents of a tree to create another identical instance
template <typename Comparable>
typename Set<Comparable>::BinaryNode * Set<Comparable>::clone(BinaryNode * t) const
{
    if(t == nullptr)
        return nullptr;
    else
    {
        BinaryNode * temp = new BinaryNode(t->element, nullptr, clone(t->left), clone(t->right));
        assert(temp);
        if(temp->left != nullptr)
            temp->left->parent = temp;
        if(temp->right != nullptr)
            temp->right->parent = temp;
        return temp;
    }
}

//Move constructor
template <typename Comparable>
Set<Comparable>::Set(Set && rhs): root{rhs.root}, theSize{rhs.theSize}
{
    rhs.root = nullptr;
    rhs.theSize = 0;;
}

//deletes every element in the tree starting with leaves, and working there way back to root. root
//is left null
template <typename Comparable>
void Set<Comparable>::clear(BinaryNode * & t)
{
    if(t != nullptr)
    {
        clear(t->left);
        clear(t->right);
        delete t;
    }
    t = nullptr;
    theSize = 0;
}

//Copies contents of source Set to current Set
template <typename Comparable>
Set<Comparable> & Set<Comparable>::operator=(const Set & rhs)
{
    Set copy = rhs;
    swap(*this, copy);
    return *this;
}

//Moves contents of source Set to current Set
template <typename Comparable>
Set<Comparable> & Set<Comparable>::operator=(Set && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

//helper function which tells findMin to start at root
template <typename Comparable>
const Comparable & Set<Comparable>::findMin() const
{
    BinaryNode * t = findMin(root);
    
    if(t == nullptr)
    {
        BinaryNode * temp = new BinaryNode(Comparable(),nullptr,nullptr,nullptr);
        return temp->element;
    }
    return t->element;
}

//Recursivly calls until reaches bottom left leaf. 
template <typename Comparable>
typename Set<Comparable>::BinaryNode * Set<Comparable>::findMin(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

//helper functions for printing contents of tree. Tells to start at root
template <typename Comparable>
void Set<Comparable>::printTree(ostream & out) const
{
    cout << "Print Tree\n";
    printTree(out,root, "", "");
}

//Recursivly goes through elements of tree to print to console. Each deeper call increases indent
template <typename Comparable>
void Set<Comparable>::printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const
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
typename Set<Comparable>::iterator Set<Comparable>::insert(const Comparable & x, BinaryNode * p, BinaryNode * & t)
{
    if(t == nullptr)
    {
        t = new BinaryNode(x,p, nullptr, nullptr);
        assert(t);
        theSize++;
	return t;
    }    
    else if (x < t->element)
        insert(x, t, t->left);
    else if (x > t->element)
        insert(x, t, t->right);
    else
        return t;
}

//recursivily compares value to find correct place to insert in tree
template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::insert(Comparable && x, BinaryNode * p, BinaryNode * & t)
{
    if(t == nullptr)
    {
	t = new BinaryNode(move(x), p, nullptr,nullptr);
        assert(t);
        theSize++;
	return t;
    }
    else if(x < t->element)
	    insert(move(x),t, t->left);
    else if(x > t->element)
	    insert(move(x),t, t->right);
    else
	return t;
}

//helper function which tells contain to start at root
template <typename Comparable>
unsigned int Set<Comparable>::count(const Comparable & x) const
{
    return count(x,root);
}

//recursively calls to one side of tree till found or at nullptr
template <typename Comparable>
unsigned int Set<Comparable>::count(const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr)
	    return false;
    else if(x < t->element)
	    return count(x,t->left);
    else if(x > t->element)
	    return count(x,t->right);
    else
	    return true;
}

//first part searches tree bases on size of element. If element has two children, find
//the min value to the right of that node and assing to that position. then find that 
//node and erase. If one child move child to spot being deleted. If no children
//delete node. 
template <typename Comparable>
void Set<Comparable>::erase(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr)
	    return;
    if(x < t->element)
	    erase(x,t->left);
    else if(x > t->element)
	    erase(x,t->right);
    else if(t->left != nullptr && t->right != nullptr)
    {
	    t->element = findMin(t->right)->element;
	    erase(t->element,t->right);
    }
    else
    {
	    BinaryNode *oldNode = t;
        BinaryNode *p = t->parent;
	    t = (t->left != nullptr) ? t->left : t->right;
        if(t != nullptr)
            t->parent = p;
	    delete oldNode;
        theSize--;
    }
}

//Returns an iterator to the begining of the Set which is a left slide
template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::begin() const
{
    BinaryNode *temp = root;
    while(temp && temp->left)
	temp = temp->left;
    return iterator(temp);
}

//Return an iterator to the end of Set which is a nullptr
template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::end() const
{
    return iterator(nullptr);
}

//helper function to find a value x in Set. Tells to start at root
template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::find(const Comparable & x) const
{
    return find(x,root);
}

//returns an iterator of were the value of x is found in the Set.
template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::find(const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr)
        return iterator{};
    else if(x < t->element)
        return find(x,t->left);
    else if(x > t->element)
        return find(x,t->right);
    else
        return iterator{t};
}

//uses iterator to find value to be deleted. if source node has children, redirect
//the next node to point back to the source nodes parent, then point the parent at
//the next node
template <typename Comparable>
void Set<Comparable>::erase(Set<Comparable>::iterator itr)
{
    if(itr == end())
        return;
    
    BinaryNode* temp;
    if(itr.current->left != nullptr && itr.current->right != nullptr) //two children
    {
        temp = itr.current->right;
        while(temp->left != nullptr)
        {
            temp = temp->left;
        }
        itr.current->element = temp->element;
    }
    else
        temp = itr.current;
    
    //adjust child pointer
    BinaryNode * p = temp->parent;
    if(p != nullptr)
    {
        if(p->left == temp)
            p->left = (temp->left != nullptr) ? temp->left : temp->right;
        else
            p->right = (temp->right != nullptr) ? temp->left : temp->right;
    }

    //adjust parent pointer
    if(temp->left != nullptr)
        temp->left->parent = p;
    else if(temp->right != nullptr)
        temp->right->parent = p;

    delete temp;
    theSize--;
}


/***************************************************************************************************
*class Set_iterator
**************************************************************************************************/

template <typename Comparable>
class Set_iterator
{
public:
    typedef typename Set<Comparable>:: BinaryNode BinaryNode;

    Set_iterator() = default;
    Set_iterator(const Set_iterator & it) = default;
    Set_iterator(Set_iterator && it) = default;
    ~Set_iterator() = default;
    Set_iterator & operator=(const Set_iterator & itr) = default;
    Set_iterator & operator=(Set_iterator && itr) = default;

    Set_iterator(BinaryNode * t): current{t} {}

    bool operator==(Set_iterator itr) const {return current == itr.current;}
    bool operator!=(Set_iterator itr) const {return current != itr.current;}
    Set_iterator & operator++();
    Set_iterator operator++(int);
    Comparable & operator*() {return current->element;}

protected:
    BinaryNode * current;

friend class Set<Comparable>;
};

//inorder traversal, pre-increment
template <typename Comparable>
Set_iterator<Comparable> & Set_iterator<Comparable>::operator++()
{
    if(current->right)
    {
        current = current->right;
        while(current->left)
            current = current->left;
    }
    else
    {
        BinaryNode * child = current;
        current = current->parent;
        while(current && current->right == child)
        {
            child = current;
            current = current->parent;
        }
    }
    return *this;
}

//inorder traversal, post-increment
template <typename Comparable>
Set_iterator<Comparable> Set_iterator<Comparable>::operator++(int)
{
    Set_iterator<Comparable> clone(*this);
    ++(*this);
    return clone;
}
#endif
