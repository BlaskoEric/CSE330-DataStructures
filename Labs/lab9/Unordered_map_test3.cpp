/*********************************************************************************
 * Eric Blasko
 * Unordered_map_test3.cpp
 * 03/14/2018
 * This program test the methods found in Unordered_map.h. Test for this program 
 * will include inserting, itterating, amd rehashing the map. Results will be 
 * printed to console to verify its results
 ********************************************************************************/
#include <iostream>

#include "Unordered_map.h"

using namespace std;

//hash function
template <typename Key>
class Another
{
public:
    unsigned operator()(const Key & k) const
    {
        return k;
    }
};

//Main function to test class Unordered_map.h
int main()
{
    Unordered_map<string, string, Hasher> h(7);

    h.insert(make_pair("Red", "123 Main"));
    h.insert(make_pair("Brown", "45 First"));
    h.insert(make_pair("Blue", "20 2nd St"));
    h["Jack"] = "500 E St";
    h["Jill"] = "400 Lakewood";
    h["Jake"] = "2 Sierra Madre";
    h["Green"] = "Mile";
    h["One more"] = "Something";
    h.print();

    Unordered_map<string, string>::iterator i;
    for (i = h.begin(); i != h.end(); i++)
        cout << "(" << i->first << ":" << i->second << ") ";
    cout << endl;

    h.rehash(11);
    cout << "\nAfter rehash(11)\n\n";
    h.print();

    for (i = h.begin(); i != h.end(); i++)
        cout << "(" << i->first << ":" << i->second << ") ";
    cout << endl;


    Unordered_map<unsigned, string, Another> k(5);

    k.insert(make_pair(13, "cookie"));
    k.insert(make_pair(12, "monster"));
    k.insert(make_pair(17, "eat"));
    k.insert(make_pair(25, "something"));
    k.insert(make_pair(10, "else"));

    cout << endl;
    k.print();

    Unordered_map<unsigned, string, Another>::iterator j;
    for (j = k.begin(); j != k.end(); j++)
        cout << "(" << j->first << ":" << j->second << ") ";
    cout << endl;

    k.rehash(7);
    cout << "\nAfter rehash(7)\n\n";
    k.print();

    for (j = k.begin(); j != k.end(); j++)
        cout << "(" << j->first << ":" << j->second << ") ";
    cout << endl;
}
