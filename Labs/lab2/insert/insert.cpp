/****************************************************************************
 * Eric Blasko
 * insert.cpp
 * 01/24/2018
 * This program creates a vector of random integers of size n, which is based
 * off of users input.The vector is then sorted and printed to console
 ***************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

void insert(vector<int>&);

//Main function creates a vector of random integers, sorts it, and prints it
int main()
{
    srand(time(0));
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> v(n);

    for(int i = 0; i < n; i++)
    {
        v[i] = rand() % 1000000;
    }

    insert(v);

    for(int i = 0; i < n; i++)
    {
        cout << v[i] << endl;
    }
}

//This function sorts a vector that was passed by reference
void insert(vector<int>& v)
{
    int elem, j, i;
    for(i = 1; i < v.size(); i++)
    {
        elem = v[i];
        for(j = i-1; (j >= 0) && (elem < v[j]); j--)
        {
            v[j+1] = v[j];
        }
        v[j+1] = elem;
    }
}
