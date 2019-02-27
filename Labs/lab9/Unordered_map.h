/*************************************************************************************************
 * Eric Blasko
 * Unordered_map.h
 * 03/14/2018
 * This class imitates the methods found in the unordered map found in STL. This class utilizes
 * hash functions which is used to index data within a vector of linked list. therefor there
 * are three classes within this code, the class for the hash function, the class for 
 * unordered maps, and a class for hash iterator
 ***********************************************************************************************/
#ifndef UNORDERED_H
#define UNORDERED_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

//function used to override the stream output
template<class Key, class Value>
ostream & operator<<(ostream & out, const pair<Key, Value> & in)
{
    out << "(" << in.first << ":" << in.second << ")";
    return out;
}

/***********************************************************************************************
 * Class Hasher
 ***********************************************************************************************/
template <typename Key>
class Hasher
{
public:
    unsigned operator()(const Key & k) const;   
};

//Overloads () operator to take in string to be able to hash and return value
template <>
class Hasher<string>
{
public:
    unsigned operator()(const string & k) const
    {
        unsigned hashVal = 0;
        
        for(char ch: k)
            hashVal = 37 * hashVal + ch;

        return hashVal;
    }
};

//Overloads () operator to take in unsigned value to be used in hash and returns value
template <>
class Hasher<unsigned>
{
public:
    unsigned operator()(const unsigned & k) const
    {
        return k%37;
    }
};

//forward prototype
template <typename Key, typename Value, template <typename> class Hash> class Hash_iterator;

//hash table of "num_buckets" buckets. eash bucket is an stl list of pairs
template <typename Key, typename Value, template <typename> class Hash = Hasher>
class Unordered_map
{
private:
    unsigned num_buckets;
    vector<list < pair < Key, Value> > > bucket;
    Hash<Key> hashFunc;
    unsigned theSize;
    
    //set bucket index based on key, if key is found in bucket[index] return true and set i
    bool find(const Key & key, unsigned & index, typename list< pair< Key, Value > >::iterator & i)
    {
        index = hashFunc(key)%num_buckets;
    
        for(i = bucket[index].begin(); i != bucket[index].end(); i++)
            if(i->first == key)
                break;

        if(i != bucket[index].end())
            return true;
        return false;
    }

public:

    typedef Hash_iterator<Key, Value, Hash> iterator;

    //default constructor
    Unordered_map(unsigned count = 11): num_buckets(count), hashFunc(Hash<Key>()), theSize(0)
    {
        bucket = vector< list < pair < Key, Value > > >(num_buckets);
    }

    //destructor. calls default destructor for vector and list
    ~Unordered_map() = default;

    //copy constructor
    Unordered_map(const Unordered_map & rhs): num_buckets{rhs.num_buckets}, hashFunc{rhs.hashFunc}, theSize{0}
    {
        bucket = vector<list<pair<Key,Value>>>(num_buckets);
        
        typename list<pair<Key,Value>>::const_iterator j;
        for(int i = 0; i < rhs.num_buckets; i++)
            for(j = rhs.bucket[i].begin(); j != rhs.bucket[i].end(); j++)
                insert(*j);
    }

    //Overloaded assignment operator, move
    Unordered_map(Unordered_map && rhs): num_buckets{rhs.num_buckets}, bucket{move(rhs.bucket)}, hashFunc{rhs.hashFunc}, theSize{rhs.theSize} {}

    Unordered_map & operator=(const Unordered_map & rhs)
    {
        Unordered_map<Key, Value, Hash> copy{rhs};
        swap(*this, copy);
        return *this;
    }

    //Overloaded assingment operator, copy
    Unordered_map & operator=(Unordered_map && rhs)
    {
        swap(num_buckets, rhs.num_buckets);
        swap(bucket, rhs.bucket);
        swap(hashFunc, rhs.hashFunc);
        swap(theSize, rhs.theSize);
        return *this;
    }

    //returns number of buckets in vector
    unsigned bucket_count()
    {
        return num_buckets;
    }

    //returns overall size
    unsigned size()
    {
        return theSize;
    }

    //returns size of bucket in linked list
    unsigned bucket_size(unsigned n)
    {
        if(n >= num_buckets)
            return 0;

        return bucket[n].size();
    }

    //Overload [] operator to take in Key values, looks to see if value is already in buckets, if it
    //is return its value, if not insert it to front of linked list. copy method
    Value & operator[](const Key & key)
    {
        unsigned index;
        typename list<pair<Key, Value>>::iterator i;
    
        if(find(key,index,i))
            return i->second;

        bucket[index].push_front(pair<Key, Value>(key, Value()));
        theSize++;
        return bucket[index].front().second;
    }

    //Overload [] operator to take in Key value, looks to see if value is already in buckets, if it
    //is return its value, if not insert it to front of linked list. move mehtod
    Value & operator[](Key && key)
    {
        unsigned index;
        typename list<pair<Key, Value>>::iterator i;
    
        if(find(key,index,i))
            return i->second;

        bucket[index].push_front(pair<Key, Value>(move(key), Value()));
        theSize++;
        return bucket[index].front().second;
    }

    //looks to see if key is in buckets first and replaces value if found. if not, insert value into 
    //front of linked list at index. copy method
    void insert(const pair<Key, Value> & r)
    {
        unsigned index;
        typename list<pair<Key, Value>>::iterator i;

        if(find(r.first, index, i))
            *i = r;
        else
        {
            bucket[index].push_front(r);
            theSize++;
        }
    }
    
    //looks to see if key is in buckets first and replaces value if found. if not, insert value into
    //front of linked list at index. move method
    void insert(pair<Key, Value> && r)
    {
        unsigned index;
        typename list<pair<Key, Value>>::iterator i;

        if(find(r.first, index, i))
            *i = move(r);

        else 
        {
            bucket[index].push_front(move(r));
            theSize++;
        }
    }
    
    //prints all contents of each bucket
    void print()
    {
        for(int i = 0; i < num_buckets; i++)
        {
            cout << "bucket[" << i << "] size=" << bucket_size(i) << " ";

            typename list<pair<Key, Value>>::iterator j;
            for(j = bucket[i].begin(); j!= bucket[i].end(); j++)
                cout << *j << " ";
            cout << endl;
        }
    }

    //searches for were data first occurs in vector and returns that pos. Else it returns the end
    //of the vector
    iterator begin()
    {
        iterator iter(this);
    
        unsigned index = 0;
        while(index < num_buckets and bucket[index].size() == 0)
            ++index;
        if(index < num_buckets)
        {
            iter.bucket_index = index;
            iter.current = bucket[index].begin();
        }
        else
        {
            iter.bucket_index = num_buckets-1;
            iter.current = bucket[num_buckets-1].end();
        }
        return iter;
    }
    
    //returns the last pos of the vector and linked list.
    iterator end()
    {
        iterator iter(this);
        iter.bucket_index = num_buckets-1;
        iter.current = bucket[num_buckets-1].end();
        return iter;
    }

    //searches for key in entire vector and linked list. if found set iterator and index,
    //else return end of list
    iterator find(const Key & key)
    {
        unsigned index;
        iterator iter(this);
        typename list<pair<Key,Value>>::iterator i;
        if(find(key, index, i))
        {
            iter.bucket_index = index;
            iter.current = i;
        }
        else
        {
            iter.bucket_index = num_buckets-1;
            iter.current = bucket[num_buckets-1].end();
        }
        return iter;
    }

    //uses search to find if key is present, if it is find returns index and i to be able
    //to delete data
    void erase(const Key & key)
    {
        unsigned index;
        typename list<pair<Key,Value>>::iterator i;
        if(find(key,index,i))
        {
            bucket[index].erase(i);
            theSize--;
        }
    }

    //allocate new vector and rehash all previous data into new vector
    void rehash(unsigned x)
    {
        Unordered_map<Key,Value,Hash>copy(x);
        iterator current, i = begin();
        while(i != end())
        {
            current = i++;
            copy.insert(*current);
        }
        *this = move(copy);
    }
friend class Hash_iterator<Key,Value,Hash>;
};

/*************************************************************************
* Hash_iterator
*************************************************************************/
template <typename Key, typename Value, template <typename> class Hash>
class Hash_iterator
{
    Unordered_map<Key, Value, Hash> *theMap;
    typename list< pair< Key, Value> >::iterator current;
    unsigned bucket_index;
public:
    //default constructor
    Hash_iterator(Unordered_map<Key, Value, Hash> * m = nullptr): theMap{m} {}
    
    //destructor
    ~Hash_iterator() = default;
    
    //copy constructor
    Hash_iterator(const Hash_iterator & iter): theMap{iter.theMap}, current{iter.current}, bucket_index{iter.bucket_index} {}
    
    //move constructor
    Hash_iterator(Hash_iterator && iter): theMap{iter.theMap}, current{move(iter.current)}, bucket_index{iter.bucket_index} {iter.theMap = nullptr;}
    
    //overload assingment operator. copy method
    Hash_iterator & operator=(const Hash_iterator & iter)
    {
        theMap = iter.theMap;
        current = iter.current;
        bucket_index = iter.bucket_index;
        return *this;
    }
    
    //overload assingment operator. move method
    Hash_iterator & operator=(Hash_iterator && iter)
    {
        swap(theMap, iter.theMap);
        swap(current, iter.current);
        swap(bucket_index, iter.bucket_index);
        return *this;
    }

    //pre increment
    Hash_iterator & operator++() 
    {
        if(current == theMap->bucket[theMap->num_buckets-1].end())
            return *this;
        ++current;
        if(current == theMap->bucket[bucket_index].end())
        {
            ++bucket_index;
            while(bucket_index < theMap->num_buckets and theMap->bucket[bucket_index].size() == 0)
                ++bucket_index;
            if(bucket_index < theMap->num_buckets)
                current = theMap->bucket[bucket_index].begin(); 
            else
                current = theMap->bucket[theMap->num_buckets-1].end();
        }
        return *this;
    }

    //post increment which call pre increment
    Hash_iterator operator++(int)
    {
        Hash_iterator copy = *this;
        ++(*this);
        return copy;
    }

    //overload * operator to return current value
    pair<Key, Value> & operator*()
    {
        return *current;
    }

    //Overload -> operator for current to return values at current
    typename list<pair<Key,Value>>::iterator operator->()
    {
        return current;
    }   

    //Overload == operator to return bool if values are equal
    bool operator==(const Hash_iterator & rhs)
    {
        return current == rhs.current;
    }

    //Overload != operator to return bool if values are not equal
    bool operator!=(const Hash_iterator & rhs)
    {
        return !(*this == rhs);
    }    
friend class Unordered_map<Key,Value,Hash>;
}; 


#endif
