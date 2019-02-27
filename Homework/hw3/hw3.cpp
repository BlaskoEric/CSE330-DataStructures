/*****************************************************************************************************
 * Eric Blasko
 * hw3.cpp
 * 02/28/2018
 * This program finds the union and intersect of two sorted list. The list used are from the
 * standard library while the functions to find the union and intersect are provided above main.
 * Program will print the contents of both list, then print their union and intersect after
 ****************************************************************************************************/ 
#include <iostream>
#include <list>

using namespace std;

//This function uses const_iterators to go through both list. Each value is compared and pushed onto
//a temp list. If one list reaches its end, a second loop will finish pushing remaining values to temp
template <typename T>
list<T> getUnion(const list<T> & a, const list<T> & b)
{
    list<T> temp;
    typename list<T>::const_iterator i = a.begin();
    typename list<T>::const_iterator j = b.begin();

    //done until one iterator reachs the end. Continue makes sure condidtion is checked after each
    //if statement is completed
    while(i != a.end() && j != b.end())
    {
        if(*i == *j)
        {
            temp.push_back(*i);
            i++;
            j++;
            continue;
        }
        if(*i < *j)
        {
            temp.push_back(*i);
            i++;
            continue;
        }
        if(*j < *i)
        {
            temp.push_back(*j);
            j++;
            continue;
        }
    }

    //if one iterator didnt reach end, finsh getting its values. Other will not loop as its at the end
    while(i != a.end())
    {
        temp.push_back(*i);
        i++;
    }
    while(j != b.end())
    {
        temp.push_back(*j);
        j++;
    }
    return temp;        
};

//The function loops using interators to find equal values in two list. Value that are equal are pushed
//onto a temp and returned at the end
template <typename T>
list<T> my_intersect(const list<T> & a, const list<T> & b)
{
    list<T> temp;
    typename list<T>::const_iterator i = a.begin();
    typename list<T>::const_iterator j = b.begin();

    while(i != a.end())
    {
        for(j = b.begin(); j != b.end(); j++)
        {
            if(*i == *j)
            {
                temp.push_back(*i);
                break;
            }
        }
        i++;
    }
    return temp;
};

//Main function. Will push values onto two list and print there values. my_union and my_intersect will
//run after and print there values
int main()
{
    list<int> L1;
    list<int> L2;
    list<int> myUnion;
    list<int> myIntersect;

    L1.push_back(15);
    L1.push_back(20);
    L1.push_back(25);
    L1.push_back(30);
    L1.push_back(35);
    L1.push_back(40);
    L1.push_back(45);
    L1.push_back(60);
    L1.push_back(65);
    L1.push_back(80);
    L1.push_back(85);
    L2.push_back(5);
    L2.push_back(10);
    L2.push_back(11);
    L2.push_back(25);
    L2.push_back(33);
    L2.push_back(40);

    L2.push_back(40);
    L2.push_back(80);
    L2.push_back(85);
    L2.push_back(99);
    L2.push_back(100);
    cout << "L1" << endl;
    for(list<int>::iterator it = L1.begin(); it != L1.end(); it++)
        cout << *it << " ";
    cout << endl;

    cout << "L2" << endl;
    for(list<int>::iterator it2 = L2.begin(); it2 != L2.end(); it2++)
        cout << *it2 << " ";
    cout << endl;

    myUnion = getUnion(L1,L2);

    cout << "Union" << endl;
    for(list<int>::iterator it3 = myUnion.begin(); it3 != myUnion.end(); it3++)
        cout << *it3 << " ";
    cout << endl; 

    myIntersect = my_intersect(L1,L2);

    cout << "Intersect" << endl;
    for(list<int>::iterator it4 = myIntersect.begin(); it4 != myIntersect.end(); it4++)
        cout << *it4 << " ";
    cout << endl;
}
