/***********************************************************************************
 * Eric Blasko
 * List.h
 * 02/14/2018
 * This class minics the main functions found in the STL class list. There is two
 * nested class, const_iterator and iterator, along with a struct Node. 
 **********************************************************************************/ 

#ifndef LIST_H
#define LIST_H

using namespace std;

//Function for class list
template <typename Object>
class List
{
    struct Node;
    
    int theSize;
    Node *head;
    Node *tail;

    void init();

public:
    class const_iterator;
    class iterator;

    List() {init();}
    List(const List & rhs);
    List(List && rhs);
    ~List();
    List & operator=(const List & rhs);
    List & operator=(List && rhs);
    
    iterator begin() {return head->next;}
    const_iterator begin() const {return head->next;}
    iterator end() {return tail;}
    const_iterator end() const {return tail;}

    int size() const {return theSize;}
    bool empty() const {return theSize == 0;}
    
    void clear();
    
    Object & front() {return *begin();}
    const Object & front() const {return *begin();}
    Object & back() {return *--end();}
    const Object & back() const {return *--end();}

    void push_front(const Object & x) {insert(begin(),x);}
    void push_front(Object && x) {insert(begin(),move(x));}
    void push_back(const Object & x) {insert(end(), x);}
    void push_back(Object && x) {insert(end(),move(x));}

    void pop_front() {erase(begin());}
    void pop_back() {erase(--end());}

    iterator insert(iterator, const Object &);
    iterator insert(iterator, Object &&);

    iterator erase(iterator);
    iterator erase(iterator, iterator);
};

//Sets defaults during creation of new Node
template <typename Object>
void List<Object>::init()
{
    theSize = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

//copy constructor
template <typename Object>
List<Object>::List(const List & rhs)
{
    init();
    for(auto & x: rhs)
        push_back(x);
}

//move operator
template <typename Object>
List<Object> & List<Object>::operator=(List && rhs)
{
    swap(theSize, rhs.theSize);
    swap(head, rhs.head);
    swap(tail, rhs.tail);

    return *this;
}

//insert with a const object (copy)
template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator itr, const Object & x)
{
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{x, p->prev, p}};
}

//move constructor
template <typename Object>
List<Object>::List(List && rhs)
   :theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
   rhs.theSize = 0;
   rhs.head = nullptr;
   rhs.tail = nullptr;
}

//destructor
template <typename Object>
List<Object>::~List()
{
    clear();
    delete head;
    delete tail;
}
 
//copy operator
template <typename Object>
List<Object> & List<Object>::operator=(const List & rhs)
{
    List copy = rhs;
    std::swap(*this,copy);
    return *this;
}

//clear entire content of list
template <typename Object>
void List<Object>::clear()
{
    while(!empty())
        pop_front();
}

//insert with rvalue (move)
template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator itr, Object && x)
{
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{move(x),p->prev, p}};
}

//erase node at iterator.iterator returns pointer to next node
template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator itr)
{
    Node *p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
}

//erase from iterator to iterator
template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator from, iterator to)
{
    for( iterator itr = from; itr != to;)
        itr = erase(itr);

    return to;
}


/************************************************************************************************
 * Struct Node
 ***********************************************************************************************/

template <typename Object>
struct List<Object>::Node
{
    Object data;
    Node *prev;
    Node *next;
    
    Node(const Object & d = Object{}, Node * p = nullptr, Node * n = nullptr)
       : data{d}, prev{p}, next{n} {}
    Node(Object && d, Node *p = nullptr, Node *n = nullptr)
       : data{move(d)}, prev{p}, next{n} {}
};



/************************************************************************************************
 * Class const_iterator
 ***********************************************************************************************/

template <typename Object>
class List<Object>::const_iterator
{
public:
    const_iterator(): current{nullptr} {}
    const Object & operator*() const {return retrieve();}
    
    const_iterator & operator++();
    const_iterator operator++(int);
    
    const_iterator & operator--();
    const_iterator operator--(int);

    bool operator==(const const_iterator & rhs) const {return current == rhs.current;}
    bool operator!=(const const_iterator & rhs) const {return current != rhs.current;}

protected:
    Node *current;
    
    Object & retrieve() const {return current->data;}
    const_iterator(Node *p): current{p} {}

    friend class List<Object>;
};

//increase current position of iterator(post)
template <typename Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

//increase current position of iterator(pre)
template <typename Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this);
    return old;
}

//decrease current position of iterator(post)
template <typename Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

//decrease current position of iterator(pre)
template <typename Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --(*this);
    return old;
}


/*******************************************************************************************
 * Class iterator
 *******************************************************************************************/

template <typename Object>
class List<Object>::iterator: public List<Object>::const_iterator
{
public:
    iterator() {}
    Object & operator*() {return List<Object>::const_iterator::retrieve();}
    const Object & operator*() const {return List<Object>::const_iterator::operator*();}

    iterator & operator++();
    iterator operator++(int);
    
    iterator & operator--();
    iterator operator--(int);

protected:
    iterator(Node *p): List<Object>::const_iterator{p} {}
    friend class List<Object>;
};

//increase current position of iterator(post)
template <typename Object>
typename List<Object>::iterator & List<Object>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

//increase current position of iterator(pre)
template <typename Object>
typename List<Object>::iterator List<Object>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

//decrease current postion of iterator(post)
template <typename Object>
typename List<Object>::iterator & List<Object>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

//decrease current position of iterator(pre)
template <typename Object>
typename List<Object>::iterator List<Object>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;
}


#endif




